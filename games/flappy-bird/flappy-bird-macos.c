// clang -std=c11 -Wall -Wextra -pedantic bird_macos.c -o bird_macos
#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <termios.h>
#include <sys/select.h>
#include <string.h>

#define SCREEN_W 80
#define SCREEN_H 24
#define PIPE_WIDTH 3
#define PIPE_COUNT 5
#define FRAME_USEC 100000

static int Grade = 1;
static int Score = 0;
static int Max_blank = 9;
static int Distance = 18;

typedef struct Bird {
    int x, y;
    int condition;
} Bird;

typedef struct Bg {
    int x, y;
    int l_blank;
    int reward[9];
    struct Bg *pri;
    struct Bg *next;
} Bg;

static Bird *bird = NULL;
static Bg *bg1 = NULL;
static struct termios orig_termios;
static int term_initialized = 0;

static void disable_raw_mode(void) {
    if (term_initialized) {
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
        term_initialized = 0;
    }
    printf("\033[?25h\033[0m\n");
    fflush(stdout);
}

static void enable_raw_mode(void) {
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) {
        perror("tcgetattr");
        exit(EXIT_FAILURE);
    }
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    raw.c_iflag &= ~(IXON | ICRNL);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 0;
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
        perror("tcsetattr");
        exit(EXIT_FAILURE);
    }
    term_initialized = 1;
    atexit(disable_raw_mode);
}

static int kbhit(void) {
    fd_set set;
    struct timeval tv = {0, 0};
    FD_ZERO(&set);
    FD_SET(STDIN_FILENO, &set);
    return select(STDIN_FILENO + 1, &set, NULL, NULL, &tv) > 0;
}

static int read_key(void) {
    unsigned char c;
    if (read(STDIN_FILENO, &c, 1) == 1) {
        return c;
    }
    return -1;
}

static void clear_screen(void) {
    printf("\033[2J\033[H");
}

static void create_bird(void) {
    bird->x = 41;
    bird->y = 10;
    bird->condition = 0;
}

static void create_bg(void) {
    Bg *bg2 = (Bg *)malloc(sizeof(Bg));
    if (!bg2) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    bg1->x = 90;
    bg1->y = 8;
    bg2->x = bg1->x + Distance;
    bg2->y = 9;
    bg1->l_blank = Max_blank - Grade;
    bg2->l_blank = Max_blank - Grade;
    bg1->next = bg2;
    bg1->pri = bg2;
    bg2->next = bg1;
    bg2->pri = bg1;
}

static void insert_bg(Bg *p) {
    int temp = rand();
    Bg *bgs = (Bg *)malloc(sizeof(Bg));
    if (!bgs) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    bgs->x = p->pri->x + Distance;
    bgs->l_blank = Max_blank - Grade;
    if (temp % 2 == 0) {
        if ((temp % 4 + p->pri->y + Max_blank - Grade) < 21)
            bgs->y = p->pri->y + temp % 4;
        else
            bgs->y = p->pri->y;
    } else {
        if ((p->pri->y - temp % 4) > 2)
            bgs->y = p->pri->y - temp % 4;
        else
            bgs->y = p->pri->y;
    }
    bgs->pri = p->pri;
    bgs->next = p;
    p->pri->next = bgs;
    p->pri = bgs;
}

static void check_bg(Bg *q) {
    Bg *p = q;
    for (int i = 0; i < PIPE_COUNT; ++i) {
        if (p->x > -4) {
            p = p->next;
        } else {
            int temp = rand();
            if (temp % 2 == 0) {
                if ((temp % 4 + p->y + Max_blank - Grade) < 21)
                    p->y = p->y + temp % 4;
                p->x = p->pri->x + Distance;
                p->l_blank = Max_blank - Grade;
            } else {
                if ((p->y - temp % 4) > 2)
                    p->y = p->y - temp % 4;
                p->x = p->pri->x + Distance;
                p->l_blank = Max_blank - Grade;
            }
        }
    }
}

static void loop_bg(Bg *q) {
    Bg *p = q;
    for (int i = 0; i < PIPE_COUNT; ++i) {
        p->x = p->x - 1;
        p = p->next;
        if (bird->x == p->x) {
            Score += 1;
            if (Score % 4 == 0 && Grade < 4)
                Grade++;
        }
    }
}

static int check_collision(Bg *q) {
    Bg *p = q;
    for (int i = 0; i < PIPE_COUNT; ++i) {
        if (bird->y > 23 || bird->y < 2)
            return 1;
        if (bird->x == p->x && bird->y <= p->y)
            return 1;
        if ((bird->x == p->x || bird->x == p->x + 1 || bird->x == p->x + 2) && bird->y == p->y)
            return 1;
        if (bird->x == p->x && bird->y > p->y + p->l_blank)
            return 1;
        if ((bird->x == p->x || bird->x == p->x + 1 || bird->x == p->x + 2) && bird->y == p->y + p->l_blank)
            return 1;
        p = p->next;
    }
    return 0;
}

