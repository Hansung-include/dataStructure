# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define MAZE_SIZE 6
#define MAX_STACK_SIZE 100

typedef struct {
	short r;
	short c;
} element;
//typedef➡구조체를 새로운 타입으로 선언
//구조체tag : None, element : 새로운 데이터 타입의 이릅 (int, float 뭐 그런것 처럼)
//이 구조체는 두개의 1byte 정수형 데이터를 묶음

typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

// 스택 초기화 함수
void init_stack(StackType* s) {
	s->top = -1;
}

// 공백 상태 검출 함수
int is_empty(StackType* s) {
	return (s->top == -1);
}

// 포화 상태 검출 함수
int is_full(StackType* s) {
	return (s->top == (MAX_STACK_SIZE - 1));
}

// 삽입 함수
void push(StackType* s, element item) {
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}

// 삭제 함수
element pop(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}

// 피크 함수
element peek(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[s->top];
}

element here = { 1, 0 }, entry = { 1, 0 };
//here / entry : 현재 / 입구 위치를 나타내는 구조체 타입의 변수
//즉, here ➡ r=1, c=0 이렇게 두개의 멤버가 정의 됨

char maze[MAZE_SIZE][MAZE_SIZE] = {
	{'1', '1', '1', '1', '1', '1'},
	{'e', '0', '1', '0', '0', '1'},
	{'1', '0', '0', '0', '1', '1'},
	{'1', '0', '1', '0', '1', '1'},
	{'1', '0', '1', '0', '0', 'x'},
	{'1', '1', '1', '1', '1', '1'}
};
//배열 : 동일한 타입의 데이터를 한번에 여러개 만들 때 
// maze : 2차원 문자배열

void push_loc(StackType * s, int r, int c)
//void 는 자료형이 없는 거... 
//int main(void) = int main(void) main함수는 인수를 받을 필요가 없기때문에.. 
{
	if (r < 0 || c < 0) return;
	if (maze[r][c] != '1' && maze[r][c] != '.') {
		element tmp;
		tmp.r = r;
		tmp.c = c;
		push(s, tmp);
		// push가 p.136의 원리를 위해...
	}
}

void maze_print(char maze[MAZE_SIZE][MAZE_SIZE])
{
	printf("\n");
	for (int r = 0; r < MAZE_SIZE; r++) {
		for (int c = 0; c < MAZE_SIZE; c++) {
			printf("%c", maze[r][c]);
		}
		printf("\n");
	}
}

int main(void)
{
	int r, c;
	StackType s;

	init_stack(&s);
	//스택 코드의 s값과 여기서 정의한 s값은 다른 값이다.
	here = entry;
	while (maze[here.r][here.c] != 'x') {
		r = here.r;
		//here구조체 안에 있는 r을 사용?
		c = here.c;
		maze[r][c] = '.';
		maze_print(maze);
		push_loc(&s, r - 1, c);
		push_loc(&s, r + 1, c);
		push_loc(&s, r, c - 1);
		push_loc(&s, r, c + 1);

		if (is_empty(&s)) {
			printf("실패\n");
			return;
		}
		else
			here = pop(&s);
	}
	printf("성공\n");
	return 0;
}