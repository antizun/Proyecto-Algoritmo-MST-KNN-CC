#include "knn.h"
void insertionSort(struct KNN **gknn,int index) 
{


      int i, j,n;
      double tmp;
      char id[50];
      int key;

      n=gknn[0][0].length;      
      
      for (i = 1; i < n; i++)
      {
	  j = i;

            
	     while (j > 0 && gknn[index][j-1].distance > gknn[index][j].distance) {

                  tmp = gknn[index][j].distance;

		  
                  gknn[index][j].distance = gknn[index][j-1].distance;
                  gknn[index][j-1].distance = tmp;
		 
		  /////////////////////////////////////////////////////////
		  //KEY
		  key=gknn[index][j].key;
		  gknn[index][j].key=gknn[index][j-1].key;
		  gknn[index][j-1].key=key;
		  /////////////////////////////////////////////////////////
		  

		  
                  j--;

            }

      }


}

struct KNN** knnAlgorithm(struct MATRIX2 **matrix)
{
  int i,j,n;
  //struct GKNN *knn = malloc(matrix[0].length*sizeof(struct GKNN));
  
  KNN **knn=(KNN**)malloc(matrix[0][0].length*sizeof(KNN*));
  for(i=0;i<matrix[0][0].length;i++)knn[i]=(KNN*)malloc(matrix[0][0].length*sizeof(KNN));
  
  
  
  n=matrix[0][0].length;
  knn[0][0].length=n;
  
  for(i=0;i<n;i++)
  {
    strcpy(knn[i][0].id,matrix[i][0].id);
    for(j=0;j<n;j++)
    {
        //strcpy(knn[i][j].id,matrix[i][j].id);
        knn[i][j].key=matrix[i][j].key;
	knn[i][j].distance=matrix[i][j].distance;
      
    }
  }
    i=0;j=0;
    for(i=0;i<n;i++)
    {
	  insertionSort(knn,i);
	  //printf("id:%s",knn[i][0].id);
	  
// 	  for(j=0;j<n;j++)
// 	  {
// 	    if(knn[i][j].distance!=0)
// 	    {
// 
// 	      printf("[%d %d;%lf]\n",i,knn[i][j].key,knn[i][j].distance); 
// 	    }
// 	   
// 	  }
// 	  if(i==0)exit(0);
// 	  printf("\n\n");  
    }

    return knn;
    
  
}

