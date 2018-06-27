
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
    if (is_full(s)){ // 배열로 구현할 경우 stack의 시간복잡도.
        reallocate(s); // 현재 데이터에 저장된 데이터개수가 n개라면
        // n개의 데이터를 옮기는 작업이므로 O(n)일 것.
    } // reallocate를 제외한 나머지 계산의 시간복잡도는 O(1)
    // 현재 있는 데이터의 양과는 무관한 함수들이기 때문.
    
    // 보통 reallocate 를 시간복잡도에는 잘 넣지 않는다.
    // 사실 stack 크기를 처음에 만들 때 크게 만들어버리면, reallocation 안 해도 되다 보니.

    s->top++;
    s->contents[s->top]=i;
}
Item pop(Stack s){
    if (is_empty(s)==0){
        printf("in pop\n");
        terminate("Error in create: stack could not be created.\n");
    }
    s->top--;
    return s->contents[s->top+1]; //O(1)
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




// 연결리스트로 구현했을 경우
// push와 pop의 시간복잡도는 O(1)이다.
// 노드 삽입과 삭제는 현재 연결리스트의 길이와 무관함 -> O(1)

// enqueue, dequeue도 마찬가지로 O(1)이다.
// 배열로 구현하건 연결리스트로 구현하건 똑같음.

// 정렬된 리스트에 삽입하기 : 배열의 경우

void insert_to_ordered_array(int n, int data[], int item){
    int i=n-1;
    for (;i>=0 && data[i]>item; i--){
        data[i+1] = data[i]; // 한 칸 뒤로 데이터 shift
    }
    data[i+1] = item;
}
// 이 정렬 알고리즘은 최악의 경우 O(n)이다. 

// 1. 데이터가 크기순으로 정렬되어 있다면, 이진검색을 통해 새 데이터가 들어갈 위치를 찾을 수 있다.
//  이 경우 위치를 찾는 데 걸리는 시간을 log2N으로 줄일 수 있다.
//  그래봐야 어차피 나머지 데이터를 뒤로 미뤄야 하므로 전체 시간복잡도는 크게 변하지 않음.
// 2. 앞에서부터 순차적으로 찾는 방법.
//  처음으로 나보다 큰 값이 나오면, 그 값 앞에 자리한다.
//  좋은 아이디어는 아니다. 작은 값들을 전부 비교해봐야 하고
//  큰 값들은 전부 하나씩 뒤로 미루는 연산을 해야 하므로
// 3. 뒤에서부터 검사하기.
//  나보다 작은 값이 나오기 전까지 큰 값을 뒤로 보낸다.
//  나보다 작은 값을 볼 필요가 없기에 좀 더 효율적이다. 위의 insert_to_ordered_array가 이 원리에 기반함.


// 정렬된 리스트에 삽입하기-> 연결리스트의 경우

// 단방향 연결리스트는 뒤에서부터 찾을 수도 없고 이진검색도 못 쓰니까
// 그냥 앞에서부터 쭉 가야 한다.

Node *insert_to_ordered_linked_list(Node *head, int item){
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node -> data = item;
    new_node ->next = NULL;

    Node *p =  head, *q = NULL; // 단방향이므로 노드 포인터 두 개 필요
    while(p!=NULL && p->data <item){
        q=p;
        p=p->next;
    }
    if (q==NULL){
        new_node ->next = head;
        head = new_node;
    }
    else{
        new_node->next = p;
        q->next = new_node;
    }
    return head;
    // 연결리스트의 첫 번째 노드를 저장하는 변수가 전역변수가 아니라고 가정한다면
    // 첫 번째 노드의 주소를 변경할 가능성이 있는 함수들은
    // 항상 첫 번째 노드의 주소를 반환하도록 구현하는 것이 일반적이다.
    // 최악의 경우 O(n)이다.


    // 사실 전역변수로 head를 선언하면 이렇게 복잡하게 안 해도 된다.
    // 하지만 모든 노드의 head를 전역변수로 저장할 필요가 없을 때에는 이렇게 해줘야 함
}