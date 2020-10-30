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

// Pointer to the first node
static Node *head = NULL;

// Pointer to the last node
static Node *tail = NULL;

// List's size
static size_t size;

// TODO: implement peek() function (it returns the first node's data')
// TODO: implement contains() function (it receives the data and returns
// either true or false depending on the presence of the specified data in the queue)

// Add an element to the end of the queue
static void enqueue(const int data) {
    // Creates a new node
    Node *new_node = (Node *)malloc(sizeof(Node));

    new_node->data = data;

    // Points it to old last node
    new_node->nxt = tail;

    ++size;

    if (head) {
        // Makes the new node become the last node
        tail = new_node;
    } else {
        // If it is the only node in the queue, it'll be the first and the last
        head = tail = new_node;
    }
}

// Delete a node at the beginning of the queue and returns its data
static int dequeue() {
    // If there's is some node in the queue its data will be returned
    // otherwise 'false' will be returned
    if (head) {
        Node *previous_node = NULL;
        int returned_data;

        while (previous_node->nxt != NULL) {
            // Find the node previous to the node which will be deleted
            previous_node = previous_node->nxt;
        }

        previous_node->nxt = NULL;

        --size;

        returned_data = head->data;

        free(head);
        head = previous_node;

        return returned_data;
    } else {
        return false;
    }
}
