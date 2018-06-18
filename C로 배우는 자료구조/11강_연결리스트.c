// 컴퓨터에서 다루는 데이터 중 가장 많이 쓰는 게 리스트. (set도 있긴 함. 집합)
// 기본연산: insert, remove, search 등.
// 리스트를 구현하는 두 가지 방법 -> 
//      배열, 연결리스트

// 배열의 단점: 크기가 고정되어 있어 reallocation이 필요함
// 리스트 중간에 원소를 삽입해야 할 경우 다수의 데이터를 옮겨야 한다.

// 연결리스트: 다른 데이터 이동 없이 중간에 삽입이나 삭제가 가능하다.
// 길이의 제한이 없음.
// but random access가 불가능하다.
// -> 특정 데이터에 접근하려면 맨 처음부터 쭉 따라가야 한다.
// (배열의 경우 index로 접근 가능하다) 
//  -> 시작주소 + 메모리 1칸크기 * 위치 = 원하는 위치의 주소값

// 데이터 변경이 자주 일어날 경우 
// + 검색할 일이 자주 있지 않은 경우 연결리스트가 더 효율적이다.

// 배열 = 연속된 메모리 공간에 데이터 저장.
// 연결리스트 = 연속된 메모리공간은 아니고, 
// 한 메모리 공간 안에 '다음 데이터가 저장된 주소값'이 있다.
// 마지막 데이터값은 null을 저장함

// 데이터 삽입 시 앞뒤 '주소값'만 연결해 주면 되고
// 삭제 시에도 앞뒤 주소값만 변경하면 되기 때문에 삽입 삭제에 편리함.
// 노드들이 서로 링크로 연결된 자료구조. -> 연결리스트

// 노드?
// 각각의 노드는 필요한 데이터필드 & 하나 or 그 이상의 링크 필드로 구성
// "링크 필드"는 다음 노드의 주소를 저장한다.
// 첫 번째 노드의 주소는 따로 저장해야 한다.
// (연결리스트 첫 번째 노드의 주소는 따로 저장해야 하며 절대 잊어버려서는 안 된다.)

