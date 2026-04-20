#include "stdio.h"
#include "stdlib.h"
#define MAXSIZE 200
#define END '\n'

#define OPERATOR 1
#define OPERAND  0
#define NUMBER 0
#define ALPHA_CHAR 2
#define OTHER_CHAR 3

#define POP 0
#define	GET 1

#define RADIAN_MODE 0
#define DECIAML_MODE 1

#define the_stack_is_null 1
#define the_stack_is_full 2
#define found_some_illegal_words_or_undefined_commands 3
#define found_some_illegal_characters 4
#define	the_real_number_is_illegal 5
#define the_breckets_do_not_match	6
#define the_operator_between_the_breckets_is_missing 7
#define the_divisor_can_not_be_zero 8
#define the_operand_in_tangent_function_must_not_be_integer_multiple_of_90_or_half_pi 9
#define the_antilogarithm_must_be_greater_than_zero 10
#define the_operator_before_the_percent_sign_must_be_a_number 11
#define the_string_exceeds_the_length_of_the_provisions 12
#define missing_a_operator_before_the_unary_operator 13
#define missing_a_operand_before_the_binary_operator 14
#define missing_a_operand_before_the_right_brecket 15
#define missing_a_operator_after_the_right_brecket 16
#define missing_a_operator_before_the_left_brecket 17
#define the_expression_is_null 18
#define the_element_is_null_between_the_match_beckets 19
#define set_successfully_explicit 20
#define set_successfully_implicit 21
#define undefined_error 22

extern char operators[MAXSIZE/10];   //运算符栈
extern double operands[MAXSIZE/10];  //操作数栈
extern short top[2];        //运算符栈顶标识
void push(double,short); //进栈
double pop_or_get(short,short); //取出元素 出栈
void ini_stack();  //初始化栈

extern char unknownstring[MAXSIZE+2];
void input();
int type_char(char,bool);


double calculate();

struct run_event
{
	short incident;
	bool is_write_protected;
};
typedef struct run_event RUN_EVENT;
extern RUN_EVENT event_box;
void massage(short);
void event_report(short);
void ini_incident();


void logo();