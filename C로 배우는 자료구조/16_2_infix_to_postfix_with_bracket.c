/* 추가될 규칙
1. 여는 괄호는 무조건 스택에 push한다. 
(괄호가 닫힐 때까지, 괄호 안의 수식이 절대적인 우선순위를 갖기 때문)
이 때, 스택 내의 어떤 연산자도 pop하지 않는다.
2. 어떤 연산자를 스택에 push할 때, 스택의 top에 여는 괄호가 있으면
아무도 pop하지 않고 그냥 push한다.
3. 입력에 닫는 괄호가 나오면 스택에서 여는 괄호가 나올 때까지 pop하여 출력.
닫는 괄호는 스택에 push하지 않는다.
괄호는 제 역할이 끝나면 출력창에는 나오지 않도록 한다. (버린다)

*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "15_2_stackADT.h"


static char OPERATORS[] = "+-*/()"; //괄호 추가
static int PRECEDENCE[] = {1,1,2,2,-1,-1}; //여는 괄호와 닫는 괄호 우선순위는 -1
// -1로 해두면 여는 괄호냐 아니냐를 검사할 필요가 없어지므로, 좀 더 간결해진다

char *convert(char *infix);
char *process_op(char op, char *pos);
int is_operator(char ch);
int precedence(char op);
void handle_exception(const char *err_msg);
int eval(char *expr);
int eval_op(char op);
int read_line(FILE *fp, char str[], int n);

typedef int Item;

typedef struct stack_type *Stack;

Stack operator_stack; 
Stack operand_stack;

char *convert(char *infix){
    operator_stack = create();
    char *postfix = (char *)malloc(strlen(infix)+1);
    char *pos = postfix;

    char *token = strtok(infix, " ");
    while (token != NULL){
        if (token[0]>='0'&& token[0]<='9'){ // 숫자가 들어온 경우
            sprintf(pos,"%s ",token); 
    // pos가 가리키는 주소 위치에, "%s "라는 형식으로 token값을 넣는다는 뜻.
            //sprintf를 이용해 문자열에 append한다
            // sprintf의 의미? 
            // char * 로 선언된 변수 안에 
            // 입력된 내용이 문자열로써 담기게 되는 것.
            // 다시말해 int형의 정수를 쉽게 char *로 전환할 수 있다.
            pos += (strlen(token)+1);
            // %s 뒤의 공백도 반영해야 하므로 +1
        }else if(is_operator(token[0])>-1){ //operator임을 의미
            pos = process_op(token[0],pos);
            // process_op 함수가 연산자를 append한 후, (pos에 집어넣어야 하니까)
            // 문자열 끝 주소를 반환한다.
        } else{
            handle_exception("Error");
        }
        token = strtok(NULL," ");
    }
    while(is_empty(operator_stack)==1){ //operator 스택이 아직 남아있는 경우
        char op = (char)pop(operator_stack);
        if (op == '('){ //스택에 여는 괄호가 남아있어선 안 된다.
    // 괄호가 열렸는데 닫히지 않았단 뜻이므로. infix자체가 잘못되었단 의미다.
            handle_exception("Unmatched parenthesis.");
        }
        sprintf(pos, "%c ",op);
        pos += 2;
    }
    *pos = '\0';
    return postfix;
}

char *process_op(char op, char *pos){
    if (is_empty(operator_stack)==0|| op=='('){ 
        // 스택이 비어 있거나 여는 괄호이면 그대로 push한다
        push(operator_stack,op);
    }else{
        char top_op = peek(operator_stack);
        if (precedence(op)>precedence(top_op)){ 
        //op의 우선순위가 스택 top_op보다 높으면
        // 그대로 넣는다
        // 여는 괄호일 경우 우선순위가 -1이 되므로, 여는 괄호 뒤에 나온 모든 연산자는 여기 들어간다
            push(operator_stack,op);
        }else{
            while(is_empty(operator_stack)&& precedence(op)<=precedence(top_op)){
    // op의 우선순위가 top_op보다 낮다
    // = * 다음에 +가 들어온다 (연산의 우선순위는 *가 먼저 pop돼야 하는데)
    // 그리고 op 닫는 괄호라면 우선순위가 -1이므로 반드시 이 while문에 들어온다
                pop(operator_stack);
                if (top_op == '('){
                    break;
                }
                sprintf(pos, "%c ",top_op);
                pos+=2;
                if (is_empty(operator_stack)==1){ // 아직 operator_stack에 값이 남아 있다면
                // 남은 값을 top_op에 다시 저장하고 while문을 돈다
                    top_op = (char)peek(operator_stack);
                }
            }
            if(op!=')'){
                push(operator_stack,op);
            }
        }
    }
    return pos;
}

int is_operator(char ch){
    for (int i=0;i<strlen(OPERATORS);i++){
        if (OPERATORS[i]==ch){
            return i;
        }
    }
    return -1;
}
int precedence(char op){
    return PRECEDENCE[is_operator(op)];
} // 연산자를 받아 우선순위를 반환하는 함수.
// precedence(op1) > precedence(op2)와 같은 식으로
void handle_exception(const char *err_msg){
    printf("%s\n",err_msg);
    exit(1);
}


