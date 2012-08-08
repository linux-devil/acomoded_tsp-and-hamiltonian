#include "ham.h"
float power(float x,int p)
{   if(p==1)
    return 1;
    else
    return x*power(x,p-1) ;
}


int ACOHAM(Element x[SIZE][SIZE],int n,int deg[SIZE],int k[2*SIZE],float q)
{   
	    int i,j,c,q1,q2;   
	    
	    for(i=0;i<n;i++)
	{ 
	    x[i][n+1].flag=0;
	    for(j=0;j<n;j++)
	    {   
		if(i==j)
		x[i][j].flag=1;
		else
		x[i][j].flag=0;
	     }
	}
	    int t;
	    int count = 0;
	    int dest,p=0,check = 0;
	    int source = GetRand(0,n-1);
	    int f = source ;
	/*  printf("\n %d \n",source) ; */
	    while(count < n && check != -1)
	    {  
	       
		  if(count==(n-1) && x[k[2*count -1]][f].e == 1)
		  {	
			  	dest=f;
		  	        
				k[p] = k[2*count-1] ;
				k[++p] = f;
				count++;
				printf("\n");
				for(t = 0;t<(2*count);t++)
				printf(" %d ",k[t]+1);
				printf("\n");  
				return count;
		   }
		  if(count == (n-1) && x[k[2*count -1]][f].e == 0)
			  { 
	  			check = -1 ;
				printf("\n");
				for(t = 0;t<(2*count);t++)
				printf(" %d ",k[t]+1);
				printf("\n");  
				return count;
			   }
		  
		  dest = pseudorand(x,source,n,f,deg,q);
		  printf("dest = %d count = %d",dest,count);
		  if(dest==n+1)
		  {
			  	check = -1 ;
				printf("count1= %d ",count);
				
				printf("\n");
				for(t = 0;t<(2*count);t++)
				printf(" %d ",k[t]+1);
				printf("\n");  
				return count;
		  }
		  else
		  {
			  x[source][n+1].flag++;
			  x[dest][n+1].flag++;
			  x[source][dest].flag++;
			  x[dest][source].flag++;
			  count++;
			  k[p]=source;
		      /*  printf("  %d,%d  ",source,dest); */
			  k[++p]=dest;
		  }
		  p++;
		  source = dest ;
	       } 
		  return count;
     }
     
 	   int pseudorand(Element x[SIZE][SIZE],int source,int n,int k,int deg[SIZE],float q)
	{   
	    
	    int q1 = GetRand(1,100);
	    if(q1>(int)(100*q) )
	    return random1(x,source,n,k,deg);
	    else
	    return maxim(x,source,n,k,deg);
	}
	
	int random1(Element x[SIZE][SIZE],int source,int n,int k,int deg[SIZE])
	{   
	     int a = GetRand(0,99);
	     float m=0;
	     float sum=0;
	     int i,j;
	     
	     for(i=0;i<n;i++) 
	     {   
	       { if(x[i][n+1].flag!=2 && x[source][i].flag==0 && source != i && i!=k)
	          sum += x[source][i].p * x[source][i].e * deg[i] ;
	       }      
	     } 
	     if(sum == 0)
                return n+1;
	    // printf("  sum = %f  ",sum);
	     for(i=0;i<n;i++)
	     {   
		 
		 
	         { if(x[i][n+1].flag!=2 && x[source][i].flag==0 && source!=i && i!=k)   
	           {   
	              m+= ( 100 * x[source][i].p * x[source][i].e * deg[i])/sum ;
		      //printf("  m=%f  ",m);
	              if((float)a<m)
		      {  
			 //printf("   i = %d  ",i);
	                 return i;
			
		       }
	            }
	          }  
		  
	     }
	     //printf("a=%d yo m = %f",a,m);
	     return n+1;
	}
	
	int maxim(Element x[SIZE][SIZE],int source,int n,int k,int deg[SIZE])
	{   
	    float max = 0;
	    int p1=k,fl = 0;
	    int i;
	    
	    for(i=0;i<n;i++)
	    {    
	       { if(x[i][n+1].flag!=2 && x[source][i].flag==0 && source!= i && (x[source][i].p * x[source][i].e * deg[i])>max && i!=k)
	         {  max = (x[source][i].p * x[source][i].e *deg[i]) ;
	            p1 = i;
                    fl = 1;
	         }
	        }
	     }
	     //printf(" p1 =%d fl = %d ",p1,fl);	
	     if(fl == 1)
	     return p1 ;
             else
	     {
		
                return n+1 ;
              }
	}
	
	int GetRand(int min, int max)
	{
	  static int Init = 0;
	  int rc;
	  
		  if (Init == 0)
		  {
		    /*
		     *  As Init is static, it will remember it's value between
		     *  function calls.  We only want srand() run once, so this
		     *  is a simple way to ensure that happens.
		     */
		    srand(time(NULL));
		    Init = 1;
		  }
		
		  /*
		   * Formula:  
		   *    rand() % N   <- To get a number between 0 - N-1
		   *    Then add the result to min, giving you 
		   *    a random number between min - max.
		   */  
		  rc = (rand() % (max - min + 1) + min);
		  
  		  return (rc);
	 }
	 
	 int shuffle(Element x[SIZE][SIZE],int n,int deg[SIZE],int k[SIZE],int temp[SIZE],float q,int flagb[SIZE][SIZE],int best)
	 {
	 		int i,count,flag_upd = 0;
			count = best ;
			i = GetRand(0,n-1) ;
 			int counter = 0;
			printf("\n%d\n",i);
	 		while(counter < n)
	 		{ 
				counter++;									
				if(i>n-1)
				i = 0;
 				if(flagb[k[2*i]][n+1] == 2 && x[(k[2*i])][k[(2*best - 1)]].e == 1 && i!=k[2*best-2])
		  		{
		  			flag_upd = 1;
					int j,l = 0, tmp, temp1[SIZE] ;
					tmp = k[2*i+1] ;
					k[2*i + 1] = k[2*best -1];
					k[2*i + 2] = k[2*best -1];
					k[2*best-1] = tmp;
					for(j = 2*best-2;j>2*i+2;j--)
					{   
					    temp1[l] = k[j];
					    l++; 	  
					}
					l = 0;
					for(j= 2*i+3;j<2*best - 1;j++)
					{   
						k[j] = temp1[l];
						l++;
						
					}
					int t;
					printf("\n CHANGE1 \n");
					for(t = 0;t<(2*count);t++)
					printf(" %d ",k[t]+1);
					printf("\n");  
     				        
		  		}
				if(flag_upd == 1)
				break;
				else
				i++;
	 		}
			
			int source,f,dest,p = 2*best;
	 		if(flag_upd == 1)
	 		{
	 			printf("\n CHANGE \n");
                                count = best ;
				
				source = k[2*best-1] ; 
				f = k[0];
				
	 			int p1,p2;
	 			for(p1=0;p1<n;p1++)
				{
					x[p1][n+1].flag = flagb[p1][n+1];
					for(p2=0;p2<n;p2++)
					x[p1][p2].flag = flagb[p1][p2];
				}
    				x[k[2*best-1]][n+1].flag = 1;
				x[k[2*i+1]][n+1].flag = 2;
    				x[k[2*best -1]][k[2*i]].flag = 0 ;
    				x[k[2*i]][k[2*best -1]].flag = 0 ;
    				x[k[2*i]][k[2*i+1]].flag = 1;
    				x[k[2*i+1]][k[2*i]].flag = 1;			
	 		 }
	 		 if(flag_upd == 1)
	 		 {
				int check = 0,t;
		 		while(count < n && check != -1)
			    {  
			          
			          if(count==(n-1) && x[k[2*count -1]][f].e == 1)
			          {	
					  	dest=f;
		  	        
						k[p] = k[2*count-1] ;
						k[++p] = f;
						count++;
						printf("\n 1 count =%d \n",count);
						for(t = 0;t<(2*count);t++)
						{
							printf(" %d ",k[t]+1);
							temp[t] = k[t];
 						}
						printf("\n");  
						return count;
			           }
			           if(count == (n-1) && x[k[2*count -1]][f].e == 0)
					  { 
			  			check = -1 ;
						printf("\n n-1/-1 \n");
						for(t = 0;t<(2*count);t++)
						{
							printf(" %d ",k[t]+1);
							temp[t] = k[t];
 						}
						printf("\n");  
						return count;
					   }
					  else
					  dest = pseudorand(x,source,n,f,deg,q);
					  printf("dest = %d count = %d",dest,count);
					  if(dest==n+1)
					  {
						  	check = -1 ;
							printf("count1= %d ",count);
				
							printf("\n 1 \n");
							for(t = 0;t<(2*count);t++)
							{
								printf(" %d ",k[t]+1);
								temp[t] = k[t];
	 						}
							printf("\n");  
							return count;
					  }
					  else
					  {
						  x[source][n+1].flag++;
						  x[dest][n+1].flag++;
						  x[source][dest].flag++;
						  x[dest][source].flag++;
						  count++;
						  k[p]=source;
					      /*  printf("  %d,%d  ",source,dest); */
						  k[++p]=dest;
					  }
					  p++;
					  source = dest ;
				  } 
	 		 }

		  	       
		return count;
     }
     
     void update(Element x[SIZE][SIZE],int n,int k[2*SIZE],int count)
     {
		int i,j,m ;
		float q[SIZE][SIZE];
		for(i=0;i<n;i++)
    		for(j=0;j<n;j++) 
   		q[i][j]=0;	
		   
	 	for(m=0;m<(2*count-3);m=m+2)
	    {   
	        i=k[m];
	        j=k[m+1];
	        q[i][j]= (count/n) ;
	        q[j][i]=q[i][j];
	     } 
		 
		for(i=0;i<n;i++)
    		for(j=0;j<n;j++)
    		x[i][j].p = ( 0.75*x[i][j].p ) + q[i][j] ;
       }
	 				
	 
