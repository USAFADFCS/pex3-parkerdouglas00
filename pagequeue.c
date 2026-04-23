/** pagequeue.c
 * ===========================================================
 * Name: _______________________, __ ___ 2026
 * Section: CS483 / ____
 * Project: PEX3 - Page Replacement Simulator
 * Purpose: Implementation of the PageQueue ADT — a doubly-linked
 *          list for LRU page replacement.
 *          Head = LRU (eviction end), Tail = MRU end.
 * =========================================================== */
#include <stdio.h>
#include <stdlib.h>

#include "pagequeue.h"

/**
 * @brief Create and initialize a page queue with a given capacity
 */
PageQueue *pqInit(unsigned int maxSize) {
    // TODO: malloc a PageQueue, set head and tail to NULL,
    //       size to 0, maxSize to maxSize, and return the pointer
    PageQueue* newPageQueue = (PageQueue*) malloc(sizeof(PageQueue));
    newPageQueue->head = NULL;
    newPageQueue->tail = NULL;
    newPageQueue->size = 0;
    newPageQueue->maxSize = maxSize;
    return newPageQueue;
}

/**
 * @brief Access a page in the queue (simulates a memory reference)
 */
long pqAccess(PageQueue *pq, unsigned long pageNum) {
    // TODO: Search the queue for pageNum (suggest searching tail->head
    //       so you naturally count depth from the MRU end).
    //
    // HIT path (page found at depth d):
    //   - Remove the node from its current position and re-insert
    //     it at the tail (most recently used).
    //   - Return d.
    //
    // MISS path (page not found):
    //   - Allocate a new node for pageNum and insert it at the tail.
    //   - If size now exceeds maxSize, evict the head node (free it).
    //   - Return -1.
    PqNode* currentNode = pq->tail;
    long d = 0;

    while (currentNode != NULL) {
        // HIT
        if (currentNode->pageNum == pageNum) {
            // if the hit node isn't the tail already
            if (currentNode != pq->tail) {
                // if currentNode is not head
            if (currentNode->prev != NULL) {
                currentNode->prev->next = currentNode->next;
            }
            // if currentNode is head
            if (currentNode == pq->head) {
                pq->head = currentNode->next;
            }
            currentNode->next->prev = currentNode->prev;
            currentNode->prev = pq->tail;
            currentNode->next = NULL;
            pq->tail->next = currentNode;
            pq->tail = currentNode;
            }
            return d;
        }
        d++;
        currentNode = currentNode->prev;
    }

    // MISS
    PqNode* newNode = (PqNode*) malloc(sizeof(PqNode));
    newNode->pageNum = pageNum;
    newNode->next = NULL;
    newNode->prev = pq->tail;

    // queue is not empty
    if (pq->tail != NULL) {
        pq->tail->next = newNode;
    }
    // queue is empty
    else {
        pq->head = newNode;
    }

    pq->tail = newNode;
    pq->size++;

    //size now exceeds maxSize
    if (pq->size > pq->maxSize) {
        PqNode* nodeToEvict = pq->head;
        pq->head = pq->head->next;
        // if evicted node was not only node
        if (pq->head != NULL) {
            pq->head->prev = NULL;
        }
        // if evicted node was only node
        else {
            pq->tail = NULL;
        }
        free(nodeToEvict);
        pq->size--;
    }
    
    return -1;
}

/**
 * @brief Free all nodes in the queue and reset it to empty
 */
void pqFree(PageQueue *pq) {
    // TODO: Walk from head to tail, free each node, then free
    //       the PageQueue struct itself.
    PqNode* currentNode = pq->head;
    while (currentNode != NULL) {
        PqNode* nextNode = currentNode->next;
        free(currentNode);
        currentNode = nextNode;
    }
    free(pq);
}

/**
 * @brief Print queue contents to stderr for debugging
 */
void pqPrint(PageQueue *pq) {
    // TODO (optional): Print each page number from head to tail,
    //                  marking which is head and which is tail.
    //                  Useful for desk-checking small traces.
}
