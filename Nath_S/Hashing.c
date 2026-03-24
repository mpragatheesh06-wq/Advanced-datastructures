#include <stdio.h>
#include <stdlib.h>
#define Table_size 15


struct Node{
    int key;
    struct Node* next;
};

struct Node* hash_table[Table_size];

void initialize(){
    for(int i=0;i<Table_size;i++){
        hash_table[i]=NULL;
    }
}

int hash(int key){
    return key%Table_size;
}

void insert(int key){
    int index = hash(key);
    struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
    newnode->key=key;
    newnode->next=hash_table[index];
    hash_table[index]=newnode;
    printf("Number inserted succesfully\n");
}
void search(int key){
    int index = hash(key);
    struct Node* temp= hash_table[index];
    while(temp!=NULL){
        if(temp->key==key){
            printf("Key found at index %d \n",index);
            return;
        }
        temp=temp->next;
    }
    printf("The key %d not found \n",key);
}

void display(){
    for(int i=0;i<Table_size;i++){
        printf("Index %d ",i);
        struct Node* temp= hash_table[i];
        while(temp!=NULL){
            printf("%d -> ",temp->key);
            temp=temp->next;
        }
        printf("NULL\n");
    }
}

void delete(int key){
    int index = hash(key);
    struct Node* temp = hash_table[index];
    struct Node* prev = NULL; 
    while(temp!=NULL){
        if(prev==NULL){
            hash_table[index]=temp->next;
        }else{
            prev->next = temp->next;
        free(temp);
        printf("Key deleted successfully \n");
        return;
        }
        prev=temp;
        temp = temp->next;
    }
    printf("Key not found \n");
}

int main() {
    int choice, key;
    initialize();
        while(1){
        printf("\n1.Insert\n2.Search\n3.Delete\n4.Display\n5.Exit\n");
        printf("Enter your choice ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                printf("Enter your number to Insert ");
                scanf("%d",&key);
                insert(key);
                break;
            case 2:
                printf("Enter your number to Search ");
                scanf("%d",&key);
                search(key);
                break;
            case 3:
                printf("Enter element to be Deleted");
                scanf("%d",key);
                delete(key);
                break;
            case 4:
                printf("Display");
                display();
                break;
            case 5:
                printf("\nCode exited\n Thank you!\n");
                exit(0);
                break;
            default:
                printf("Invalid Choice");
        }
}
    return 0;
}