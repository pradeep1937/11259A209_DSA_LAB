#include <stdio.h>
#include <stdlib.h>
struct Node {
int data;
struct Node *left, *right;
};
struct Node *createNode(int val) {
struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
newNode->data = val;
newNode->left = newNode->right = NULL;
return newNode;
}
struct Node *insert(struct Node *root, int val) {
if (root == NULL)
return createNode(val);
if (val < root->data)
root->left = insert(root->left, val);
else if (val > root->data)
root->right = insert(root->right, val);
return root;
}
void inorder(struct Node *root) {
if (root != NULL) {
inorder(root->left);
printf("%d ", root->data);
inorder(root->right);
}
}
void preorder(struct Node *root) {
if (root != NULL) {
printf("%d ", root->data);
preorder(root->left);
preorder(root->right);
}
}
void postorder(struct Node *root) {
if (root != NULL) {
postorder(root->left);
postorder(root->right);
printf("%d ", root->data);
}
}
#define QMAX 100
void levelorder(struct Node *root) {
struct Node *queue[QMAX];
int front = 0, rear = 0;
if (root == NULL) {
printf("Tree is empty.\n");
return;
}
queue[rear++] = root;
while (front < rear) {
struct Node *curr = queue[front++];
printf("%d ", curr->data);
if (curr->left != NULL)
queue[rear++] = curr->left;
if (curr->right != NULL)
queue[rear++] = curr->right;
}
}
int main() {
struct Node *root = NULL;
int n, i, val, choice;
printf("Enter number of nodes to insert: ");
scanf("%d", &n);
printf("Enter %d values: ", n);
for (i = 0; i < n; i++) {
scanf("%d", &val);
root = insert(root, val);
}
do {
printf("\n--- BST Traversal Menu ---\n");

printf("1. In-order\n2. Pre-order\n3. Post-order\n4. Level-
order\n5. Insert new node\n6. Exit\n");

printf("Enter your choice: ");
scanf("%d", &choice);
switch (choice) {
case 1:
printf("In-order Traversal: ");
inorder(root);
printf("\n");
break;
case 2:
printf("Pre-order Traversal: ");
preorder(root);
printf("\n");
break;
case 3:
printf("Post-order Traversal: ");
postorder(root);
printf("\n");
break;
case 4:
printf("Level-order Traversal: ");
levelorder(root);
printf("\n");
break;
case 5:
printf("Enter value to insert: ");
scanf("%d", &val);
root = insert(root, val);
break;
case 6:
printf("Exiting program.\n");
break;
default:
printf("Invalid choice.\n");
}
} while (choice != 6);
return 0;
}