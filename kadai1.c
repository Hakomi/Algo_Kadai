#include <stdio.h>

int main(void){
	int a,b,c,d,f;
	int max,second;
	printf("b1015118  Sato Taro\n");
	printf("Value of a:");scanf("%d",&a);
	printf("Value of b:");scanf("%d",&b);
	printf("Value of c:");scanf("%d",&c);
	printf("Value of d:");scanf("%d",&d);
	printf("Value of f:");scanf("%d",&f);
	max = a;
	second = a;
	if(b > max) {
	second = max;
	max = b;
	}
	if(c > max) {
	second = max;
	max = c;
	}
	if(d > max) {
	second = max;
	max = d;
	}
	if(f > max) {
	second = max;
	max = f;
	}
	if(max = second){
		if(max = b){
			second=c;
			if(d>c)second=d;
			if(f>d)second=f;
		}
		if(max = c){
			second=b;
			if(b>d)second=d;
			if(d>f)second=f;
		}
		if(max = d){
			second=b;
			if(c>b)second=c;
			if(f>c)second=f;
		}
		if(max = f){
			second=b;
			if(c>b)second=c;
			if(d>c)second=d;
		}
	}
	printf("2nd Maximum : %d\n",second);
	return(0);
}