// 노드는 구조체로 만들어야 한다

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node{
    char *data;
    struct node *next;
    // 다음 노드의 주소를 저장할 필드이다.
    // 이렇게 자신과 동일한 구조체에 대한 포인터를 멤버로 가진다는 의미에서
    // '자기참조형 구조체' 라고도 한다.
} Node;
Node *head = NULL; // 첫 번째 연결리스트 주소를 저장하는 값.
void add_first(char *item);
// 노드가 필요할 때마다 그때그때 추가해
// 연결노드를 만든다.
// 만드는 방식은 동적메모리할당
int main(){
    head = (Node *)malloc(sizeof(Node));
    head->data = "Tuesday";
    head->next = NULL; // 맨 첫번째 노드 설정

    Node *q = (Node *)malloc(sizeof(Node)); //해당 노드의 주소를 가리킨다.
    q->data = "thursday";
    q->next = NULL;
    head->next = q; // 두 번째 노드를 만들고, 첫번째 노드의 next에 두번째 노드 주소를 넣는다.

    q = (Node *)malloc(sizeof(Node));
    q->data = "Monday";
    q->next = head; // 원래 head가 갖고 있던 주소값을 q의 next에 넣는다.
    //이 경우 q가 첫번째 노드가 된다. 
    head = q; // 이제 q는 첫번째 노드인 head가 되었다.
    // 세 개 코드를 다 돌면
    // head는 monday를 반환하고
    // 그 다음부터 tuesday, thursday까지 반환한다. 

    // 즉 q를 가지고 노드로 쓸 구조체를 만들었지만, 그 구조체를 가리키는 값은 없다.
    // thursday를 만들고 q가 주소값이 되었었지만, 그 다음 q를 head로 바꾸면서
    // 변수에 주소값을 할당받은 건 없어졌고, tuesday도 마찬가지로 사라졌다.

    // 결국 head 주소값만 컴퓨터가 보관하고
    // 나머지 주소값은 리스트를 따라가면서 하나씩 확인하는 구조!
    Node *p = head;
    while(p!= NULL){
        printf("%s\n",p->data);
        p = p -> next; // 가장 자주 쓰게 될 문장.
    } 
    // 왜 head를 쓰지 않고 p라는 이름을 새로 썼을까
    // head 변수가 그대로 들어가면,
    // 원래 head의 정의인 '첫 번째 노드의 주소값을 가리킨다'가 훼손된다.
    // while문 다 돌고 나면 head는 null이 됨.

}
// 연결리스트 맨 앞에 새로운 노드 삽입하기?
/*
    1.새로운 노드를 만들고 추가할 데이터를 저장한다.
    2.새로운 노드의 next 필드가 현재의 head노드를 가리키도록 수정한다.
    3.새로운 노드를 head노드로 지정한다.
    (순서를 지켜야 노드 주소의 혼선이 없다!)
    Node *tmp = (Node *)malloc(sizeof(Node));
    tmp->data = "data";
    tmp->next = head;
    head = tmp;

    만약 head가 null값이라면??
    -> tmp의 next에 null이 들어간다 = 첫 번째 노드 생성의 개념이 된다.
*/
/*
연결 리스트를 다루는 프로그램에서 가장 주의할 점은
내가 작성한 코드가 일반적인 경우뿐 아니라 특수한 경우에도 작동하는지 확인하는 것이다.
기존의 연결 리스트의 길이가 0인 경우, 즉 head가 Null인 경우에도 문제가 없는가?
  특수 상황에서도 작동하는지 항상 확인해야 한다!
  // 일반적인 상황에서의 코드 작성 후 예외상황 처리하기.
*/
void add_first(char *item){
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->data = item;
    temp->next = head;
    head = temp;
    // 첫번째노드를 가리키는 포인터 head가 전역변수인 경우 가능한 구조.
}
// 만약 head가 특정 함수의 지역변수라면
void add_first_local(Node **ptr_head, char *item){
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->data = item;
    temp->next = *ptr_head;
    *ptr_head = temp;

    // 포인터 변수 head의 주소를 매개변수로 받아야 한다.
    // 따라서 Node ** ptr_head가 등장함.
    // 즉 head 노드의 값을 넘겨주는 (default인 call by value) 방식이 아니라
    // head 노드의 주소값을 받아야 한다.
    // 따라서 add_first_local(&head, item_to_store) 가 되어야 함.
}
// 또는 이렇게 함수를 만들 수도 있다.

Node *add_first2(Node *head, char *item){
    Node *temp = (Node *)malloc(sizeof(Node));
    temp -> data = item;
    temp->next = head;
    return temp; // 새로운 head 노드의 주소를 return하도록 만들 수 있다.
}
// 이렇게 구현할 경우 이 함수는
// head = add_first(head, item);
// head 노드 = temp 주소값을 받는 형태



/*      어떤 노드 뒤에 새로운 노드 삽입하기.
// 새로운 노드를 만들고 데이터를 저장한다.
새로운 노드의 next가 prev의 다음 노드를 가리키도록 한다.
새로운 노드를 prev의 다음 노드로 만든다.
-> 앞 사례와 마찬가지로 순서는 매우 중요하다

    Node *tmp = (Node *)malloc(sizeof(Node));
    tmp->data = "data_to_store";
    tmp->next = prev->next;
    prev->next = tmp;
*/
int add_after(Node *prev, char *item){
    if (prev ==NULL){ //이전의 노드가 마지막 노드라면 return 0
        return 0;
    }
    Node *tmp = (Node *)malloc(sizeof(Node));
    tmp->data = item;
    tmp->next = prev->next;
    prev->next = tmp;
    return 1;
    // 연결리스트에 새로운 노드를 삽입할 때, 삽입할 위치의 바로 앞 노드의 주소가 필요하다.
    // 어던 노드의 뒤에 삽입하는 건 그래서 쉽지만
    // 반대로 어떤 노드의 앞에 삽입하는 건 간단하지 않다.
}


