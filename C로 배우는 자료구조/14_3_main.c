#include "14_2_string_tools.h"
#include "14_1_library.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



#define BUFFER_LENGTH 200

void handle_add();
void process_command();

int main(){

    process_command();

}

void process_command(){
    char command_line[BUFFER_LENGTH];
    char * command;
    while(1){
        printf("$ "); //prompt
        
        if (read_line(stdin,command_line,BUFFER_LENGTH)<=0){
            continue; //라인 단위로 입력받기
        } // read line 구현하러 string_tool로 이동
        command = strtok(command_line," ");
        // 첫 번째 명령어 입력
        if (strcmp(command, "add")==0){
            handle_add();
        }/*else if (strcmp(command, "search")==0){
            handle_search();
        }else if (strcmp(command, "delete")==0){
            handle_delete();
        }else if (strcmp(command, "status")==0){
            handle_status();
        }else if (strcmp(command, "play")==0){
            handle_play();
        }else if (strcmp(command, "save")==0){
            handle_save();
        }*/else if (strcmp(command, "exit")==0){
            break;
        }
        
    }
}
// int read_line(FILE *fp, char str[], int n){
// // main.cpp에서 이 함수를 써야 하니까 헤더에도 선언해준다.
//     int ch, i = 0;
//     while((ch=fgetc(fp))!='\n' && ch != EOF){
//         if (i<n-1){
//             str[i++]=ch;
//         }
//     }
//     str[i] = '\0';
//     return i;
// }// #define으로 string_tools를 걸었더니
// 자꾸 undefined reference 오류가 난다.
// 구글링해도 해결방법이 딱히 안 나와서 그냥 가지고옴.


void handle_add(){
    char buffer[BUFFER_LENGTH];
    char *artist = NULL, *title = NULL, *path  = NULL;
    printf("        Artist: "); 
    if (read_line(stdin, buffer, BUFFER_LENGTH)>0){
        artist = strdup(buffer); //buffer에 가수명 이름 등등 다받을 거라서. strdup으로 복사해 받아야 한다.
    } // strdup 함수 인식을 못해서, 인터넷에 정의된 strdup함수를 string_tools에 넣음
    // 가수 이름 받기
    printf("        Title: "); 
    if (read_line(stdin, buffer, BUFFER_LENGTH)>0){
        title = strdup(buffer); //buffer에 가수명 이름 등등 다받을 거라서. strdup으로 복사해 받아야 한다.
    } //제목 받기 
    printf("        Path: "); 
    if (read_line(stdin, buffer, BUFFER_LENGTH)>0){
        path = strdup(buffer); //buffer에 가수명 이름 등등 다받을 거라서. strdup으로 복사해 받아야 한다.
    } //경로 받기

    // printf("%s, %s, %s\n",artist,title,path); 작동완료 확인
    add_song(artist,title,path);
}

