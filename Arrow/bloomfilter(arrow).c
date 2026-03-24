#include <stdio.h>
#define SIZE 50

int bloom[SIZE];

int h1(int x) {
    return x%SIZE;
}

int h2(int x) {
    return (x*13)%SIZE;
}

void add(int x) {
    bloom[h1(x)]=1;
    bloom[h2(x)]=1;
}

int check(int x) {
    if(bloom[h1(x)] && bloom[h2(x)])
        return 1;
    return 0;
}

int main() {
    for(int i=0;i<SIZE; i++)
        bloom[i]=0;

    add(18);
    add(25);
    add(73);

    printf("56:%s\n",check(56)?"Present":"Not Present");
    printf("25:%s\n",check(25)?"Present":"Not Present");
    printf("43:%s\n",check(43)?"Present":"Not Present");

    return 0;
}