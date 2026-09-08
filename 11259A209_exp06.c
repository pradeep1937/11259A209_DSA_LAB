#include <stdio.h>
#define MAX 100
int pq[MAX];
int n = 0;
void insert(int val) {
 if (n == MAX) {
 printf("Priority Queue is full.\n");
 return;
 }
 pq[n++] = val;
 printf("%d inserted into priority queue.\n", val);
}
int findMinIndex() {
 int i, minIndex = 0;
 for (i = 1; i < n; i++)
 if (pq[i] < pq[minIndex])
 minIndex = i;
 return minIndex;
}
void findMin() {
 if (n == 0) {
 printf("Priority Queue is empty.\n");
 return;
 }
 printf("Minimum element (highest priority): %d\n", pq[findMinIndex()]);
}
void deleteMin() {
 int i, minIndex;
 if (n == 0) {
 printf("Priority Queue is empty. Cannot delete.\n");
 return;
 }
 minIndex = findMinIndex();
 printf("Deleted min element: %d\n", pq[minIndex]);
 for (i = minIndex; i < n - 1; i++)
 pq[i] = pq[i + 1];
 n--;
}
void display() {
 int i;
 if (n == 0) {
 printf("Priority Queue is empty.\n");
 return;
 }
 printf("Priority Queue elements: ");
 for (i = 0; i < n; i++)
 printf("%d ", pq[i]);
 printf("\n");
}
int main() {
 int choice, val;
 do {
 printf("\n--- Priority Queue Menu ---\n");
 printf("1. Insert\n2. FindMin\n3. DeleteMin\n4. Display\n5. Exit\n");
printf("Enter your choice: ");
 scanf("%d", &choice);
 switch (choice) {
 case 1:
 printf("Enter value to insert: ");
 scanf("%d", &val);
 insert(val);
 break;
 case 2:
 findMin();
 break;
 case 3:
 deleteMin();
 break;
 case 4:
 display();
 break;
 case 5:
 printf("Exiting program.\n");
 break;
 default:
 printf("Invalid choice.\n");
 }
 } while (choice != 5);
 return 0;
}
