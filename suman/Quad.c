#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define a point
typedef struct {
    int x, y;
} Point;

// Define boundary (rectangle)
typedef struct {
    int x, y;      // center
    int w, h;      // half width & half height
} Boundary;

// QuadTree node
typedef struct QuadTree {
    Boundary boundary;
    Point *point;
    bool divided;

    struct QuadTree *nw;
    struct QuadTree *ne;
    struct QuadTree *sw;
    struct QuadTree *se;
} QuadTree;

// Create a new point
Point* createPoint(int x, int y) {
    Point *p = (Point*)malloc(sizeof(Point));
    p->x = x;
    p->y = y;
    return p;
}

// Create boundary
Boundary createBoundary(int x, int y, int w, int h) {
    Boundary b = {x, y, w, h};
    return b;
}

// Create QuadTree node
QuadTree* createQuadTree(Boundary boundary) {
    QuadTree *qt = (QuadTree*)malloc(sizeof(QuadTree));
    qt->boundary = boundary;
    qt->point = NULL;
    qt->divided = false;
    qt->nw = qt->ne = qt->sw = qt->se = NULL;
    return qt;
}

// Check if point is inside boundary
bool contains(Boundary b, Point *p) {
    return (p->x >= b.x - b.w &&
            p->x <= b.x + b.w &&
            p->y >= b.y - b.h &&
            p->y <= b.y + b.h);
}

// Subdivide node
void subdivide(QuadTree *qt) {
    int x = qt->boundary.x;
    int y = qt->boundary.y;
    int w = qt->boundary.w / 2;
    int h = qt->boundary.h / 2;

    qt->nw = createQuadTree(createBoundary(x - w, y - h, w, h));
    qt->ne = createQuadTree(createBoundary(x + w, y - h, w, h));
    qt->sw = createQuadTree(createBoundary(x - w, y + h, w, h));
    qt->se = createQuadTree(createBoundary(x + w, y + h, w, h));

    qt->divided = true;
}

// Insert point
bool insert(QuadTree *qt, Point *p) {
    if (!contains(qt->boundary, p)) {
        return false;
    }

    if (qt->point == NULL) {
        qt->point = p;
        return true;
    }

    if (!qt->divided) {
        subdivide(qt);
    }

    if (insert(qt->nw, p)) return true;
    if (insert(qt->ne, p)) return true;
    if (insert(qt->sw, p)) return true;
    if (insert(qt->se, p)) return true;

    return false;
}

// Print points (DFS)
void printTree(QuadTree *qt) {
    if (qt == NULL) return;

    if (qt->point != NULL) {
        printf("(%d, %d)\n", qt->point->x, qt->point->y);
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
    Boundary boundary = createBoundary(0, 0, 10, 10);
    QuadTree *qt = createQuadTree(boundary);

    insert(qt, createPoint(1, 1));
    insert(qt, createPoint(-2, 3));
    insert(qt, createPoint(4, -1));
    insert(qt, createPoint(-3, -3));

    printf("QuadTree Points:\n");
    printTree(qt);

    return 0;
}