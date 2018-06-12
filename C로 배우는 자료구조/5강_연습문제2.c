// 사용자가 입력한 문장 중 불필요한 공백을 전부 제거한다.
// 공백이 아닌 문장을 반환한다. 두 개 이상의 공백문자가 입력될 경우 하나만 남기고 지운다.
// 제거한 후의 길이를 출력한다.

#include <stdio.h>
#include <string.h>

void compress_line(char strp[]);
int read_line_with_compression(char str[], int limit);

int main(){
    char str[] = "          Is   it fun   !  ";
    compress_line(str);
    printf("%s:%d\n",str,strlen(str));

}
void compress_line(char str[]){
    int i,j = 0;
    char compressed[100];
    char prev = '\0';
    while (str[i]==' ' ){
        i++; //맨 앞의 blank는 skip한다.
    }
    while (str[i] !='\0'){
        if (str[i] != ' '  || prev != ' ' ){
            compressed[j] = str[i];
            j++;
        }
        prev = str[i];
        i++;
        
    }
    if (prev == ' '){
        j--;
    }
    compressed[j] = '\0';
    strcpy(str, compressed);
}
// 꼭 compressed라는 또다른 배열을 써야 할까?
// 자기 자신 안에서도 충분히 할 수 있지 않나?
// -> 함수의 compressed를 str로 바꾸기만 해도 그대로 가능하다.
// compressed를 지울 경우 strcpy도 필요 없다.


//키보드에서 한 줄 입력받고 compress하기.
int read_line_with_compression(char str[], int limit){
    char ch,prev = '\0', i=0;
    while ((ch = getchar())== ' '); // 이 조건이 만족되는 동안은 아무 일도 하지 마라
    while (ch !='\n'){
        if (i<limit-1 && !( prev== ' ' && ch ==' ' )){
            str[i++]=ch;
        }
        prev = ch;
        ch = getchar();
        // 엔터키를 치면 이 while문을 빠져나간다.
    }
    if (i > 0 && str[i-1]== ' '){ // 적어도 하나의 문자가 저장 + 마지막으로 저장한 문자가 공백일 경우
        str[i-1] = '\0'; //null값으로 교체
        return i-1; // 실제 입력값은 i-1개이므로 return i-1
    }
    str[i] = '\0';
    return i;
}