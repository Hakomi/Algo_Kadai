#include  <stdio.h> 
#include  <string.h> 
#include  <stdlib.h> 
#include  <limits.h>
#define   String_Max  80  
/*--- 文字列型スタックを実現する構造体 ---*/ typedef struct{
   int  max;   /* スタックの容量 */   
   int  ptr;   /* スタックポインタ */   
   char **stk; /* スタック本体(char* へのポインタ配列 )*/ 
} StringsStack;  

/*--- スタックの初期化 ---*/ 
int Initialize(StringsStack *s, int max){
  	s->ptr = 0;  

  	if ((s->stk = calloc(max, sizeof(char *))) == NULL) {     
  		s->max = 0;  /* char* の配列の確保に失敗 */     
  	return -1;   
  	}
  	
  	/* char* の配列の確保に成功 */   
  	s->max = max;   
  	return 0; 
}

/*--- スタックの後始末 ---*/ 
void Terminate(StringsStack *s){
    if (s->stk != NULL){     
    	while( --s->ptr >= 0)        
    		free(s->stk[s->ptr]); /* 動的な文字列保存用配列を解放 */     
    		free(s->stk);   
    	}   
    	s->max = s->ptr = 0; 
    }  
/*--- スタックにデータをプッシュ ---*/ int Push(StringsStack *s, char *x){   
	if (s->ptr >= s->max) 
		return -1; /* スタック満杯 */   
	if ((s->stk[s->ptr] = calloc(strlen(x)+1, sizeof(char))) == NULL)     /* データをコピーするための動的な文字列保存用配列を確保することに失敗 */     
		return -1;   
	strcpy(s->stk[s->ptr], x);   
	s->ptr++;   
	return 0; 
}  

/*--- スタックからデータをポップ ---*/ int Pop(StringsStack *s, char *x){   
	if (s->ptr <= 0) 
		return -1; /* スタックは空 */   
	s->ptr--;   
	strcpy(x, s->stk[s->ptr]);   
	free(s->stk[s->ptr]); /* ポップしたので，動的な文字列保存用配列を解放 */   
	return 0; 
	} 

/*--- スタックからデータをピーク ---*/int Peek(StringsStack *s, char *x){
 	if (s->ptr <= 0) 
 		return -1;   
 	strcpy(x, s->stk[s->ptr - 1]);   
 		return 0; 
 }  

/*--- スタックの容量 ---*/int Capacity(const StringsStack *s){   
 	return s->max; 
 }

/*--- スタックに積まれているデータ数 ---*/ int Size(const StringsStack *s){   
 	return s->ptr;
}

/*--- スタックの全データの表示 ---*/ void Print(const StringsStack *s){   
	int i;      
	for(i = 0; i < s->ptr; i++)     
		printf("%s\n", s->stk[i]); 
}  

int main(void){   
	StringsStack s;   
	int max;  
	
	printf("スタックの大きさを入力してください");
	scanf("%d", &max);  
  	if (Initialize(&s, max)==-1){      
  		puts("スタックの生成に失敗しました．\n");     
  		return 1;   
  	}  
  	while (1) {     
  		int  menu;     
  		char x[String_Max];  
    	printf("現在のデータ数：%d/%d\n",Size(&s), Capacity(&s));     
    	printf("(1)プッシュ (2)ポップ (3)ピーク (4)表示 (0)終了：");     
    	scanf("%d", &menu);  
    	if (menu == 0) break;          
    	switch (menu) {      
    	case 1: /* プッシュ */        
    		printf("プッシュする文字列：");        
    		scanf("%s", x);        
    		if (Push(&s, x) == -1)           
    			puts("\a エラー：プッシュに失敗しました．\n");        
    		break;      
    	case 2: /* ポップ */        
    		if (Pop(&s, x) == -1)           
    			puts("\a エラー：ポップに失敗しました．\n");        
    		else{            
    			printf("ポップした文字列は%s，", x);        
    		}        
    		break;      
    	case 3: /* ピーク */        
    		if (Peek(&s, x) == -1)
    			puts("\a エラー：ピークに失敗しました．\n");
			else{
				printf("ピークした文字列は%s，", x);
			}
			break;
		case 4: /* 表示 */
			Print(&s);
			break;
		}
	}
	Terminate(&s);
	return 0;
}


int Search(StringsStack *s , char *x)  {
  int stk_len = Size(s);
  for (int i = 0; i < stk_len; i++){
    if(bm_text_match(x,s[i]->stk[i])!=NULL){
      return bm_text_match(x,s[i]->stk[i]);
    }
    return 0;
  }
}

char* bm_text_match(char *pat , char *txt){
    char  *pt;   /* txt をなぞるカーソル */   
    char  *pp;   /* pat をなぞるカーソル */ 
  
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
          return pt;
        }       
        pp--;       
        pt--;     
      }     
      pt += (skip[*pt]> strlen(pp)) ? skip[*pt] : strlen(pp);   
    }
    
    return NULL;
    
}