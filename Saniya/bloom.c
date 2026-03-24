#include<stdio.h>
#include<stdlib.h>
#define bloom 100

int bloomfilter[bloom]={0};
int hash1(int key){
    return key % bloom;
}
int hash2(int key){
    return (key+1) % bloom;
}
int hash3(int key){
    return (key/7) % bloom;
}
void insert(){
    int key;
    printf("element to insert:");
    scanf("%d",&key);
    int index1=hash1(key);
    bloomfilter[index1]=1;
    
    int index2=hash2(key);
    bloomfilter[index2]=1;
   
    int index3=hash3(key);
    bloomfilter[index3]=1;
    printf("values inserted\n");
    }
    
void search(){
    int key;
    printf("key to search:");
    scanf("%d",&key);
    int index1=hash1(key);
    int index2=hash2(key);
    int index3=hash3(key);
    if(bloomfilter[index1]&&bloomfilter[index2]&&bloomfilter[index3]==1){
        printf("key may present");
    }
    else{
        printf("key is not present");
    }
}
void display(){
    for(int i=0;i<bloom;i++)
    printf("%d\n",bloomfilter[i]);
    
}
int main(){
    int choice;
    do{
    printf("1.insert\n");
    printf("2. search\n");
    printf("3.display\n");
    printf("4.exit\n");
    printf("choice enter:\n");
    scanf("%d",&choice);
    switch(choice){
        case 1: insert();
        break;
        
        case 2 : search();
        break;
        
        case 3 : display();
        break;
        
        case 4: printf("exiting");
        break;
        
        default: printf("wrong choice ");
        
    }
}

while(choice!=4);
}
