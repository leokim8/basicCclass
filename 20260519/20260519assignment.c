#include <stdio.h>
#include <stdlib.h>
void add(int *balance, int answer, int a);
int subtract(int* balance, int answer, int a);
int givemoney(int* balance, int giver, int thankyou, int a);
int idcheck ();
int main() {
    int * balance = (int *)malloc(sizeof(int) * 1000);
    for (int i=0;i<100;i++){
        *(balance+i) = 0;
    }
    int menu = 0;
    int answer,answer2;
    while (menu != 4) {
        printf("==menu==\n");
        printf("1. 입금\n");
        printf("2. 출금\n");
        printf("3. 송금\n");
        printf("4. 끝내기\n");
        scanf("%d", &menu);
        if (menu == 1) {
            answer = idcheck();
            if (answer != 0) {
                printf("얼마를 입금?: ");
                scanf("%d", &answer2);
                add(balance,answer,answer2);
                printf("현재 ID %d에서의 보유 잔고: %d\n", answer, * (balance +(answer-1)));
            }
        }
        else if (menu == 2) {
            answer = idcheck();
            if (answer != 0) {
                printf("얼마를 출금?: ");
                scanf("%d", &answer2);
                int result = subtract(balance,answer,answer2);
                if (result == 1)
                    printf("현재 ID %d에서의 보유 잔고: %d\n", answer, * (balance +(answer-1)));
                else if (result == 0)
                    printf("잔고가 부족합니다.\n");
            }
            
        }
        else if (menu == 3) {
            int giver, thankyou;
            printf("송금할 ID: ");
            scanf("%d", &giver);
            if ((giver-1) / 1000 != 0){
                printf("잘못된 ID\n");
            }
            else {
                printf("송금받을 ID: ");
                scanf("%d", &thankyou);
                if ((thankyou-1) / 1000 != 0){
                    printf("잘못된 ID\n");
                }
                else {
                    printf("얼마를 송금?: ");
                    scanf("%d", &answer);
                    int result = givemoney(balance,giver,thankyou,answer);
                    if (result == 1)
                        printf("현재 ID %d에서의 보유 잔고: %d\n현재 ID %d에서의 보유 잔고: %d\n", giver, * (balance +(giver-1)),thankyou, * (balance +(thankyou-1)));
                    else if (result == 0)
                        printf("잔고가 부족합니다.\n");
                }
            }
            
        }
    }
    printf("서비스를 이용해 주셔서 감사합니다.");
}

void add(int * balance, int answer, int a) {
    * (balance +(answer-1))+= a;
}
int subtract(int * balance, int answer, int a) {
    if (*(balance +(answer-1)) - a >= 0) {
        *(balance +(answer-1)) -= a;
        return 1;
    }
    else {
        return 0;
    }
}
int givemoney(int * balance, int giver, int thankyou, int a) {
    if (*(balance +(giver-1)) - a >= 0) {
        *(balance +(giver-1)) -= a;
        *(balance +(thankyou-1)) += a;
        return 1;
    }
    else {
        return 0;
    }
}
int idcheck() {
    int answer;
    printf("ID: ");
    scanf("%d", &answer);
    if ((answer-1) / 1000 != 0){
        printf("잘못된 ID\n");
        return 0;
    }
    else
        return answer;
}
