#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define OK 1
typedef int ElemType;
//S盒//个数 行 列
int S[8][4][16] =//S1
 	         {{{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
   	         {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
  	          {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
  	          {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},
  	          //S2
 	           {{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
 	           {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
 	           {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
 	           {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}},
 	           //S3
 	           {{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
 	           {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
   	           {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
 	           {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}},
 	           //S4
 	           {{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
 	           {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
 	           {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
 	           {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}},
 	           //S5
 	           {{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
 	           {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
 	           {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
 	           {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}},
 	           //S6
 	           {{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
 	           {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
 	           {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
 	           {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}},
 	           //S7
 	           {{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
 	           {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
 	           {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
 	           {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}},
 	           //S8
 	           {{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
 	           {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
 	           {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
 	           {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}}};

//对左移次数的规定
int MOVE_TIMES[16] = {1,2,4,2,2,2,2,2,1,2,2,2,2,2,2,1};
int pc1[56] = { /* 置换选择1 PC-1 (key) */
  57, 49, 41, 33, 25, 17,  9,
   1, 58, 50, 42, 34, 26, 18,
  10,  2, 59, 51, 43, 35, 27,
  19, 11,  3, 60, 52, 44, 36,
  63, 55, 47, 39, 31, 23, 15,
   7, 62, 54, 46, 38, 30, 22,
  14,  6, 61, 53, 45, 37, 29,
  21, 13,  5, 28, 20, 12,  4 };

//初始置换表IP
int IP_Table[64] = {57,49,41,33,25,17,9,1,
                                 59,51,43,35,27,19,11,3,
                                 61,53,45,37,29,21,13,5,
                                 63,55,47,39,31,23,15,7,
                                 56,48,40,32,24,16,8,0,
                                 58,50,42,34,26,18,10,2,
                                 60,52,44,36,28,20,12,4,
                                 62,54,46,38,30,22,14,6}; 
//逆初始置换表IP^-1
int IP_1_Table[64] = {39,7,47,15,55,23,63,31,
		   38,6,46,14,54,22,62,30,
		   37,5,45,13,53,21,61,29,
		   36,4,44,12,52,20,60,28,
		   35,3,43,11,51,19,59,27,
		   34,2,42,10,50,18,58,26,
		   33,1,41,9,49,17,57,25,
		   32,0,40,8,48,16,56,24};

//扩充置换表E
int E_Table[48] = {31, 0, 1, 2, 3, 4,
	              3,  4, 5, 6, 7, 8,
	              7,  8,9,10,11,12,
	              11,12,13,14,15,16,
	              15,16,17,18,19,20,
	              19,20,21,22,23,24,
	              23,24,25,26,27,28,
	              27,28,29,30,31, 0};

//置换函数P
int P_Table[32] = {15,6,19,20,28,11,27,16,
				  0,14,22,25,4,17,30,9,
				  1,7,23,13,31,26,2,8,
				  18,12,29,5,21,10,3,24};





//置换选择2
int PC_2[48] = {13,16,10,23,0,4,2,27,
	          14,5,20,9,22,18,11,3,
	          25,7,15,6,26,19,12,1,
	          40,51,30,36,46,54,29,39,
	          50,44,32,47,43,48,38,55,
	          33,52,45,41,49,35,28,31};
int PN[32]={8,16,22,30,12,27,1,17,
        23,15,29,5,25,19,9,0,
		7,13,24,2,3,28,10,18,
		31,11,21,6,4,26,14,20};

int DES_MakeSubKeys(ElemType key[64],ElemType subKeys[3][48]);   
int DES_PC1_Transform(ElemType key[64], ElemType tempbts[56]);   
int DES_PC2_Transform(ElemType key[56], ElemType tempbts[48]);   
int DES_ROL(ElemType data[56], int time,ElemType temp[56]);   
int DES_IP_Transform(ElemType data[64],ElemType temp[64]);   
int DES_IP_1_Transform(ElemType data[64],ElemType temp[64]);   
int DES_E_Transform(ElemType data[32],ElemType temp[48]);   
int DES_P_Transform(ElemType data[32],ElemType temp[32]);   
int DES_SBOX(ElemType data[48],ElemType temp[32]);   
int DES_XOR(ElemType R[48], ElemType L[48],int count);   
int DES_Swap(ElemType left[32],ElemType right[32]);   
 

 
//十进制转换成二进制*/
int zhuanhua(ElemType ch,ElemType bit[4])
{
    int i = 0; 
    for(i=3;i>=0;i--)
    {
        bit[3-i]=(ch>>i)&1; 
    } 
    return 0; 
}
//二进制转换成十进制
int BitToByte(ElemType bit[4]){
	int ch;
	ch=8*bit[0]+4*bit[1]+2*bit[2]+bit[3];
	return ch;
}
//转二进制
int zr(ElemType bit[32],ElemType ch[8])
{
	int i,j,a[4];
	for(i=0;i<8;i++)
	{	for(j=0;j<4;j++)
		{
			zhuanhua(ch[i],a);
			bit[4*i+j]=a[j];
		}
	}
	return 0;
}
//转十进制
int zs(ElemType bit[32],ElemType ch[8])
{
	int i,j,a[4];
	for(i=0;i<8;i++)
	{	for(j=0;j<4;j++)
		{
			a[j]=bit[4*i+j];
			
		}
	    ch[i]=BitToByte(a);
	}
	return 0;
}

//扩展算法
int E(ElemType bit[32],ElemType ch[48])
{
	int i;
	for(i=0;i<48;i++)
		ch[i]=bit[E_Table[i]];
	return 0;
}
//p的逆置换
int pni(ElemType bit[32],ElemType ch[32])
{
	int i;
	for(i=0;i<32;i++)
		bit[i]=ch[PN[i]];
	return 0;
}
//十进制数转化为6位二进制数
int ste(ElemType shu,ElemType ch[6])
{
  int i=5;
  while(shu>0)
  {
    ch[i]=shu%2;
    shu/=2;
    i--;
  }
  return 0;
}
//十进制转化为8位二进制数
int ste1(ElemType shu,ElemType ch[8])
{
	int i=7;
	while(shu>0)
	{
		ch[i]=shu%2;
		shu/=2;
		i--;
	}
	return 0;
}
//生成子密钥
int DES_MakeSubKeys(ElemType key[64],ElemType subKeys[3][48]){
	ElemType temp[56]={0},data[56]={0};
	int cnt;
	DES_PC1_Transform(key,temp);//PC1置换
	for(cnt = 0; cnt < 3; cnt++){//3轮跌代，产生3个子密钥
		DES_ROL(temp,MOVE_TIMES[cnt],data);//循环左移
	   
		
        DES_PC2_Transform(data,subKeys[cnt]);//PC2置换，产生子密钥
	}
	return 0;
}
//密钥置换1
int DES_PC1_Transform(ElemType key[64], ElemType tempbts[56]){
	int cnt;	
	for(cnt = 0; cnt < 56; cnt++){
		tempbts[cnt] = key[pc1[cnt]-1];
	}
	return 0;
}

//密钥置换2
int DES_PC2_Transform(ElemType key[56], ElemType tempbts[48]){
	int cnt;
	for(cnt = 0; cnt < 48; cnt++){
		tempbts[cnt] = key[PC_2[cnt]];
	}
	return 0;
}

//循环左移
int DES_ROL(ElemType data[56], int time,ElemType temp[56]){	
	ElemType c0[28],d0[28],c3[28],d3[28],i;
    for(i=0;i<28;i++)
		c3[i]=data[i];
	for(i=0;i<28;i++)
		d3[i]=data[i+28];

	for(i=0;i<28;i++)
		c0[(i-time+28)%28]=c3[i],d0[(i-time+28)%28]=d3[i];
	for(i=0;i<28;i++)
		temp[i]=c0[i];
	for(i=28;i<56;i++)
		temp[i]=d0[i-28];
	
	return 0;
}

//IP置换
int DES_IP_Transform(ElemType data[64],ElemType temp[64]){
	int cnt;
	
	for(cnt = 0; cnt < 64; cnt++){
		temp[cnt] = data[IP_Table[cnt]];
	}
	
	return 0;
}

//IP逆置换
int DES_IP_1_Transform(ElemType data[64],ElemType temp[64]){
	int cnt;
	
	for(cnt = 0; cnt < 64; cnt++){
		temp[cnt] = data[IP_1_Table[cnt]];
	}

	return 0;
}



//P置换
int DES_P_Transform(ElemType data[32],ElemType temp[32]){
	int cnt;
	for(cnt = 0; cnt < 32; cnt++){
		data[cnt] = temp[P_Table[cnt]];
	}	
	
	return 0;
}

//异或
int DES_XOR(ElemType R[48], ElemType L[48] ,int count){
	int cnt;
	for(cnt = 0; cnt < count; cnt++){
		R[cnt]= (L[cnt]+R[cnt])%2;
	}
	return 0;
}

//S盒置换
int DES_SBOX(ElemType data[48],ElemType temp[32]){
	int a[8][6]={0},b[8][4],i,j;
	for(i=0;i<8;i++)
		for(j=0;j<6;j++)
			a[i][j]=data[6*i+j];
	for(i=0;i<8;i++)
		zhuanhua(S[i][(2*a[i][0]+a[i][5])][(8*a[i][1]+4*a[i][2]+2*a[i][3]+a[i][4])],b[i]);
	for(i=0;i<8;i++)
		for(j=0;j<4;j++)
			temp[4*i+j]=b[i][j];
	return 0;

}



//加密单个分组
int DES_EncryptBlock(ElemType plainBlock[2][8],ElemType subKeys[3][48],ElemType cipherBlock[2][8]){
	ElemType plainBits[64]={0},a[2][32]={0},b[2][32]={0},c[2][32]={0},d[2][32]={0};
	ElemType copyRight[48]={0},h[32]={0},h1[32]={0},h2[32]={0},temp[64]={0},temp1[64]={0},copy[32]={0};
	int i,j;
	for(i=0;i<2;i++)
		zr(a[i],plainBlock[i]);
	for(i=0;i<2;i++)
		for(j=0;j<32;j++)
			plainBits[i*32+j]=a[i][j];
    //3轮迭代

		

	    //进行E扩展
		E(a[1],copyRight);
		/*for (i=0;i<48;i++)
		{printf("%d",copyRight[i]);}
		printf("\n");*/
		//将右半部分与子密钥进行异或操作
		DES_XOR(copyRight,subKeys[0],48);
		/*for (i=0;i<48;i++)
		{printf("%d",copyRight[i]);}
		printf("\n");*/
		//异或结果进入S盒，输出32位结果
		DES_SBOX(copyRight,copy);
		/*for (i=0;i<32;i++)
		{printf("%d",copy[i]);}
		printf("\n");*/
		//P置换
		DES_P_Transform(h,copy);
		//将明文左半部分与右半部分进行异或
		DES_XOR(a[0],h,32);
		
		
		for(i=0;i<2;i++)
		   for(j=0;j<32;j++)
			   b[(1-i)%2][j]=a[i][j];
		for(i=0;i<48;i++)
			copyRight[i]=0;
		for(i=0;i<32;i++)
			copy[i]=0;

	    E(b[1],copyRight);
		DES_XOR(copyRight,subKeys[1],48);
		DES_SBOX(copyRight,copy);
		DES_P_Transform(h1,copy);
		DES_XOR(b[0],h1,32);//
		for(i=0;i<2;i++)
		   for(j=0;j<32;j++)
			   c[(1-i)%2][j]=b[i][j];
		for(i=0;i<48;i++)
			copyRight[i]=0;
		for(i=0;i<32;i++)
			copy[i]=0;

		
		E(c[1],copyRight);
		DES_XOR(copyRight,subKeys[2],48);
		DES_SBOX(copyRight,copy);
		DES_P_Transform(h2,copy);
		DES_XOR(c[0],h2,32);

		for(i=0;i<32;i++)
			plainBits[i]=c[1][i],plainBits[i+32]=c[0][i];
    for(i=0;i<2;i++)
		for(j=0;j<32;j++)
		   d[i][j]=plainBits[i*32+j];
	for(i=0;i<2;i++)
		zs(d[i],cipherBlock[i]);
    return 0;
}
void main()
{
	int bL3[3][32],bL30[3][32],bL0[3][32],bL00[3][32];
	int bR3[3][32],bR30[3][32],bR0[3][32],bR00[3][32];
	int L0[3][8]={7,4,8,5,0,2,12,13,4,8,6,9,1,1,0,2,3,5,7,4,1,8,13,10},
	    R0[3][8]={3,8,4,5,1,0,9,7,6,10,12,13,15,15,3,1,0,1,3,15,14,12,8,6};
	int L00[3][8]={3,8,7,4,7,5,6,4,3,7,5,11,13,3,1,15,1,2,5,4,9,8,4,7},
		R00[3][8]={3,8,4,5,1,0,9,7,6,10,12,13,15,15,3,1,0,1,3,15,14,12,8,6};
	int L3[3][8]={0,3,12,7,0,3,0,6,4,5,15,10,2,8,5,11,13,8,10,3,1,11,2,15},
		R3[3][8]={13,8,10,0,9,15,1,0,14,5,10,13,12,7,3,0,2,8,11,11,12,5,12,15};
	int L30[3][8]={7,8,5,6,0,10,0,9,1,3,4,15,7,9,1,5,0,15,3,1,7,10,12,2},
		R30[3][8]={6,0,14,6,13,4,12,11,10,12,2,5,3,4,5,7,11,2,3,12,11,9,4,4};
	int c3[28]={0},d3[28]={0},c0[28]={0},d0[28]={0},KK[64]={0},key1[8]={0};
	int subkey[3][48]={0};
	int plainBlock[2][8]={7,4,8,5,0,2,12,13,3,8,4,5,1,0,9,7};
	int cipherBlock[2][8]={0},o=0,kkk[64]={0};
	int i,B[3][48],m[3][48],n[3][48],A[3][32],C[3][32],key[6],K[8][64]={0},j,c[3][8],a,ww[8][6]={0};
    int d,k,h=0,hh[48],H[56]={0},b[3][8];
	int X[6],Y[6],ww1[4],ww2[4],ww3[4];
	for(d=0;d<3;d++)
	{
    zr(bL3[d],L3[d]);
    zr(bL30[d],L30[d]);
	zr(bL0[d],L0[d]);
	zr(bR30[d],R30[d]);
	zr(bL00[d],L00[d]);
	zr(bR3[d],R3[d]);
	zr(bR0[d],R00[d]);
	zr(bR00[d],R0[d]);
    E(bL3[d],m[d]);
    E(bL30[d],n[d]);
    for(i=0;i<48;i++)
		B[d][i]=(m[d][i]+n[d][i])%2;
	zs(B[d],b[d]);//   s盒第三轮输入差B
	
	
	for(i=0;i<32;i++)
		A[d][i]=(bL0[d][i]+bL00[d][i]+bR3[d][i]+bR30[d][i])%2;
	pni(C[d],A[d]);        // s盒第三轮输出差C
    zs(C[d],c[d]);


	//计算第3轮8个s盒可能的6比特子密钥
	for(a=0;a<8;a++)
	{  
	   for(i=0;i<64;i++)
	   {
		for(k=0;k<6;k++)
			key[k]=0;
		ste(i,key);
		for(j=0;j<6;j++)
		{
			X[j]=(m[d][j+6*a]+key[j])%2;
			Y[j]=(n[d][j+6*a]+key[j])%2;
		}
		
		zhuanhua(S[a][(2*X[0]+X[5])][(8*X[1]+4*X[2]+2*X[3]+X[4])],ww1);
		zhuanhua(S[a][(2*Y[0]+Y[5])][(8*Y[1]+4*Y[2]+2*Y[3]+Y[4])],ww2);
		for(k=0;k<4;k++)
		{
			ww3[k]=(ww1[k]+ww2[k])%2;
		}
		if(BitToByte(ww3)==c[d][a])
			K[a][i]++;
		}
	    
	}
	
	
	}
	for(a=0;a<8;a++)
	{  
	   for(i=0;i<64;i++)
	   {
		   if(K[a][i]==3)
			   key[h]=i,h++;
	   }
       	
	}
	for(i=0;i<8;i++)
		ste(key[i],ww[i]);
	for(i=0;i<8;i++)
		for(j=0;j<6;j++)
			hh[6*i+j]=ww[i][j];
//求解56bit密钥 hh【48】为第三轮子密钥
	for(i=0;i<56;i++)
		H[i]=8;
	for(i=0;i<48;i++)
		H[PC_2[i]]=hh[i];
	for(i=0;i<28;i++)
		c3[i]=H[i],d3[i]=H[i+28];
    for(i=0;i<28;i++)
		c0[(4+i)%28]=c3[i],d0[(4+i)%28]=d3[i];
    for(i=0;i<28;i++)
		KK[pc1[i]-1]=c0[i];
	for(i=28;i<56;i++)
		KK[pc1[i]-1]=d0[i-28];
	for(i=0;i<256;i++)
	{
		for(k=0;k<8;k++)
			key1[k]=0;
		ste1(i,key1);
        
		
		k=0;

		for(j=0;j<64;j++)
		{
			kkk[j]=KK[j];
			if(kkk[j]==8)
				kkk[j]=key1[k],k++;
		}
	    DES_MakeSubKeys(kkk,subkey);
	    printf("%d   ",i);
        DES_EncryptBlock(plainBlock,subkey,cipherBlock);
	    for(d=0;d<2;d++)
		    for(o=0;o<8;o++)
			{  
			   if(cipherBlock[0][0]==0)
			        printf("%x",cipherBlock[d][o]);
			}
		for(d=0;d<2;d++)
		    for(o=0;o<8;o++)
			    cipherBlock[d][o]=0;
			printf("\n");  
		
	}
	//加密第一组明文 寻找与之对应的密文
	for(k=0;k<8;k++)
			key1[k]=0;
		ste1(88,key1);
        k=0;
        for(j=0;j<64;j++)
		{
			kkk[j]=KK[j];
			if(kkk[j]==8)
				kkk[j]=key1[k],k++;
		}
			printf("              得到的密钥为\n");
		for(j=0;j<64;j++)

			printf("%d ",kkk[j]);

}