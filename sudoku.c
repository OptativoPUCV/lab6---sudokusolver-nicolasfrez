#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n)
{
  int filas[9][10] = {0};
  int columnas[9][10] = {0};
  
  for(int i=0 ; i<9 ; i++)
    {
      for(int j=0; j<9 ; j++)
        {
          int num_fila = n->sudo[i][j];
          int num_columnas = n->sudo[j][i];

          if(num_fila!=0)
          {
            if(filas[i][num_fila]==1)
              return 0;
            filas[i][num_fila] = 1;
          }
          if(num_columnas!=0)
          {
            if(columnas[i][num_columnas]==1)
              return 0;
            columnas[i][num_columnas] = 1;
          }
        }
    }
  for(int i=0 ; i<9 ; i+=3)
    {
      for(int j=0; j<9 ; j+=3)
        {
          int subMatriz[10] = {0};
          for(int x=i; x<i+3; x++)
          {
            for(int y=j; y<j+3; y++)
              {
                int numSubMatriz = n->sudo[x][y];
                if(numSubMatriz!=0)
                {
                  if(subMatriz[numSubMatriz]==1)
                    return 0;
                  subMatriz[numSubMatriz] = 1;
                }
              }
          }
        }
    }
    return 1;
}


List* get_adj_nodes(Node* n)
{
  List* list=createList();
  int encontrado = 0;

  for(int i=0; i<9; i++)
  {
    for(int j=0; j<9; j++)
    {
      if(n->sudo[i][j]==0)
      {
        encontrado = 1;
        for(int num=0; num<=9 ; num++)
        {
          Node* nuevo = copy(n);
          nuevo->sudo[i][j]=num;
          if(is_valid(nuevo)==1)
            pushBack(list, nuevo);
          else
            free(nuevo);
        }
      }
      if(encontrado==1)
        break;
    }
    if(encontrado==1)
      break;
  }
 return list;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/