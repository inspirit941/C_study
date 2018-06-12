#include <stdio.h>
#define BUFFER_SIZE 20
int read_line(char str[],int limit);

int main(void){
    char buffer[40];

    while(1){
        printf("$ ");
        int len = read_line(buffer,BUFFER_SIZE);
        // scanf_s("%s",buffer); // %s는 공백 기준으로 단어를 잘라내는 형태다. 문장 전체를 세야 하므로 다른 방법을 생각해야 함.
        //scanf의 문제는, buffer의 범위를 벗어나서도 데이터를 써낸다는 것.
        // 이를테면 buffer[10]인데 scanf로 받은 데이터가 30이 넘어가도, scanf는 이를 다 받아낸다.
        //프로그램의 측면에서는 심각한 문제.
        // 그래서 scanf_s를 쓴다고 함.
        

// fgets(buffer,BUFFER_SIZE,stdin); 
        //gets가 line 단위로 읽어내는 함수라고 한다.
        // 다만 scanf와 마찬가지의 문제가 발생한다.
        // 그래서 fgets를 씀. 세번째 매개변수는 file의 pointer라고 함.
        // 키보드에서 데이터를 입력받는 것이므로 '표준입력파일'임. 표준입력파일 = stdin.

// buffer[strlen(buffer)-1] = '\0'; //  \n을 \0으로 변경.
        printf("%s:%d\n",buffer, len);
        // fgets가 \n (줄바꿈 문자)까지 포함해 카운트한다.
        

        // buffer size보다 큰 문장이 들어오면, 20글자까지만 읽고 값을 반환한다.
        // fgets의 종료조건이 두 개라는 소리. array 상한선에 도달하거나 \n을 만나거나.
// fgets를 쓰면, 앞부분 20개까지를 읽고 저장한 다음
// 그 다음 부분을 다시 buffer에 저장하는 문제가 발생한다.
        
        // while문이 계속 돌기 때문에, 아직 읽지 못한 나머지 input이 다시 count되는 현상이 발생함.
        // 우리가 원하는 건, 20글자 넘어가면 뒷부분은 그냥 무시하기.
        
        // gets나 scanf_s같은 내장함수의 상태가 영 좋지 않기 때문에
        // 보통 C 프로그래머들은 read_line 함수를 알아서 정의해 쓴다고 함.
        // 나름대로 커스터마이즈해서 쓴다고.

    }
    return 0;
}

int read_line(char str[],int limit){
    int ch,i=0;
    while ((ch=getchar())!='\n'){ //getchar()의 반환타입은 int이다.
        if (i < limit){
            str[i++]=ch;
        }
    }
    str[i]='\0';
    return i;
}