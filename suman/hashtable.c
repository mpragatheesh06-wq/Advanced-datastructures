#include <stdio.h>
#include <stdlib.h>
#define TABLE_SIZE 10

struct Node 
{
    int key;
    struct Node* next;
};
struct Node* hashTable[TABLE_SIZE];
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

void insert(int key) 
{
    int index=hashFunction(key);
    struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
    newNode->key=key;
    newNode->next=hashTable[index];
    hashTable[index]=newNode;
}
int search(int key) 
{
    int index=hashFunction(key);
    struct Node* temp=hashTable[index];
    while(temp!=NULL)
    {
        if (temp->key==key)
         return 1;
        temp=temp->next;
    }
    return 0;
}

void delete(int key) {
    int index=hashFunction(key);
    struct Node*temp=hashTable[index];
    struct Node*prev=NULL;
    while (temp!=NULL) {
        if(temp->key==key) {
            if(prev==NULL)
                hashTable[index]=temp->next;
            else
                prev->next=temp->next;
            free(temp);
            return;
        }
        prev=temp;
        temp=temp->next;
    }
void display() 
{
    int i;
    struct Node*temp;
    for (i=0;i<TABLE_SIZE;i++) 
    {
        printf("%d:",i);
        temp=hashTable[i];
        while (temp!=NULL) {
            printf("%d->",temp->key);
            temp=temp->next;
        }
        printf("NULL\n");
    }
}
int main() {
    int choice,key,i;
    for (i=0;i<TABLE_SIZE;i++)
        hashTable[i]=NULL;
    while(1) 
    {
        printf("\n1.Insert\n2.Search\n3.Delete\n4.Display\n5.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice==1) 
        {
            printf("Enter key:");
            scanf("%d",&key);
            insert(key);
        } 
        else if (choice==2) 
        {
            printf("Enter key:");
            scanf("%d",&key);
            if (search(key))
                printf("Key found\n");
            else
                printf("Key not found\n");
        } 
        else if (choice==3)
        {
            printf("Enter key:");
            scanf("%d",&key);
            delete(key);
        } 
        else if (choice==4) 
        {
            display();
        } 
        else if (choice==5) 
        {
            break;
        }
    }
    return 0;
}