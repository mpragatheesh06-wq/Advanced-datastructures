#include <stdio.h>

#define SIZE 10   

int main() {

    int bloom[SIZE];
    int i, key;

     
    for (i = 0; i < SIZE; i++) {
        bloom[i] = 0;
    }

    
    int values[] = {15, 23, 42};
    int n = 3;

    
    for (i = 0; i < n; i++) {

        key = values[i];

        
        int h1 = key % SIZE;
        int h2 = (key / SIZE) % SIZE;

        bloom[h1] = 1;
        bloom[h2] = 1;
    }

    
    printf("Bloom Filter Array:\n");
    for (i = 0; i < SIZE; i++) {
        printf("%d ", bloom[i]);
    }

   
    key = 23;

    int h1 = key % SIZE;
    int h2 = (key / SIZE) % SIZE;

    if (bloom[h1] == 1 && bloom[h2] == 1)
        printf("\n\n%d is probably present\n", key);
    else
        printf("\n\n%d is definitely not present\n", key);

    return 0;
}