#include <stdio.h>
#define MAX 10000

int main(void){
// 파일 입출력 - 파일 저장 및 불러오기.
// .fputs, fgets -> 문자열 저장용
// .fprintf, fscanf -> 정형화된 포멧에 맞춰 읽고쓰기.


//파일 쓰기
// char line[MAX]; //char line 1만


// FILE *file = fopen("test1.txt","wb");
// if (file == NULL){
//     printf("파일 열기 실패\n");
//     return 1;
// }
// fputs("fputs를 이용해 글을 적는다.\n",file);
// fputs("확인\n",file);
// fclose(file);


//파일 불러오기
// FILE *file = fopen("test1.txt","rb");
// if (file == NULL){
//     printf("파일 열기 실패\n");
//     return 1;
// }
// while (fgets(line, MAX, file)!=NULL){
//     printf("%s",line);
// }
// fclose(file);

int num[6] = {0,0,0,0,0,0}; //추첨번호
int bonus = 0;
char str1[MAX];
char str2[MAX];

//파일에 쓰기
// FILE * file = fopen("test2.txt","wb");
// if (file == NULL){
//     printf("파일 열기 실패\n");
//     return 1;
// }
// // 로또 추첨번호 저장
// fprintf(file,"%s %d %d %d %d %d %d\n", "추첨번호",1,2,3,4,5,6);
// fprintf(file, "%s %d\n", "보너스번호",7);
// fclose(file);

//파일 읽기
FILE * file = fopen("test2.txt","rb");
if (file == NULL){
    printf("파일 열기 실패\n");
    return 1;
}
// 로또 추첨번호 저장
fscanf(file,"%s %d %d %d %d %d %d\n", str1, &num[0],&num[1],&num[2],&num[3],&num[4],&num[5]);
printf("%s %d %d %d %d %d %d\n", str1, num[0],num[1],num[2],num[3],num[4],num[5]);
fscanf(file, "%s %d",str2, &bonus);
printf("%s %d\n",str2, bonus);
fclose(file);

return 0;
}
// 파일 열면 파일 닫는 습관 필요