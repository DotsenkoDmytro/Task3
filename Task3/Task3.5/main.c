#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct {
    double x, y, z;
    double m;
} Point;

double distance(Point a, Point b);
Point* reduce_points(Point *points, int *n);

int main() {
    int n = 5;

    Point *points = (Point *)malloc(n * sizeof(Point));

    points[0] = (Point){1, 2, 2, 1};
    points[1] = (Point){5, 2, 1, 2};
    points[2] = (Point){1, 3, 2, 7};
    points[3] = (Point){2, 2, 2, 2};
    points[4] = (Point){4, 3, 4, 6};


    points = reduce_points(points, &n);
    printf("Final point: (%f, %f, %f);\nmass %f\n", points[0].x, points[0].y, points[0].z, points[0].m);

    free(points);
    return 0;
}


Point* reduce_points(Point *points, int *n) {
    while (*n > 1) {
        int min_index = 0;
        for (int i = 1; i < *n; i++) {
            if (points[i].m < points[min_index].m) {
                min_index = i;
            }
        }

        int min_dist_index = (min_index == 0) ? 1 : 0;
        double min_dist = distance(points[min_index], points[min_dist_index]);
        for (int i = 0; i < *n; i++) {
            if (i == min_index) continue;
            double dist = distance(points[min_index], points[i]);
            if (dist < min_dist) {
                min_dist_index = i;
                min_dist = dist;
            }
        }

        points[min_dist_index].m += points[min_index].m;
        points[min_index] = points[*n - 1];
        (*n)--;
    }
    return points;
}

double distance(Point a, Point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}


