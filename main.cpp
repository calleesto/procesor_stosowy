#include <iostream>
using namespace std;

#define MAX_INPUT 20000

struct Node {
    string data;
    int index;
    Node* next;
};

void printStack(Node* node) {
    if (node == nullptr) return;
    cout << node->index << ": " << node->data << endl;
    printStack(node->next);
}

void addDataToLastNode(Node* node, char ch) {
    node->data = ch + node->data;
}

void appendNode(Node*& node) {
    if (node == nullptr) {
        node = new Node;
        node->data = "";
        node->next = nullptr;
        node->index = 0;
        return;
    }

    if (node->data != "") {
        Node* newNode = new Node;
        newNode->data = "";
        newNode->next = nullptr;
        node->next = newNode;
    }
}

Node* findLastNode(Node* node, int i) {
    if (node == nullptr || node->next == nullptr) {
        node->index = i;
        return node;
    }
    return findLastNode(node->next, ++i);
}

void removeNode(Node*& node, Node* target) {
    if (node == nullptr) return;

    if (node == target) {
        Node* temp = node;
        node = node->next;
        temp->next = nullptr;
        delete temp;
        return;
    }

    if (node->next != nullptr && node->next == target) {
        Node* temp = node->next;
        node->next = node->next->next;
        temp->next = nullptr;
        delete temp;
        return;
    }

    removeNode(node->next, target);
}

void manageInput(Node*& node, char ch) {
    if (node == nullptr && ch == '\'') {
        appendNode(node);
        return;
    }

    if (node == nullptr) return; // Ignore other chars before first apostrophe

    Node* currentLast = findLastNode(node, 0);
    switch (ch) {
        case '\'':
            appendNode(currentLast);
        break;
        case ',':
            removeNode(node, currentLast);
        break;
        default:
            addDataToLastNode(currentLast, ch);
        break;
    }
}

void cleanup(Node* node) {
    if (node == nullptr) return;
    cleanup(node->next);
    delete node;
}

int main() {
    char input[MAX_INPUT];

    cin.getline(input, MAX_INPUT);

    Node* head = nullptr;

    for (int i = 0; input[i] != '\0'; ++i) {
        manageInput(head, input[i]);
    }

    printStack(head);
    cleanup(head);

    return 0;
}