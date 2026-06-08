#include <stdio.h>
#include <string.h>

#define TASKNUM 100
#define STRSIZE 256

void load(char todos[][STRSIZE], int *count);
void save(char todos[][STRSIZE], int count);
void show(char todos[][STRSIZE], int count);

int main()
{
    char todos[TASKNUM][STRSIZE];
    int count = 0;
    int menu;

    load(todos, &count);

    while (1)
    {
        printf("\n===== TODO =====\n");
        printf("1. 할 일 추가\n");
        printf("2. 목록 보기\n");
        printf("3. 완료 처리\n");
        printf("4. 종료\n");

        printf("선택: ");
        fflush(stdout);
        scanf("%d", &menu);

        while (getchar() != '\n') {}

        if (menu == 1)
        {
            if (count >= TASKNUM)
            {
                printf("더 이상 저장할 수 없습니다.\n");
                continue;
            }

            char input[STRSIZE];

            printf("할 일 입력: ");
            fgets(input, sizeof(input), stdin);

            input[strcspn(input, "\n")] = '\0';

            sprintf(todos[count], "[ ] %s\n", input);
            count++;

            save(todos, count);

            printf("저장되었습니다.\n");
        }

        else if (menu == 2)
            show(todos, count);

        else if (menu == 3)
        {
            int num;
            
            if (count == 0)
            {
                printf("완료할 항목이 없습니다.\n");
                continue;
            }

            show(todos, count);

            printf("완료 처리할 번호: ");
            scanf("%d", &num);

            while (getchar() != '\n') {}

            if (num < 1 || num > count)
            {
                printf("잘못된 번호입니다.\n");
                continue;
            }

            if (todos[num - 1][1] == ' ')
                todos[num - 1][1] = 'x';

            save(todos, count);

            printf("완료 처리되었습니다.\n");
        }

        else if (menu == 4)
        {
            printf("프로그램을 종료합니다.\n");
            break;
        }

        else
            printf("잘못된 메뉴입니다.\n");
    }

    return 0;
}

void load(char todos[][STRSIZE], int *count)
{
    FILE *fp = fopen("todo.txt", "r");

    if (fp == NULL)
        return;

    while (fgets(todos[*count], STRSIZE, fp) != NULL)
        (*count)++;

    fclose(fp);
}

void save(char todos[][STRSIZE], int count)
{
    FILE *fp = fopen("todo.txt", "w");

    if (fp == NULL)
    {
        printf("파일 저장 실패\n");
        return;
    }

    for (int i = 0; i < count; i++)
        fputs(todos[i], fp);

    fclose(fp);
}

void show(char todos[][STRSIZE], int count)
{
    if (count == 0)
    {
        printf("등록된 할 일이 없습니다.\n");
        return;
    }

    for (int i = 0; i < count; i++)
        printf("%d. %s", i + 1, todos[i]);
}