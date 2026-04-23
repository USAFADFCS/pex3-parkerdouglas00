/** 
 * ================================================================
 * Name: Parker Doutlas
 * Section: Hemmes M3
 * Project: Implementation of Double-Linked List Library
 * =================================================================
 */
#include "listAsDoubleLinkedList.h"

DoubleLinkedList* createLinkedList() {
    DoubleLinkedList* newList = (DoubleLinkedList*) malloc(sizeof(DoubleLinkedList));
    newList->head = NULL;
    newList->tail = NULL;
    newList->numberOfElements = 0;
    return newList;
}

void deleteLinkedList(DoubleLinkedList* list) {
    Node* currentNode = list->head;
    while (currentNode != NULL) {
        Node* nextNode = currentNode->next;
        free(currentNode);
        currentNode = nextNode;
    }
    free(list);
}

void appendElementLinkedList(DoubleLinkedList* list, int element) {
    insertElementLinkedList(list, list->numberOfElements, element);
}

int lengthOfLinkedList(DoubleLinkedList* list) {
    return list->numberOfElements;
}

void printLinkedList(DoubleLinkedList* list) {
    Node* currentNode = list->head;
    while (currentNode != NULL) {
        printf("%d\n", currentNode->data);
        currentNode = currentNode->next;
    }
}

int getElementLinkedList(DoubleLinkedList* list, int position) {
    Node* currentNode = list->head;
    for (int i = 0; i < position; i++) {
        if (currentNode == NULL) {
            return -1;
        }
        currentNode = currentNode->next;
    }
    return currentNode->data;
}

void deleteElementLinkedList(DoubleLinkedList* list, int position) {
    //deleting the only node
    if (list->numberOfElements == 1) {
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        list->numberOfElements--;
    }
    //deleting the first node
    else if (position == 0) {
        Node* temp = list->head;
        list->head = list->head->next;
        list->head->prev = NULL;
        free(temp);
        list->numberOfElements--;
    }
    //deleting the last node
    else if (position == list->numberOfElements - 1) {
        Node* temp = list->head;
        while (temp->next != list->tail) {
            temp = temp->next;
        }
        temp->next = NULL;
        free(list->tail);
        list->tail = temp;
        list->numberOfElements--;
    }
    //deleting a middle node
    else {
        Node* nodeToDelete;
        Node* nodeBefore = list->head;
        int currentPosition = 0;
        while (currentPosition < position - 1) {
            nodeBefore = nodeBefore->next;
            currentPosition++;
        }
        nodeToDelete = nodeBefore->next;
        nodeBefore->next = nodeToDelete->next;
        nodeToDelete->next->prev = nodeBefore;
        free(nodeToDelete);
        list->numberOfElements--;
    }
}

void insertElementLinkedList(DoubleLinkedList* list, int position, int element) {
    //empty list
    if (list->numberOfElements == 0) {
        Node* newNode = (Node*) malloc(sizeof(Node));
        newNode->data = element;
        list->head = newNode;
        list->tail = newNode;
        list->numberOfElements++;
    }
    //insert at beginning
    else if (position == 0) {
        Node* newNode = (Node*) malloc(sizeof(Node));
        newNode->data = element;
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
        list->numberOfElements++;
    }
    //insert at end
    else if (position == list->numberOfElements) {
        Node* newNode = (Node*) malloc(sizeof(Node));
        newNode->data = element;
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
        list->numberOfElements++;
    }
    //insert in middle
    else {
        Node* newNode = (Node*) malloc(sizeof(Node));
        newNode->data = element;
        Node* temp = list->head;
        int currentPosition = 0;
        while (currentPosition != position-1) {
            temp = temp->next;
            currentPosition++;
        }
        newNode->next = temp->next;
        newNode->prev = temp;
        newNode->next->prev = newNode;
        temp->next = newNode;
        list->numberOfElements++;
    }
}

void changeElementLinkedList(DoubleLinkedList* list, int position, int newElement) {
    Node* currentNode = list->head;
    int currentPosition = 0;
    while (currentPosition != position) {
        currentNode = currentNode->next;
        currentPosition++;
    }
    currentNode->data = newElement;
}

int findElementLinkedList(DoubleLinkedList* list, int element) {
    Node* currentNode = list->head;
    int currentPosition = 0;
    while(currentNode != NULL) {
        if (currentNode->data == element) {
            return currentPosition;
        }
        currentNode = currentNode->next;
        currentPosition++;
    }
    return -1;
}