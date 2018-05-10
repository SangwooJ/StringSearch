#include <stdio.h>
#define max_length 1000
/* 
1. enter  
질문? : 1000입력 후 바뀌었을때 1000초과시
? : 특수문자 예외처리 여부
*/

int getLength(char a[]) {
	//문자열의 길이를 반환
	int i = 0;
	while (a[i++] != '\n');
	return i - 1;
}

int search(char main[], char given[], int point) {
	//point 시점부터 검색한다	못찾을경우: return -1 찾을경우: return 끝위치
	int i = 0;
	int j = 0;
	int k = 0;
	for (i = point; i < getLength(main); i++) { 
		for (j = 0, k=i; given[j] == main[k]; k++,j++) { //첫번째원소부터 일치하는지 
			if (j == getLength(given)-1) //given의 모든원소와 일치하는지
				return k;
		}
	}
	return -1;
}

void swap(char main[], char given[], char change[], int point, int temp[]) {
	//point는 search로부터 가져옴(끝위치)
	int i = 0;
	int j = 0;
	int main_end_point = getLength(main) - 1; //main의 끝지점
	int end_point = point; //바꿀끝지점
	int start_point = end_point - getLength(given) + 1; //바꿀시작지점
	int difference=0; //given과 change의 길이차이
	int move_start_point = 0; //옮기기 시작할지점
	if (getLength(change) < getLength(given)) {
		difference = getLength(given) - getLength(change);
		for (i = 0; i < getLength(change); i++) { //교체
			main[start_point] = change[i];
			start_point++;
		}
		start_point = end_point - getLength(given) + 1; //start point 초기화
		move_start_point = end_point - difference + 1;

		for (j = move_start_point; j < main_end_point + 1; j++) { //앞으로당기기
			main[j] = main[j + difference];
		}
		temp[0] = end_point - difference + 1;
		
	}
	else if(getLength(change) == getLength(given)){
		for (i = 0; i < getLength(change); i++) { //교체
			main[start_point] = change[i];
			start_point++;
		}
		start_point = end_point - getLength(given) + 1; //start point 초기화
		temp[0] = end_point + 1;
	}
	else {
		difference = getLength(change) - getLength(given);
		for (j = main_end_point+1; j >= end_point + 1; j--) { //뒤로밀기
			main[j+difference] = main[j];
		}
		for (i = 0; i < getLength(change); i++) { //교체
			main[start_point] = change[i];
			start_point++;
		}
		temp[0] = end_point + difference + 1;

	}
}

int main(void) {

	int i=0;

	char main[max_length]; //메인 문자열
	char given[max_length]; //교체할 부분 기존 문자열
	char change[max_length]; //교체할 문자열

	int main_point = -1;
	int temp[1]; // 최근 수정위치 기억
	temp[0] = 0;


	//메인 문자열 입력
	while ((main[i++] = getchar()) != '\n');
	if (main[0] == '0') {
		return 0;
	}
	
	while (1) {
		i = 0;
		temp[0] = 0;
		//교체할 문자열 입력 
		while ((given[i++] = getchar()) != '\n');
		if (given[0] == '0') {
			return 0;
		}
		//교체하는 문자열 입력
		i = 0;
		while ((change[i++] = getchar()) != '\n'); 
		if (change[0] == '0') {
			return 0;
		}
		//일치시 교환할거 여러개일경우 최근수정위치 기억해서 그부분부터 반복검색
		while (search(main, given, temp[0]) != -1)
		{
			swap(main, given, change, search(main, given, temp[0]),temp);
		}	
		for (i = 0; main[i] != '\n'; i++) {
			printf("%c", main[i]);
		}
		printf("\n");
	}
	/*
	디버깅
	for (i = 0; main[i]!= '\n'; i++){
	printf("%c", main[i]);
	}
	printf("\n");
	*/
}
