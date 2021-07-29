#include "mst.h"
#include "knn.h"
int mstKnnConsensus(struct G_CLUSTER2 **cluster,struct MATRIX2 **matrix,int flag2,int sz);	
struct MATRIX2** init();
int** interMstKnn2(struct MST *gmst,struct KNN **gknn,int _K);
void initCluster(struct G_CLUSTER2 **cluster);
void addCluster(struct G_CLUSTER2 **cluster,struct MATRIX2 **matrix,int index,int row,int column);
struct MATRIX2** createMatrix(struct MATRIX2 **matrix,int reach[],int n);
int** knnConnected(struct KNN **gknn,int _K);
int nRowCluster(struct G_CLUSTER2 **cluster);
void printITT(struct G_CLUSTER2 **cluster,int length);
int buscarPosMatrix(char id[50]);
void printCluster(struct G_CLUSTER2 **cluster);




struct MATRIX2 **matrix;

int main()
{

  
  int flag,i,j,n,k,it,cl,row,column;
  int posFirstObj;
  
  
  int id_key,id_parent;
  double aux_distance=0,sumaDist=0;
  
  
   int itt_inter[N_NODOS-1][N_NODOS-1];
   i=0,j=0;
   for(i=0;i<(N_NODOS-1);i++){for(j=0;j<(N_NODOS-1);j++){itt_inter[i][j]=0;}}    
   

   double jaccard_index[N_NODOS-1][N_NODOS-1];
   i=0,j=0;
   for(i=0;i<(N_NODOS);i++){for(j=0;j<(N_NODOS);j++){jaccard_index[i][j]=0;}}    


   double jaccard_index2[N_NODOS][N_NODOS];
   i=0,j=0;
   for(i=0;i<(N_NODOS);i++){for(j=0;j<(N_NODOS);j++){jaccard_index2[i][j]=0;}}    
   
   
   
   
   int ji_correlacion[N_NODOS-1][N_NODOS-1];
   i=0,j=0;
   for(i=0;i<(N_NODOS-1);i++){for(j=0;j<(N_NODOS-1);j++){ji_correlacion[i][j]=0;}}    
   
   int ji_correlacion_aux[N_NODOS-1][N_NODOS-1];
   i=0,j=0;
   for(i=0;i<(N_NODOS-1);i++){for(j=0;j<(N_NODOS-1);j++){ji_correlacion_aux[i][j]=0;}}    


   int ji_correlacion_aux2[N_NODOS-1][N_NODOS-1];
   i=0,j=0;
   for(i=0;i<(N_NODOS-1);i++){for(j=0;j<(N_NODOS-1);j++){ji_correlacion_aux2[i][j]=0;}}    
   
   
   
   double sum_consensus=0;
   float j_index=0;
   double media=0;
   double ds=0;
   double var_ninversa=0;
   double min_ds=1000;
   int id_particion;
   int R=0;
   int U=0;
   int V=0;
   
   
  
    
  
   matrix=init();

  
  MST *mst;
  mst = primAlgorithm2(matrix);
  
  
  ITT *itt;
  itt=(ITT*)malloc((N_NODOS-1)*sizeof(ITT*));
  
  i=0,j=0,k=0;
  for(i=0;i<mst[0].length;i++)
  {


      flag=0;
      
      G_CLUSTER2 **cluster=(G_CLUSTER2**)malloc(N_NODOS*sizeof(G_CLUSTER2*));
      for(k=0;k<N_NODOS;k++)cluster[k]=(G_CLUSTER2*)malloc(N_NODOS*sizeof(G_CLUSTER2));

      cluster[0][0].length=N_NODOS;
      initCluster(cluster);

      
//      for(i=0;i<mst[0].length;i++)
// 	printf("%s %d %lf\n",mst[i].id,mst[i].parent,mst[i].distance);
//       exit(0);
      
      if(mst[i].distance>0)
     {
      
	/////////////////////////////////////////////////////////
	//D-ei tal que ei-->inf
	id_key=mst[i].key;
	id_parent=mst[i].parent;

	
        //printf("[ITERACION %d]MATRIX[%d][%d]:%lf-----------------------------\n",i,id_key,id_parent,matrix[id_key][id_parent].distance); 
	
	aux_distance=matrix[id_key][id_parent].distance;
	matrix[id_key][id_parent].distance=1000;// se fuerza distancia para no volver a recorrer
	/////////////////////////////////////////////////////////
	
	
	
	
	mstKnnConsensus(cluster,matrix,0,matrix[0][0].length);
	
	//printCluster(cluster);
	
	matrix[id_key][id_parent].distance=aux_distance;
	

	k=0;  
	itt[i].key=i;	
        itt[i].cluster=(G_CLUSTER2**)malloc((nRowCluster(cluster))*sizeof(G_CLUSTER2));
	
	
	
	for(k=0;k<nRowCluster(cluster);k++)itt[i].cluster[k]=(G_CLUSTER2*)malloc(N_NODOS*sizeof(G_CLUSTER2));
	
 	for(row=1;row<nRowCluster(cluster);row++)
 	{
 	  for(column=0;column<N_NODOS;column++)
 	  {
 	    itt[i].cluster[row][column].c=0;
 	  }
 	}

	row=0,column=0;
	
	for(row=0;row<nRowCluster(cluster);row++)
	{
	
	  //printf("%d %s\n",i,cluster[row][0].id);   
	  
	  posFirstObj=buscarPosMatrix(cluster[row][0].id);
	  sumaDist=0;
	  for(column=0;column<N_NODOS;column++)
	  {
	    
	    
	    if(cluster[row][column].c==1) 
	    {
	  
	      
	      strcpy(itt[i].cluster[row][column].id,cluster[row][column].id);
	      itt[i].cluster[row][column].c=1;
	      itt[i].cluster[row][column].key=buscarPosMatrix(cluster[row][column].id);
	      
	      sumaDist+=matrix[posFirstObj][itt[i].cluster[row][column].key].distance;
	      //printf("%lf %s\n",sumaDist,cluster[row][column].id);
	    }
	  }
	  itt[i].cluster[row][0].group=(1000-sumaDist);
	  //printf("%d %s %lf\n",posFirstObj,cluster[row][0].id,sumaDist);
	  //exit(0);
	}
	itt[i].length=nRowCluster(cluster);
	printf("\nITT[%d]-----------------\n",i);
	printITT(itt[i].cluster,nRowCluster(cluster));
	cluster=NULL;
	free(cluster);
     }
  }
  
	
      i=0,j=0,row=0,column=0;
      
      int row2=0,column2=0,aux=0,key=-1,inter=0,r=0,c=0,aux_p2=0;
      
      
      for(aux=0;aux<mst[0].length;aux++) //por la primera itt
      {
      U=0,R=0,V=0;
      if(mst[aux].distance>0)	
      {
	  row=0;column=0,row2=0,column2=0;
	  inter=0;
	  
	  //POR CADA UNO DE LAS ITERACIONES SE DEFINIEN LOS GRUPOS QUE SON ALMACENADOS EN UNA MATRIZ AUXILIAR JI_CORRELACION
	  for(row=0;row<itt[aux].length;row++) //por cada una de las filas
 	  {
	      
	      if(itt[aux].cluster[row][0].c==1) //limite cluster
	      {
		posFirstObj=buscarPosMatrix(itt[aux].cluster[row][0].id);
		for(column=0;column<N_NODOS;column++) //por cada una de las columnas
		{
		  if(itt[aux].cluster[row][column].c==1) //limite cluster columna
		  {
			      ji_correlacion[posFirstObj][itt[aux].cluster[row][column].key]=1;//segundo grupo
			      //ji_correlacion[itt[aux].cluster[row][column].key][posFirstObj]=1;//segundo grupo
		    
		  }
		  
		}
	      }
	  }
	  
	  
	  
	  
	  for(aux_p2=aux+1;aux_p2<mst[0].length;aux_p2++) //OK
	  {
	    //printf("aux:%d,aux2:%d\n",aux,aux_p2);
		row2=0;column2=0,r=0,c=0;
		for(row2=0;row2<itt[aux_p2].length;row2++)
		{
		      if(itt[aux_p2].cluster[row2][0].c==1) 
		      {
			  posFirstObj=buscarPosMatrix(itt[aux_p2].cluster[row2][0].id);
			  for(column2=0;column2<N_NODOS;column2++) //por cada una de las columnas
			  {
			    if(itt[aux_p2].cluster[row2][column2].c==1) //limite cluster columna
			    {
				     ji_correlacion_aux[posFirstObj][itt[aux_p2].cluster[row2][column2].key]=1;//segundo grupo
				     //ji_correlacion_aux[itt[aux_p2].cluster[row2][column2].key][posFirstObj]=1;//segundo grupo
				     //ji_correlacion_aux[posFirstObj][itt[aux_p2].cluster[row2][column2].key]=1;//segundo grupo
			    }
			  }
		      }
		 }
		i=0;j=0; 
		for(i=0;i<N_NODOS;i++)
		{
		  for(j=0;j<N_NODOS;j++)
		  {
		       if(j!=i)
		       {
		       if(ji_correlacion[i][j]==1 && ji_correlacion_aux[i][j]==1)
			{
			  ji_correlacion_aux2[i][j]=2;//interseccion
			  //ji_correlacion_aux2[j][i]=2;//interseccion
			}
			if(ji_correlacion[i][j]==0 && ji_correlacion_aux[i][j]==1)
			{
			    ji_correlacion_aux2[i][j]=3;//part_2
			    //ji_correlacion_aux2[j][i]=3;//part_2 
			}
			if(ji_correlacion[i][j]==1 && ji_correlacion_aux[i][j]==0)
			{
			      ji_correlacion_aux2[i][j]=1;//part_1
			      //ji_correlacion_aux2[j][i]=1;//part_1
			}
		       }
		  }
		  
		}	 
		
		

		i=0,U=0,R=0,V=0,j_index=0;
		for(i=0;i<N_NODOS-1;i++)
		{
		  for(j=0;j<N_NODOS-1;j++)
		  {
		      if(ji_correlacion_aux2[i][j]==1)
			U+=1;
		      if(ji_correlacion_aux2[i][j]==2)
			R+=1;
		      if(ji_correlacion_aux2[i][j]==3)
			V+=1;
		    
		  }
		    
		}      
		//U=U-1;
		//printf("[%d][%d]\n",aux,aux_p2);//exit(0);
		j_index=(double)(R/(double)(U+V+R));
// // //   	        if(aux_p2==8)
// // // 		{
// // // 
// // // 			for(i=0;i<N_NODOS-1;i++)
// // // 			  {
// // // 			    for(j=0;j<N_NODOS-1;j++)
// // // 			    {
// // // 			      printf("%d",ji_correlacion_aux[i][j]);
// // // 			    }
// // // 			    printf("\n");
// // // 			  }
// // // 		          //exit(0);
// // // 		          printf("---------------------------------------------------------------\n");
// // // 		  
// // // 		  
// // // 		          for(i=0;i<N_NODOS-1;i++)
// // // 			  {
// // // 			    for(j=0;j<N_NODOS-1;j++)
// // // 			    {
// // // 			      printf("%d",ji_correlacion_aux[i][j]);
// // // 			    }
// // // 			    printf("\n");
// // // 			  }
// // // 		          
// // // 		          printf("---------------------------------------------------------------\n");
// // // 		  
// // // 		          for(i=0;i<N_NODOS-1;i++)
// // // 			  {
// // // 			    for(j=0;j<N_NODOS-1;j++)
// // // 			    {
// // // 			      printf("%d",ji_correlacion_aux2[i][j]);
// // // 			    }
// // // 			    printf("\n");
// // // 			  }
// // // 			
// // //  		  printf("%d-%d[U:%d][V:%d][R:%d]%lf\n",aux,aux_p2,U,V,R,j_index);
// // //  		  //exit(0);
// // // 		  
// // // 		}
		jaccard_index[aux][aux_p2]=j_index;
		jaccard_index[aux_p2][aux]=j_index;

		//i=0,j=0;
		for(i=0;i<N_NODOS;i++)
		{
		  for(j=0;j<N_NODOS;j++)
		  {
		    ji_correlacion_aux[i][j]=0;
		    ji_correlacion_aux2[i][j]=0;
		  }
		}
	    
	    }// FIN FOR 2	  
	    
	}
	for(i=0;i<N_NODOS;i++){for(j=0;j<N_NODOS;j++){ji_correlacion[i][j]=0;ji_correlacion_aux[i][j]=0;ji_correlacion_aux2[i][j]=0;}}
	//i=aux;
	U=0,V=0,R=0;
      
      }// FIN FOR 1

      //printf("aux:%d,aux2:%d",aux,aux_p2);
//exit(0);	
//printf("-----------\n");
      //exit(0);	

// // // // //intersecciones
// // // // printf("---------------------------------------------------------------\n");
// // // // printf("Matriz Inter Particiones\n");
// // // // printf("---------------------------------------------------------------\n");
// // // // 	for(i=1;i<(N_NODOS-1);i++)
// // // // 	{
// // // // 	  for(j=1;j<(N_NODOS-1);j++)
// // // // 	  {
// // // // 	    printf("[%d]",itt_inter[i][j]);
// // // // 	  }
// // // // 	  printf("\n");
// // // // 	}     	  
// // // // printf("---------------------------------------------------------------\n");	
//printf("Jaccard Index\n");
//printf("---------------------------------------------------------------\n");

	//printf("\t\t");
// // 	printf("\t\t");
// // 	for(i=0;i<N_NODOS;i++)
// // 	  printf("\t%s",matrix[i][0].id);
// // 	printf("\n");
// // 	for(i=0;i<N_NODOS;i++)
// // 	{
// // 	  printf("\t%s",matrix[i][0].id);
// // 	  for(j=0;j<N_NODOS;j++)
// // 	  {
// // 	    
// // 	   printf("\t\t[11111]");
// // 	  }
// // 	  printf("\t\n");
// // 	}  
// // 
// // 	exit(0);  


        for(i=1;i<(N_NODOS);i++)
	{
	  for(j=1;j<(N_NODOS);j++)
	  {
	    if(i==j)
	      jaccard_index[i][j]=1;
	    printf("[%lf]",jaccard_index[i][j]);
	    //printf("[%d][%d]\n",i,j);
	  }
	  printf("\n");
	}     	  
	//exit(0);
printf("---------------------------------------------------------------\n");

//exit(0);
/////////////////////////////////////////////////////////////////////////////////////
//CONSENSUS CLUSTERING



/////////////////////////////////////////////////////////////////////////////////////
//proMedioS IndiViduAles

printf("Suma Prom Jaccard Index por particiones\n");
printf("---------------------------------------------------------------\n");
	i=0,j=0;
	for(i=1;i<(N_NODOS);i++)
	{
	  sum_consensus=0;
	  for(j=1;j<(N_NODOS);j++)
	  {
	    //if(i!=j)
	      sum_consensus+=jaccard_index[i][j];
	    //printf("[%lf]",jaccard_index[i][j]);
	  }
	  itt[i].consensus=(sum_consensus)/((double)(N_NODOS-1));
	  
	  printf("[%d] \t [%lf]\n",i,itt[i].consensus);
	}     	  
printf("---------------------------------------------------------------\n");
/////////////////////////////////////////////////////////////////////////////////////
	
/////////////////////////////////////////////////////////////////////////////////////
//Media AritmEtiK
/////////////////////////////////////////////////////////////////////////////////////
	printf("\n");
printf("Media Aritmetica\n");	
printf("---------------------------------------------------------------\n");
	i=0,j=0,sum_consensus=0;;
	for(i=1;i<(N_NODOS);i++)
	{
	  sum_consensus+=itt[i].consensus;	
	}   	
        //media
	media=sum_consensus/(double)(N_NODOS-1);
	printf("\n");
	
	printf("Media:[%lf]\n",media);
printf("---------------------------------------------------------------\n");
/////////////////////////////////////////////////////////////////////////////////////	

/////////////////////////////////////////////////////////////////////////////////////	
//DesViaCion Standar
/////////////////////////////////////////////////////////////////////////////////////	
printf("Desviacion Estandar, la minima desviacion sera considerada para determinar el cluster final\n");		
printf("---------------------------------------------------------------\n");
	i=0,sum_consensus=0;;
	for(i=1;i<(N_NODOS);i++)
	{
	  var_ninversa=(double)((1)/(double)(N_NODOS-1));
	  itt[i].ds=sqrt(var_ninversa*(itt[i].consensus-media)*(itt[i].consensus-media));	
	  printf("[%d] \t [%lf]\n",i,itt[i].ds);
	  
	  
	  if(itt[i].ds<min_ds && itt[i].ds!=0)
	  {
	    min_ds=itt[i].ds;
	    id_particion=i;
	  }
	    
	}
printf("---------------------------------------------------------------\n");
/////////////////////////////////////////////////////////////////////////////////////	

printf("Desviacion Estandar-Id particion con DS minima\n");
printf("---------------------------------------------------------------\n");
	printf("desviacion minima:[%lf]\n",min_ds);
	printf("ID Particion:%d\n",id_particion);
printf("---------------------------------------------------------------\n");

/////////////////////////////////////////////////////////////////////////////////////	
//ClusTer FinaL
/////////////////////////////////////////////////////////////////////////////////////	

printf("Cluster Final, Consensus Clustering\n");
printf("---------------------------------------------------------------\n");
      i=0,row=0,column=0;	
      for(row=1;row<itt[id_particion].length;row++)
      {
 	  for(column=0;column<N_NODOS;column++)
 	  {
	      if(itt[id_particion].cluster[row][column].c==1) 
	      {
		printf("[%s]",itt[id_particion].cluster[row][column].id);   
		
	      }
 	  }
 	  printf("\n");
       }
printf("---------------------------------------------------------------\n");
// // // // /////////////////////////////////////////////////////////////////////////////////////	
	
  
  
  itt=NULL;
  free(itt);
  //for(i=0;i<mst[0].length;i++)
  return 0;

}
int buscarPosMatrix(char id[50])
{
    int i,j,key=-1;
    
    for(i=0;i<N_NODOS;i++)
    {
	//printf("%s\n",matrix[i][0].id);
        if(strcmp(id,matrix[i][0].id)==0)
	  key=matrix[i][0].key;
    }  
    return (key);
}

