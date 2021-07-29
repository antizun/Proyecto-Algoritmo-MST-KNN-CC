#include "utils.h"
#ifndef KNN_H_
#define KNN_H_

typedef struct KNN {
 int key;
 char  id[50];
 int length;
 double distance;
}KNN;

void insertionSort(struct KNN **gknn,int index); 
struct KNN** knnAlgorithm(struct MATRIX2 **matrix);

#endif