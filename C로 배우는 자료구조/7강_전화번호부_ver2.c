// 파일 저장하고 로드하기, 알파벳 순으로 정렬하기.
// read 명령어로 텍스트파일 읽어오기
// add, remove 시행
// save로 수정사항을 파일에 저장한다.
// exit으로 종료

// + 알파벳 순으로 정렬된 상태 유지하도록 만든다. 


/*
    정렬 상태를 유지하는 알고리즘
    1. bubblesort 등의 sort알고리즘 사용하기.
    (단 이 방법은 새로운 데이터가 계속 추가되는 우리 상황에서는 부적절)
    2. 새로운 데이터가 추가될 때마다 제자리를 찾아서 삽입하는 방법
    (우린 이걸 쓸 거다.)
    맨 뒤에서부터 검사한다. input값보다 크면 메모리칸을 한 칸씩 뒤로 미룬다.

    add할 때 검사하도록 만들 예정이므로 add함수에 넣을 것.
*/

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
void delete();
void read();
void save();
int search();

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
        }else if (strcmp(command,"delete")==0){
            delete();
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
    // names[n]=strdup(buf1);
    // numbers[n]=strdup(buf2);
    int i = n-1; //i는 마지막 사람을 뜻함.
    while (i>=0 &&strcmp(names[i],buf1)>0){
        // strcmp에서 name[i]이 buf1보다 크면(사전배열에서 뒤쪽에 있을 경우) 음수 반환
        // 반대의 경우 양수 반환. 즉 둘 중 누가 사전식 순서로 앞서는지 판단할 수 있다.
        // 여기서 양수라는 건, 입력받은 buf1의 값이 c이고 
        // 사전식 배열에서 name[i]이 k인 경우에 해당함.
        names[i+1]=names[i];
        numbers[i+1]=numbers[i];
        i--;
    }
    names[i+1] = strdup(buf1);
    numbers[i+1] = strdup(buf2);

    n++;
    printf("%s was added successfully.\n",buf1);
}
void find(){ //이름을 받고 전화번호를 찾는 기능.
    char buf[BUFFER_SIZE];
    scanf("%s",buf);

    int index = search(buf);
    if (index ==-1){
        printf("No person named '%s' exists.\n",buf);       
    } else{
        printf("%s\n",numbers[index]);
    }
}
    // int i;
    // for (i=0; i<n; i++){
    //     if (strcmp(buf, names[i])==0){
    //         printf("%s\n", numbers[i]);
    //         return;
    //     }
    // }
    
void status(){
    int i;
    for (i=0; i<n; i++){
        printf("%s %s\n",names[i],numbers[i]);
    printf("Total %d persons.\n",n);
    }
}
void delete(){
    char buf[BUFFER_SIZE];
    scanf("%s",buf);
    
    int index = search(buf);
    if (index==-1){
        printf("No person named '%s' exists.\n",buf);
        return;
    }
    int j = index;
    for(; j<n-1;j++){
        names[j] = names[j+1];
        numbers[j] = numbers[j+1];
    }
    n--;
    printf("'%s' was deleted successfully.\n",buf);
    // int i;
    // for(i=0;i<n;i++){
    //     if (strcmp(buf, names[i])==0){ // 삭제할 사람을 찾았다면 아래 일을 시행한다.
    //         names[i] = names[n-1]; //맨 마지막 사람을 삭제된 자리로 옮겨놓는다.
    //         numbers[i] = numbers[n-1];
    //         n--;
    //         printf("'%s' was deleted successfully. \n",buf);
    //         return;
    //         // 누군가를 삭제한 자리를 빈칸으로 두면, status 함수값에 오류가 생김.
    //     }
    // }
    

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
    fclose(fp);
}

void save(){
    int i;
    char filename[BUFFER_SIZE];
    scanf("%s", filename); // save 다음에 이름이 아니라 이상한 게 오면 안 된다.
    // 강의에서는 save as 파일이름 형태이다 보니
    // as를 받아서 무력화하기 위해 char tmp 설정하고 scanf("%s",tmp)로 as라는 단어를 처리했다.

    FILE * fp = fopen(filename,"w");
        if (fp==NULL){
            printf("Open failed.\n");
            return;
        }
        for (i=0;i<n;i++){
            fprintf(fp, "%s %s\n",names[i],numbers[i]);
        }
        //fprintf는 file printf의 약자.
        // printf는 컴퓨터의 모니터에 해당하는 주소값으로 출력
        // fprintf는 fprint의 첫 번째 매개변수로 사용된 파일포인터가 가리키는 파일에 저장 (FILE *fp 이니까 이 경우 fp에 저장)
        /*
        printf

        printf는 화면에서 출력을 수행하는 데 사용됩니다.
        구문 = printf("control string ", argument );
        파일 입력 / 출력과 관련이 없습니다.
        fprintf

        fprintf는 FILE 핸들이 가리키는 파일에서 쓰기 작업을 수행하는 데 사용됩니다.
        구문은 fprintf (filename, "control string ", argument );
        파일 입 / 출력과 관련됩니다.
        */
        fclose(fp);
    }

int search(char * name){ // 근데 왜 변수로 메모리변수 *name을 받지?
// 이름 = 문자열. 문자열을 지정할 때는 해당 배열의 주소를 필요로 한다.
    int i;
    for (i=0;i<n;i++){
        if (strcmp(name, names[i])==0){
            return i;
        }
    }
    return -1;
}