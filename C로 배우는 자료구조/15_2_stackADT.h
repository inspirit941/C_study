#ifndef STACKADT_H
#define STACKADT_H

#include <stdbool.h> //C99 only

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

#endif