#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int *items;
    int size;
    int capacity;
} ArrayList;

void init_array(ArrayList *arr) {
    arr->size = 0;
    arr->capacity = 4;
    // initial memory
    arr->items = malloc(sizeof(int) * arr->capacity);
    if (arr->items == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        exit(1);
    }
}

// check memory capacity
void ensure_capacity(ArrayList *arr) {
    if (arr->size == arr->capacity) {
        arr->capacity *= 2;
        // Reallocating memory
        arr->items = realloc(arr->items, sizeof(int) * arr->capacity);
        if (arr->items == NULL) {
            fprintf(stderr, "Failed to reallocate memory\n");
            exit(1);
        }
    }
}

void add(ArrayList *arr, int item) {
    ensure_capacity(arr);
    arr->items[arr->size++] = item;
}

void insert(ArrayList *arr, int index, int item) {
    if (index < 0 || index > arr->size) {
        fprintf(stderr, "Index out of bounds\n");
        return;
    }

    ensure_capacity(arr);
    for (int i = arr->size; i > index; i--) {
        arr->items[i] = arr->items[i-1];
    }
    arr->items[index] = item;
    arr->size++;
}

int size(ArrayList *arr) {
    return arr->size;
}

void remove_index(ArrayList *arr, int index) {
    if (index < 0 || index >= arr->size) {
        fprintf(stderr, "Index out of bounds\n");
        return;
    }

    for (int i = index; i < arr->size - 1; i++) {
        arr->items[i] = arr->items[i+1];
    }
    arr->size--;
}

void set(ArrayList *arr, int index, int item) {
    if (index < 0 || index >= arr->size) {
        fprintf(stderr, "Index out of bounds\n");
        return;
    }

    arr->items[index] = item;
}

int get(ArrayList *arr, int index) {
    if (index < 0 || index >= arr->size) {
        fprintf(stderr, "Index out of bounds\n");
        return -1;
    }

    return arr->items[index];
}

// free memory
void free_array(ArrayList *arr) {
    free(arr->items);
}

// example
int main() {
    ArrayList arr;
    init_array(&arr);

    add(&arr, 1);
    add(&arr, 2);

    printf("Size: %d\n", size(&arr));

    printf("Insert a value...\n");
    insert(&arr, 1, 4);
    printf("Value at index 1: %d\n", get(&arr, 1));
    printf("Setting a value...\n");
    set(&arr, 1, 5);
    printf("Value at index 1 after set: %d\n", get(&arr, 1));
    printf("Removing...\n");
    remove_index(&arr, 1);
    printf("Value at index 1 after remove: %d\n", get(&arr, 1));

    free_array(&arr);

    return 0;
}
