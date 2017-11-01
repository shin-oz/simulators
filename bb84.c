//bb84 sim  by chanou

#include <stdio.h>
#include <stdlib.h>	//rand()を内蔵
#include <time.h>	//time()を内蔵->ビット乱数生成に用いる

int ran(void);
int noi(void);
int obs(int x,int y);
int sum(int x,int y);

/*
 * 基底 |  0  |  1  | 
 * +(0) |  1  | -1  |
 * ×(1) |  2  | -2  |
*/

int up = 1;		//オブサーバルビット：0　観測基底：0(直線基底)
int down = -1;		//オブサーバルビット：1　観測基底：0(直線基底)
int slant_up = 2;	//オブサーバルビット：0　観測基底：1(対角基底)
int slant_down= -2;	//オブサーバルビット：1　観測基底：1(対角基底)
int noise;	//ノイズにより壊れたとき

//Main Program
int main(void){
	int i;
	//試行回数
	int try;
	//ノイズの混入率
	int noi_rate;
	//Eveの有り/無し
	int ex_ev;
	
	//確率密度関数

	while(1){
		//試行回数：一回ビットを送り測定->そもそもtryで試行回数はおかしい->alceが送るqビットの数（=bobがそくていする回数）
		printf("-試行回数を入力： ");		//stdio.h
		scanf("%d",&try);			//stdio.h
		if(0<try){
			break;
		}
		printf("入力値エラー\n");
	}
	//ノイズがある場合、ノイズの混入率だけAliceのbitが変わる
	while(1){
		printf("-ノイズの混入率を入力(整数)： "); //50を越えると四捨五入ですべてになる
		scanf("%d",&noi_rate);
		if((0<=noi_rate)&&(noi_rate<=100)){
			break;
		}
		printf("入力値エラー\n");
	}
/*
	while(1){
		printf("-盗聴者有り or 盗聴者無しを選択 (1/0)： ");
		scanf("%d",&ex_ev);
		if((ex_ev==0)||(ex_ev==1)){
			break;
		}
		printf("入力値エラー\n");
	}
*/
	ex_ev=0;
	
	//基底
	int ali_basis[try];
	int bob_basis[try];
	int eve_basis[try];

	//ビット情報
	int ali_bit[try];
	int bob_bit[try];
	int eve_bit[try];

	//偏光
	int ali_polar[try];
	int bob_polar[try];
	int eve_polar[try];

	printf("-----BB84 Cryptography Simulator-----\n");
	//アリスの送る光子の基底
	for(i=0;i<try;i++){
		ali_basis[i] = ran();
	}
	//アリスの送るビット情報
	for(i=0;i<try;i++){
		ali_bit[i] = ran();
	}
	//アリスの送る光子の偏光
	for(i=0;i<try;i++){
		ali_polar[i] = obs(ali_bit[i],ali_basis[i]);
	}
	//ボブの測定の基底
	for(i=0;i<try;i++){
		bob_basis[i] = ran();
	}
	//ボブの得る光子のビット情報
	if(noi_rate==0){//ノイズ無しの場合
		for(i=0;i<try;i++){
			bob_bit[i] = ali_bit[i];
		}
	}else{//ノイズ有りの場合
		for(i=0;i<try;i++)
			if(i%(100/noi_rate)==(100/noi_rate-1)){//ここを改善したい
				noise = noi();
				bob_bit[i] = noise;		//ノイズにより壊れたとき
			}else{
				bob_bit[i] = ali_bit[i];
			}
		}
	
	//ボブの測定する光子の偏光->アリスのビットをボブの基底で測定
	for(i=0;i<try;i++){
		bob_polar[i] = obs(bob_bit[i],bob_basis[i]);
	}

	//Summry
	printf("\tSummry\n");
	//Alice
	printf("Alice -bit-\t");
	for(i=0;i<try;i++){
		printf("%3d",ali_bit[i]);
	}
	printf("\n");
	printf("Aliec -basis-\t");
	for(i=0;i<try;i++){
		printf("%3d",ali_basis[i]);
	}
	printf("\n");
	printf("Alice -polar-\t");
	for(i=0;i<try;i++){
		printf("%3d",ali_polar[i]);
	}
	printf("\n");
	//Bob
	printf("Bob -bit-\t");
	for(i=0;i<try;i++){
		if(bob_bit[i]==noise){	//ノイズにより壊れたとき
			printf("  X");
		}else{
			printf("%3d",bob_bit[i]);
		}
	}
	printf("\n");
	printf("Bob -basis-\t");
	for(i=0;i<try;i++){
		printf("%3d",bob_basis[i]);
	}
	printf("\n");
	printf("Bob -polar-\t");
	for(i=0;i<try;i++){
		if(bob_polar[i]==noise){	//ノイズにより壊れたとき
			printf("  X");
		}else{
			printf("%3d",bob_polar[i]);
		}
	}
	printf("\n");
	printf("----------------");
	for(i=0;i<try;i++){
		printf("---");
	}
	printf("\n");
	//shared
	printf("shared\t\t");
	for(i=0;i<try;i++){
		if((ali_basis[i]==bob_basis[i])&&(ali_polar[i]==bob_polar[i])){
			printf("  *");
		}else{
			printf("   ");
		}
	}
	printf("\n");

	//Common Key
	printf("\tCommon Key\n");
	for(i=0;i<try;i++){
		if((ali_basis[i]==bob_basis[i])&&(ali_polar[i]==bob_polar[i])){
			printf("%3d",ali_bit[i]);
		}	
	}
	printf("\n");
	
	//Resurt
	printf("\tResult\n");
	int success,success_basis;
	int numerator,denominator;
	//成功率
	for(i=0;i<try;i++){
		if(ali_basis[i]==bob_basis[i]){
			success += sum(ali_polar[i],bob_polar[i]);
		}
	}
	numerator = success;
	denominator = try;
	printf("成功率\t\t\t\t%3.2f\n",(float)numerator/(float)denominator);
	//基底の一致率
	for(i=0;i<try;i++){
		success_basis += sum(ali_basis[i],bob_basis[i]);
	}
	numerator = success_basis;
	denominator = try;
	printf("基底の一致率\t\t\t%3.2f\n",(float)numerator/(float)denominator);
	//成功率/基底の一致率
	numerator = success;
	denominator = success_basis;
	printf("成功率/基底の一致率\t\t%3.2f\n",(float)numerator/(float)denominator);
	//ノイズの混入率
	numerator = noi_rate;
	denominator = 100;
	if(noi_rate!=0){
		printf("(ノイズの混入率\t\t\t%3.2f)\n",(float)numerator/(float)denominator);
	}
	printf("\n");

	return 0;
}











//ビット乱数生成関数…時間で初期化しなくて良いらしい
int ran(void){
	//srand((unsigned)time(NULL));   //乱数の初期化を実行時間を元に実行
	int a = rand() % 2;       //代入時に強制的にキャスト変

	return a;
}

//ビット破損関数
int noi(void){
	int a = 9;
	return a;
}
//光子観測関数
int obs(int x, int y){	//第1引数：オブサーバル,第2引数：観測基底,戻り値：観測結果
	int a;
	if(x==0){
		if(y==0){	//オブサーバルビット：0　観測基底：0(直線基底)
			a = up;
		}else{		//オブサーバルビット：0　観測基底：1(対角基底)
			a = slant_up;
		}
	}else if(x==1){
		if(y==0){	//オブサーバルビット：1　観測基底：0(直線基底)
			a = down;
		}else{		//オブサーバルビット：1　観測基底：1(対角基底)
			a = slant_down;
		}
	}else{//ノイズにより情報が失われた
		a = noise;
	}
	return a;
}

//率算出関数
int sum(int x, int y){
	if(x==y){
		return 1;
	}
	return 0;
}
