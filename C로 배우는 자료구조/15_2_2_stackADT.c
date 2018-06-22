// 연결리스트로 스택 구현하기

#include <stdio.h>
#include <stdlib.h>
#include "15_2_stackADT.h"

struct node{
    Item data;
    struct node *next;
};

struct stack_type{
    struct node *top;
}; // 연결리스트의 stack type
// 노드의 head를 지정하는 역할.

static void terminate(const char *message){
    printf("%s\n",message);
    exit(EXIT_FAILURE);
}

Stack create(){
    Stack s = malloc(sizeof(struct stack_type));
    if (s==NULL){
        terminate("error in create: stack could not be created");
    }
    s->top = NULL;
    return s;
}

void destroy(Stack s){
    make_empty(s);
    free(s);
    // 각각의 노드를 free시킨 이후 stack을 free시킨다.
}
void make_empty(Stack s){
    while(is_empty(s)==1){
        pop(s); 
        // pop 안에서 필요없는 노드를 free선언하는 것.
    }
}
int is_empty(Stack s){
    if (s->top == NULL){
        return 0;
    }else{
        return 1;
    }
}

void push(Stack s, Item i){
    struct node *new_node = malloc(sizeof(struct node));
    if (new_node ==NULL){
        terminate("Error in push. stack is full.\n");
    }
    new_node->data = i;
    new_node->next = s->top;
    s->top = new_node;
    // 맨 앞에 새 노드 삽입.
}
Item pop(Stack s){
    struct node *old_top;
    Item i;
    if (is_empty(s)==0){
        terminate("error in pop: stack is empty.\n");
    }
    old_top = s->top;
    // 맨 앞 노드 가져오기
    i =  old_top->data;
    // 맨 앞 노드의 데이터를 i에 저장
    s->top = old_top->next;
    //첫번째 노드 말고, 두 번째 노드를 첫번째 노드로 설정
    free(old_top); // 연결이 끊어진 첫 번째 노드 free선언
    return i;
}

Item peek(Stack s){
    if (is_empty(s)==0){
        terminate("error in peek: stack is empty");
    }
    return s->top->data;
}
int main(){
    Stack s1 = create();
    push(s1,8);
    printf("%d\n",peek(s1));
    return 0;
}
// 동적메모리로 stack만들고, stack의 변수를 매개변수로 받음
// 동시에 2개 이상의 스택을 만들어야 하는 경우 해결 (create())

// 스택에 저장될 데이터 타입이 다른 경우..?
// Generic Programming...
// 모든 형식이 동일한데 데이터타입만 다른 경우의 프로그래밍->Generic Programming
// but C언어는 이 방식을 지원하지 않음. 워낙 오래된 언어라서 그렇다고

// void * 타입을 이용해 generic한 stack을 구현할 수는 있으나 단점이 있음.
//-> 객체지향 프로그래밍 언어

// 전문 개발자가 될 거라면 방법을 아는 게 중요하겠지만,
// 자바나 c++같은 객체지향 언어를 쓰는 걸 추천.
