#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SEED 67

enum Result { NO = 0, YES = 1 };

struct Filter {
    int size;
    int *bits;
};

void initFilter(struct Filter *f, int n) {
    f->size = n;
    f->bits = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        f->bits[i] = 0;
}

int mix(struct Filter *f, int key) {
    int p = (int)pow(2, key);
    return (key + p + SEED) % f->size;
}

void mark(struct Filter *f, int idx) {
    f->bits[idx] = 1;
}

enum Result probe(struct Filter *f, int key) {
    int idx = mix(f, key);
    return f->bits[idx] ? YES : NO;
}

int main() {
    struct Filter f;
    int count;
    initFilter(&f, 20);

    printf("enter number of elements to insert: ");
    scanf("%d", &count);

    for (int i = 0; i < count; i++) {
        int num;
        printf("enter number ");
        scanf("%d", &num);
        mark(&f, mix(&f, num));
    }

    int q;
    printf("check number\n");
    scanf("%d", &q);

    if (probe(&f, q))
        printf("probably in set\n");
    else
        printf("definitely not in set\n");

    return 0;
}