void printCluster(struct G_CLUSTER2 **cluster)
{

  int i,j;
      for(i=0;i<N_NODOS;i++)
      {
	for(j=0;j<N_NODOS;j++)
	{
	  if(cluster[i][j].c==1) 
	  {
	    printf("[%s]",cluster[i][j].id);
	  }
	}
	if(cluster[i][0].c==1)
	{
	  printf("\n");
	}
	
      }
  
  
}

void printITT(struct G_CLUSTER2 **cluster,int length)
{

  int i,j;
      for(i=0;i<length;i++)
      {
	for(j=0;j<N_NODOS;j++)
	{
	  if(cluster[i][j].c==1) 
	  {
	    printf("[%s]",cluster[i][j].id);
	  }
	}
	if(cluster[i][0].c==1)
	{
	  printf("\n");
	}
	
      }
  
  
}

int nRowCluster(struct G_CLUSTER2 **cluster)
{
      int i=0,cont=0;
      for(i=0;i<N_NODOS;i++)
      {
	if(cluster[i][0].c==1)
	  cont++;
	else
	  return cont;
      }
      return cont;
}

void initCluster(struct G_CLUSTER2 **cluster)
{
  int i,j;
  for(i=0;i<N_NODOS;i++)
  {
    for(j=0;j<N_NODOS;j++)
    {
      cluster[i][j].c=0;
      cluster[i][j].distance=0;
    }
      
  }
  return;
}
void initReach(int reach[],int n)
{
  int i;
  for(i=0;i<n;i++)
  {
    reach[i]=0;
  }
  return;
}
int mstKnnConsensus(struct G_CLUSTER2 **cluster,struct MATRIX2 **matrix,int flag2,int sz)
{
  int i=0,j=0,n=0,c=0,index=0,k=0,lg=0;
  
  struct KNN **knn;
  struct MST *mst;
  struct G_CLUSTER2 **gCluster;
  
  struct MATRIX2 **mat;
  
  int *reach;
  
  int *aux;
  
  int flag=0,flag_log=0,flag_knn;
  int visitado=0;
  int no_visitado=0;
  int row=0,column=0;;
  int **matAdj;
  int flag_ei=0;
  int id_key;
  int id_parent;

  matAdj=NULL;
  
  //printf("sz=%d\n",sz);
  

  reach = malloc(sz*sizeof(int));
  aux = malloc(sz*sizeof(int));
  mat=matrix;
  
  ///////////////////////////////////////////////////////
  //PRIM ALGORITHM
  mst=primAlgorithm2(mat);  
  ///////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////
  //KNN ALGORITHM
  knn=knnAlgorithm(mat); 
  ///////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////
  //Log natural
   ///////////////////////////////////////////////////////
  lg=(int)log(sz);
  
  //printf("%d,%lf\n",lg,log(sz));
  
  
//   matAdj=knnConnected(knn,lg);
//   
// 
//   
//   initReach(reach,sz);
//   dfsKnn(matAdj,0,reach,sz);
//   flag_log=isConnected(reach,sz);


  ///////////////////////////////////////////////////////
  // se determina el minimo Ginn donde Ginn es conexo
   flag_knn=0,k=1; 
   
   while(flag_knn==0 && k<sz)
   {
      
      free(matAdj);
      matAdj=NULL;
      matAdj=knnConnected(knn,k);
      
      
      initReach(reach,sz);
      dfsKnn(matAdj,0,reach,sz);
      flag_knn=isConnected(reach,sz);
      
      if(flag_knn==1)
      {
	break;
      }
      k=k+1;
   }
   //printf("%d\n",flag_log);exit(0);

  
  // Si el grafo es conexo, se elije el menor entre el logaritmo y la minima cantidad de veces donde Gin es conexo
  if(flag_knn==1)
  {
    if(lg<k)
      k=lg;
  }
	
  
  //printf("%d\n",k);exit(0);
  
  //printf("%d,%lf,%d\n",lg,log(sz),k);
   
  ///////////////////////////////////////////////////////
  //interseccion de vertices
  matAdj=NULL;    
  
  
  
//   for(i=0;i<sz;i++)
//   {	
//       //if(gmst[i].distance>0 && gmst[i].parent!=-1)
// 	//clr_new[i][gmst[i].parent]=1;
//        printf("%d %lf %d\n",i,mst[i].distance,mst[i].parent);
//   }
//   exit(0);
  
  
  matAdj=interMstKnn2(mst,knn,k);

    
//   for(i=0;i<sz;i++)  
//   {
//     for(j=0;j<sz;j++)  
//     {
//       printf("%d",matAdj[i][j]);
//     }
//     printf("\n");
//   }
  //exit(0);

  
  
  initReach(reach,sz);
  dfsKnn(matAdj,1,reach,sz);//se tiene que inicializar en 1 para el segundo recorrido en profundidad
  flag=isConnected(reach,sz);
  
    
  //printf("%d\n",flag);
  
  if(flag==0)//no conexo
  {

    visitado=0;
    no_visitado=0;
    
    row=0;column=0;
    for(row=0;row<sz;row++)
    {
      if(cluster[row][0].c==0)
	break;
    }
    //printf("\n");
    for(i=0;i<sz;i++)
    {
	  
	  if(reach[i]==1)
	  {
	    visitado++;
	    addCluster(cluster,mat,i,row,column);//donde i es el nodo visitado
	    //printf("[%s]",mat[i][0].id);
	    column++;
	  }
	  else if(reach[i]==0)
	  {
	    no_visitado++;	  
	  }  
    }
    	    //printf("---------------------------------\n");
    //exit(0);
  }
  
  
  //printf("no_visitado:%d\n",no_visitado);
  
  if(no_visitado>1)
  {
      mat=createMatrix(matrix,reach,no_visitado);
  
      return mstKnnConsensus(cluster,mat,++flag2,no_visitado);  
     
    
  } 
  else
    return;
return;  
}



