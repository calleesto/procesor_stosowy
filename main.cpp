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

void appendNode(Node* node) {
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
        delete node;
        temp = node->next;
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

void manageInput(Node* node, char ch) {
    Node* currentNode = findLastNode(node, 0);
    switch (ch) {
        case '\'':
            appendNode(currentNode);
            break;
        case ',':
            removeNode(node, currentNode);
            break;
        default:
            addDataToLastNode(currentNode, ch);
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

    if (!input.empty() && input[0] == '\'') {
        Node* head = new Node;
        head->data = "";
        head->next = nullptr;
        head->index = 0;
        for (char ch : input) {
            manageInput(head, ch);
        }
        printStack(head);
        cleanup(head);
    }

    return 0;
}