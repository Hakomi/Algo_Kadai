#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <limits.h>
#define MAX 80

typedef struct{
	double vision;
	int height;
}Body;

typedef struct{
	Body body;
	char *name;
}PhysCheck;

typedef struct{
	int max;
	int ptr;
	PhysCheck *stk;
}PhysCheckStack;

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

int Initialize(PhysCheckStack *s,int max){
	s->ptr = 0;
	if((s->stk = calloc(max,sizeof(PhysCheck *))) == NULL){
		s->max = 0;
		return -1;
	}
	s->max = max;
	return 0;
}

int Push(PhysCheckStack *s, PhysCheck p){
	
	if(s->ptr >= s->max){
		return -1;
	}

	s->stk[s->ptr].name = calloc(strlen(p.name)+1,sizeof(char));

	if(s->stk[s->ptr].name == NULL){
		return -1;
	}
	
	strcpy(s->stk[s->ptr].name,p.name);
	s->stk[s->ptr].body = p.body;
	s->ptr++;
	return 0;
}

int Pop(PhysCheckStack *s, PhysCheck *p){
	if(s->ptr <= 0){
		return -1;
	}
	s->ptr--;
	
	//*p = s->stk[s->ptr];
	free(&(s->stk[s->ptr]));
	return 0;
}

int Peek(PhysCheckStack *s, PhysCheck *p){
	if(s->ptr <= 0){
		return -1;
	}
	*p = s->stk[s->ptr-1];
	return 0;
}

int Capacity(const PhysCheckStack *s){
	return s->max;
}

int Size(const PhysCheckStack *s){
	return s->ptr;
}

void Print(const PhysCheckStack *s){
	int i;

	for (i = 0; i < s->ptr; ++i){
		printf("名前 :　%s ", s->stk[i].name);
		printf("視力 :　%1.1lf ", s->stk[i].body.vision);
		printf("身長 :　%d \n", s->stk[i].body.height);
	}
}

int Count(PhysCheckStack *s, char *pat){
	int result = 0;
	int i;
	for(i = 0; i < (s->ptr - 1); i++){
			result += bm_text_match(pat, s->stk[i].name);
		
	}
	return result;
}

void Terminate(PhysCheckStack *s){
	if (s->stk != NULL){
		free(s->stk);
	}
	s->max = s->ptr =0;
}

int Search(PhysCheckStack *s, PhysCheck *p){
	char  *pt;   /* txt をなぞるカーソル */   
   	char  *pp;   /* pat をなぞるカーソル */    
   	int  pat_len = strlen(p->name); /* pat の文字数 */   
   	int  skip[UCHAR_MAX + 1]; /* スキップテーブル */   
    int  i;

	for (i = 0; i <= UCHAR_MAX; i++){ /* スキップテーブルの作成 */     
		skip[i] = pat_len;
	}
	for (pp = p->name; *pp != '\0'; pp++){
		skip[*pp] =  strlen(pp) - 1;
	}
	
	skip[*(pp - 1)] = pat_len;  /* パターンの最後文字の移動距離はパターンの文字数 */  

	for(i = (s->ptr-1); i > -1; i--){
		printf("%s\n",s->stk[i].name);
		int  txt_len = strlen(s->stk[i].name); /* txt の文字数 */ 
	    char *a = s->stk[i].name;/* txtの先頭 */
   	 	char *b = s->stk[i].name + txt_len - 1;/* txt の末尾(\0ではない) */
  		pt = s->stk[i].name + pat_len - 1;       /* pat の末尾と比較する txt の文字を決定 */   

	  	while ( pt < s->stk[i].name + txt_len) { /* txt の比較する文字の位置が txt の末尾を越えるまで */     
	  		pp = p->name + pat_len - 1; /* pat の最後の文字に着目 */     
	  		while (*pt == *pp) {       
	  			if (pp == p->name){ 
	  				return  i;
	  			}       
	  		pp--;       
	  		pt--;     
	  		}     
			pt += (skip[*pt]> strlen(pp)) ? skip[*pt] : strlen(pp);   
	  	}
  	}
  	return -1;
  	
}

int main(void){
	PhysCheckStack s;
	int max;
	char x[MAX];
	printf("スタックの数を入力してね : ");
	scanf("%d",&max);
	Initialize(&s,max);

	while(1){
		int menu;
		PhysCheck p;

		printf("現在のデータ数 : %d/%d \n", Size(&s), Capacity(&s));
		printf("(1) プッシュ (2) ポップ (3) ピーク (4) 表示 (5)計数 (6)探索 (0) 終了 :");
		scanf("%d", &menu);

		if(menu == 0){
			Terminate(&s);
			break;
		}

		switch(menu){
		case 1:
			printf("データ 名前 ：");
			scanf("%s",&x);
			printf("データ 視力 ：");
			scanf("%lf",&p.body.vision);
			printf("データ 身長 ：");
			scanf("%d",&p.body.height);
			
			p.name = x;

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
			scanf("%s",&x);

			p.name = x;
			
			if(Count(&s, p.name) > 0){
				printf("結果 : %d\n",Count(&s, p.name));
			}else{
				printf("パターンは存在しません。\n");
			}
			break;
		case 6:
			printf("パターン :");
			scanf("%s",&x);

			p.name = x;
			
			if(Search(&s, &p) > 0){
				printf("見つかったデータは　名前：%s 視力：%1.2lf 身長：%d です\n",s.stk[Search(&s, &p)].name, s.stk[Search(&s, &p)].body.vision,s.stk[Search(&s, &p)].body.height);
			}else{
				printf("パターンは存在しません。\n");
			}

			break;


		}

	}
	return 0;

}