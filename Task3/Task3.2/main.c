#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;
typedef struct {
    Node* head;
    int size;
} LinkedList;

void init_list(LinkedList* list) {
    list->head = NULL;
    list->size = 0;
}
Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if(new_node == NULL) {
        fprintf(stderr, "Unable to allocate memory for new node\n");
        exit(-1);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void add(LinkedList* list, int data) {
    Node* new_node = create_node(data);
    if(list->head == NULL) {
        list->head = new_node;
    } else {
        Node* temp = list->head;
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
    list->size++;
}
void insert(LinkedList* list, int index, int data) {
    if(index < 0 || index > list->size) {
        fprintf(stderr, "Index out of bounds\n");
        return;
    }

    Node* new_node = create_node(data);
    if(index == 0) {
        new_node->next = list->head;
        list->head = new_node;
    } else {
        Node* temp = list->head;
        for(int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }
        new_node->next = temp->next;
        temp->next = new_node;
    }
    list->size++;
}
int size(LinkedList* list) {
    return list->size;
}
void remove_index(LinkedList* list, int index) {
    if(index < 0 || index >= list->size) {
        fprintf(stderr, "Index out of bounds\n");
        return;
    }

    Node* to_remove;
    if(index == 0) {
        to_remove = list->head;
        list->head = list->head->next;
    } else {
        Node* temp = list->head;
        for(int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }
        to_remove = temp->next;
        temp->next = to_remove->next;
    }
    free(to_remove);
    list->size--;
}
void set(LinkedList* list, int index, int data) {
    if(index < 0 || index >= list->size) {
        fprintf(stderr, "Index out of bounds\n");
        return;
    }

    Node* temp = list->head;
    for(int i = 0; i < index; i++) {
        temp = temp->next;
    }
    temp->data = data;
}
int get(LinkedList* list, int index) {
    if(index < 0 || index >= list->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(-1);
    }

    Node* temp = list->head;
    for(int i = 0; i < index; i++) {
        temp = temp->next;
    }
    return temp->data;
}

int main() {
    LinkedList list;
    init_list(&list);

    add(&list, 1);
    add(&list, 2);

    printf("Size: %d\n", size(&list));

    printf("Insert a valeu...\n");
    insert(&list, 1, 4);
    printf("Value at index 1: %d\n", get(&list, 1));
    printf("Setting a value...\n");
    set(&list, 1, 5);
    printf("Value at index 1 after set: %d\n", get(&list, 1));
    printf("Removing...\n");
    remove_index(&list, 1);
    printf("Value at index 1 after remove: %d\n", get(&list, 1));

    return 0;
}

