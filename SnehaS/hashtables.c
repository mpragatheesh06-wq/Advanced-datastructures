//quadratic probing
#include <stdio.h>
#define SIZE 10
#define DELETED -2
int table[SIZE];


int main() {
    int i,j,index,choice,key;
    for(i=0;i<SIZE;i++)
    table[i]=-1;
    while(1){
      printf("\n1)insert\n2)search\n3)delete\n4)display\n5)exit\n");
      scanf("%d", &choice);
      if(choice==1){
          printf("Enter key:");
          scanf("%d", &key);
          index=key%SIZE;
          for(j=0;j<SIZE;j++){
              int newindex=(index+j*j)%SIZE;
              if(table[newindex]==-1||table[newindex ==DELETED]){
                  table[newindex]=key;
                  printf("inserted");
                  break;
              }
          }
      }
      else if(choice==2){
          printf("Enter key to search:");
          scanf("%d",&key);
          index=key%SIZE;
          int found=0;
          for(j=0;j<SIZE;j++){
              int newindex=(index+j*j)%SIZE;
              if(table[newindex]==-1){
                  break;
              }
              if(table[newindex]==key){
                  found=1;
                  break;
              }
            }
            if(found){
                printf("key founded");
            }
            else{
                printf("key not founded");
            }
          }
        else if(choice==3){ 
          printf("Enter key:");
          scanf("%d",&key);
          index=key%SIZE;
          for(j=0;j<SIZE;j++){
              int newindex=(index+j*j)%SIZE;
              if(table[newindex]==-1){
                  break;
              }
              if(table[newindex]==key){
                  table[newindex]=DELETED;
                  printf("deleted");
                  break;
              }
          }
      }
      else if(choice==4){
          for(i=0;i<SIZE;i++){
              if(table[i]==-1){
                  printf("index %d:EMPTY\n", i);
              }
              else if(table[i]==DELETED){
                  printf("index %d:DELETED\n", i);
              }
              else{
                  printf("index %d:%d\n",i,table[i]);
              }
             
          }
      }
      else if(choice==5){
          break;
      }
      else{
          printf("invalid choice\n");
      }
    }
    return 0;
}