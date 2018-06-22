
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


int main(){
    Stack s1 = create();
    
    push(s1,12);
    // push(s2,9);
    printf("%d\n",pop(s1));
    Stack s2 = create();
    push(s2,3);
    printf("%d\n",pop(s2));
    return 0;
    // 실행하면 오류가 뜨는데, 왜인지 모르겠다.
}

// 어느 커서에서 실행하냐에 따라 오류가 나기도 하고 안나기도 한다?
// main 맨 끝에서는 오류 안 나고, push(s2,3)에 커서 대면 오류나고..