#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    // Can be replaced by whatever datatype is required
    // Even by a union/struct to handle multiple datatypes at the same time
    int data;

    // Pointer to next node
    struct Node *nxt;

    // Array like index to indentify the node
    size_t idx;

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

    // All nodes' indexes will be shifted to right (incremented)
    for (Node *node = head; node != NULL; node = node->nxt) {
        ++node->idx;
    }

    // Set new node's index to 0 (it indicates new_node's gonna be the first node)
    new_node->idx = 0;

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

    // Set new node's index to biggest index (it indicates new_node's gonna be the last node)
    new_node->idx = tail->idx + 1;

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

    for (Node *node = head; node != NULL; node = node->nxt) {
        if (node->idx == idx) {
            new_node->data = data;

            // The new node'll point to the node after the location it'll be inserted
            new_node->nxt = node;

            // Set the new node's index to the the position it'll be inserted
            new_node->idx = idx;
        } else if (node->idx == idx - 1) {
            // The node behind the position that the new node will be inserted
            // will point to the new node
            node->nxt = new_node;
        }

        // All nodes after the position the new node was inserted
        // will have their indexes shifted to right (incremented)
        if (node->idx >= idx) {
            ++node->idx;
        }
    }

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

    // All nodes' indexes will be shifted to left (decremented)
    for (Node *node = head; node != NULL; node = node->nxt) {
        --node->idx;
    }

    --size;

    return deleted_node;
}

// Delete a node at the end of the linked list and returns it
static Node *delete_last() {
    // Node to be deleted
    Node *deleted_node = tail;

    for (Node *node = head; node != NULL; node = node->nxt) {
        if (node->idx == size - 2) {
            // The second last node'll no more point to the last node
            // which means it'll become the new last node
            node->nxt = NULL;

            // Makes the second last node become the last node
            tail = node;
        }
    }

    --size;

    return deleted_node;
}

// Delete a node in the middle of the list and returns it
static Node *delete_middle(const size_t idx) {
    // Node to be deleted
    Node *deleted_node = NULL;

    // Node previous to the node to be deleted
    Node *previous_deleted_node = NULL;

    for (Node *node = head; node != NULL; node = node->nxt) {
        if (node->idx == idx - 1) {
            // Identities the node previous to the node to be deleted
            previous_deleted_node = node;
        } else if (node->idx == idx) {
            // Identities the node to be deleted
            deleted_node = node;

            // It no longer points to the node at next position
            deleted_node->nxt = NULL;
        } else if (node->idx == idx + 1) {
            // The previous node'll point to the node after the position it'll be deleted
            previous_deleted_node->nxt = node;
        }

        // All nodes after the position the node was deleted
        // will have their indexes shifted to left (decremented)
        if (node->idx >= idx) {
            --node->idx;
        }
    }

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
