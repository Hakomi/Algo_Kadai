/*年内の経過日数を求める*/ #include  <stdio.h>  
/*- 各月の日数 -*/ int mdays[][13] = {
   {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
   {-2, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};
 /*--- 西暦 year 年のカレンダー ---*/ 
int *calendar(int year){
    if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
         return (int *)mdays + 13;
    else
         return (int *)mdays ;
}
 /*--- 西暦 y 年 m 月 d 日の年内の経過日数を求める ---*/
int dayofyear(int y, int m, int d){
    int *i;   int days = d; /* 日数 */
    for (i = calendar(y) + m - 1; *i > 0; i--){  
    	days += *i ; 
	}   
	return (days);
}

int main(void){   
	int year, month, day; /* 年・月・日 */
    int retry;     /* もう一度？ */  
  	do {
        printf("年：");  scanf("%d", &year);
        printf("月：");  scanf("%d", &month);
        printf("日：");  scanf("%d", &day);
        printf("年内で%d 日目です。\n", dayofyear(year, month, day));     
        printf("もう一度しますか（1…はい／0…いいえ）：");     
        scanf("%d", &retry);
    } while (retry == 1);
    return (0); 
} 