struct MATRIX2** createMatrix(struct MATRIX2 **matrix,int reach[],int n)
{
  int i=0,j=0,k=0;
  int row=0,col=0;
  double aux;

    
    //struct MATRIX *new = malloc(n*sizeof(struct MATRIX));    
  
     MATRIX2 **new=(MATRIX2**)malloc(n*sizeof(MATRIX2*));
    for(i=0;i<n;i++)new[i]=(MATRIX2*)malloc(n*sizeof(MATRIX2));

    
    //printf("%d",matrix[0][0].length);exit(0);
    row=0;
    new[0][0].length=n;
    for(i=0;i<matrix[0][0].length;i++)
    {
	    
	    if(reach[i]==0)
	    {
		strcpy(new[row][0].id,matrix[i][0].id);//id
		new[row][0].key=row;
		row++;
		col=0;
		
		for(j=0;j<matrix[0][0].length;j++)
		{
		
			  if(reach[j]==0)
			  {
			    //printf("row:%d,col:%d\n",row,col);
			    new[row-1][col].key=col;
			    new[row-1][col].distance=matrix[i][j].distance;
			    col++;
			  }
			  
		}
		
	      
	    
	    }  
      
    }
/*
    for(i=0;i<n;i++)
    {
    for(j=0;j<n;j++)
     {
	printf("[%lf]",new[i][j].distance);
     }
     printf("\n");
    }

*/
     return new;

  
}


