
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

    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of employees.\n");
        return 1;
    }

    emp = (struct Employee *)malloc(n * sizeof(struct Employee));

    if (emp == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("\nEnter details for employee %d\n", i + 1);

        printf("ID: ");
        if (scanf("%d", &emp[i].id) != 1) {
            printf("Invalid ID.\n");
            free(emp);
            return 1;
        }

        printf("Name: ");
        if (scanf("%49s", emp[i].name) != 1) {
            printf("Invalid name.\n");
            free(emp);
            return 1;
        }

        printf("Salary: ");
        if (scanf("%f", &emp[i].salary) != 1) {
            printf("Invalid salary.\n");
            free(emp);
            return 1;
        }
    }

    do {
        printf("\n--- Employee Record Menu ---\n");
        printf("1. Display all employees\n");
        printf("2. Search employee by ID\n");
        printf("3. Exit\n");

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            free(emp);
            return 1;
        }

        if (choice == 1) {
            printf("\n%-6s %-20s %-10s\n",
                   "ID", "Name", "Salary");

            for (i = 0; i < n; i++) {
                printf("%-6d %-20s %-10.2f\n",
                       emp[i].id,
                       emp[i].name,
                       emp[i].salary);
            }
        }

        else if (choice == 2) {
            int searchId, found = 0;

            printf("Enter ID to search: ");

            if (scanf("%d", &searchId) != 1) {
                printf("Invalid ID.\n");
                free(emp);
                return 1;
            }

            for (i = 0; i < n; i++) {
                if (emp[i].id == searchId) {
                    printf("\nEmployee Found!\n");
                    printf("ID = %d\n", emp[i].id);
                    printf("Name = %s\n", emp[i].name);
                    printf("Salary = %.2f\n", emp[i].salary);

                    found = 1;
                    break;
                }
            }

            if (!found) {
                printf("Employee with ID %d not found.\n",
                       searchId);
            }
        }

        else if (choice == 3) {
            printf("Exiting program.\n");
        }

        else {
            printf("Invalid choice.\n");
        }

    } while (choice != 3);

    free(emp);

    return 0;
}
