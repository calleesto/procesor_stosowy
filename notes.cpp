#include <iostream>
#include <string>
using namespace std;

struct Node {
    string data;
    int index;
    Node* next;
};

void printStack(Node* node) {
    if (node == NULL) return;
    cout << node->index << ": " << node->data << endl;
    printStack(node->next); // Recursively print the next node
}

void addDataToLastNode(Node* node, char ch) {
    node->data = ch + node->data; // Add the character to the node's data
}

void appendNode(Node* node) {
    if (node->data != "") {
        Node* newNode = new Node;
        newNode->data = "";
        newNode->next = NULL;
        node->next = newNode; // Link to the new node
    }
}

Node* findLastNode(Node* node, int i) {
    if (node == NULL || node->next == NULL) {
        node->index = i;
        return node; // Base case: return the last node
    }
    return findLastNode(node->next, ++i); // Recurse to the next node
}

// void updateIndex(Node* node, int i) {
//     if (node == NULL || node->next == NULL) {
//         node->index = i;
//     }
//     updateIndex(node->next, ++i); // Recurse to the next node
// }

void removeNode(Node*& node, Node* target) {
    if (node == NULL) return; // Empty list, nothing to remove

    // If the node to be removed is the head node (first node)
    if (node == target) {
        Node* temp = node;
        node = node->next; // Move the node pointer to the next node
        temp->next = nullptr; // Break the link to avoid accessing freed memory
        delete temp; // Free the memory of the old node
        return;
    }

    // Recurse to find the node to remove (middle or last node)
    if (node->next != nullptr && node->next == target) {
        Node* temp = node->next; // Node to be deleted
        node->next = node->next->next; // Bypass the node to delete
        temp->next = nullptr; // Ensure the deleted node's next is null
        delete temp; // Free the memory of the deleted node
        return;
    }

    // Continue the search recursively
    removeNode(node->next, target);
}

void manageInput(Node* node, char ch) {
    Node* currentNode = findLastNode(node, 0);
    switch (ch) {
        case '\'':
            appendNode(currentNode); // Add a new node when encountering '\'
            break;
        case ',':
            removeNode(node, currentNode); // Remove the current node when encountering ','
            break;
        default:
            addDataToLastNode(currentNode, ch); // Add the character to the last node
            break;
    }
}

// Recursively clean up nodes
void cleanup(Node* node) {
    if (node == NULL) return; // Base case: no more nodes to delete
    cleanup(node->next);      // Recurse to the next node
    delete node;              // Delete the current node
}

int main() {


    string input;
    getline(cin, input); // Read the input string

    // Check if the first character is the apostrophe (')
    if (!input.empty() && input[0] == '\'') {
        Node* head = new Node;
        head->data = "";
        head->next = NULL;
        head->index = 0;
        for (char ch : input) {
            // Find the last node each time in the loop
            manageInput(head, ch); // Process the current character
        }
        printStack(head);

        // Recursively clean up dynamically allocated memory
        cleanup(head);
    }

    // Use one loop for processing the input string


    // Print the stack recursively


    return 0;
}