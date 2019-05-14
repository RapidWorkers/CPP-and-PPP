#include <stdio.h>

int main() {
	char string[1000001]; //char 배열 1,000,001칸짜리 선언(왜? 마지막 칸 null 문자)
	int count = 0;//띄어쓰기 개수 저장
	int meetSpace = 1;//직전에 글자가 아닌 띄어쓰기를 만났는지?
	//처음에 위 값을 1로 한 이유는 처음의 공백을 무시하기 위해서


	gets(string); //gets는 엔터가 나올때 까지 입력을 받는 함수

	for (int i = 0; string[i] != '\0'; i++) {//널 문자를 만날때 까지 == 끝날때까지
		if (string[i] == ' ' && meetSpace == 0) {//스페이스바를 만났고 이전에 공백이 없었다면
			count++;//단어 개수 증가
			meetSpace = 1;//플래그 설정
		}
		else if (string[i] != ' ') {//만약에 스페이스바가 아니면
			meetSpace = 0;
		}
	}

	if (meetSpace == 0) count++; //공백으로 끝난게 아니라면 마지막 단어를 개수에 추가
	
	printf("%d", count); //결과 출력
}
