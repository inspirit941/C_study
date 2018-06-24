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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "15_2_stackADT.h"


///---------------------------------------------------------------------------------//
// undefined reference 오류 대체 뭐냐 ㅡㅡ

typedef int Item;
// 이 문장의 의미. -> 정수를 저장하는 stack.
// push나 pop의 return 타입이 int인 경우가 많다.
// 혹시 나중에 이 코드를 가져와서 '실수를 저장하는 스택'과 같이 재사용하려 할 때 편하게 하려고
// int를 Item이란 이름으로 rename을 하고,
// 저장 형식을 Item으로 했음.
// 나중에 int를 float으로 변형할 때에는 Item의 속성만 바꾸면 된다.

// 즉 코드의 재사용과 관련된 노하우

typedef struct stack_type *Stack;
// struct의 데이터 저장형식을 포인터 타입으로 진행.
// struct의 stack type이라는 구조체를 포인터변수로 저장.
Stack create();
void destroy(Stack s);
void make_empty(Stack s);
int is_empty(Stack s);
void push(Stack s, Item i);
Item pop(Stack s);
Item peek(Stack s);
//////////////////////////////////////////////////////////////////////////////////////////////


static char OPERATORS[] = "+-*/";
static int PRECEDENCE[] = {1,1,2,2};
// 연산자 +-*/ 의 우선순위를 순서대로 1,1,2,2로 지정했다. 큰 값은 높은 우선순위를 의미함
Stack operator_stack; //연산자의 저장.
// 사실 이전에 만든 postfix expression은 operand_stack를 썼는데,
// 이 스택은 정수를 받아 저장하는 스택이었다.
// 지금 만든 스택은 char를 받아 저장하는 stack임. 그래서 원래 stack에서 받는 데이터의 타입이 char여야 한다.
// 하지만 C언어는 정수와 char 사이의 호환성을 어느 정도 제공해 주기에 지금은 그냥 진행해도 문제가 없다고 함

// 해당 문자가 operator인지 아닌지, 우선순위는 누가 더 큰지 구현해야 함
char *convert(char *infix);
int is_operator(char ch);
int precedence(char op);
void handle_exception(const char *err_msg);
char *process_op(char op, char *pos);

int main(){
    return 0;
}

char *convert(char *infix){ //infix는 일반적인 형태의 식을 받는다
    operator_stack = create();

    char *postfix = (char *)malloc(strlen(infix)+1);
    //infix를 postfix로 변환할 때 저장할 문자열이 필요함. 
    //그걸 선언하는 게 *postfix. 동적할당 메모리의 시작주소.
    char *pos = postfix;
    // postfix에 현재 어디까지 메모리가 사용되었는지 위치를 표시할 포인터가 pos이다.
    // 처음 선언할 때는 시작값이 같을 것이다. 데이터 쌓이면서 pos가 변할 것.

    char *token = strtok(infix, " ");
    while (token!=NULL){
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
            // pos가 맨 마지막 위치를 유지하도록 만든 거라는데
            // 뭔소린지 모르겠다
        } else{
            handle_exception("Error");
        }
        token = strtok(NULL," ");
    }
    while(is_empty(operator_stack)==1){
        char op = (char)pop(operator_stack);
        sprintf(pos, "%c ",op);
        pos+=2;
    }
    *pos = '\0'; //주소 맨 마지막 값에 \0을 넣어 문자열의 끝을 표시한다.
    return postfix;
    // postfix에 저장된 최종 배열을 불러온다.
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

char *process_op(char op, char *pos){
    if (is_empty(operator_stack)==0){
        push(operator_stack,op);
    }else{
        char top_op = peek(operator_stack); 
        //현재 operator의 값을 top_op에 넣는다
        if(precedence(op)>precedence(top_op)){
            //현재 op의 값이 top op보다 크면 그대로 진행한다.
            // 3+5*2의 경우, 3 5 2 * + 형태여야 하는데
            // 먼저 +가 operator_stack에 들어간 다음에 *가 등장.
            // *의 우선순위가 +보다 높으니까, 그대로 stack 위에 push된다.
            push(operator_stack,op);
        }else{
            while(is_empty(operator_stack)==1 && precedence(op)<precedence(top_op)){
                // 5*3+2 의 경우, 5 3 * 2 + 형태여야 한다.
                // 먼저 *가 들어가고 다음에 +가 operator_stack에 등장하는데
                // 문제는, 먼저 *가 pop된 다음에 +가 나와야 한다
                // 이 경우 top_op의 우선순위가 2, op의 우선순위가 1이므로
                //while문 조건에 해당한다.
                // 이런 문제를 해결하는 함수
                pop(operator_stack);
                //어차피 pop한 결과물이 top_op와 동일하므로 굳이 두 번 저장하지 않는다.
                sprintf(pos,"%c ",top_op);
                //sprintf로 pos배열에 top_op 연산자를 넣는다. 5 3 *를 해준단 소리
                pos+=2; // 연산자+공백이므로 +2
                if (is_empty(operator_stack)==1){
                    top_op = (char)peek(operator_stack);
                    // 스택이 아직 비어있지 않다면
                    // 다시 top_op를 설정한 다음 위 while문의 처음부터 돌아간다
                }
            }
            push(operator_stack,op);
            // 우선순위 작업이 다 끝났으면 그제서야 operator를 stack에 넣는다.
        }
    }
    return pos; 
    // if에서 empty상태에 새 연산자가 추가됐다는 건,
    // operator_stack에 저장은 하되, 연산자를 postfix에 아직 넣지 않는단 의미다.
    // 5+2를 postfix로 바꾸면  5 2 +이니까. +가 나왔다면 아직 postfix에서는 나올 차례 아닌 거지
    // 그래서 return pos 그대로 진행한다. if문을 통과하면.
}




///////////////////////////////////////////////////////////////////////////////

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


// int main(){
//     Stack s1 = create();
    
//     push(s1,12);
//     // push(s2,9);
//     printf("%d\n",pop(s1));
//     Stack s2 = create();
//     push(s2,3);
//     printf("%d\n",pop(s2));
//     return 0;
//     // 실행하면 오류가 뜨는데, 왜인지 모르겠다.
// }

// 어느 커서에서 실행하냐에 따라 오류가 나기도 하고 안나기도 한다?
// main 맨 끝에서는 오류 안 나고, push(s2,3)에 커서 대면 오류나고..