void addCluster(struct G_CLUSTER2 **cluster,struct MATRIX2 **matrix,int index,int row,int column)
{

  strcpy(cluster[row][column].id,matrix[index][0].id);
  cluster[row][column].c=1;
  //printf("%s %lf\n",matrix[index][0].id,matrix[index][1].distance);
  
  return;
}


int** interMstKnn2(struct MST *gmst,struct KNN **gknn,int _K)
{
       int i=0,j=0,k=0,n=0;
       n=gmst[0].length;

      int **clr_new=(int**)malloc(n*sizeof(int*));
      for(i=0;i<n;i++)clr_new[i]=(int*)malloc(n*sizeof(int));
       for(i=0;i<n;i++)
       {
	 for(j=0;j<n;j++)
	 {
	   clr_new[i][j]=0; 
	   
	 }
       }
       
       for(i=0;i<n;i++)
       {	
	    if(gmst[i].distance>0 && gmst[i].parent!=-1)//el -1 es un caso eventual
	      clr_new[i][gmst[i].parent]=1;
       }

       for(i=0;i<n;i++)
       {
	 for(j=0;j<_K;j++)
	 {
	        k=gknn[i][j].key;
		if(gknn[i][j].distance>0)//por defecto esta inicializada en =
		  clr_new[i][k]=1*clr_new[i][k];
 		//else
		  //clr_new[i][k]=0;
		//clr_new[i][k]=1;
	 }
       }
       return clr_new;
  
}


