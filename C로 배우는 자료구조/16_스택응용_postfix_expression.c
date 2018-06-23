//일반적으로 사용하는 수식의 표기법을 중위(infix) 표기식이라고 부른다.
// 연산자가 피연산자 사이에 들어감
// 4*7 =28 | 4*(7+2) = 36 같은. 보통 우리가 쓰는 거

// postfix expression: 연산자가 피연산자 뒤에 나오는 것
// 4 7 * = 28 |2 3 4 + *  => 3+4를 먼저 하고, 결과값 7 *2 = 14가 정답이다.
// 연산자가 나오면, 연산자 바로 앞의 두 수를 연산한다.
// 후위표기식의 정의 = 후위표기식을 계산하는 알고리즘 만들기와 같은 의미이다.

// 연산자가 나오면, 바로 앞의 두 피연산자를 꺼내 계산한다.
// stack 구조?
// 피연산자들을 나오는 순서대로 stack에 push하면서 진행한다.
// 연산자가 나오면, pop을 두 번 해서 두 개의 피연산자를 꺼내 계산한다.
// 결과값을 다시 스택에 push한다.
// 피연산자가 나오면 스택에서 값을 두 개 꺼낸다

// 반복한다.
// 스택에서 먼저 꺼낸 값이 오른쪽 연산, 다음에 꺼낸 값이 왼쪽이다.UNICODE
// 4 7 * 일 경우, stack에서 꺼내는 순서는 7, 4 순이다.
// 따라서 4*7의 형태이려면 첫 번째로 꺼낸 값이 7이니까 연산자 오른쪽, 두 번째로 꺼낸 값이 연산자 왼쪽이다.

// 피연산자들은 전부 정수이다. (음이 아닌 정수라고 가정한다)
// 모든 연산을 마쳤을 때는 스택에 한 개의 값만 남아 있어야 한다.


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "15_2_stackADT.h"

static char OPERATORS[] = "+-*/"; // 프로그램이 지원하는 모든 연산자를 하나의 string에 모아두었다.
// 이 프로그램의 가정
// 모든 피연산자는 양의 정수다.
// 모든 피연산자와 연산자 사이에는 하나 이상의 공백이 있다.
Stack operand_stack; //피연산자를 저장할 스택

struct node{
    Item data;
    struct node *next;
};

struct stack_type{
    struct node *top;
};


int is_operator(char ch){
    for (int i=0;i<strlen(OPERATORS);i++){
        if (OPERATORS[i]==ch){
            return i;
        }
    }
    return -1;
}
int eval(char *expr){ // expr = 후위표기식.
    operand_stack = create(); //스택 만듬. 스택 객체의 주소를 저장하는 포인터값을 생성함.
    char *token = strtok(expr," "); // 모든 연산자와 피연산자는 공백으로 구분되어 있다고 가정한다.
    while (token != NULL){
        if (token[0]>='0' && token[0]<='9'){ // 피연산자일 경우. asci코드가 digit일 경우
            int value = atoi(token); // 정수값으로 변환해 주는 걸 의미함. 문자열로 표현된 걸 정수값으로 변환하는 함수가 atoi.
            push(operand_stack,value);
        }else if (is_operator(token[0])>-1){ // 연산자의 경우
            int result = eval_op(token[0]); //eval_op = 계산하고 결과값 반환
            push(operand_stack,result);
        }else{
            handle_exception("Syntax Error: invalid character encountered.");
        }
        token = strtok(NULL," ");
    }
    // 올바른 수식이라면, 스택에는 값이 하나만 있어야 한다
    if (is_empty(operand_stack)==0){
        handle_exception("Syntax error: stack empty in eval_op.");
    }
    int answer = pop(operand_stack);
    if(is_empty(operand_stack)==0){
        return answer;
    }else{
        handle_exception("Syntax error: stack should be empty.");
        return -1;
    }
}

int eval_op(char op){
    if (is_empty(operand_stack)==0){
        handle_exception("Syntax error: stack empty in eval_op.");
    } // 스택 값이 비어있다면, 뭔가 잘못되었다는 소리다.
    // 연산자가 나오기 전에는 최소 두 개 이상의 피연산자(숫자)가 있어야 하므로.
    int rhs = pop(operand_stack); //right hand side
    if(is_empty(operand_stack)==0){
        handle_exception("Syntax error: stack empty in eval_op.");
    }
    int lhs = pop(operand_stack); //left hand side
    int result = 0;
    switch (op){
        case '+': result = lhs+rhs;break;
        case '-': result = lhs-rhs;break;
        case '*': result = lhs*rhs;break;
        case '/': result = lhs/rhs;break;
    }
    return result;
}

void handle_exception(const char *err_msg){
    printf("%s\n",err_msg);
    exit(1);
}
