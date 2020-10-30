#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    // Can be replaced by whatever datatype is required
    // Even by a union/struct to handle multiple datatypes at the same time
    int data;

    // Pointer to next node
    struct Node *nxt;

    // TODO: add function pointers to the operations (functions below) to simulate methods
} Node;

// Pointer to the node at top of the stack
static Node *tail = NULL;

// List's size
static size_t size;

// TODO: implement peek() function (it returns the first node's data')
// TODO: implement contains() function (it receives the data and returns
// either true or false depending on the presence of the specified data in the stack)

// Add a node to the top of the stack
static void push(const int data) {
    // Creates a new node
    Node *new_node = (Node *)malloc(sizeof(Node));

    new_node->data = data;

    // Points it to old top node
    new_node->nxt = tail;

    ++size;

    // Makes the new node become the top node
    tail = new_node;
}

// Delete the node at the top of the stack and returns its data
static int pop() {
    // If there's is some node in the stack its data will be returned
    // otherwise 'false' will be returned
    if (tail) {
        Node *deleted_node = tail;
        int returned_data;

        tail = tail->nxt;

        deleted_node->nxt = NULL;

        --size;

        returned_data = deleted_node->data;

        free(deleted_node);
        deleted_node = NULL;

        return returned_data;
    } else {
        return false;
    }
}
