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
/*
switch문이란, 조건문의 일종인데, 
여러 개의 if~else 문을 대신하여 간결하게 작성할 때 사용하는 것입니다.
if~else 문이 중첩되어 있으면 가독성이 떨어지기 때문에 스위치문이 필요합니다.

그러나 switch문 다음의 괄호()에는 "i <= 0" 이런 식의 판단문이 들어갈 수는 없고, 
정수형이나 문자형(char)의 숫자만 들어갈 수 있는 제약이 있습니다. 
double 등의 실수는 안되고 
error C2450: switch expression of type 'double' is illegal 이런 에러가 납니다.

스위치문에서 주의해야 할 점은 각 case문 끝에 break; 를 꼭 붙여야 한다는 것입니다. 
break; 가 없으면, 그 아래쪽의 case문들까지 모두 실행되어 버립니다.
break;를 만날 때까지 멈추지 않고 계속 실행됩니다.

의도적으로 break;를 생략한 경우가 아니라, 
실수로 누락했을 때는 소스가 폭주하여 위험한 에러가 발생할 수 있습니다. 
따라서 우선 무조건 break;를 붙여 놓고 소스의 흐름을 검토하는 것이 안전합니다.

default 라는 것은, 위의 case문들 중에서 어느 것도 해당되지 않을 때 실행할 코드입니다. 
필요하지 않다면 default문이 없어도 됩니다.
*/

void handle_exception(const char *err_msg){
    printf("%s\n",err_msg);
    exit(1);
}

// infix 형태를 postfix expression 형태로 변경하기.
// postfix expression - infix의 '괄호'가 없다
// 연산자는 등장한 순서대로 계산된다.
// infix나 prefix나, 피연산자의 순서는 동일하다.
// postfix는 연산자의 순서가 가장 마지막에 등장한다.
// infix에서 가장 먼저 계산될 연산자(괄호 안에 들어있는 것)는 postfix에서 가장 먼저 등장한다.
// 피연산자는 나오는 순서대로 출력, 연산자는 infix에서 계산되어야 하는 순서대로 등장한다.

// 후위표기식으로 변환 1 - 괄호 없는 경우
// 피연산자는 그대로 output에 넣는다.
// 2 - 10 / 5 * 6 + 4의 경우
// 2는 (피연산자는) 그대로 output으로.
// -는 바로 출력할 수 없으므로 stack에 보관
// 10은 출력
// /도, 나눗셈에 필요한 피연산자가 나오지 않았으므로 /를 push에 넣는다.
// 다음 5는 출력
// 곱하기 연산자도 stack에 push되어야 한다.
// but 그전에, 나누기와 곱하기는 동일한 우선순위를 갖고 나눗셈에 적용되는 피연산자가 전부 출력되어 있으믈
// 나누기는 pop으로 출력된다. 그 후에야 곱셈연산자가 push된다.
// 6 피연산자 push
// 그 다음 덧셈 연산자가 나오는데, stack에 push된 뺄셈 연산자가 우선순위에 있다. 
//(동일한 우선순위라면 먼저 나온 게 먼저 계산되므로)

//따라서 먼저 pop으로 -연산자를 호출한 다음, + 연산자를 stack에 push한다
// 그 다음 output은 4이다.
// 더 이상 수식이 없으니, stack에 남은 연산자를 output 마지막에 붙인다.

// 2 10 5 / 6 * - 4 + 형태의 output을 얻게 된다.

/*
infix 표기식을 순서대로 tokenize하면서
피연산자는 즉시 출력
모든 연산자는 일단 스택에 push
단, 이때 스택 내에 우선순위가 자신보다 더 높은 연산자가 있으면 pop하여 출력한 후 push한다
수식이 종료되면 스택에 있는 모든 연산자를 pop하여 출력한다.
*/
