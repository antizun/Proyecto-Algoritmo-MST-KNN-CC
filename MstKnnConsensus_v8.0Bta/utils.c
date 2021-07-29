#include "utils.h"
#include "knn.h"


void dfsKnn(int **graph,int index,int reach[],int n)
{
 int i;
 reach[index]=1;
 for(i=0;i<n;i++)
 {  
    if(graph[index][i]>0 && !reach[i]==1)
    {
        //printf("\n %d->%d",index,i);
	return dfsKnn(graph,i,reach,n);
    }
 }
 return;
 
 //return reach;
}

int isConnected(int reach[],int n)
{
 int i=0,count=0; 
 
 for(i=0;i<n;i++)
 {
  if(reach[i])
   count++;
 }
 
  if(count==n)
  {
    
    //printf("conexo");
    return 1;
  }
  else
  {
    //printf("no conexo"); 
    return 0;
  }
    
 
}

