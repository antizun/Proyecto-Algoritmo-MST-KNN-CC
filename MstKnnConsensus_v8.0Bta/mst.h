#include "utils.h"
#ifndef MST_H_
#define MST_H_
typedef struct MST{
 int key;
 char id[50];
 int parent;  
 double distance;
 int length;
}MST;
int minValue(double key[], int mstSet[],int n);
struct MST* mstInput(int parent[],struct MATRIX2 **graphMST);
struct MST* primAlgorithm2(struct MATRIX2 **graphMST);
#endif