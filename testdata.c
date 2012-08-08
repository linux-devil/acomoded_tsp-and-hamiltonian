#include<stdio.h>
#include<math.h>
#include<string.h>
#define MAX = 50000
#define SIZE 1000

int main(int argc ,char * argv[])
{  int i,j,k=0;
   struct cord
   {  
      float x;
      float y ;
   };
   typedef struct cord cr;
   
   cr E[SIZE] ;
   
float sqroot(float m)
{
     float i=0;
     float x1,x2;
     while( (i*i) <= m )
          i+=0.1;
          x1=i;
   int j;
   for(j=0;j<10;j++)
   {
      x2=m;
      x2/=x1;
      x2+=x1;
      x2/=2;
      x1=x2;
   }

     return x2;
}


   FILE *source,*f1,*f2,*f3;
   f1=fopen("data.txt","w");
   f2 =fopen("opt.txt","r");
 /*  f3 =fopen("ch.txt","r"); */
   float sum = 0;
   float w[SIZE][SIZE];
   int n ;
   char pgm[25];
   printf("Enter the size ");
   scanf("%d",&n);
   strcpy(pgm,argv[1]);
   source = fopen(pgm,"r");
	if(source==NULL)
	{
		fprintf(stderr,"FILE %s not found\n",pgm);
		return 1;
	}
    
   for(i=0;i<n;i++)
   {  
     fscanf(source," %d ",&j) ;
     fscanf(source," %f ",&E[i].x) ;
     fscanf(source," %f ",&E[i].y) ;
    }

   for(i=0;i<n;i++)
   for(j=0;j<n;j++)
   {  if(i!=j)
      w[i][j] = (sqroot((pow(E[i].x - E[j].x,2)) + (pow(E[i].y - E[j].y,2))))/10 ;
      else
      w[i][j] = 50000 ;
   }
   
 
   for(i=0;i<n;i++)
   for(j=0;j<n;j++)
   { if(i!=j)
     fprintf(f1," %f ",w[i][j]) ;}
   int s,v=0,a ;
   float sum1=0;
   fscanf(f2," %d ",&s);
   printf(" %d ",s);
   a = s;
   for(i=0;i<n;i++)
   {   if(i!=n-1)
       { fscanf(f2," %d ",&v) ;
         sum += w[s-1][v-1];
         s=v;
       }
       else
       {  sum+= w[s-1][a-1] ;
        }
   }

/*   for(i=0;i<2*n;i=i+2)
   {   fscanf(f3," %d ",&s);
       fscanf(f3," %d ",&v);
       sum1+= w[s-1][v-1];
    }
   printf(" %f ",sum1) ;  */
   printf(" %f ",sum);      
   fclose(source);
   fclose(f1);
   fclose(f2) ; 
  /* fclose(f3) ; */
   return 0;
  }
 
