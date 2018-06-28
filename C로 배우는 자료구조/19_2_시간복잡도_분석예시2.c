// 2 way merging -> 2개의 배열이 정렬되어 있을 때,
/*  새로운 배열 C에 정렬된 상태로 저장하는 것.
배열 A가 m개, B가 n개. 합칠 배열 C의 공간에 부족함이 없다고 할 때

*/

void merge_sorted_arrays(int m, int a[], int n, int b[], int c[]){
    for (int i=0; i<m; i++){
        c[i] = a[i]; //배열 A의 데이터를 그대로 배열 C에 복사
    }
    for (int j=0;j<n;j++){
        insert_to_ordered_array(n+j,c,b[j]);
        // 배열 b의 데이터 각각을 배열 c에 insert한다
    }// 즉 하나를 그냥 때려박은 다음, 두 번째 배열을 넣을 때 정렬해서 넣는다.
}
// 이 경우, 최악의 경우 시간복잡도는 O(mn)이다.

//two_way_merging

void merge_sorted_arrays_linear(int m, int a[], int n, int b[], int c[]){
    // m 과 n은 배열의 크기
    int i=0, j=0, k=0;
    while (i<m && j<n){
        if (a[i]<=b[j]){
            c[k++] = a[i++]; // 배열 두 개 크기 비교해서
            // 둘 중 a가 작으면 a를 append
            // b가 작으면 b를 append
        }else{
            c[k++]=b[j++];
        } //두 개 비교하는 작업이 끝나면
    }
    while (i<m){ // a나 b의 남은 배열을 집어넣는다.
        c[k++] = a[i++];
    }
    while (j<n){
        c[k++] = b[j++];
    }
}
//최악의 경우 시간복잡도는 O(m+n)이다.


// 정렬된 두 연결리스트 합치기

Node *merge_two_ordered_list(Node *first, Node *second){
    Node *p = second;
    Node *q = first;
    // second의 노드를 first에 넣는 것.
    while (p!=NULL){
        Node *the_node = p;
        p=p->next;
        first = insert_to_ordered_list(first, the_node);
    }
    return first;
}
// 최악의 경우 시간복잡도는 O(mn)이다. (second 노드 개수가 m, first노드개수가 n)
// 긴 리스트를 두고, 짧은 리스트를 append하는 게 시간복잡도의 측면에서 더 효율적이다.


// 정렬된 두 연결리스트 합치기 2
Node *merge_two_ordered_list2(Node *first, Node *second){
    Node *head = NULL, *tail = NULL;
    Node *tmp;
    while (first!=NULL && second !=NULL){
        if (first->data <=second->data){ //first의 노드를 tmp에 저장
            tmp = first;
            first = first->next;
        } else {
            tmp = second;
            second = second ->next;
        }
        tmp ->next = NULL;
        if (tail==NULL){ // empty list라는 의미이므로, 처음으로 노드 삽입하는 것
            head = tail = tmp;
        } else { // tail->next에 tmp를 넣고
        // 새로운 tail node가 tmp가 된다.
            tail -> next = tmp;
            tail = tmp;
        }
    }// 노드가 소진될 때까지 while문 반복.

        if (first !=NULL){
            tail->next = first;
        }else if (second !=NULL){
            tail->next = second;
        }
        return head;
    // 최악의 경우 시간복잡도는 O(m+n)이다
}


Node *merge_two_ordered_list3(Node *first, Node *second){
    Node *p = second;
    Node *q = first, *pre_q = NULL;
    while(p!=NULL){
        Node *the_node = p;
        p = p->next;
        while (q!=NULL && q->data < the_node->data){
            pre_q = q;
            q = q->next;
        }
        if (pre_q ==NULL){
            the_node->next = first;
            first = the_node;
        }else{
            the_node->next = q;
            pre_q->next = the_node;
        }
        pre_q = the_node;
    }
    return first;
    // while문이 두 번이지만, 최악의 경우 시간복잡도는 O(m+n)이다.
    // while문이 돌아가지만 for문처럼 앞에서부터 뒤까지 반복하는 게 아니라
    // 전진만 하기 때문
}
Node *inverse_list(Node *head){
    if (head ==NULL || head->next ==NULL){
        return head;
    }
    Node *p = head;
    Node *q = NULL;
    Node *r = p->next;

    while (p!=NULL){
        p->next = q;
        q=p;
        p=r;
        if (r!=NULL){
            r = r->next;
        }
    }
    return q;
    // 시간복잡도는 O(n)이다
}

Node *remove_all_divisible(Node *head, int divisor){
    Node *p = head;
    Node *q = NULL, *deleted = NULL;
    while (p!=NULL){
        if (p->data%divisor==0){ //값이 일치할 경우
            if (q==NULL){ //q가 맨 앞이란 의미니까
            // 원래 있던 head값을 p->next로 변경. 즉 맨 앞 노드의 값을 지운다
                head = p->next;
            }else{ //p 바로 다음 주소값을 q의 next로 갖는다.
                q->next = p->next;
            }
            deleted = p; // p를 지운다
            p = p->next;
            free(deleted);
        }
        else{
            q=p;
            p=p->next;
        }
        //시간복잡도는 O(n)
    }
}