static void draw_frame(Bg *q) {
    char screen[SCREEN_H][SCREEN_W + 1];
    for (int y = 0; y < SCREEN_H; ++y) {
        for (int x = 0; x < SCREEN_W; ++x) {
            screen[y][x] = ' ';
        }
        screen[y][SCREEN_W] = '\0';
    }

    screen[0][0] = '+';
    screen[0][SCREEN_W - 1] = '+';
    screen[SCREEN_H - 1][0] = '+';
    screen[SCREEN_H - 1][SCREEN_W - 1] = '+';
    for (int x = 1; x < SCREEN_W - 1; ++x) {
        screen[0][x] = '-';
        screen[SCREEN_H - 1][x] = '-';
    }
    for (int y = 1; y < SCREEN_H - 1; ++y) {
        screen[y][0] = '|';
        screen[y][SCREEN_W - 1] = '|';
    }

    for (int x = 1; x < SCREEN_W - 1; ++x) {
        screen[22][x] = '=';
    }

    Bg *p = q;
    for (int i = 0; i < PIPE_COUNT; ++i) {
        if (p->x >= 1 && p->x <= SCREEN_W - 2) {
            for (int col = 0; col < PIPE_WIDTH; ++col) {
                int sx = p->x - 1 + col;
                if (sx < 1 || sx >= SCREEN_W - 1) continue;
                for (int y = 1; y < p->y - 1; ++y) {
                    screen[y][sx] = '#';
                }
                if (p->y - 1 >= 1 && p->y - 1 < SCREEN_H - 1) screen[p->y - 1][sx] = '#';
                int lower = p->y + p->l_blank - 1;
                if (lower >= 1 && lower < SCREEN_H - 1) screen[lower][sx] = '#';
                for (int y = lower + 1; y < 22; ++y) {
                    screen[y][sx] = '#';
                }
            }
        }
        p = p->next;
    }

    if (bird->y >= 1 && bird->y < SCREEN_H - 1 && bird->x >= 1 && bird->x < SCREEN_W - 1) {
        screen[bird->y - 1][bird->x - 1] = '@';
    }

    char score_line[SCREEN_W + 1];
    snprintf(score_line, sizeof(score_line), "Score:%d  Grade:%d  Control: W / UpArrow / Space  Quit: Q", Score, Grade);
    for (int i = 0; score_line[i] != '\0' && i < SCREEN_W - 2; ++i) {
        screen[1][i + 1] = score_line[i];
    }

    printf("\033[H");
    for (int y = 0; y < SCREEN_H; ++y) {
        printf("%s\n", screen[y]);
    }
    fflush(stdout);
}

static void print_intro(void) {
    clear_screen();
    printf("========================================\n");
    printf("         C language - Flappy Bird       \n");
    printf("========================================\n");
    printf("1. Press W / Space / UpArrow to jump\n");
    printf("2. The higher the score, the harder it gets\n");
    printf("3. Press Q to quit\n\n");
    printf("Press Enter to start...");
    fflush(stdout);

    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main(void) {
    srand((unsigned int)time(NULL));

    bird = (Bird *)malloc(sizeof(Bird));
    bg1 = (Bg *)malloc(sizeof(Bg));
    if (!bird || !bg1) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    print_intro();
    enable_raw_mode();
    printf("\033[?25l");
    clear_screen();

    create_bg();
    insert_bg(bg1);
    insert_bg(bg1);
    insert_bg(bg1);
    create_bird();

    while (1) {
        if (check_collision(bg1))
            break;

        check_bg(bg1);
        draw_frame(bg1);
        loop_bg(bg1);
        bird->y = bird->y + 1;

        while (kbhit()) {
            int ch = read_key();
            if (ch == 'q' || ch == 'Q') {
                disable_raw_mode();
                return 0;
            }
            if (ch == 'w' || ch == 'W' || ch == ' ') {
                bird->y -= 4;
            } else if (ch == 27) {
                int ch2 = read_key();
                int ch3 = read_key();
                if (ch2 == '[' && ch3 == 'A') {
                    bird->y -= 4;
                }
            }
        }

        struct timespec ts = {0, FRAME_USEC * 1000L};
        while (nanosleep(&ts, &ts) == -1 && errno == EINTR) {}
    }

    draw_frame(bg1);
    printf("\033[%d;1H", SCREEN_H + 1);
    printf("You Lost! Final Score: %d\n", Score);
    fflush(stdout);
    return 0;
}
