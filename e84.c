//いろんな使う関数の宣言
#include <stdio.h>
#include <math.h>
#include <stdlib.h>	//rand()関数を使用するために必要なヘッダファイル
#include <time.h>

//記号定数
#define ndim 100000
#define nsml 5

int iniran()
{
    int ti;
    ti = time(NULL);
    srand(ti);
    return ti;
}

float uniran()
{
    float x, x1, x2;
    x1 = rand();	//rand()…乱数を発生させる関数
    x2 = RAND_MAX;
    x = x1 / x2;
    return x;
}

int biran(float p)
{
    int bb;
    bb = 0;
    if(uniran() < p)
    {      
    bb = 1;
    }
    return bb;
}

int biflip(int bi, float p){
    int bb;
    bb = bi;
  if(uniran() < p){
    bb = abs(1 - bb);	//abs関数…絶対値を取果
  }
return bb; }

int upst(float st[])
{
  st[0] = 1;
  st[1] = 0;
return 0;
}

int dwst(float st[])
{
  st[0] = 0;
  st[1] = 1;
return 0;
}

int rist(float st[])
{
  float tw;
  tw = (float)1.0 / (float)sqrt(2.0);
  st[0] = tw;
  st[1] = tw;
   return 0; 
}

int lfst(float st[])
{
  float tw;
  tw = (float)1.0 / (float)sqrt(2.0);
  st[0] = tw;
  st[1] = - tw;
    return 0;
}

int getwv(float st[], int code, int basis)
{
  if(basis == 0)
  {
    if(code == 0)
    {
      upst(st);
    }else dwst(st);
   }else
   {
    if(code == 0)
    {
    rist(st);
    }else lfst(st);
    }
   return 0;
}

float ampl(float st1[], float st2[])
{
  float am;
  int i;
  am = 0;
  for(i=0;i<2;i++)
  {
    am = am + (st1[i] * st2[i]);
  }
return am;
}

int cpst(float st1[], float st2[])
{
int i;
  for(i=0;i<2;i++)
  {
    st2[i] = st1[i];
  } 
  return 0;
}

int wrtpsi(float st1[], int ki)
{
int i;
  printf("%4d ", ki);
  //for(i=0;i<(ki - 1) * 12;i++)	//ここは必要なくね?
  //{
   // printf("  ");
 // }
  printf("  |ps%1d>=", ki);
  for(i=0;i<2;i++)
  {
    printf("+%5.3f|%1d>", st1[i], i);
  }
  printf("\n");
return 0;
}

int clpwf(int ibas, int icod, float amp, float wff[])
{
  int idrc;
  idrc = biflip(icod, 1 - (amp * amp));
  getwv(wff, idrc, ibas);
  return idrc;
}






//Main Program

