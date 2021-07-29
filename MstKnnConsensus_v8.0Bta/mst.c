#include "mst.h"

int minValue(double key[], int mstSet[],int n)
{
   double min = INT_MAX;
   int min_index;
   int v;
   //int n;
   
   //n=N_NODOS;
   
   //printf("\n");
  //for (v = 0; v < n; v++)
   //{
    //printf("key[%d]=%lf\n",v,key[v]);
     
   //}
   
   //printf("\n");
   for (v = 0; v < n; v++)
   {
     
     //printf("if(mst[%d]==0 && key[%d]<%lf)\n",v,v,min);
     if (mstSet[v] == 0 && key[v] < min)
     {
         //printf("mstSet[%d]=%d\n",v,mstSet[v]);
	 //printf("key[%d]=%lf\n",v,key[v]);
	 min = key[v], min_index = v;
	 //printf("\nmin= key[%d]=%lf, min_index=v=%d\n",v,min,min_index);
     }

   }
   return min_index;
}

struct MST* mstInput(int parent[],struct MATRIX2 **graphMST)
{
   int i,n;
   n=graphMST[0][0].length;
   //printf("\n");
   
   MST *mst = malloc(n*sizeof(struct MST));
   mst[0].length=n;
   
   for (i = 0; i < n; i++)
   {
      
     
      mst[i].parent=parent[i];
      mst[i].distance=graphMST[i][parent[i]].distance;
      mst[i].key=graphMST[i][0].key;


      strcpy(mst[i].id,graphMST[i][0].id);
      
      //printf("[%d][%s]-[%d] %lf \n",i,mst[i].id,mst[i].parent,mst[i].distance);
      
      
      
   }
   
   return mst;
}



struct MST* primAlgorithm2(struct MATRIX2 **graphMST)
{
     
     int n;
     
     n=graphMST[0][0].length;
     
     int parent[n]; // vector MST
     double key[n];   // vector para almacenar la minima distancia
     int mstSet[n];  // conjunto de vertices no incluidos en MST

     // inicialización hasta INT_MAX
     int i;
     for (i = 0; i < n; i++)
     {
       
       key[i] = INT_MAX;//tiende a infinito
       mstSet[i] = 0;
       parent[i]=0;
     }
     //inicializacio vertices
     key[0] = 0;     
     //parent[0] = -1; 
     
     

     
     int count;
     int u; 
     int v;
     // se recorre hasta V-1 vertices
     for (count = 0; count < n-1; count++)
     {
        u= minValue(key, mstSet,n);
        mstSet[u] = 1;
	
	//printf("\nminValue=%d\n",u);
	
        
        for (v = 0; v < n; v++)
	{

	  if ((graphMST[u][v].distance && mstSet[v] == 0) && graphMST[u][v].distance <  key[v])
	  {
	    parent[v]  = u;
            key[v] = graphMST[u][v].distance;
	    //printf("\n");
	    //printf("parent[%d]=%d\n",v,u);
	    //printf("key[%d]=%lf\n",v,key[v]);
	  }
	}	
	//printf("--------------------------------------------------------------------------------");	
	//if(count==1)break;
     }
     
  
     //struct MST *mst2;
  
     //return (struct MST*)mst2;
     return mstInput(parent,graphMST);
    //mstInput(parent, graphMST);
    //return 1; 
     
    
}



