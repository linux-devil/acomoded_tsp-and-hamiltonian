#include"tsp.h"


float power(float x,int p)
{   if(p==1)
    return 1;
    else
    return x*power(x,p-1) ;
}


void operation(Element x[SIZE][SIZE],int n)
{    
     float min[SIZE];
     int i,j;
 /*    for(i=0;i<n;i++)
     { min[i]=x[i][0].p;
       for(j=1;j<n;j++)
     { if(x[i][j].p < min[i])
          min[i]=x[i][j].p;
     }
     }
    
   for(i=0;i<n;i++)
   for(j=0;j<n;j++)
   {  if(i!=j)
      x[i][j].p += (-min[i]);
    }
   
   for(i=0;i<n;i++)
   for(j=0;j<n;j++)
   { if(i!=j && x[i][j].flag!=1)
     { x[i][j].p = (x[i][j].p + x[j][i].p)/2;
       x[j][i].flag=1;
       x[i][j].flag=1;
       }
   }
       
   for(i=0;i<n;i++)
   for(j=0;j<n;j++)
   {
       if(i!=j)
      { if(x[i][j].p==0)
       x[i][j].p= (((float)min[i])/4) ; 
      }
   }
*/
   for(i=0;i<n;i++)
   for(j=0;j<n;j++)
   x[i][j].p = (3/x[i][j].p);

}   

  
   
     

float ACO(Element x[SIZE][SIZE],int n,int k[2*SIZE],int m)
{   
    int i,j,c,q1,q2;   
    

    if(m==0)
    { 
       q1 = 38 ;
       q2 = 33 ;
    }
    else
    {
      q1 = 70 ;
      q2 = 65 ;
    }
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
    
    float sum=0;
    int dest,p=0;
    int source = GetRand(0,n-1);
    int f = source ;
/*  printf("\n %d \n",source) ; */
    for(c=0;c<n;c++)
    {  
       
          if(c==(n-1))
          dest=f;
          else
          dest = pseudorand(x,source,n,f,q1,q2);
          if(dest==n+1)
          return 0;
          x[source][n+1].flag++;
          x[dest][n+1].flag++;
          x[source][dest].flag++;
          x[dest][source].flag++;
          sum+=x[source][dest].e;
          k[p]=source;
      /*  printf("  %d,%d  ",source,dest); */
          k[++p]=dest;
          p++;
          source = dest ;
         } 
     
     return sum;
}
        
int pseudorand(Element x[SIZE][SIZE],int source,int n,int k,int q,int p)
{   
    
    int q1 = GetRand(0,99);
    if(q1> q )
    return random1(x,source,n,k);
    if(q1> p )
    return nn(x,source,n,k) ;
    else
    return maxim(x,source,n,k);
}

int nn(Element x[SIZE][SIZE],int source,int n,int k)
{
       float near = MAX ;
       int p,i;

       for(i=0;i<n;i++)   
       {
           if(i!=k)
           {   
              if(x[i][n+1].flag!=2 && x[source][i].flag!=1 && source != i && x[source][i].e<near)
              {          
                     near = x[source][i].e ;
                     p = i;
               }
            }
         }

         return p ;
}


int maxim(Element x[SIZE][SIZE],int source,int n,int k)
{   
    float max = 0;
    int p;
 /* if(source!=0) 
    { max = x[source][0].e;
      p=0; 
     }
    else
    {  
       max = x[source][1].e;
       p = 1;
     }  */
    int i;
    
    for(i=0;i<n;i++)
    {    if(i!=k)
       { if(x[i][n+1].flag!=2 && x[source][i].flag!=1 && source != i && (x[source][i].p * power(((float)1/ x[source][i].e),6))>max)
         {  max = (x[source][i].p * power(((float)1/ x[source][i].e),6)) ;
            p = i;
         }
        }
     }
     return p ;
}


int random1(Element x[SIZE][SIZE],int source,int n,int k)
{   
     int a = GetRand(0,99);
     float m=0;
     float sum=0;
     int i,j;
     
     for(i=0;i<n;i++) 
     {   if(i!=k)
       { if(x[i][n+1].flag!=2 && x[source][i].flag!=1 && source != i)
          sum += x[source][i].p * power(((float)1/ x[source][i].e),6) ;
       }      
     } 
      
     for(i=0;i<n;i++)
     {   if(i!=k)
       { if(x[i][n+1].flag!=2 && x[source][i].flag!=1 && source != i)   
         {   
            m+= ( 100 * x[source][i].p *power(((float)1/x[source][i].e),6))/sum ;
            if((float)a<m)
            return i;
          }
        }  
     }
     return n+1;
     
}


