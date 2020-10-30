#include <stdio.h>
#include <stdlib.h>

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

// TODO: implement clear() function (Removes all the elements from the list)
// TODO: implement reverse() function (Reverses the order of the list)
// TODO: implement search() function (Receives the data and returns the index)
// TODO: implement access() function (Receives the index and returns the data)

// ##########################
// ### ADDITION FUNCTIONS ###
// ##########################

// Add an element to the beginning of the linked list
static void insert_first(const int data) {
    // Creates a new node
    Node *new_node = (Node *)malloc(sizeof(Node));

    new_node->data = data;

    // Points it to old first node
    new_node->nxt = head;

    // Makes the new node become the first node
    head = new_node;

    ++size;
}

// Add a node to the end of the linked list
void append(const int data) {
    // Creates a new node
    Node *new_node = (Node *)malloc(sizeof(Node));

    new_node->data = data;

    new_node->nxt = NULL;

    // Makes the old last node become second last node
    tail->nxt = new_node;

    // Makes the new node become the last node
    tail = new_node;

    ++size;
}

// Insert a new node in the middle of the list
static void insert_middle(const size_t idx, const int data) {
    // Creates a new node
    Node *new_node = (Node *)malloc(sizeof(Node));
    Node *previous_node = head;

    for (int i = 0; i < idx - 1; i++) {
        // Find the node previous to the position that the new node will be inserted
        previous_node = previous_node->nxt;
    }

    new_node->data = data;

    // The new node'll point to the node after the location it'll be inserted
    new_node->nxt = previous_node->nxt;

    // The node behind the position that the new node
    // will be inserted will point to the new node
    previous_node->nxt = new_node;

    ++size;
}

// Add a new node at the specified position
void insert(const int idx, const int data) {
    if (idx == 0)
        insert_first(data);
    else if (idx == -1)
        append(data);
    else {
        insert_middle(idx, data);
    }
}

// ##########################
// ### DELETION FUNCTIONS ###
// ##########################

// Delete a node at the beginning of the linked list and returns it
static Node *delete_first() {
    // Node to be deleted
    Node *deleted_node = head;

    // Points it to seconde node which will become the new first node
    head = head->nxt;

    deleted_node->nxt = NULL;

    --size;

    return deleted_node;
}

// Delete a node at the end of the linked list and returns it
static Node *delete_last() {
    // Node to be deleted
    Node *deleted_node = tail;
    Node *previous_node = head;

    while (previous_node->nxt != NULL) {
        // Find the node previous to the node which will be deleted
        previous_node = previous_node->nxt;
    }

    // The second last node'll no more point to the last node
    // which means it'll become the new last node
    previous_node->nxt = NULL;

    // Makes the second last node become the last node
    tail = previous_node;

    --size;

    return deleted_node;
}

// Delete a node in the middle of the list and returns it
static Node *delete_middle(const size_t idx) {
    // Node to be deleted
    Node *deleted_node = NULL;

    // Node previous to the node to be deleted
    Node *previous_node = head;

    for (int i = 0; i < idx - 1; i++) {
        // Find the node previous to the position that the new node will be inserted
        previous_node = previous_node->nxt;
    }

    // Set the node to be deleted
    deleted_node = previous_node->nxt;

    // The previous node'll point to the node after the position it'll be deleted
    previous_node->nxt = previous_node->nxt->nxt;

    // It no longer points to the node at next position
    deleted_node->nxt = NULL;

    --size;

    return deleted_node;
}

// Deletes a node at the specified position and returns it
Node *delete(const int idx) {
    if (idx == 0)
        return delete_first();
    else if (idx == -1)
        return delete_last();
    else
        return delete_middle(idx);
}
