#include <stdio.h>

int main(void){
//배열

int subway_array[3]; //몇 개의 값을 갖는 array를 만들지 선언
subway_array[0]=30;
subway_array[1]=40;
subway_array[2]=50;

for (int i=0;i<3;i++){
    printf("지하철 %d호차에 %d명이 타고 있다.\n",i+1,subway_array[i]);
}
//값 설정
int arr[10]={1,2,3,4,5,6,7,8,9,10};
for(int i=0; i<10;i++){
    printf("%d",arr[i]);
}
// 만약 값을 초기화하지(넣지) 않으면 이상한 값이 들어간다.
// 이 값이 dummy값. 알 수 없는 값임.

// 숫자 변수형 값은 배열에 사용 불가능
// int size=10;
// int arr[size]; 이런 형태는 불가능하다는 뜻.

int arr2[10]={1,2};
for(int i=0; i<10;i++){
    printf("%d",arr2[i]);
}
// 이 경우 1,2,0,0,0,0,0,0,0,0이 반환된다.
// dummy값을 반환하는 게 아님

int arr3[] = {1,2};
//안에 숫자를 지정하지 않으면, 주어진 값의 수만큼 array를 정의함
float arr_f[5] = {1.0f,2.0f,3.0f};
for(int i=0; i<5;i++){
    printf("%.2f\n",arr_f[i]);
}

// 문자 vs 문자열(1글자 vs 여러 글자)
char c='A';
printf("%c\n",c);
//문자열 끝에는 '끝'을 의미하는 NULL문자가 필요하다.
// '\0'이 필요하다고. 따라서 문자열 개수+1개만큼 공간선언어 필요하다는 게 인강.
// 실제로 sizeof()로 크기 검증해 보면 6이 아니라 7이다. null문자 공간이 있다는 소리.
char str[]="coding";
printf("%s\n",str);
printf("%d\n",sizeof(str));

char kor[] = "나도코딩";
printf("%d\n",sizeof(kor));
//영어 1글자 - 1 byte
//한글 1글자 - 2 byte. 
// 따라서 sizeof에서 할당된 바이트가 한글은 한글자당2 byte라는 소리.
// 근데 내 VScode에서는 3바이트 할당인 모양이다. 13이 return됨

char c_array[10]={'c','o','d','i','n','g','\0'};
printf("%s\n",c_array);
//할당된 배열 개수 10보다 적은 string개수(7)가 들어가 있으면
//남은 값은 빈칸으로 인식한다.
for (int i=0;i<sizeof(c_array);i++){
    printf("%d\n",c_array[i]);
    //결과를 출력할 경우 99,101 등의 숫자가 나온다.
    //이게 ASCII 코드값임. 아스키 코드값이 출력되며
    //빈칸은 0으로 반환된다.
}

// 참고: ASCII는 미국표준협회에서 제시한 표준코드체계
// 7bit. 총 128개 코드. (0-127)
printf("%c\n",'a');
printf("%d\n",'a');
printf("%c\n",'\0');
printf("%d\n",'\0');
for (int i=0;i<128;i++){
    printf("아스키코드 정수 %d = %c\n",i,i);
}
    return 0;
}

