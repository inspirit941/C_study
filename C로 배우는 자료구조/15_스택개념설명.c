/*
스택은 일종의 리스트. 단 데이터의 삽입과 삭제가 한쪽 끝에서만 이루어짐.
LIFO (Last-in, first-out)
삽입, 삭제가 일어나는 쪽을 스택의 top이라고 부른다.

스택이 지원하는 연산
push: 새 원소를 삽입
pop: 스택의 top에 있는 원소를 스택에서 제거하고 반환
peek: 스택 top 원소를 제거하지 않고 반환
empty: 스택이 비었는지를 검사.

스택 응용 예시: 괄호 검사 문제
어떤 수식이 있다고 할때
여는 괄호는 별도의 스택에 push
닫는 괄호가 나오면 아까 저장한 스택에서 pop한 후, 두 괄호가 같은 유형이어야 한다.
마지막에 스택에 남는 괄호가 없어야 한다.

*/
// paren _checker 파일

#include <stdio.h>
#include <string.h>
// #include "bits/stl_stack.h"
// 문자를 저장하는 스택이 stack.c파일에 구현되어 있다고 가정한다.

#define MAX_LENGTH 100

char open[] = "([{";
char closed[] = ")]}";

int is_balanced(char *expr);
int is_open(char ch);
int is_close(char ch);

int main(){
    char expr[MAX_LENGTH];
    scanf("%s",expr); //입력은 괄호만으로 이루어진 하나의 문자열이다
    if (is_balanced(expr)){
        printf("%s : balanced.\n",expr);
    }else{
        printf("%s : unbalanced.\n",expr);
    }
}

int is_balanced(char *expr){
    int balanced = 1;
    int index = 0;
    while (balanced && index<strlen(expr)){
        char ch = expr[index];
        if(is_open(ch)>-1){ // 여는 괄호인지 묻는 것
            push(ch);
        }
        else if(is_closed(ch)>-1){ // 닫는 괄호인지 묻는 것
            if(is_empty()){ // pop이 가능한지 검사한다
                balanced=0;// stack이 비었다면, 열린 괄호가 닫히지 않았다는 뜻
                break;
            }
            char top_ch = pop();
            if(is_open(top_ch)!= is_close(ch)){//괄호순서를 동일하게 했기 때문에, 같은 괄호라면 숫자가 일치함
                 balanced=0; //같은 유형의 괄호인지 검사한다.
                // 다를 경우 balanced = 0;
                // balanced가 0이면 while문을 빠져나온다
            }
        }
        index++;
    }
    return (balanced==1 && is_empty()==1); //스택이 비어 있고, 모든 값이 일치할 때에만 1을 return
}

int is_closed(char ch){
    for (int i=0;i<strlen(closed);i++){
        if (open[i]==ch){
            return i;
        }
    }
    return -1;
}
int is_open(char ch){
    for (int i=0;i<strlen(open);i++){
        if (open[i]==ch){
            return i;
        }
    }
    return -1;
}