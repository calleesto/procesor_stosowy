#include <iostream>
#include <string>
using namespace std;

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

    if (!node->data.empty()) {
        Node* newNode = new Node;
        newNode->data = "";
        newNode->next = nullptr;
        node->next = newNode;
    }
}

Node* findLastNode(Node* node) {
    if (node == nullptr || node->next == nullptr) {
        return node;
    }
    return findLastNode(node->next);
}

void updateIndex(Node* node, int i) {
    if (node == nullptr) return;

    if (node != nullptr) {
        node->index = i++;
    } else {
        node->index = -1;
    }

    updateIndex(node->next, i);
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
    if (node == nullptr) {
        appendNode(node); // Create head
        updateIndex(node, 0);
    }

    Node* currentLast = findLastNode(node);

    switch (ch) {
        case '\'':
            appendNode(currentLast);
            updateIndex(node, 0);
        break;
        case ',':
            removeNode(node, currentLast);
        updateIndex(node, 0);
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
    string input;
    getline(cin, input);

    Node* head = nullptr;

    for (char ch : input) {
        manageInput(head, ch);
    }

    printStack(head);
    cleanup(head);

    return 0;
}