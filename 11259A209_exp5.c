#include <stdio.h>
#define MAX 5
int queue[MAX];
int front = -1, rear = -1;
void enqueue(int val) {
 if (rear == MAX - 1) {
 printf("Queue Overflow\n");
 return;
 }
 if (front == -1)
 front = 0;
 queue[++rear] = val;
 printf("%d enqueued to queue.\n", val);
}
void dequeue() {
 if (front == -1 || front > rear) {
 printf("Queue Underflow\n");
 return;
 }
 printf("%d dequeued from queue.\n", queue[front]);
 front++;
 if (front > rear)
 front = rear = -1;
}
void display() {
 int i;
 if (front == -1 || front > rear) {
 printf("Queue is empty.\n");
 return;
 }
 printf("Queue elements: ");
 for (i = front; i <= rear; i++)
 printf("%d ", queue[i]);
 printf("\n");
}
int main() {
 int choice, val;
 do {
 printf("\n--- Simple Queue Menu ---\n");
 printf("1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\n");
 printf("Enter your choice: ");
 scanf("%d", &choice);
 switch (choice) {
 case 1:
 printf("Enter value to enqueue: ");
 scanf("%d", &val);
 enqueue(val);
 break;
 case 2:
 dequeue();
 break;
 case 3:
 display();
 break;
 case 4:
 printf("Exiting program.\n");
 break;
 default:
 printf("Invalid choice.\n");
 }
 } while (choice != 4);
 return 0;
}
