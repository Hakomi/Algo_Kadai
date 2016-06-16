
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define String_Max 82

typedef struct{
    int max;
    int ptr;
    char **stk;
}StringStack;

int Initialize(StringStack *s,int max){
	s->ptr = 0;
	s->max = max;
    s->stk = calloc(max,sizeof(char *));
	return 0;
}

int Push(StringStack *s,char *c){
	if(s->ptr >= s->max){
		return -1;
	}
    s->stk[s->ptr] = calloc(strlen(c)+1,sizeof(char));
	strcpy(s->stk[s->ptr],c);
	s->ptr++;
	return 0;
}

int Pop(StringStack *s, char **c){
	if(s->ptr <= 0){
		return -1;
	}
	s->ptr--;
	*c = s->stk[s->ptr];
	return 0;
}
int isEmpty(StringStack *s){
    if(s->ptr > 0){
        return 1;
    }
    return 0;
}


/*--- 真に再帰的な関数 recur3 ---*/
void recur3(char *st){
    StringStack stk;
    Initialize(&stk,100);
    int n;
    Top:
    n = strlen(st);
    if(n > 0){
        Push(&stk,st);
        if(n > 1)st = st + 2;
        else st = st + 1;
        goto Top;
    }
    if(isEmpty(&stk) == 1){
        Pop(&stk,&st);
        printf("%c",*st);
        st = st + 1;
        goto Top;
    }
}


int main(void){
 char x[String_Max];
 printf("文字列をを入力せよ：");
 scanf("%s", x);
 recur3(x);
 printf("\n");
 return (0);
}