struct MATRIX2** init()
{
  int i,j,k,n;
  char buffer[8000000];
  char* cpToken; 
  FILE* fp;
  char fp_name[50]="./YS_79_2467.csv.dis.txt";
  //char fp_name[50]="test.text";
  //char fp_name[50]="test2.text";
  
  
  
  fp = fopen (fp_name, "r"); 
  double aux;
  char *ptr;  

    i=0;
    j=0;
    buffer[0]='\0';
    fp = fopen (fp_name, "r"); 
    
    MATRIX2 **new=(MATRIX2**)malloc(N_NODOS*sizeof(MATRIX2*));
    for(i=0;i<N_NODOS;i++)new[i]=(MATRIX2*)malloc(N_NODOS*sizeof(MATRIX2));

    
    
    i=0;
    while (fgets(buffer,1000,fp)!=NULL)
	{
	    j=0;
	    k=0;
	    cpToken = strtok (buffer,";");
	    strcpy(new[i][0].id,cpToken);//id
	    while(cpToken!=NULL)
	    {
	      cpToken = strtok (NULL,";");
	      if(cpToken!=NULL){
		aux = strtod(cpToken, &ptr);
		//if(j>0)
		new[i][j].key=j;
		new[j][0].key=j;
		new[i][j].distance=aux;
		j++;
	      }
	    }
	    i++;
	}
	
      new[0][0].length=i;
	
      fclose(fp);
      return new;

  
}
int** knnConnected(struct KNN **gknn,int _K)
{
       
      
       int i=0,j=0,k=0,n=0;
       n=gknn[0][0].length;
       

       //////////////////////////////////////////////////////////////////
       //init cluster
       int **clr_new=(int**)malloc(n*sizeof(int*));
       for(i=0;i<n;i++)clr_new[i]=(int*)malloc(n*sizeof(int));
       //////////////////////////////////////////////////////////////////
       
       for(i=0;i<n;i++)
       {
	  //strcpy(clr_new[i][0].id,gknn[i][0].id);
	  for(j=0;j<n;j++)
	  {
	    clr_new[i][j]=0; 
	  }
	
       }
       for(i=0;i<n;i++)
       {
	 for(j=0;j<_K;j++)
	 {
	        k=gknn[i][j].key;
		clr_new[i][k]=1;
		//strcpy(clr_new[i].KNN[k].id,gknn[i].KNN[j].id);
	 }
       }

      return clr_new;
  
}
