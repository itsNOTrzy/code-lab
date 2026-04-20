#include <stdio> 
#include <stdlib> 

int sudoku[81] ; // 數獨題目陣列 
int tempNum[81] ; // 上一次填數位置 
int tempSp= 0 ; // 上一次填數位置指標 
int startH[81] ; // 列位置的起點 
int startV[81] ; // 行位置的起點 
int startB[81] ; // 九宮格位置的起點 
int addH[9] ; // 列位置的加值 
int addV[9] ; // 行位置的加值 
int addB[9] ; // 九宮格位置的加值 

int main(int argc, char *argv[]) { 
int j ; 
if(argc>1) for(j=0; j<81; j++) sudoku[j]= argv[1][j]-'0' ; 
else exit(0) ; 
printf( "------------------\n"); 
printSudoku(sudoku) ; 
init() ; // 參數設定 
tryAns() ; // 測試求解 
printf( "------------------\n"); 
printSudoku(sudoku) ; 
printf( "------------------\n"); 
} 

int init() { 
// 參數設定(設定這些參數之後，無論檢查行、列、九宮格都方便多了) 
int i ; 
for(i=0; i<81; i++) { 
startH[i]= i/9* 9 ; // 列位置的起點 
startV[i]= i% 9 ; // 行位置的起點 
startB[i]= ((i/9)/3)*27+ ((i%9)/3)*3 ; // 九宮格位置的起點 
} 
for(i=0; i<9; i++) { 
addH[i]= i ; // 列位置的加值 
addV[i]= i*9 ; // 行位置的加值 
addB[i]= (i/3)*9+ (i%3) ; // 九宮格位置的加值 
} 
} 

int printSudoku(int *prn) { 
// 印出數獨題目(陣列內容) 
int i ; 
for(i=0; i<81>9) { // 如果本位置的數字已大於 9 時則回到上一個位置繼續測試 
sudoku[sp]= 0 ; 
sp= pop() ; 
} else { 
if(check(sp)==0) { // 如果同行、列、九宮格都沒有相同的數字，則到下一個空白處繼續 
push(sp) ; // 當然，如果發現有相同的數字時，就需把原位置的數字加 1(所以本處什麼都不做) 
sp= getNextBlank(sp) ; 
} 
} 
} while(sp>=0 && sp<81) ; 
} 

int getNextBlank(int sp) { 
// 取得下一個空白的位置 
do { 
sp++ ; 
} while(sp<81>0) ; 
return(sp) ; 
} 

int check(int sp) { 
// 檢查同行、列、九宮格有沒有相同的數字，若有傳回 1 
int fg= 0 ; 
if(!fg) fg= check1(sp, startH[sp], addH) ; // 檢查同列有沒有相同的數字 
if(!fg) fg= check1(sp, startV[sp], addV) ; // 檢查同行有沒有相同的數字 
if(!fg) fg= check1(sp, startB[sp], addB) ; // 檢查同九宮格有沒有相同的數字 
return(fg) ; 
} 

int check1(int sp, int start, int *addnum) { 
// 檢查指定的行、列、九宮格有沒有相同的數字，若有傳回 1 
int fg= 0, i, sp1 ; 
for(i=0; i<9; i++) { 
sp1= start+ addnum[i] ; 
if(sp!=sp1 && sudoku[sp]==sudoku[sp1]) fg++ ; 
} 
return(fg) ; 
} 

int push(int sp) { 
// 將指定的位置放入堆疊中 
tempNum[tempSp++]= sp ; 
} 

int pop() { 
// 取出堆疊中的上一個位置 
if(tempSp<0) return(-1) ; 
else return(tempNum[--tempSp]) ; 
}