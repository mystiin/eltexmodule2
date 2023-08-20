#include <stdio.h>
#include <stdlib.h>

struct Node 
{
    int data;
    struct Node* next;
};

struct Node* head = NULL;
struct Node* tail = NULL;

void printList(struct Node* node) 
{
    while (node != NULL) 
    {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

void printListReverse(struct Node* node) 
{
    if (node == NULL) 
    {
        return;
    }
    printListReverse(node->next);
    printf("%d ", node->data);
    printf("\n");
}

void pushFront(int data) 
{
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = head;
    head = newNode;
    if (tail == NULL) 
    {
        tail = newNode;
    }
}

void pushBack(int data) 
{
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    if (tail != NULL) 
    {
        tail->next = newNode;
    }
    tail = newNode;
    if (head == NULL) 
    {
        head = newNode;
    }
}

void popFront() 
{
    if (head == NULL) 
    {
        return;
    }
    struct Node* temp = head;
    head = head->next;
    if (head == NULL) 
    {
        tail = NULL;
    }
    free(temp);
}

void popBack() 
{
    if (head == NULL) 
    {
        return;
    }
    if (head == tail) 
    {
        head = tail = NULL;
        return;
    }
    struct Node* current = head;
    while (current->next != tail) 
    {
        current = current->next;
    }
    current->next = NULL;
    free(tail);
    tail = current;
}

void insertAfter(struct Node* prevNode, int data) 
{
    if (prevNode == NULL) 
    {
        return;
    }
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = prevNode->next;
    prevNode->next = newNode;
    if (prevNode == tail) 
    {
        tail = newNode;
    }
}

void insertBefore(struct Node* nextNode, int data) 
{
    if (nextNode == NULL) 
    {
        return;
    }
    if (nextNode == head) 
    {
        pushFront(data);
        return;
    }
    struct Node* current = head;
    while (current->next != nextNode) 
    {
        current = current->next;
    }
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = nextNode;
    current->next = newNode;
}

void deleteNode(struct Node* node) 
{
    if (node == NULL) 
    {
        return;
    }
    if (node == head) 
    {
        popFront();
        return;
    }
    if (node == tail) 
    {
        popBack();
        return;
    }
    struct Node* current = head;
    while (current->next != node) 
    {
        current = current->next;
    }
    current->next = current->next->next;
    free(node);
}

void fillRandom(int n) 
{
    for (int i = 0; i < n; i++)
    {
        int data = rand() % 100;
        pushBack(data);
    }
}

void freeList() 
{
    struct Node* current = head;
    while (current != NULL) 
    {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
    head = tail = NULL;
}

void swap(struct Node* a, struct Node* b) 
{
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}

void insertionSort(struct Node* head_ref) 
{
    struct Node* curr = head_ref->next;
    struct Node* prev = head_ref;
    struct Node* next;
    while (curr != NULL) 
    {
        next = curr->next;
        while (prev != head_ref && curr->data < prev->data) 
        {
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        prev->next = curr;
        prev = curr;
        curr = next;
    }
}

void bubbleSort() {
    int swapped;
    struct Node* ptr1;
    struct Node* lptr = NULL;

    if (head == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) 
            {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void combSort() {

    int gap = sizeof(head) / sizeof(head->data);
    float shrink = 1.3;

    int swapped = 1;

    while (gap > 1 || swapped) {

        gap = gap / shrink;

        struct Node* curr = head;
        swapped = 0;

        while (curr->next != NULL) {

            struct Node* next = curr->next;

            if (next == NULL) {
                break;
            }

            if (curr->data < next->data) {

                swap(curr, next);
                swapped = 1;

            }

            curr = next;
        }
    }
}
int getNextGap(int gap) {
    gap = (gap * 10) / 13;
    if (gap < 1) {
        return 1;
    }
    return gap;
}
int main() {
    int choice;
    do 
    {
        printf("1. Print list\n");
        printf("2. Print reverse\n");
        printf("3. Add in head\n");
        printf("4. Add in tail \n");
        printf("5. Delete in head\n");
        printf("6. Delete in tail\n");
        printf("7. Insert after\n");
        printf("8. Insert before\n");
        printf("9. Delete node\n");
        printf("10. Fill random\n");
        printf("11. Clear all\n");
        printf("12. Bubble sort\n");
        printf("12. Comb sort\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf_s("%d", &choice);
        struct Node* prevNode;
        struct Node* nextNode;
        struct Node* node = head;
        int data;
        switch (choice) {
        case 1:
            system("cls");
            printList(head);
            break;
        case 2:
            printListReverse(head);
            break;
        case 3:
            printf("Enter data: ");
            scanf_s("%d", &data);
            pushFront(data);
            break;
        case 4:
            printf("Enter data: ");
            scanf_s("%d", &data);
            pushBack(data);
            break;
        case 5:
            popFront();
            break;
        case 6:
            popBack();
            break;
        case 7:
            printf("Enter previous node data: ");
            scanf_s("%d", &data);
            prevNode = head;
            while (prevNode != NULL && prevNode->data != data) {
                prevNode = prevNode->next;
            }
            if (prevNode == NULL) {
                printf("Node not found\n");
                break;
            }
            printf("Enter data to insert: ");
            scanf_s("%d", &data);
            insertAfter(prevNode, data);
            break;
        case 8:
            printf("Enter next node data: ");
            scanf_s("%d", &data);
            nextNode = head;
            while (nextNode != NULL && nextNode->data != data) {
                nextNode = nextNode->next;
            }
            if (nextNode == NULL) {
                printf("Node not found\n");
                break;
            }
            printf("Enter data to insert: ");
            scanf_s("%d", &data);
            insertBefore(nextNode, data);
            break;
        case 9:
            printf("Enter node data: ");
            scanf_s("%d", &data);
            while (node != NULL && node->data != data) {
                node = node->next;
            }
            if (node == NULL) {
                printf("Node not found\n");
                break;
            }
            deleteNode(node);
            break;
        case 10:
            printf("Enter number of nodes: ");
            scanf_s("%d", &data);
            fillRandom(data);
            break;
        case 11:
            freeList();
            printf("List cleared\n");
            break;
        case 12:
            bubbleSort();
            printf("List sort(bubble)\n");
            break;
        case 13:
            combSort();
            printf("List sort(comb)\n");
            break;
        case 0:
            printf("Exiting...\n");
            freeList();
            break;
        default:
            printf("Invalid choice\n");
        }
    } while (choice != 0);
    return 0;
}
