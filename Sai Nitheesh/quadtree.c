#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 2

// Structure for a point
typedef struct Point {
    int x, y;
} Point;

// Structure for QuadTree node
typedef struct QuadTree {
    int x, y, w, h;   // boundary (rectangle)
    Point points[CAPACITY];
    int count;

    struct QuadTree *nw, *ne, *sw, *se;
    int divided;
} QuadTree;

// Create a new QuadTree node
QuadTree* createNode(int x, int y, int w, int h) {
    QuadTree* node = (QuadTree*)malloc(sizeof(QuadTree));
    node->x = x;
    node->y = y;
    node->w = w;
    node->h = h;
    node->count = 0;
    node->divided = 0;
    node->nw = node->ne = node->sw = node->se = NULL;
    return node;
}

// Check if point is inside boundary
int contains(QuadTree* qt, Point p) {
    return (p.x >= qt->x && p.x < qt->x + qt->w &&
            p.y >= qt->y && p.y < qt->y + qt->h);
}

// Subdivide node into 4 children
void subdivide(QuadTree* qt) {
    int x = qt->x;
    int y = qt->y;
    int w = qt->w / 2;
    int h = qt->h / 2;

    qt->nw = createNode(x, y, w, h);
    qt->ne = createNode(x + w, y, w, h);
    qt->sw = createNode(x, y + h, w, h);
    qt->se = createNode(x + w, y + h, w, h);

    qt->divided = 1;
}

// Insert a point into QuadTree
void insert(QuadTree* qt, Point p) {
    if (!contains(qt, p))
        return;

    if (qt->count < CAPACITY) {
        qt->points[qt->count++] = p;
    } else {
        if (!qt->divided)
            subdivide(qt);

        insert(qt->nw, p);
        insert(qt->ne, p);
        insert(qt->sw, p);
        insert(qt->se, p);
    }
}

// Print points (for testing)
void printTree(QuadTree* qt) {
    for (int i = 0; i < qt->count; i++) {
        printf("(%d, %d)\n", qt->points[i].x, qt->points[i].y);
    }

    if (qt->divided) {
        printTree(qt->nw);
        printTree(qt->ne);
        printTree(qt->sw);
        printTree(qt->se);
    }
}

// Main function
int main() {
    QuadTree* qt = createNode(0, 0, 100, 100);

    Point p1 = {10, 20};
    Point p2 = {30, 40};
    Point p3 = {70, 80};
    Point p4 = {90, 10};

    insert(qt, p1);
    insert(qt, p2);
    insert(qt, p3);
    insert(qt, p4);

    printf("Stored Points:\n");
    printTree(qt);

    return 0;
}