#include"ham.h"

int main(int argc ,char * argv[])
{  int i,j,n;
   float total;
   int k[2*SIZE];
   FILE *source;
   Element x[SIZE][SIZE];
   //f3 = fopen("check.txt","w");
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
{  x[i][n+1].flag=0;
{  for(j=0;j<n;j++)
   if(i!=j)
   {  fscanf(source,"%f ",&x[i][j].e);
      x[i][j].p=1.0;
      x[i][j].flag=0;
   }
   else
   { fscanf(source,"%f ",&x[i][j].e);
     x[i][j].p=0.0001;
     x[i][j].flag=1;
   }
}
}
	int deg[SIZE] ;
	for(i=0;i<n;i++) 
	{
		deg[i] = 0 ;
		for(j = 0;j<n;j++)
		{
		 	if(x[i][j].e == 1)
		 	deg[i]++;
		}
	}
   //operation(x,n);//
   total = optHam(x,n,deg,15,k);
   printf("Optimal value = %f  \n",total);
   int best = total;
  
   for(i=0;i<2*best;i=i+2)
   printf(" %d,%d ",k[i]+1,k[i+1]+1);
 //  for(i=0;i<n;i++)
 //  for(j=0;j<n;j++)
 //  fprintf(f3," %f  ",x[i][j].e) ;
 //  fclose(f3); 
   return 0;
   }