#define MAX_LENGTH 100
int main(){
    char infix[MAX_LENGTH];
    read_line(stdin, infix, MAX_LENGTH); //infix expression에 공백문자가 포함되어 있으므로 scanf는 불가능하다.

    printf("%s : = ",infix);
    char *postfix = convert(infix);
    printf("%d\n",eval(postfix));
}

// 미흡한 점 - 연산자가 양의 정수만 허용된다. 음수나 실수로 확장 필요
// -> 2/3 하면 0이 나옴.
// 모든 토큰이 공백문자로 구분되어 있어야 함 (2+3은 인식 못하고 2 + 3은 인식)
// 일진(unary) 연산자의 처리 - (-2)같은 것 (-2를 빼기 = +2인거)
// right associativity를 갖는 연산자의 처리 -> 2^3^4 -> 우선순위가 동일한 연산자가 연속해 나올 때 어떻게 할 건가.
// ex) 2-3-4 같은 경우 보통은 left associativity다. 왼쪽부터 순서대로 계산함.
// right 연산자-> 지수연산의 경우가 보통 해당.
// 2^3^4 는 2^3을 먼저 하느냐, 3^4를 먼저 하느냐에 따라 값이 다른데
// 지수의 경우 3^4를 먼저 하고, 그 다음에 2^.. 를 계산한다.

// 후위표기식으로 변환하는 일과 후의표기식을 계산하는 일을 하나로 합치는 문제.
//(두 개의 작업을 굳이 구분할 필요가 없음)



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//16_스택응용_postfix_expression.c의 일부



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
////////////////////////////////////////////////////////////////////////////////////////////
//14_2_string_tools.c의 read_line

int read_line(FILE *fp, char str[], int n){
// main.cpp에서 이 함수를 써야 하니까 헤더에도 선언해준다.
    int ch, i = 0;
    while((ch=fgetc(fp))!='\n' && ch != EOF){
        if (i<n-1){
            str[i++]=ch;
        }
    }
    str[i] = '\0';
    return i;
}










///////////////////////////////////////////////////////////////////////////////////

// stackADT.c 파일 내용들.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "15_2_stackADT.h"

#define INIT_CAPACITY 100

struct stack_type{
    Item *contents; //배열 (정수형 배열)
    int top;
    int size; //배열의 크기 (동적메모리 할당할 때 필요한)
};

static void terminate(const char *message){ //예외상황 발생 시 메세지 보내고 종료
    printf("%s\n",message);
    exit(1);
}
// 파일 내부에서만 유효한 함수를 말하는 듯. static.
// 다른 함수가 stackADT를 호출해 쓴다고 해도 terminate에는 접근이 불가능하다.
// 같은 이름을 가진 함수를 파일마다 만들 수 있어서 유용하다고 함.

Stack create(){ // 스택 만들고 포인터 return
    Stack s = (Stack)malloc(sizeof(Stack));
    // Struct stack_type의 포인터를 stack으로 정의했기 때문에
    // malloc으로 할당받을 때 굳이 포인터로 받지 않는다고 하는데
    //근데 왜 오류가 나지
    if (s==NULL){
        printf("in create\n");
        terminate("Error in create: stack could not be created.\n");
    }
    s->contents = (Item *)malloc(INIT_CAPACITY * sizeof(Item));
    // contents 배열을 동적메모리할당으로 생성.
    if (s->contents == NULL){
        free(s);
        // printf("contetn is null\n");
        terminate("Error in create: stack could not be created.\n");
    }
    s->top = -1;
    s->size = INIT_CAPACITY;
    return s;
}
void destroy(Stack s){
    free(s->contents);
    free(s);
}

void make_empty(Stack s){
    s->top = -1;
    // 완전히 지우는 게 아니고, 새로 데이터를 넣기 위해 초기화하는 것.
}
int is_empty(Stack s){
    if(s->top == -1){
        return 0;
    }else{
        return 1;
    }
    
}

void push(Stack s, Item i){
    // if (is_full(s)){
    //     reallocate(s);
    // }
    s->top++;
    s->contents[s->top]=i;
}
Item pop(Stack s){
    if (is_empty(s)==0){
        printf("in pop\n");
        terminate("Error in create: stack could not be created.\n");
    }
    s->top--;
    return s->contents[s->top+1];
}   

Item peek(Stack s){
    if (is_empty(s)==0){
        printf("in peek\n");
        terminate("Error in create: stack could not be created.\n");
    }
    return s->contents[s->top];
}

void reallocate(Stack s){
    Item *tmp = (Item *)malloc(2*s->size*sizeof(Item));
    if(tmp ==NULL){
        terminate("Error in create: stack could not be created.\n");
    }
    for (int i=0;i<s->size;i++){
        tmp[i] = s->contents[i];
    }
    free(s->contents);
    s->contents=tmp;
    s->size*=2;
}
////////////////////////////////////////////////////////////////////////////////////