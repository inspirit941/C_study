#include <stdio.h>

void swap(int a, int b);
void swap_addr(int * a, int *b);
void changeArray(int *ptr);
int main(void){
    int a=1;
    int b=2;
    int c=3;
    //집 문앞의 암호
    // 집 주소 = 메모리 주소
    // 강의에서는 한글변수를 입력해도 실행에 문제가 없었으나
    // 내 VScode에서는 한글변수 입력이 불가능함.
    printf("철수네 주소: %d, 암호: %d\n",&a, a);
    // 할당된 메모리주소를 확인하려면 변수 앞에 &를 붙인다.

    // 1. 아파트의 각 집에 방문하여 문에 적힌 암호 확인하기.
    int * mission; //포인터 변수. (앞에 *가 붙는다)
    mission = &a;
    printf("방문하는 곳 주소: %d, 암호: %d\n",mission, *mission);
    // 주소값을 저장하려면 포인터 변수를 선언해 준다.
    // 주소값에 저장된 데이터를 불러오려면 변수 앞에 *를 붙이면 된다.

    //2. 각 암호에 3을 곱한다.
    *mission = *mission * 3;
    printf("암호 변경: %d\n",*mission);

    //변수의 주소값을 알 수도 있고, 주소값으로 찾아가 변수를 변경하는 것이 가능하다.

    //3. mission이 바꾼 암호에서 2를 빼는 또다른 변수의 등장
    int *spy = mission;
    //두 개 이상의 포인터가 하나의 메모리주소를 가리킬 수 있다.
    spy = &a;
    *spy = *spy-2;
    // 포인터를 알고 있으면 주소값을 변경하는 게 가능함.
    printf("spy가 변경한 주소 : %d\n",*spy);
    
    printf("mission의 주소: %d\n",&mission);
    printf("spy의 주소: %d\n",&spy);

    //배열과 포인터의 관계
    int arr[3]={5,10,15};
    int * ptr = arr;
    for (int i=0;i<3;i++){
        printf("배열 arr[%d]의 값: %d\n",i,arr[i]);
    }
    for (int i=0;i<3;i++){
        printf("포인터 ptr[%d]의 값: %d\n",i,ptr[i]);
    }
// 포인터: 배열 하나하나의 주소값을 그대로 가지고 있다.
    ptr[0]=100;
    ptr[1]=200;
    ptr[2]=300;
    for (int i=0;i<3;i++){
        printf("배열 arr[%d]의 값: %d\n",i,arr[i]);
    }
    for (int i=0;i<3;i++){
        printf("포인터 ptr[%d]의 값: %d\n",i,ptr[i]);
    }
    // *(arr+i) == arr[i] 와 동일한 표현
    // arr == arr 배열의 첫번째 값 주소와 동일하다.
    printf("arr 자체의 값: %d\n",arr);
    printf("arr[0]의 주소: %d\n",&arr[0]);

    printf("arr 자체의 값은 주소를 갖는다. 이 주소의 실제 값: %d\n", *arr);
    printf("arr[0]의 실제 값:%d\n",*&arr[0]);

    //즉 메모리 주소를 지정해야 할 때는 변수를 선언할 때 *를 붙인다. 
    // int *ptr = arr (arr이란 이름은 arr이란 array의 가장 첫번째 값의 주소를 갖는다.)
    // 주소 변수 앞에 *를 붙이면, 그 주소의 값을 가져온다.
    // 값을 반환하는 변수 앞에 &를 붙이면 그 변수의 주소를 반환한다.
    // 따라서 *&가 동시에 붙어 있으면 별 의미가 없다.

    int k=10;
    int m=20;
    //a와 b의 값을 바꾼다
    printf("Swap 함수이전- k:%d, m:%d\n",k,m);
    printf("Swap 함수이전 주소값- k:%d, m:%d\n",&k,&m);
    swap(k,m);
    printf("swap 함수 이후 k:%d, m:%d\n",k,m);
    printf("Swap 함수이후 주소값- k:%d, m:%d\n",&k,&m);
    
    // 값에 의한 복사 (call by value)
    // swap 함수 내에서 실행될 때는 '값'만 받은 것.
    // 주소가 변하지 않음.
    // 즉 함수 안에서 실행될 때는, 원래 정의된 k,m의 주소값을 쓰는 게 아니라
    // 새로운 주소값에 k와 m의 '값'만을 넣어 계산한 것.

    // 만약 주소값 자체를 넘길 경우???
    printf("Swap 함수이전- k:%d, m:%d\n",k,m);
    printf("Swap 함수이전 주소값- k:%d, m:%d\n",&k,&m);
    swap_addr(&k,&m);
    printf("swap 함수 이후 k:%d, m:%d\n",k,m);
    printf("Swap 함수이후 주소값- k:%d, m:%d\n",&k,&m);
    

    
    int arr2[3] = {10,20,30};
    //배열일 때 arr2는 주소를 나타낸다.(arr2[0]의 주소값)
    // 그래서 changeArray에서 arr2를 바로 넣을 수 있는 것.
    // arr 대신에 &arr[0]를 넣어도 동일하게 작동한다.
    changeArray(arr2);
    for (int i=0; i<3;i++){
        printf("%d\n",arr2[i]);
    }
    
    //scanf에서 input값을 &변수명으로 저장하는 이유 -> 해당 변수의 주소값에 넣기 위해서.
    return 0;
    // 값만 보내서 바뀌는 게 아니라, 주소값을 보내야 제대로 된 변환이 이루어진다.

}

void swap(int a, int b){
    int temp = a;
    a = b;
    b = temp;
    printf("swap 함수 안에서 k:%d, m:%d\n",a,b);
    printf("Swap 함수 안에서 주소값- k:%d, m:%d\n",&a,&b);
    
}

void swap_addr(int *a, int *b){
    int temp = *a; //여기서 정의한 *a는 주소에 실제 들어있는 값을 지칭함.
    *a = *b;
    *b = temp;
    printf("swap 함수 안에서 k:%d, m:%d\n",a,b);
    printf("Swap 함수 안에서 주소값- k:%d, m:%d\n",*a,*b);
    
}

void changeArray(int *ptr){
    ptr[2] = 50;
}