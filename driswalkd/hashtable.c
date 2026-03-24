#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXVAL 100
#define OFFSET 67

enum Status { FAIL = 0, OK = 1 };

struct Cell {
    int key;
    char data[MAXVAL];
    struct Cell *link;
};

struct Store {
    int limit;
    struct Cell **slots;
};

int hashCalc(struct Store *s, int key) {
    return (key + OFFSET) % s->limit;
}

void initStore(struct Store *s, int n) {
    s->limit = n;
    s->slots = malloc(sizeof(struct Cell *) * n);
    for (int i = 0; i < n; i++)
        s->slots[i] = NULL;
}

void put(struct Store *s, int key, char *val) {
    int pos = hashCalc(s, key);
    struct Cell *c = malloc(sizeof(struct Cell));
    c->key = key;
    strcpy(c->data, val);
    c->link = s->slots[pos];
    s->slots[pos] = c;
    printf("inserted key :- %d\n", key);
}

char *get(struct Store *s, int key) {
    int pos = hashCalc(s, key);
    struct Cell *cur = s->slots[pos];
    while (cur) {
        if (cur->key == key)
            return cur->data;
        cur = cur->link;
    }
    return NULL;
}

enum Status erase(struct Store *s, int key) {
    int pos = hashCalc(s, key);
    struct Cell *cur = s->slots[pos];
    struct Cell *prev = NULL;

    while (cur) {
        if (cur->key == key) {
            if (prev)
                prev->link = cur->link;
            else
                s->slots[pos] = cur->link;
            free(cur);
            printf("key del:- %d\n", key);
            return OK;
        }
        prev = cur;
        cur = cur->link;
    }

    printf("not found\n");
    return FAIL;
}

int main() {
    struct Store s;
    int size;
    printf("table size: ");
    scanf("%d", &size);
    initStore(&s, size);

    while (1) {
        int ch;
        printf("\n1.insert \n2.search \n3.delete \n4.exit\n");
        printf("choice: ");
        scanf("%d", &ch);

        if (ch == 1) {
            int k;
            char v[MAXVAL];
            printf("key: ");
            scanf("%d", &k);
            printf("Enter value: ");
            scanf("%s", v);
            put(&s, k, v);
        } 
        else if (ch == 2) {
            int k;
            printf("Enter key to search: ");
            scanf("%d", &k);
            char *res = get(&s, k);
            if (res)
                printf("Value: %s\n", res);
            else
                printf("Key not found\n");
        } 
        else if (ch == 3) {
            int k;
            printf("Enter key to delete: ");
            scanf("%d", &k);
            erase(&s, k);
        } 
        else if (ch == 4) {
            printf("Exit\n");
            break;
        } 
        else {
            printf("Invalid choice\n");
        }
    }

    return 0;
}
