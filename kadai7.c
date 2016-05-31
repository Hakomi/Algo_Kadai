#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {/*--- キューを実現する構造体 ---*/
 int max; /* キューの容量 */
 int num; /* 現在の要素数 */
 int front;/* 先頭要素カーソル */
 int rear; /* 末尾要素カーソル */
 int *que; /* キュー本体（の先頭要素へのポインタ） */
} IntQueue;

typedef struct {/*--- キューを実現する構造体 ---*/
 int max; /* キューの容量 */
 int num; /* 現在の要素数 */
 int front;/* 先頭要素カーソル */
 int rear; /* 末尾要素カーソル */
 char **que; /* キュー本体（の先頭要素へのポインタ） */
} StringQueue;

int bm_text_match(char *pat , char *txt){
   	char  *pt;   /* txt をなぞるカーソル */   
   	char  *pp;   /* pat をなぞるカーソル */ 
	int  count=0;  
   	int  txt_len = strlen(txt); /* txt の文字数 */   
   	int  pat_len = strlen(pat); /* pat の文字数 */   
   	int  skip[UCHAR_MAX + 1]; /* スキップテーブル */   
	int  i;
    char *a = txt;/* txtの先頭 */
    char *b = txt + txt_len - 1;/* txt の末尾(\0ではない) */

	for (i = 0; i <= UCHAR_MAX; i++){ /* スキップテーブルの作成 */     
		skip[i] = pat_len;
	}
	for (pp = pat; *pp != '\0'; pp++){
		skip[*pp] =  strlen(pp) - 1;
	}

	skip[*(pp - 1)] = pat_len;  /* パターンの最後文字の移動距離はパターンの文字数 */  
  	pt = txt + pat_len - 1;       /* pat の末尾と比較する txt の文字を決定 */   

	  	while ( pt < txt + txt_len) { /* txt の比較する文字の位置が txt の末尾を越えるまで */     
	  		pp = pat + pat_len - 1; /* pat の最後の文字に着目 */     
	while (*pt == *pp) {       
		if (pp == pat){ 
			count++;
			break;
		}       
		pp--;       
		pt--;     
	}     
	pt += (skip[*pt]> strlen(pp)) ? skip[*pt] : strlen(pp);   
	}

	return count;

}

/*--- キューの初期化 ---*/
int Initialize(StringQueue *q, int max){
	q->num = q->front = q->rear = 0;
	if ((q->que = calloc(max, sizeof(char *))) == NULL) {
 q->max = 0; /* 配列の確保に失敗 */
		return -1;
	}
	q->max = max;
	return 0;
}
/*--- キューの後始末 ---*/
void Terminate(StringQueue *q){
	if (q->que != NULL) {
	free(q->que);/* 配列を解放 */
		q->max = q->num = q->front = q->rear = 0;
	}
}
/*--- キューにデータをエンキュー ---*/
int Enque(StringQueue *q, char *x){
	if (q->num >= q->max){
 		/* キューは満杯 */
 		char **que_o;

 		while(q->front > 0){
 			int i;
 			char *first;
 			
 			first = calloc(strlen(q->que[0])+1, sizeof(char *));
 			strcpy(first,q->que[0]);

			for(i = 1; i < q->max; i++){
		
				q->que[i-1] = calloc(strlen(q->que[i])+1, sizeof(char *));
				strcpy(q->que[i-1], q->que[i]);
		
				}
			
			strcpy(q->que[q->max-1],first); 
			free(first);
			q->front--;
 		}

 		if((que_o = realloc(q->que, (q->max + 8) * sizeof(char *))) == NULL){
 			puts("\a キューの容量の拡張に失敗しました ");
 		}else{
 			q->que = que_o;
 			que_o = NULL;
 			q->rear = q->max;
 			q->max += 8;
	 	}
	}

	q->num++;
	if ((q->que[q->rear] = calloc(strlen(x)+1, sizeof(char *))) == NULL){
		return -1;
	}
	strcpy(q->que[q->rear], x);
	int i;
		
	q->rear++;
		
	if (q->rear == q->max) q->rear = 0;
		return 0;
	
	}

/*--- キューからデータをデキュー ---*/
	int Deque(StringQueue *q, char *x){
		if (q->num <= 0)/* キューは空 */
			return;
		else {
			q->num--;
			strcpy(x, q->que[q->front]);
			free(q->que[q->front]);
			q->front++; 
			if (q->front == q->max) q->front = 0;

			if(q->num < (q->max - 16)){

				while(q->front > 0){
					int i;
					for(i = q->front; i < q->max; i++){
						q->que[i-1] = q->que[i];
					}
					q->front--;
				}

				char **que_i;
 				que_i = realloc(q->que, (q->max -5) * sizeof(char *));
	 			q->que = que_i;
	 			que_i = NULL;
	 			q->front = 0;
	 			q->rear = q->num;
	 			q->max -= 5;
			}

			return 0;
		}
	}

/*--- キューからデータをピーク ---*/
	int Peek(const StringQueue *q, char *x)
	{
		if (q->num <= 0)
			return -1;
 //&x = q->que[q->front];
		return 0;
	}
/*--- キューの容量 ---*/
	int Capacity(const StringQueue *q){
		return (q->max);
	}
/*--- キューに蓄えられているデータ数 ---*/
	int Size(const StringQueue *q){
		return (q->num);
	}
/*--- 全データの表示 ---*/
	void Print(const StringQueue *q){
		int i;

		for(i = 0; i < q->num; i++)
			printf("%s ", q->que[(i + q->front) % q->max]);
		putchar('\n');
	}

	int Count(StringQueue *q, char *pat){
		int result = 0;
		int i;
		for(i = 0; i < (q->rear); i++){
			result += bm_text_match(pat, q->que[i]);

		}
		return result;
	}

	int main(void){
		StringQueue que;

		if (Initialize(&que, 6) == -1) {
			puts("キューの生成に失敗しました。");
			return 1;
		}
		while (1) {
			char x[80];
			int m;

			printf("現在のデータ数：%d/%d\n", Size(&que), Capacity(&que));
			printf("(1) エンキュー (2) デキュー (3) ピーク (4) 表示 (5)パターンの計数 (0) 終了：");
			scanf("%d", &m);

			if (m == 0) break;
			switch(m){
				case 1: printf("データ："); scanf("%s", &x);
				if (Enque(&que, x) == -1)
					puts("\a エラー:データのエンキューに失敗しました。");
				break;
				case 2:
				if (Deque(&que, x) == -1)
					puts("\a エラー:デキューに失敗しました。");
				else
					printf("デキューしたデータは%s です。\n", &x);
				break;
 				case 3: /* ピーク */
				if (Peek(&que, x) == -1)
					puts("\a エラー：ピークに失敗しました。");
				else
					printf("ピークしたデータは%s です。\n", x);
				break;
				case 4: /* 表示 */
				Print(&que);
				break;
				case 5:
				printf("パターン :");
				scanf("%s",&x);
				if(Count(&que, x) > 0){
					printf("結果 : %d\n",Count(&que, x));
				}else{
					printf("パターンは存在しません。\n");
				}
				break;

			}

		}
		Terminate(&que);
		return 0;
	}