int rand1(Element x[SIZE][SIZE],int n,int k)
{   
    int a = GetRand(0,n-1);
    int i;
     
    if(x[a][n+1].flag==2 || a==k)
    {  
       for(i=a+1;i<n;i++)
       { 
           if(x[i][n+1].flag!=2)
           return i;
        }
       for(i=0;i<a;i++)
       { 
           if(x[i][n+1].flag!=2)
           return i;
        }
     }
 
      return a;
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
    
    

float optTSP(Element x[SIZE][SIZE],int n,int k[2*SIZE],int t,int m)
{   
    int i=0,p;
    float j;
    int l[2*SIZE];
    float best=MAX;      
    while(i<t) 
    {    
         j= ACO(x,n,k,m);
         
         if(j!=0 && j<best)
         {   
            best=j; 
            for(p=0;p<2*n;p++)
            l[p]=k[p];
            if(i>3)
            update(x,n,k,best,0);
            }
          i++;
     }
     for(p=0;p<2*n;p++)
            k[p]=l[p];
     return best;
}  
         
void update(Element x[SIZE][SIZE],int n,int k[2*SIZE],int l,int fl)
{   
    int i,j,m;
    float q[SIZE][SIZE];
    int f;
    if(fl==0)
    f = 65*n ;
    else
    { f = 900*fl ;
     /* printf(" f = %d  ",f) ;*/ }
    for(i=0;i<n;i++)
    for(j=0;j<n;j++) 
    q[i][j]=0;

    for(m=0;m<2*n;m=m+2)
    {   
        i=k[m];
        j=k[m+1];
        q[i][j]= power((f/l),3) ;
        q[j][i]=q[i][j];
     }
  
    for(i=0;i<n;i++)
    for(j=0;j<n;j++)
    x[i][j].p = ( 0.75*x[i][j].p ) + q[i][j] ;
    
}


void partition(Element x[SIZE][SIZE],int n,int k[2*SIZE],Element A[SIZE][SIZE],Element B[SIZE][SIZE],int p[SIZE],int q[SIZE],int a[2],int b[2],float sum[2])
{    
     int i,j,m=0,c,f,r[2];
     sum[0] = 0;
     int w[2*SIZE];
     int z[SIZE];
     int next = 0 ;
     for(i=0;i<n;i++)
     {   
         z[i] = 0;
     }
     
     for(i=0;i<(2*n);i++)
     {   
         w[i] = MAX;
     }
    
     c = 2 * GetRand(0,n-1) ;
     f = c/2;
  /*   printf(" \n %d \n ",c) ; */
     for(i=0;i < 2 * n;i=i+2)
     { 
         
        if(w[(2*k[i])] == MAX)
        w[(2*k[i])] = k[i+1];
        else
        w[(2*k[i]+1)] = k[i+1];
        if(w[(2*k[i+1])] == MAX)
        w[(2*k[i+1])] = k[i];
        else
        w[(2*k[i+1])+1] = k[i];
      }
    
    /* for(i=0;i<2*n;i++)
     {  printf("  %d  ",k[i] ) ; }
        printf(" \n ");  */
 /*    for(i=0;i<2*n;i++)
     {  
        
        printf("  %d  ",w[i] ) ; 
     }   
     */
     printf(" \n ");
     
     a[0] = w[c]; 
     if(w[2*w[c]] != f)
     b[0] = w[2*w[c]] ;
     else 
     b[0] = w[(2*w[c] +1)] ; 
     for(j=0,m=0;j < (n/2);c=m)
     { 
        if(z[w[c]]==0)
        {  
           p[j] = w[c] ;
           if(p[j]!=f)
          {sum[0] += x[c/2][p[j]].e ;
           /* printf("   %f  " ,sum[0] ) ; */
           }
           j++ ;
           z[w[c]] = 1 ;
           if(w[c] != f)
           m = 2 * w[c] ;
         }
 
         if(z[w[c+1]] == 0)
         {
            p[j] = w[c+1] ;
            if(p[j]!=f)
            {sum[0] += x[c/2][p[j]].e ; 
             /* printf("   %f  " ,sum[0] ) ;   */   
            }
            j++ ;
            z[w[c+1]] = 1 ;
            if(w[c+1] != f)
            m = 2* w[c+1] ;
          }
       
      }
     a[1] = p[j-1] ;
     if(z[w[2*p[j-1]]]==0)
     b[1] = w[2*p[j-1]];
     else 
     b[1] = w[2*p[j-1]+1] ;  
     sum[1] = (-sum[0] - x[a[0]][b[0]].e - x[a[1]][b[1]].e) ;   
     printf(" a0 = %d, a1 = %d,b0 = %d,b1 = %d",a[0],a[1],b[0],b[1]) ; 
     for(c=0,m=0;j<n;c++)
     {
         if(z[w[c]]==0)
         { q[m] = w[c] ;
           if(q[m] == b[0])
           r[0] = m;
           if(q[m] == b[1])
           r[1] = m;
           z[w[c]]=1 ; 
           j++;
           m++;
          }
      }  
     
     a[0] = 0;
     a[1] = n/2 -1 ;
     b[0] = r[0] ;
     b[1] = r[1] ;     
      
     for(i=0;i<(n/2);i++)
     for(j=0;j<(n/2);j++)
     {   
         if(i==j)
         { A[i][j].e = MAX ;
           A[i][j].flag = 1;
         }
         else 
         {  
            A[i][j].e = x[p[i]][p[j]].e ;   
            A[i][j].p = x[p[i]][p[j]].p ;
         }
      }
 
      m = (n/2) + (n%2) ;
      for(i=0;i<m;i++)
      for(j=0;j<m;j++)
      {   
         if(i==j)
         { B[i][j].e = MAX ;
           B[i][j].flag = 1;
         }
         else
         {  
            B[i][j].e = x[q[i]][q[j]].e ;   
            B[i][j].p = x[q[i]][q[j]].p ;
         }
      }
      
}          




void join(Element x[SIZE][SIZE],int n,Element A[SIZE][SIZE],Element B[SIZE][SIZE],int l[SIZE],int m[SIZE])
{
      int i,j,k;

      if(n%2==0)
      k=n/2;
      else
      k =(n/2)+1 ;  

      for(i=0;i<(n/2);i++)
      for(j=0;j<(n/2);j++)
      x[l[i]][l[j]].p = A[i][j].p ;
  
      for(i=0;i<k;i++)
      for(j=0;j<k;j++)
      x[m[i]][m[j]].p = B[i][j].p ;

}      


float raco(Element x[SIZE][SIZE],int n,int k[2*SIZE],int t)
{    
     float d1,d2,p,q,sum[2];
     int a,b,i,j ;
     sum[0] = 0;
     sum[1] = 0;
     int l[SIZE],m[SIZE],g[2],h[2],d[2*SIZE],p1[2*SIZE],p2[2*SIZE];
      
     d1 = optTSP(x,n,k,(int)(4*t/5),0);
     for(i=0;i<2*n;i++)
     d[i]=k[i]; 
    
/*   printf("\n"); 
     for(i=0;i<5;i++)
     for(j=0;j<5;j++)
     printf(" %f  ",x[i][j].p);  */ 
     if(n>70)
     {  Element A[SIZE][SIZE],B[SIZE][SIZE];
        
        partition(x,n,k,A,B,l,m,g,h,sum);
        sum[1] += d1 ;
        printf("\n total = %f , sum[0] = %f ,sum[1] =%f \n",d1,sum[0],sum[1]) ; 
        if(n%2==0)
        a= n/2;
        else
        a = (n/2 + 1);
        b = (int)(0.70*t) ;
        p=racoR(A,(n/2),p1,b,g,sum[0],n);
        q=racoR(B,a,p2,b,h,sum[1],n);
     /*   for(i=0;i<n-2;i++)
        printf(" %d  ",p1[i]);  */
        join(x,n,A,B,l,m);
        printf(" \n values of rec are %f , %f " ,p,q); 
     }  
     d2 = optTSP(x,n,d,(int)(t/5),1);
     if(d1<d2)
     { /* printf(" d1"); */
       return d1;
     }
     else
     { for(i=0;i<2*n;i++)
       k[i]=d[i];     
       return d2;
     }
     
}







float ACOr(Element x[SIZE][SIZE],int n,int k[2*SIZE],int a[2])
{   
    int i,j,c;   
 
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
    
    float sum1=0;
    int dest,g;
    int p=0;
    int z = 0;
    int source = a[z];
    int f = source ;
    x[f][n+1].flag = 1 ;
    g = a[1] ;
/*  printf("\n %d \n",source) ; */
    for(c=0;c<(n-1);c++)
    {  
       
          if(c==(n-2))
          dest=g;
          else
          dest = pseudorand(x,source,n,g,36,32);
          if(dest==n+1)
          { /* printf("error"); */
            return 0;  }
          x[source][n+1].flag++;
          x[dest][n+1].flag++;
          x[source][dest].flag++;
          x[dest][source].flag++;
          sum1+=x[source][dest].e;
          k[p]=source;
 /*       printf("  %d,%d  ",source,dest); */ 
          k[++p]=dest;
          p++;
          source = dest ;
         }
/*    printf("  %d  ",sum1);   */
         return sum1;
     
}


void partitionR(Element x[SIZE][SIZE],int n,int k[2*SIZE],Element A[SIZE][SIZE],Element B[SIZE][SIZE],int p[SIZE],int q[SIZE],int a[2],int b[2],float sum[2])
{    
     int i,j,m=0,c,f;
     sum[0] = 0 ;
     sum[1] = 0 ;
     int w[2*SIZE];
     int z[SIZE];
     int next = 0 ;
     
     a[0] = 0 ;
     b[1] = (n/2)+(n%2)-1 ;
   
     
     for(i=0;i<n;i++)
     {   
         z[i] = 0;
     }
     printf("\n %d \n",n);
     for(i=0;i<(2*n-2);i++)
     {   
         printf(" %d ",k[i]);
     }
     printf("\n");
/*    for(i=0;i<(2*n);i++)
     {   
         w[i] = MAX;
     }
    
     c = 2 * GetRand(0,n-1) ;
     f = c/2;
     printf(" \n %d \n ",c) ;
     for(i=0;i < 2 * n;i=i+2)
     { 
         
        if(w[(2*k[i])] == MAX)
        w[(2*k[i])] = k[i+1];
        else
        w[(2*k[i]+1)] = k[i+1];
        if(w[(2*k[i+1])] == MAX)
        w[(2*k[i+1])] = k[i];
        else
        w[(2*k[i+1])+1] = k[i];
      }
    
     for(i=0;i<2*n;i++)
     {  printf("  %d  ",k[i] ) ; }
        printf(" \n ");
     for(i=0;i<2*n;i++)
     {  
        
        printf("  %d  ",w[i] ) ; 
     }   
     
     printf(" \n ");       
     a[0] = w[c]; 
     if(w[2*w[c]] != f)
     b[0] = w[2*w[c]] ;
     else 
     b[0] = w[(2*w[c] +1)] ; */
     
     for(i=0,j=0;j < (n/2);i++)
     { 
        if(z[k[i]]==0)
        {  
           p[j] = k[i] ;
           if(i!=0)
           {  sum[0] += x[p[j]][p[j-1]].e ;
              
           }

           z[k[i]] = 1 ;
           j++ ;
         }
        
     }
     a[1] = j-1;
     sum[1] = - sum[0] - x[k[i]][k[i+1]].e ;
     i=i+2; 
     m=0;
     int r = 0 ;
     while(m < (n/2 +(n%2)))
     { 
        if(z[k[i]]==0)
        {  
           q[m] = k[i] ;
          /* if(i%2 != 0)
           { sum[1] += x[k[i]][k[i-1]].e ;
            }*/
           z[k[i]] = 1 ;
           
           m++;
           i++ ;
         }
        else
           i++;
     }  
     
     b[0] = 0 ;
 /*  if(z[w[c+1]] == 0)
         {
            p[j] = w[c+1] ;
          
            j++ ;
            z[w[c+1]] = 1 ;
            if(w[c+1] != f)
            m = 2* w[c+1] ;
          }  
       
      }
     a[1] = p[j-1] ;
     if(z[w[2*p[j-1]]]==0)
     b[1] = w[2*p[j-1]];
     else 
     b[1] = w[2*p[j-1]+1] ;  
     sum[1] = (-sum[0] - x[a[0]][b[0]].e - x[a[1]][b[1]].e) ;   
     printf(" a0 = %d, a1 = %d,b0 = %d,b1 = %d",a[0],a[1],b[0],b[1]) ; 
     for(c=0,m=0;j<n;c++)
     {
         if(z[w[c]]==0)
         { q[m] = w[c] ;
           if(q[m] == b[0])
           b[0] = m;
           if(q[m] == b[1])
           b[1] = m;
           z[w[c]]=1 ; 
           j++;
           m++;
          }
         
     }  
     
     a[0] = 0;
     a[1] = n/2 -1 ;
*/      
     printf(" a0 = %d, a1 = %d,b0 = %d,b1 = %d",a[0],a[1],b[0],b[1]) ; 
     for(i=0;i<(n/2);i++)
     for(j=0;j<(n/2);j++)
     {   
         if(i==j)
         { A[i][j].e = MAX ;
           A[i][j].flag = 1;
         }
         else 
         {  
            A[i][j].e = x[p[i]][p[j]].e ;   
            A[i][j].p = x[p[i]][p[j]].p ;
         }
      }
 
     
      for(i=0;i<m;i++)
      for(j=0;j<m;j++)
      {   
         if(i==j)
         { B[i][j].e = MAX ;
           B[i][j].flag = 1;
         }
         else
         {  
            B[i][j].e = x[q[i]][q[j]].e ;   
            B[i][j].p = x[q[i]][q[j]].p ;
         }
      }
      
}          

float optTSPr(Element x[SIZE][SIZE],int n,int k[2*SIZE],int t,int a[2],float best,int fl)
{   
    int i=0,p,flag = 0;
    float j;
    int l[2*SIZE];
    while(i<t) 
    {    
         j= ACOr(x,n,k,a);
         
         if(j!=0 && j<best)
         {  flag = 1 ; 
            best=j; 
            for(p=0;p<2*n;p++)
            l[p]=k[p];
            
            update(x,n,k,best,fl);
            }
          i++;
     }
     if(flag==1)
     {
      for(p=0;p<2*n;p++)
            k[p]=l[p];
      }
      return best;
}  

float racoR(Element x[SIZE][SIZE],int n,int k[2*SIZE],int t,int arr[2],float best,int fl)
{    
     float d1,d2,p,q,sum[2] ;
     int p1[2*SIZE],p2[2*SIZE],i,a,b ;
     sum[0] = 0;
     sum[1] = 0;
     int l[SIZE],m[SIZE],g[2],h[2];
     d1 = optTSPr(x,n,k,1,arr,MAX,(fl/20));
     d1 = optTSPr(x,n,k,(3*t/5),arr,best,fl);
     /*for(i=0;i<2*n;i++)
       d[i]=k[i];*/ 
    
     if(n>70)
     {  Element A[SIZE][SIZE],B[SIZE][SIZE];
        float check =0;
        int r=0;
        partitionR(x,n,k,A,B,l,m,g,h,sum);
        sum[1] += d1 ; 
        printf("\n total = %f , sum[0] = %f ,sum[1] =%f \n",d1,sum[0],sum[1]) ;
        if(n%2==0)
        a= n/2;
        else
        a = (n/2 + 1);
        b = (int)(0.65*t)  ;
        p=racoR(A,(n/2),p1,b,g,sum[0],(fl*2));
        opt2(A,(n/2),p1,p,g);
        q=racoR(B,a,p2,b,h,sum[1],(fl*2));
        opt2(B,a,p2,q,h);
        join(x,n,A,B,l,m);
        printf(" \n values of rec are %f , %f " ,p,q);
/*        check = p + q ;
        if(check < (sum[0] + sum[1]))       
        {    
           
           printf(" check = %f,p = %f q = %f ",check,p,q);
           for(i=0;i<n;i++)
           {  k[i] = l[p1[i]]; }
           k[n] = l[p1[n-1]] ;
           printf(" p1[n-1] = %d k[n-1] =%d",l[p1[n-1]],k[n-1]);
           k[n+1] = m[p2[0]] ;
           for(i = n+2;i< 2*n;i++)
          { k[i] = m[p2[(i-n-2)]]; }
            d1 = check + x[l[p1[n-1]]][m[p2[0]]].e ; 
        } */
      }
     d2 = optTSPr(x,n,k,(int)(2*t/5),arr,d1,fl);
     if(d1<d2)
     {  printf(" d1 = %f ",d1) ; 
       return d1;
     }
     else
     { /*for(i=0;i<2*n;i++)
         k[i]=d[i];*/     
       return d2;
     }
     
} 
  

void opt2(Element x[SIZE][SIZE],int n,int k[2*SIZE],float best,int arr[2])
{
     int temp,i,j,g,h;
     
     for(i = 0;i < (n - 5);i=i+2)
     for(j = i + 4; j < (n - 1) ;j = j + 2)
     {
         if( ((x[k[i]][k[i + 1]].e + x[k[j]][k[j + 1]].e) - (x[k[i]][k[j]].e + x[k[i + 1]][k[j + 1]].e)) > 0)
           {
              best = best - ( (x[k[i]][k[i + 1]].e + x[k[j]][k[j + 1]].e) - (x[k[i]][k[j]].e + x[k[i + 1]][k[j + 1]].e)) ;
              temp = k[i+1] ;
              k[i+1] = k[j] ;
              k[j] = temp ;
           
              
              printf(" best = %f ",best);
           }
     }
     update(x,n,k,best,3*n);
}
  
       



