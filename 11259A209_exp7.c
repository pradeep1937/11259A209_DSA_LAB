
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *head = NULL;

void insertBeginning(int val) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    newNode->data = val;
    newNode->next = head;
    head = newNode;

    printf("%d inserted at beginning.\n", val);
}

void insertEnd(int val) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    newNode->data = val;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        printf("%d inserted at end.\n", val);
        return;
    }

    struct Node *temp = head;

    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;

    printf("%d inserted at end.\n", val);
}

void insertPosition(int val, int pos) {
    int i;
    struct Node *temp = head;

    if (pos < 0) {
        printf("Invalid position.\n");
        return;
    }

    if (pos == 0) {
        insertBeginning(val);
        return;
    }

    for (i = 0; i < pos - 1 && temp != NULL; i++)
        temp = temp->next;

    if (temp == NULL) {
        printf("Invalid position.\n");
        return;
    }

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    newNode->data = val;
    newNode->next = temp->next;
    temp->next = newNode;

    printf("%d inserted at position %d.\n", val, pos);
}

void deleteBeginning() {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node *temp = head;

    head = head->next;

    printf("%d deleted from beginning.\n", temp->data);

    free(temp);
}

void deleteEnd() {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    if (head->next == NULL) {
        printf("%d deleted from end.\n", head->data);
        free(head);
        head = NULL;
        return;
    }

    struct Node *temp = head;

    while (temp->next->next != NULL)
        temp = temp->next;

    printf("%d deleted from end.\n", temp->next->data);

    free(temp->next);
    temp->next = NULL;
}

void deletePosition(int pos) {
    int i;

    if (pos < 0 || head == NULL) {
        printf("Invalid position or empty list.\n");
        return;
    }

    if (pos == 0) {
        deleteBeginning();
        return;
    }

    struct Node *temp = head;

    for (i = 0; i < pos - 1 && temp != NULL; i++)
        temp = temp->next;

    if (temp == NULL || temp->next == NULL) {
        printf("Invalid position.\n");
        return;
    }

    struct Node *toDelete = temp->next;

    temp->next = toDelete->next;

    printf("%d deleted from position %d.\n", toDelete->data, pos);

    free(toDelete);
}

void traverse() {
    struct Node *temp = head;

    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    printf("Linked List: ");

    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }

    printf("NULL\n");
}

void freeList() {
    struct Node *temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    int choice, val, pos;

    do {
        printf("\n--- Singly Linked List Menu ---\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at Position\n");
        printf("3. Insert at End\n");
        printf("4. Delete at Beginning\n");
        printf("5. Delete at Position\n");
        printf("6. Delete at End\n");
        printf("7. Traverse\n");
        printf("8. Exit\n");

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            freeList();
            return 1;
        }

        switch (choice) {
            case 1:
                printf("Enter value: ");

                if (scanf("%d", &val) != 1) {
                    printf("Invalid input.\n");
                    freeList();
                    return 1;
                }

                insertBeginning(val);
                break;

            case 2:
                printf("Enter value and position (0-indexed): ");

                if (scanf("%d %d", &val, &pos) != 2) {
                    printf("Invalid input.\n");
                    freeList();
                    return 1;
                }

                insertPosition(val, pos);
                break;

            case 3:
                printf("Enter value: ");

                if (scanf("%d", &val) != 1) {
                    printf("Invalid input.\n");
                    freeList();
                    return 1;
                }

                insertEnd(val);
                break;

            case 4:
                deleteBeginning();
                break;

            case 5:
                printf("Enter position (0-indexed): ");

                if (scanf("%d", &pos) != 1) {
                    printf("Invalid input.\n");
                    freeList();
                    return 1;
                }

                deletePosition(pos);
                break;

            case 6:
                deleteEnd();
                break;

            case 7:
                traverse();
                break;

            case 8:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 8);

    freeList();

    return 0;
}
