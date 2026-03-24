#include <stdio.h>
#include <string.h>
#define SIZE 20
#define MAX_LEN 50

int bloom[SIZE]={0};

int hash1(char *str){
int sum=0;
for(int i=0;str[i]!='\0';i++)sum+=str[i];
return sum%SIZE;
}

int hash2(char *str){
int sum=0;
for(int i=0;str[i]!='\0';i++)sum=(sum*3+str[i])%SIZE;
return sum;
}

void insert(char *str){
int h1=hash1(str);
int h2=hash2(str);
bloom[h1]=1;
bloom[h2]=1;
}

int search(char *str){
int h1=hash1(str);
int h2=hash2(str);
return bloom[h1]&&bloom[h2];
}

int main(){
int n;
char word[MAX_LEN];
printf("How many strings do you want to insert? ");
scanf("%d",&n);
for(int i=0;i<n;i++){
printf("Enter string %d: ",i+1);
scanf("%s",word);
insert(word);
}
printf("Enter a string to search: ");
scanf("%s",word);
if(search(word))
printf("%s is present\n",word);
else
printf("%s is not present\n",word);
return 0;
}