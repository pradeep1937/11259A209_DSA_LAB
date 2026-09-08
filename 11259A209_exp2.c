#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Employee {
 int id;
 char name[50];
 float salary;
};
int main() {
 int n, i, choice;
 struct Employee *emp;
printf("Enter number of employees: ");
 scanf("%d", &n);
 emp = (struct Employee *) malloc(n * sizeof(struct Employee));
 if (emp == NULL) {
 printf("Memory allocation failed.\n");
 return 1;
 }
 for (i = 0; i < n; i++) {
 printf("\nEnter details for employee %d\n", i + 1);
 printf("ID: ");
 scanf("%d", &(emp + i)->id);
 printf("Name: ");
 scanf("%s", (emp + i)->name);
 printf("Salary: ");
 scanf("%f", &(emp + i)->salary);
 }
 do {
 printf("\n--- Employee Record Menu ---\n");
 printf("1. Display all employees\n2. Search employee by ID\n3.Exit\n");
 printf("Enter your choice: ");
 scanf("%d", &choice);
if (choice == 1) {
 printf("\n%-6s %-20s %-10s\n", "ID", "Name", "Salary");
 for (i = 0; i < n; i++)
 printf("%-6d %-20s %-10.2f\n", (emp + i)->id, (emp + i)->name, (emp + i)->salary);
 } else if (choice == 2) {
 int searchId, found = 0;
 printf("Enter ID to search: ");
 scanf("%d", &searchId);
 for (i = 0; i < n; i++) {
if ((emp + i)->id == searchId) {
 printf("Found: ID=%d Name=%s Salary=%.2f\n",
 (emp + i)->id, (emp + i)->name, (emp + i)->salary);
 found = 1;
break;
 }
 }
 if (!found)
printf("Employee with ID %d not found.\n", searchId);
 }
 } while (choice != 3);
 free(emp);
 return 0;
}