int main()
{
  int i, nn, bi;
  int cnt=0;
  float p, pf, rf, tt;					//p:	pf:確率密度関数		rf:ノイズ混入率		exev:盗聴者のあり/なし
  static int stoa[ndim], stob[ndim], stoe[ndim];
  static int dica[ndim], dicb[ndim], dice[ndim];
  static char icci[ndim];
  int exev;
  float wfa[nsml], wfb[nsml], wfe[nsml];
  float am, tw, th;
  float rs, rsc, rud, rrl;
  int ns, nsc, nud, nrl, nuu, nrr;

  iniran();
  {
    printf("試行回数 : ");
    scanf("%d", &nn);

    p = 0.5;
    pf = (float)0.2;
    printf("Enter random flip prob.pf :");  //確率密度関数?
    scanf("%f", &pf);
    printf("ノイズの混入率 :"); 
    scanf("%f", &rf);
    printf(" BB84 Cryptography simulator\n");
    printf(" 盗聴者有り or 盗聴者無し (1/0)?");
    scanf("%d", &exev);

    for(i=0;i<nn;i++)	//試行回数の分だけなぜかicciを呼び出し
    {
      icci[i] = ' ' ;
    }

    for(i=0;i<nn;i++)
    {
      stoa[i] = biran(p);	//アリスの観測の基底？
    }
    
    for(i=0;i<nn;i++)
    {
    stob[i] = 0;		//ボブの観測の基底？->アリスの方で乱数処理によるから0で指定してる？ 
    }

    for(i=0;i<nn;i++)
    {
      dica[i] = biran(p);	//アリスのビットの結果?
    }

    for(i=0;i<nn;i++)
    {
      dicb[i] = biran(p);	//ボブのビットの結果？
    }

    for(i=0;i<nn;i++)
    {
    stoe[i] = 0;		//イブの観測の基底？
    }

    for(i=0;i<nn;i++)
    {
    dice[i] = biran(p);		//イブのビットの結果?
    }

    printf(" Alice \n");

    for(i=0;i<nn;i++)
    {
    printf("%2d(%1d)", stoa[i], dica[i]);
   // if(i%30==29)		//ここはなくてもかわらん
   // {
    //    printf("\n");
  //  }
    }
    printf("\n  Bob \n");

    for(i=0;i<nn;i++){
//– 23 –
      printf("%2d(%1d)", stob[i], dicb[i]);
 //     if(i%30 == 29)		//ここはなくてもかわらん
  //    {
    //    printf("\n");
     // }
}
    if(exev != 0)		//盗聴者eveがいる場合実行
    {
      printf("\n  Eve \n");
      for(i=0;i<nn;i++)
      {
        printf("%2d(%1d)", stoe[i], dice[i]);
        if(i%30 == 29)
        {
          printf("\n");
        }
      }   
    }
   printf("\n");

    for(i=0;i<nn;i++)
    {
      printf("\n%dnd try  Alice%2d(%1d) Bob%2d(%1d)", i+1,
               stoa[i], dica[i], stob[i], dicb[i]);
      if(dica[i] == dicb[i])
      {
        icci[i]='*';		//これはなんですの？
      }
      if(dica[i] == dicb[i])
      {
        printf(" data shared *****\n");
      }else printf("\n");
      
      getwv(wfa, stoa[i], dica[i]);	//アリスのwfaの値が決定
      getwv(wfb, stob[i], dicb[i]);	//ボブの
      getwv(wfe, stoe[i], dice[i]);	//イブの
      
      if(exev == 0)
      {
        am = ampl(wfa, wfb);
        wrtpsi(wfa, 1);
        wrtpsi(wfb, 3);
        printf(" <b|a>=%4.2f Bob%2d(%1d)", am, stob[i], dicb[i]);
        stob[i] = clpwf(dicb[i], stob[i], am, wfb);
        stob[i] = biflip(stob[i], rf);
        printf("->%1d(%1d)\n", stob[i], dicb[i]);
      }

      if(exev != 0) {
        am = ampl(wfa, wfe);
        wrtpsi(wfa, 1);
        wrtpsi(wfe, 2);
    	printf(" <e|a>=%4.2f Eve%2d(%1d)", am, stoe[i], dice[i]);
//– 24 –
	    stoe[i] = clpwf(dice[i], stoe[i], am, wfe);
	    am = ampl(wfe, wfb);
	    printf("->%1d(%1d)\n", stoe[i], dice[i]);

	    wrtpsi(wfe, 2);
	    wrtpsi(wfb, 3);

	    printf(" <b|e>=%4.2f Bob%2d(%1d)", am, stob[i], dicb[i]);
	    stob[i] = clpwf(dicb[i], stob[i], am, wfb);
	    stob[i] = biflip(stob[i], rf);
	    printf("->%1d(%1d)\n", stob[i], dicb[i]);
       }
     wrtpsi(wfb, 3);		//ノイズが入ったら変わるんじゃね？
}

printf("\n");
printf("BB84 Communication summary \n\n");

printf("A ");
for(i=0;i<nn;i++)
{
  printf("%2d(%1d)", stoa[i], dica[i]);
  if(i%30==29)
  {
    printf("\n");
  }
}

printf("\nB ");
for(i=0;i<nn;i++)
{
  printf("%2d(%1d)", stob[i], dicb[i]);
  if(i%30==29)
  {
    printf("\n");
  }
}
printf("\n  ");
for(i=0;i<nn;i++)
{
  printf(" %1c",icci[i]);
  if(i%30==29)
  {
    printf("\n");
  }
}
if(exev != 0)
{
  printf("\nE ");
  for(i=0;i<nn;i++)
  {
    printf("%2d(%1d)", stoe[i], dice[i]);
    if(i%30==29)
    {
      printf("\n");
    }
//– 25 –
  }
}

printf("\n");
ns = 0;
nsc = 0;
rs = 0.0;
rsc = 0.0;
for(i=0;i<nn;i++)
{
  if(dica[i]==dicb[i])				//基底が同じ場合
    {
    ns++;
    }
  if(dica[i]==dicb[i] && stoa[i]==stob[i])	//基底と結果が同じ場合
    {
    nsc += 1;
    }
}

rs = (float)(1.0 * ns) / (float)(1.0 * nn);
rsc = (float)(1.0 * nsc) / (float)(1.0 * nn);

printf("基底の一致率 %f(%d/%d)\n",rs,ns,nn);
printf("鍵の一致率   %f(%d/%d)\n",rsc,nsc,nn); 
printf("鍵の一致率 / 基底の一致率%f(%d/%d)\n",(rsc/rs),nsc,ns); 
printf("ノイズの混入率 %8.5f \n",(rf*100));
}
}
