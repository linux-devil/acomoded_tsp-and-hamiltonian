#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define MAX 50000.00
#define SIZE 450



struct Obj
{ 
  
  int flag;
  float p;
  float e;

};



typedef struct Obj Element;

extern int nn(Element x[SIZE][SIZE],int source,int n,int k);
extern int maxim(Element x[SIZE][SIZE],int source,int n,int k);
extern int pseudorand(Element x[SIZE][SIZE],int source,int n,int k,int q,int p) ;
extern float optTSP(Element x[SIZE][SIZE],int n,int k[2*SIZE],int t,int m);
extern int rand1(Element x[SIZE][SIZE],int n,int k);
extern int random1(Element x[SIZE][SIZE],int source,int n,int k);
extern void operation(Element x[SIZE][SIZE],int n);
extern float ACO(Element x[SIZE][SIZE],int n,int k[2*SIZE],int m);
extern int GetRand(int min,int max);
extern void update(Element x[SIZE][SIZE],int n,int k[2*SIZE],int l,int fl);
extern float raco(Element x[SIZE][SIZE],int n,int k[2*SIZE],int t);
extern float racoR(Element x[SIZE][SIZE],int n,int k[2*SIZE],int t,int a[2],float best,int fl);
extern void opt2(Element x[SIZE][SIZE],int n,int k[2*SIZE],float best,int arr[2]);
