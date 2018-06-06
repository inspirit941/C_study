#include <stdio.h>

int main(void){
    //다차원 배열
    int i; // 메모리 공간 하나
    int arr[5]; // 메모리 공간 다수 소모
    int arr2[2][5] = {
        {1,2,3,4,5},
        {1,2,3,4,5}
        }; 
    // 5개의 배열이 2 개 있다고 이해하면 된다. 뒤에서부터 읽는 느낌 - 2차원배열
    int arr3[3][3][3]; // 3차원 배열.
    /* 선언은 {
        {{1,2,3}, {1,2,3}, {1,2,3}},
         {{1,2,3}, {1,2,3}, {1,2,3}},
          {{1,2,3}, {1,2,3}, {1,2,3}}
     };
이런 식으로 될 것.

*/
    // 2차원 배열의 접근법
    //int arr2[2][5];
    // □ □ □ □ □
    // □ □ □ □ □  처럼 되어 있다.

    // [0][0] [0][1] ... [0][4]
    // [1][0] [1][1] ... [1][4] 로 지정되어 있음. 
    // 이런 식으로 차원 수에 맞게 인덱스를 가져오면 된다.

    for (int i=0;i<2;i++){
        
        for (int j=0;j<5;j++)
        printf("2차원배열 <%d>,<%d> 값은 %d\n",i,j,arr2[i][j]);
    }    

    // 차원 수에 맞게 for문을 쓰면 된다.    

    return 0;
}