int optHam(Element x[SIZE][SIZE],int n,int deg[SIZE],int it,int k[SIZE])
{
 	int best = 0,i,j,rand;
 	float q = 0.5 ;
 	int temp[SIZE],r,k1[SIZE] ;
 	
 	int flagb[SIZE][SIZE] ;
 	for(i = 0;i < it;i++)
 	{       
		rand = GetRand(0,10) ;
	        int p1,p2 ;   
		if(rand>4 || i == 0)
		j = ACOHAM(x,n,deg,temp,q) ;
		else
		{   
		    for(p1=0;p1<2*best;p1++)
		    k1[p1] = k[p1] ;
		    j = shuffle(x,n,deg,k1,temp,q,flagb,best);
		    printf(" SHUFFLE! = %d",j);
		    int t;
                    printf("\n");
                    for(t=0;t<2*j;t++)
	            printf("%d,",k1[t]);
		}
		if(j>best)
	{	for(r = 0;r<2*j;r++)			
                k[r] = temp[r];
                best = j;
                if(best == n)
                return n;
                else
                {   
                    update(x,n,k,best) ;
                    for(p1=0;p1<n;p1++)
		    {
			flagb[p1][n+1] = x[p1][n+1].flag ;
			for(p2=0;p2<n;p2++)
			flagb[p1][p2] = x[p1][p2].flag ;
		    }
                 }
					   
	   }
    }
	 	return best ;
}
	  
	  
