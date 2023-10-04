#include <stdio.h>
#include <math.h>

int countAverage(double arr[], int n);
double sumAbsNegative(double arr[], int n);

int main() {
    double arr[] = {1.5, -3.5, 2.0, 4.0, -5.0, 6.0};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Count elements above average: %d\n", countAverage(arr, n));
    printf("Sum values after first negative: %.2f\n", sumAbsNegative(arr, n));

    return 0;
}

int countAverage(double arr[], int n) {
    double sum = 0.0;
    int count = 0;

    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    double average = sum / n;

    // count
    for (int i = 0; i < n; i++) {
        if (arr[i] > average) {
            count++;
        }
    }
    return count;
}

double sumAbsNegative(double arr[], int n) {
    double sum = 0.0;
    int i = 0;
    while(i < n && arr[i] >= 0) {
        i++;
    }
    for (i = i + 1; i < n; i++) {
        sum += fabs(arr[i]);
    }
    return sum;
}