// 노드의 삭제?
// head가 현재 head노드의 다음 노드를 가리키게 만든다.
// head = head->next (head는 첫번째 노드의 주소를 가리키고 있었으므로)
Node * remove_first(){
    if (head ==NULL){
        return NULL;
        // 노드가 없다는 의미이므로 return null해준다.
    }
    else{
        Node *tmp = head;
        head = head->next;
        return tmp;
        // head는 두 번째 노드를 가리키게 하고,
        // return값은 첫 번째 노드의 주소를 가리키도록 (free해줘야 하니까)
    }
}

// 어떤 노드의 다음 노드 삭제하기
// 특정 노드를 주고, 그 노드의 다음 노드를 삭제하게 함
// 특정 노드를 삭제하려면, 그 앞 노드의 prev 주소를 변경해야 하기 때문.

Node * remove_after(Node *prev){
    Node *tmp = prev->next;
    if (tmp == NULL){
        return NULL;
    }else {
        prev->next = tmp->next;
        // tmp->next는 prev->next->next로도 쓸 수 있다.
        return tmp;
        // 마찬가지로 지워진 노드의 주소값을 반환한다.
    }
}
// 단순연결리스트에서 어떤 노드를 삭제할 때에는
// 삭제할 노드의 바로 앞 주소가 필요하다.
// 삭제할 노드의 주소만으로는 삭제할 수 없다.

//      연결리스트 순회하기 (처음부터 쭉 돌기) - traverse
// 이 경우 검색을 위해서
Node *find(char *word){
    Node *p = head; //head는 전역변수로 선언했다는 전제.
    while (p!=NULL){
        if (strcmp(p->data,word)==0){
            return p; //찾았으면 해당 노드의 주소 반환
        }
        p=p->next; //없으면 다음 노드로.
    }
    return NULL;
}

// index번째 노드의 주소 반환하기.
Node *get_node(int index){
    if (index <0){
        return NULL;
    }
    Node *p = head;
    for (int i=0;i<index&& p!=NULL;i++){
        p=p->next;
    }
    return p;
}

// add (int index) ... -> index번째 자리에 노드 생성
int add(int index, char *item){
    if (index<0){
        return 0;
    }
    if (index ==0){
        add_first(item);
        return 1;
    }

    // Node *tmp = (Node *)malloc(sizeof(Node));
    // tmp->data = item;
    // tmp->next = NULL; -> add_first나 add_after에서 수행하는 내용임
    
    Node * prev = get_node(index -1);
    if (prev!=NULL){
        add_after(prev,item);
        return 1;
    }
    return 0;
    // index의 case에 따라 별개로 코드를 만들어 처리해야 한다.
}

Node *remove_by_index(int index){
    if (index<0){
        return NULL;
    }
    if (index==0){
        return remove_first();
    }
    Node *prev = get_node(index-1);
    if (prev = NULL){
        return NULL;
    }else{
        return remove_after(prev);
    }
}
// 만약 특정 string을 저장한 노드를 찾아 삭제하는 함수를 만든다면?

Node *remove_by_item(char *item){
    Node *p = head;
    Node *q = NULL;
    while (p!=NULL && strcmp(p->data,item)!=0){
        q=p; //q를 p가 가리키는 노드로 변경
        p=p->next;// p는 전진
    }
    if (p==NULL){
        return NULL;
    }
    if (q==NULL){
        return remove_first(); // p가 첫번째 노드일 경우 q는 null이다.
    }else{
        return remove_after(q);
    }
    //but 노드를 삭제하려면, 해당 노드 바로 직전의 주소값을 알아야 한다.
    // 그래서 포인터를 하나 더 만든다.
}

void add_to_ordered_list(char *item){
    // 연결리스트에 데이터가 오름차순으로 정렬되어 있다는 가정 하에
    // 새로운 데이터를 삽입할 경우
    Node *p = head;
    Node *q = NULL;
    while (p!=NULL && strcmp(p->data, item)<=0){
        q=p;
        p=p->next;
    }
    if (q==NULL){
        add_first(item); // 데이터 삽입장소가 맨앞이라는 소리다.
    }else{
        add_after(q,item);
    }
}