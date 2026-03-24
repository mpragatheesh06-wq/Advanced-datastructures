#include<stdio.h>
#include<stdlib.h>
#define size 20
int bitArray[size];

void initialize(){
    for(int i=0;i<size;i++){
        bitArray[i]=0;
    }
}
int hash_1(int key){
    return (key*53)%size;
}

int hash_2(int key){
    return(key* 13)%size;
}

void insert(int key){
    int index_1 = hash_1(key);
    int index_2 = hash_2(key);
    
    bitArray[index_1]=1;
    bitArray[index_2]=1;
    printf("Successful\n");
}

void search(int key){
    int index_1 = hash_1(key);
    int index_2 = hash_2(key);
    if(bitArray[index_1]==1&&bitArray[index_2]==1){
        printf("The element  %d may be possibly present \n",key);
    }else{
        printf("The element %d is not present \n",key);
    }
}
void display() {
    printf("Bloom Filter Bit Array:\n");
    for (int i = 0; i < size; i++)
        printf("%d ", bitArray[i]);
    printf("\n");
}

int main(){
    int choice,key;
    initialize();
    
    while(1){
        printf("\n1)Insert \n2)Search \n3)Display \n4)Exit \n");
        printf("Enter your choice ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
              printf("Enter the element to be inserted ");
              scanf("%d",&key);
              insert(key);
              break;
            case 2:
              printf("Enter the element to be searched ");
              scanf("%d",&key);
              search(key);
              break;
            case 3:
                display();
                break;
            case 4:
                printf("\nCode exited \n Thank you!\n");
                exit(0);
            default:
                printf("Inavlid choice");
                
        }
    }
    return 0;
}