#ifndef UTILS_H_
#define UTILS_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include<stdbool.h>
#include <math.h>

#ifndef N_NODOS
#define  N_NODOS 79 //numero de objetos
//#define  N_NODOS 5 //numero de objetos
#endif


typedef struct G_CLUSTER2 {
 int key;
 int index;
 int f;
 char id[50];
 int length;
 int c;
 double distance;
 double group;
 int inter;
}G_CLUSTER2;

typedef struct ITT{
 int key;
 int length;
 double consensus;
 double ds;
 struct G_CLUSTER2 **cluster;
}ITT;


typedef struct MATRIX2 {
 int key;
 char id[50];
 double distance;
 int length;
}MATRIX2;


//int REACH[N_NODOS];


#endif













