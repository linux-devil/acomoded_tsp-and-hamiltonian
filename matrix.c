#include"matrix.h"


void ordermat(int* m[100],int n)
{    int i,j;
     for(i=0;i<n;i++)
     { quickSort(m[i],0,n-1) ;
     }
}  


void quickSort(int m[],int start,int end)
{    int pivPos;
          if(start<end)
          {  pivPos=partition(selectPiv(m,(end-start)),m,start,end) ;
             quickSort(m,start,pivPos-1);
             quickSort(m,pivPos+1,end);
           }
}


int pivPos(int k,int m,int start,int end)
{
     while (start < end)
  {
    while ((m[end] >= k) && (start < end))
      end--;
    if (start != end)
    {
      m[start] = m[end];
      start++;
    }
    while ((m[start] <= k) && (start < end))
      start++;
    if (start != end)
    {
      m[end] = m[start];
      end--;
    }
}
    

