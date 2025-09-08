#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORDS 100
#define MAXLEN 30

int main() {
    char* words[MAXWORDS];
    int n;
    scanf("%d", &n);

    char buf[MAXLEN];

    for (int i = 0; i < n; i++) {
        // 방법 1 : words가 초기화 되지 않음
        // scanf("%s", words[i]);
        //
        // 방법 2 : 입력을 받을 때 마다 buf의 내용이 바뀜 -> words[i]가 모두 같은 값(마지막 입력값)을 가짐
        // scanf("%s", buf);
        // words[i] = buf;
        //
        // 방법 3 : words가 초기화 되지 않음 + 해당 위치에 strcpy -> 런타임 에러
        // scanf("%s", buf);
        // strcpy(words[i], buf);

        // 해결
        scanf("%s", buf);
        words[i] = (char*)malloc(MAXLEN * sizeof(char));
        strcpy(words[i], buf);
    }

    // 결과 출력
    for (int j = 0; j < n; j++) {
        printf("%s\n", words[j]);
    }

    // 메모리 해제
    for (int k = 0; k < n; k++) {
        free(words[k]);
    }

    return 0;
}