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
  int i,j,k,p;

  int numcomprob;
  //int  comprobacion[10] = (int *)calloc(10, sizeof(int));
  for(i = 0; i < 9; i++)
  {
    int * comprobacion = (int *)calloc(10, sizeof(int));
    for(j = 0; j < 9; j++)
    {
      numcomprob = n->sudo[i][j];
      if(numcomprob != 0)
      {
        if(comprobacion[numcomprob] == 1) return 0;
        else 
        {
          comprobacion[numcomprob] = 1;
        }
      }
      
    }  
    
  }
  for(i = 0; i < 9; i++)
  {
      int * comprobacion = (int *)calloc(10, sizeof(int));
    for(j = 0; j < 9; j++)
    {
      numcomprob = n->sudo[j][i];
      if(numcomprob != 0)
      {
        if(comprobacion[numcomprob] == 1) return 0;
        else 
        {
          comprobacion[numcomprob] = 1;
        }
      }
    }  
    
  }
  k = 0;
  while(k < 9)
  {
    int * comprobacion = (int *)calloc(10, sizeof(int));
    for(p=0;p<9;p++)
    {
      i=3*(k/3) + (p/3) ;
      j=3*(k%3) + (p%3) ;
      numcomprob = n->sudo[i][j];
      if(numcomprob != 0)
      {
        if(comprobacion[numcomprob] == 1) return 0;
        else 
        {
          comprobacion[numcomprob] = 1;
        }
      }
   
    }
    k++; 
  }
 
  

  return 1;
}


List* get_adj_nodes(Node* n)
{
  List* list=createList();
  int i,j,k;
  for(i = 0 ; i < 9; i++)
  {
    for(j = 0; j < 9; j++)
    {
      if(n->sudo[i][j] == 0)
      {
        for(k = 1; k < 10; k++)
        {
          n->sudo[i][j] = k;
          if(is_valid(n))
          {
            Node *adj = copy(n);
            pushBack(list,adj);
          }   
        }
        n->sudo[i][j] = 0;
        return list;
      
      }
        
    }
      
  }
    return list;
}


int is_final(Node* n)
{
  if(n == NULL) return 2;
 
  for(int i = 0; i < 9; i++)
  {
    for(int j = 0; j < 9; j++)
    {
      if(n->sudo[i][j]  == 0) return 0;
    }   
     
  }
  return 1;
}

Node* DFS(Node* initial, int* cont)
{
  int estado;
  *cont = 1;
  Stack* S = createStack();
  push(S, initial);
  while((get_size(S)) != 0)
  {
    Node* n = top(S); 
    pop(S);
    *cont = *cont - 1;
    estado = is_final(n);
    if(estado == 2) return NULL;
    if(estado == 1) return n;
    else
    {
      List* l=get_adj_nodes(n);
      Node* adj=first(l);
      while(adj)
      {
        push(S,adj);
        adj=next(l);
        *cont = *cont + 1;
      }
      free(n);
      
    }
     
  }

  
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