#include <stdio.h>
void printArray(int arr[], int n) {
int i;
for (i = 0; i < n; i++)
printf("%d ", arr[i]);
printf("\n");
}
void bubbleSort(int arr[], int n) {
int i, j, temp;
for (i = 0; i < n - 1; i++) {
for (j = 0; j < n - i - 1; j++) {
if (arr[j] > arr[j + 1]) {
temp = arr[j];
arr[j] = arr[j + 1];
arr[j + 1] = temp;
}
}
}
}
void selectionSort(int arr[], int n) {
int i, j, minIndex, temp;
for (i = 0; i < n - 1; i++) {
minIndex = i;
for (j = i + 1; j < n; j++) {
if (arr[j] < arr[minIndex])
minIndex = j;
}
temp = arr[minIndex];
arr[minIndex] = arr[i];
arr[i] = temp;
}
}
void heapify(int arr[], int n, int i) {
int largest = i;
int left = 2 * i + 1;
int right = 2 * i + 2;
int temp;
if (left < n && arr[left] > arr[largest])
largest = left;
if (right < n && arr[right] > arr[largest])
largest = right;
if (largest != i) {
temp = arr[i];
arr[i] = arr[largest];
arr[largest] = temp;
heapify(arr, n, largest);
}
}
void heapSort(int arr[], int n) {
    int i, temp;
for (i = n / 2 - 1; i >= 0; i--)
heapify(arr, n, i);
for (i = n - 1; i > 0; i--) {
temp = arr[0];
arr[0] = arr[i];
arr[i] = temp;
heapify(arr, i, 0);
}
}
int main() {
int arr[100], temp[100], n, i, choice;
printf("Enter number of elements: ");
scanf("%d", &n);
printf("Enter %d elements: ", n);
for (i = 0; i < n; i++)
scanf("%d", &arr[i]);
do {
printf("\n--- Sorting Menu ---\n");
printf("1. Bubble Sort\n2. Selection Sort\n3. Heap Sort\n4.
Exit\n");
printf("Enter your choice: ");
scanf("%d", &choice);
for (i = 0; i < n; i++)
temp[i] = arr[i];
switch (choice) {
case 1:
bubbleSort(temp, n);
printf("Sorted array (Bubble Sort): ");
printArray(temp, n);
break;
case 2:
selectionSort(temp, n);
printf("Sorted array (Selection Sort): ");
printArray(temp, n);
break;
case 3:
heapSort(temp, n);
printf("Sorted array (Heap Sort): ");
printArray(temp, n);
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