// 파일 저장하고 로드하기, 알파벳 순으로 정렬하기.
// read 명령어로 텍스트파일 읽어오기
// add, remove 시행
// save로 수정사항을 파일에 저장한다.
// exit으로 종료

// + 알파벳 순으로 정렬된 상태 유지하도록 만든다. 
#include <stdio.h>
#include <string.h>

#define CAPACITY 100
#define BUFFER_SIZE 20



char * names[CAPACITY]; // 사람이름 = 문자열, 문자를 받는 배열이므로 char
char * numbers[CAPACITY]; // 생긴 건 숫자이지만, 숫자처럼 다루면 프로그램에서 맨 앞 0을 지워버리는 등의 문제 발생
// 문자열의 맨 끝에는 \0 들어가는것 잊지 말기
int n = 0; // number of people in 전화번호부

void add();
void find();
void status();
void remove();
void read();
void save();

int main(){
    char command[BUFFER_SIZE];
    while(1){
        printf("$ ");
        scanf("%s",command);
        if (strcmp(command,"add")==0){ //strcmp는 두 문자열이 동일하면 0을 반환한다. string compare
            add();
        }else if (strcmp(command,"find")==0){
            find();
        }else if (strcmp(command, "status")==0){
            status();
        }else if (strcmp(command,"remove")==0){
            remove();
        }else if(strcmp(command,"save")==0){
            save();
        }else if(strcmp(command,"read")==0){
            read();
        }else if (strcmp(command,"exit")==0){
            break;
        }
    }

    return 0;
}

void add(){
    char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
    scanf("%s", buf1);
    scanf("%s", buf2);
    names[n]=strdup(buf1);
    numbers[n]=strdup(buf2);
    
    n++;
    printf("%s was added successfully.\n",buf1);
}
void find(){ //이름을 받고 전화번호를 찾는 기능.
    char buf[BUFFER_SIZE];
    scanf("%s",buf);

    int i;
    for (i=0; i<n; i++){
        if (strcmp(buf, names[i])==0){
            printf("%s\n", numbers[i]);
            return;
        }
    }
    printf("No person named '%s exists.\n",buf);
}
void status(){
    int i;
    for (i=0; i<n; i++){
        printf("%s %s\n",names[i],numbers[i]);
    printf("Total %d persons.\n",n);
    }
}
void remove(){
    char buf[BUFFER_SIZE];
    scanf("%s",buf);

    int i;
    for(i=0;i<n;i++){
        if (strcmp(buf, names[i])==0){ // 삭제할 사람을 찾았다면 아래 일을 시행한다.
            names[i] = names[n-1]; //맨 마지막 사람을 삭제된 자리로 옮겨놓는다.
            numbers[i] = numbers[n-1];
            n--;
            printf("'%s' was deleted successfully. \n",buf);
            return;
            // 누군가를 삭제한 자리를 빈칸으로 두면, status 함수값에 오류가 생김.
        }
    }
    printf("No person named '%s' exists.\n",buf);

}

void read(){
    char filename[BUFFER_SIZE];
    char buf1[BUFFER_SIZE];
    char buf2[BUFFER_SIZE];

    scanf("%s",filename);
    FILE * fp = fopen(filename, "r");
    if (fp==NULL){
        printf("open failed.\n");
        return; // 파일 열 때 실패할 경우의 예외처리.
    }
    while((fscanf(fp, "%s",buf1)!= EOF)){
        fscanf(fp, "%s", buf2);
        names[n] = strdup(buf1);
        numbers[n] = strdup(buf2);
        n++;
    }
}

void save(){

}