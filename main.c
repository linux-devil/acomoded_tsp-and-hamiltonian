#include"tsp.h"

int main(int argc ,char * argv[])
{  int i,j,n;
   float total;
   int k[2*SIZE];
   FILE *source,*f3;
   Element x[SIZE][SIZE];
   f3 = fopen("check.txt","w");
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
   { x[i][j].e=MAX;
     x[i][j].p=0.0001;
     x[i][j].flag=1;
   }
}
}
   //operation(x,n);//
   total = raco(x,n,k,900000);
   printf("Optimal value = %f  \n",total);
   for(i=0;i<2*n;i=i+2)
   printf(" %d,%d ",k[i]+1,k[i+1]+1);
   for(i=0;i<n;i++)
   for(j=0;j<n;j++)
   fprintf(f3," %f  ",x[i][j].e) ;
   fclose(f3); 
   return 0;

}
