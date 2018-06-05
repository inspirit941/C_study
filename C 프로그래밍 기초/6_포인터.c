#include <stdio.h>

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
    return 0;
}