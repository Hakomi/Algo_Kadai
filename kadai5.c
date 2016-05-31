#include <stdio.h>
#include  <string.h> 
#include  <limits.h>
#define MAX 10

typedef struct{
	double vision;
	int height;
}Body;

typedef struct{
	Body body;
	char name[20];
}PhyCheck;

typedef struct{
	int max;
	int ptr;
	PhyCheck stk[MAX];
}PhyCheckStack;

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

int Initialize(PhyCheckStack *s,int max){
	s->ptr = 0;
	s->max = max;
	return 0;
}

int Push(PhyCheckStack *s, PhyCheck p){
	if(s->ptr >= s->max){
		return -1;
	}
	s->stk[s->ptr] = p;
	s->ptr++;
	return 0;
}

int Pop(PhyCheckStack *s, PhyCheck *p){
	if(s->ptr <= 0){
		return -1;
	}
	s->ptr--;
	*p =s->stk[s->ptr];
	return 0;
}

int Peek(PhyCheckStack *s, PhyCheck *p){
	if(s->ptr <= 0){
		return -1;
	}
	*p = s->stk[s->ptr-1];
	return 0;
}

int Capacity(const PhyCheckStack *s){
	return s->max;
}

int Size(const PhyCheckStack *s){
	return s->ptr;
}

void Print(const PhyCheckStack *s){
	int i;

	for (i = 0; i < s->ptr; ++i){
		printf("名前 :　%s ", s->stk[i].name);
		printf("視力 :　%1.1lf ", s->stk[i].body.vision);
		printf("身長 :　%d \n", s->stk[i].body.height);
	}
}

int Count(PhyCheckStack *s, char *pat){
	int result = 0;
	int i;
	int stk_len = Size(s); 
	for(i = 0; i < stk_len; i++){
			result += bm_text_match(pat,s->stk[i].name);
		
	}
	return result;
}

int main(void){
	PhyCheckStack s;

	Initialize(&s,MAX);

	while(1){
		int menu;
		PhyCheck p;

		printf("現在のデータ数 : %d/%d \n", Size(&s), Capacity(&s));
		printf("(1) プッシュ (2) ポップ (3) ピーク (4) 表示 (5)計数 (0) 終了 :");
		scanf("%d", &menu);

		if(menu == 0){
			break;
		}

		switch(menu){
		case 1:
			printf("データ 名前 ：");
			scanf("%s",&p.name);
			printf("データ 視力 ：");
			scanf("%lf",&p.body.vision);
			printf("データ 身長 ：");
			scanf("%d",&p.body.height);
			if(Push(&s,p) == -1){
				puts("\a エラー : プッシュに失敗しました。");
			}
			break;
		case 2:
			if(Pop(&s,&p) == -1){
				puts("\a エラー : ポップに失敗しました。");
			}else{
				printf("ポップしたデータは 名前： %s 視力： %1.2lf 身長： %dcm です。\n",p.name, p.body.vision, p.body.height);
			}
			break;
		case 3:
			if(Peek(&s,&p) == -1){
				puts("\a エラー : ピークに失敗しました。");
			}else{
				printf("ピークしたデータは 名前： %s 視力： %1.2lf 身長： %dcm です。\n",p.name, p.body.vision, p.body.height);
			}
			break;
		case 4:
			Print(&s);
			break;
		case 5:
			printf("パターン :");
			scanf("%s",&p.name);
			if(Count(&s, p.name) > 0){
				printf("結果 : %d\n",Count(&s, p.name));
			}else{
				printf("パターンは存在しません。\n");
			}

		}

	}
	return 0;

}