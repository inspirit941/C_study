#include <stdio.h>
#define MAX 10000
// 비밀번호를 입력받아서, 맞는 경우 글쓰기, 수정 가능
// 틀린 경우 경고메세지 발생 후 종료




int main(void){
// fgets, fputs를 활용
    char line[MAX]; //파일에서 불러온 내용 저장
    char content[MAX]; // 입력할 내용
    char password[20]; // 비밀번호 입력
    char c; //비밀번호 입력 시 키값 확인용.

// getchar()와 getch의 차이?
// getchar는 엔터 입력받아야 동작
// getch는 키 입력시 바로 동작

    printf("게시판\n");
    printf("비밀번호를 입력하세요\n");
    int i=0;
    while (1){

        c=getch();
        if (c==13){
            password[i] = "\0";
            //비밀번호 입력 종료
        } //enter키 누를 경우 동작
        else{
        printf("*");
        password[i]=c;
        }
        i++;
        // 이 경우 문자열을 지울 경우는 어떻게 하는가?
    }
    // 비밀번호 = "asdf"
    printf("\n비밀번호 확인 중.\n");
    if (strcmp(password,"asdf")==0){ //비밀번호 일치를 말함
        printf("비밀번호 확인 완료\n");
        char * filename = "post.txt";
        FILE * file = fopen(filename, "a+b");
        // 파일이 없으면 생성 + 파일이 있으면 내용을 append한다는 의미.
        if (file==NULL){
            printf("파일 열기 실패\n");
            return 1;
        }
        while (fgets(line, MAX, file)!= NULL){
            printf("%s",line);
        }
        printf("\n\n내용을 작성하세요. 종료하려면 exit을 입력하세요.");

        while (1){
            scanf("%[^\n]", content); // 줄 바꿈이 나오기 전까지 = 한 문장씩 읽는다.
            getchar(); //엔터 입력시 flush 처리

            if (strcmp(content, "exit")==0){
                printf("글 입력을 종료합니다.");
                break;
            }
            fputs(content,file);
            fputs("\n",file); //엔터를 위에서 무시처리 했기 때문에, 다시 입력해줌

        }
        fclose(file);
    } 
    else{ //비밀번호가 틀렸을 때
        printf("비밀번호가 틀렸습니다.\n");
        printf("장비를 정지합니다.\n");
    }
    return 0;
}
