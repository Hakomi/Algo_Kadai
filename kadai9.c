
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PHYSCHECK_NAME 1 /* 番号を表す定数値 */
#define PHYSCHECK_VISION 2 /* 氏名を表す定数値 */
#define PHYSCHECK_HEIGHT 4 /* 氏名を表す定数値 */

/*--- 身体データ型 ---*/
typedef struct{
double vision; /* 視力 */
int height; /* 身長 */
}Body ;
/*--- 身体検査データ型 ---*/
typedef struct{
 Body body; /* 身体データ型 ---*/
 char *name; /* 氏名 */
} PhysCheck ;

/*--- ノード ---*/
typedef struct __node {
 PhysCheck data; /* データ */
 struct __node *prev; /* 先行ノードへのポインタ */
 struct __node *next; /* 後続ノードへのポインタ */
} Dnode;
/*--- 循環・重連結リスト ---*/
typedef struct {
 Dnode *head; /* 先頭ダミーノードへのポインタ */
 Dnode *crnt; /* 着目ノードへのポインタ */
} Dlist;
/*--- 会員の氏名の比較関数 ---*/
int PhysCheckNameCmp(const PhysCheck *x, const PhysCheck *y){
 return strcmp(x->name, y->name);
}
/*--- 会員の視力の比較関数 ---*/
int PhysCheckVisionCmp(const PhysCheck *x, const PhysCheck *y){
  return x->body.vision < y->body.vision ? -1 : x->body.vision > y->body.vision ? 1 : 0;
}
/*--- 会員の身長の比較関数 ---*/
int PhysCheckHeightCmp(const PhysCheck *x, const PhysCheck *y){
  return x->body.height < y->body.height ? -1 : x->body.height > y->body.height ? 1 : 0;
}
/*--- 会員データ（氏名と視力と身長）の表示（改行なし）---*/
void PrintPhysCheck(const PhysCheck *x){
 printf("%s %2.3lf %d", x->name, x->body.vision, x->body.height);
}
/*--- 会員データ（氏名と視力と身長）の表示（改行あり）---*/
void PrintLnPhysCheck(const PhysCheck *x){
 printf("%s %2.3lf %d\n", x->name, x->body.vision, x->body.height);
}
/*--- 会員データ（氏名と視力と身長）の読込み ---*/
PhysCheck ScanPhysCheck(const char *message, int sw){
 PhysCheck temp;
 char x[82];

 printf("%s するデータを入力してください。\n", message);
 if (sw & PHYSCHECK_NAME) { printf("氏名："); scanf("%s", x); }
 if (sw & PHYSCHECK_VISION) { printf("視力："); scanf("%lf", &temp.body.vision); }
 if (sw & PHYSCHECK_HEIGHT) { printf("身長："); scanf("%d", &temp.body.height); }
 temp.name = calloc(strlen(x)+1,sizeof(char *));
 strcpy(temp.name,x);

 return temp;
}
/*--- 一つのノードを動的に生成 ---*/
static Dnode *AllocDnode(void){
 return calloc(1, sizeof(Dnode));
}
/*--- ノードの各メンバに値を設定 ----*/
static void SetDnode(Dnode *n, const PhysCheck *x,
 const Dnode *prev, const Dnode *next){
 n->data = *x; /* データ */
 n->prev = (Dnode *) prev; /* 先行ノードへのポインタ */
 n->next = (Dnode *) next; /* 後続ノードへのポインタ */
}
/*--- リストは空か ---*/
static int IsEmpty(const Dlist *list){
 return list->head->next == list->head;
}
/*--- リストを初期化 ---*/
void Initialize(Dlist *list){
 Dnode *dummyNode = AllocDnode(); /* ダミーノードを生成 */
 list->head = list->crnt = dummyNode;
 dummyNode->prev = dummyNode->next = dummyNode;
}
/*--- 着目ノードのデータを表示 ---*/
void PrintCurrent(const Dlist *list){
 if (IsEmpty(list))
 printf("着目要素はありません。");
 else
 PrintPhysCheck(&list->crnt->data);
}
/*--- 着目ノードのデータを表示（改行付き）---*/
void PrintLnCurrent(const Dlist *list){
 PrintCurrent(list);
 putchar('\n');
}
/*--- 関数 compare によって x と一致すると判定されるノードを探索 ---*/
Dnode *Search(Dlist *list, const PhysCheck *x,
 int compare(const PhysCheck *x, const PhysCheck *y)){
 Dnode *ptr = list->head->next;

 while (ptr != list->head) {
 if (compare(&ptr->data, x) == 0) {
 list->crnt = ptr;
 return ptr; /* 探索成功 */
 }
 ptr = ptr->next;
 }
 return NULL; /* 探索失敗 */
}
/*--- 全ノードのデータをリスト順に表示 ---*/
void Print(const Dlist *list){

 if (IsEmpty(list))
 puts("ノードがありません。");
 else {
 Dnode *ptr = list->head->next;

 puts("【一覧表】");
 while (ptr != list->head) {
 PrintLnPhysCheck(&ptr->data);
 ptr = ptr->next; /* 後続ノードに着目 */
 }
 }
}
/*--- p が指すノードの直後にノードを挿入 ---*/
void InsertAfter(Dlist *list, Dnode *p, const PhysCheck *x){
 Dnode *ptr = AllocDnode();
 Dnode *nxt = p->next;

 p->next = p->next->prev = ptr;
 SetDnode(ptr, x, p, nxt);
 list->crnt = ptr; /* 挿入したノードに着目 */
}
/*--- 先頭にノードを挿入 ---*/
void InsertFront(Dlist *list, const PhysCheck *x){
 InsertAfter(list, list->head, x);
}
/*--- 末尾にノードを挿入 ---*/void
InsertRear(Dlist *list, const PhysCheck *x){
 InsertAfter(list, list->head->prev, x);
}
/*--- p が指すノードを削除 ---*/
void Remove(Dlist *list, Dnode *p){
 p->prev->next = p->next;
 p->next->prev = p->prev;
 list->crnt = p->prev; /* 削除したノードの先行ノードに着目 */
 free(p);
 if (list->crnt == list->head)
 list->crnt = list->head->next;
}
/*--- 先頭ノードを削除 ---*/
void RemoveFront(Dlist *list){
 if (!IsEmpty(list))
 Remove(list, list->head->next);
}
/*--- 末尾ノードを削除 ---*/
void RemoveRear(Dlist *list){
 if (!IsEmpty(list))
 Remove(list, list->head->prev);
}
/*--- 着目ノードを削除 ---*/
void RemoveCurrent(Dlist *list){
 if (list->crnt != list->head)
 Remove(list, list->crnt);
}

