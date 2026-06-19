#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#define MAXWORDS 100
#define MAXLEN 30

int main() {
    char* words[MAXWORDS];
    int n;
    scanf("%d", &n);

    char buf[MAXLEN];

    for (int i = 0; i < n; i++) {
        // 방법 1
        // // scanf("%s", words[i]);
        // 
        // -> words는 아무런 메모리도 할당받지 않은, 초기화되지 않은 포인터
        // -> 어디에 입력값을 저장해야할 지 모름
        // -> 런타임 에러

        // 방법 2
        // scanf("%s", buf);
        // words[i] = buf;
        // 
        // buf는 고정된 배열
        // -> 입력을 받을 때 마다 buf의 내용이 바뀜
        // -> words[i]가 모두 같은 값(마지막 입력값)을 가짐

        // 방법 3
        // scanf("%s", buf);
        // strcpy(words[i], buf);
        //
        // -> words는 아무런 메모리도 할당받지 않은, 초기화되지 않은 포인터
        // -> 해당 위치에 복사 시도
        // -> 런타임 에러

        // 해결 : buf의 내용을 복사한 뒤, 새로운 복제 배열을 할당
        // strdup : 주어진 문자열을 새로운 메모리 공간에 복사 / 복사된 문자열은 동적으로 할당되며, 원본 문자열과 동일한 값을 가짐
        scanf("%s", buf);
        words[i] = _strdup(buf);
    }

    // 결과 출력
    for (int j = 0; j < n; j++) {
        printf("%s\n", words[j]);
    }

	// 동적 메모리 해제
    for (int k = 0; k < n; k++) {
        free(words[k]);
    }

    return 0;
}