/*--- 全ノードを削除 ---*/
void Clear(Dlist *list){
 while (!IsEmpty(list)) /* 空になるまで */
 RemoveFront(list); /* 先頭ノードを削除 */
}
/*--- 循環・重連結リストを後始末 ---*/
void Terminate(Dlist *list){
 Clear(list); /* 全ノードを削除 */
 free(list->head); /* ダミーノードを削除 */
}
/*--- メニュー ---*/
typedef enum {
 TERMINATE, INS_FRONT, INS_REAR, RMV_FRONT, RMV_REAR, PRINT_CRNT,
 RMV_CRNT, SRCH_NAME, SRCH_VISION, SRCH_HEIGHT, PRINT_ALL, CLEAR
} Menu;
/*--- メニュー選択 ---*/
Menu SelectMenu(void){
 int i, ch;
 char *mstring[] = {
 "先頭にノードを挿入", "末尾にノードを挿入", "先頭のノードを削除",
 "末尾のノードを削除", "着目ノードを表示", "着目ノードを削除",
 "氏名で探索", "視力で探索", "身長で検索", "全ノードを表示", "全ノードを削除"
 };
 do {
 for (i = TERMINATE; i < CLEAR; i++) {
 printf("(%2d) %-18.18s ", i + 1, mstring[i]);
 if ((i % 3) == 2)
putchar('\n');
 }
 printf("( 0) 終了 ：");
 scanf("%d", &ch);
 } while (ch < TERMINATE || ch > CLEAR);

 return (Menu)ch;
}
/*--- メイン ---*/
int main(void){
 Menu menu;
 Dlist list;
 Initialize(&list); /* 循環・重連結リストの初期化 */
 do {
 int n;
 PhysCheck x;
 PhysCheck *ptr;

 switch (menu = SelectMenu()) {
 case INS_FRONT :/* 先頭にノードを挿入 */
 x = ScanPhysCheck("先頭に挿入", PHYSCHECK_NAME | PHYSCHECK_VISION | PHYSCHECK_HEIGHT);
 InsertFront(&list, &x);
 break;

 case INS_REAR :/* 末尾にノードを挿入 */
 x = ScanPhysCheck("末尾に挿入", PHYSCHECK_NAME | PHYSCHECK_VISION | PHYSCHECK_HEIGHT);
 InsertRear(&list, &x);
 break;
 case RMV_FRONT : /* 先頭ノードを削除 */
 RemoveFront(&list);
 break;
 case RMV_REAR : /* 末尾ノードを削除 */
 RemoveRear(&list);
 break;
 case PRINT_CRNT : /* 着目ノードのデータを表示 */
 PrintLnCurrent(&list);
 break;
 case RMV_CRNT : /* 着目ノードを削除 */
 RemoveCurrent(&list);
 break;
 case SRCH_NAME : /* 番号による探索 */
 x = ScanPhysCheck("探索", PHYSCHECK_NAME);
 if (Search(&list, &x, PhysCheckNameCmp) != NULL)
PrintLnCurrent(&list);
 else
puts("その名前のデータはありません。");
 break;
 case SRCH_VISION : /* 氏名による探索 */
 x = ScanPhysCheck("探索", PHYSCHECK_VISION);
 if (Search(&list, &x, PhysCheckVisionCmp) != NULL)
PrintLnCurrent(&list);
 else
puts("その視力のデータはありません。");
 break;
 case SRCH_HEIGHT : /* 氏名による探索 */
 x = ScanPhysCheck("探索", PHYSCHECK_HEIGHT);
 if (Search(&list, &x, PhysCheckHeightCmp) != NULL)
PrintLnCurrent(&list);
 else
puts("その身長のデータはありません。");
 break;
 case PRINT_ALL : /* 全ノードのデータを表示 */
 Print(&list);
 break;
 case CLEAR : /* 全ノードを削除 */
 Clear(&list);
 break;
 }
 } while (menu != TERMINATE);
 Terminate(&list); /* 循環・重連結リストの後始末 */
 return 0;
}