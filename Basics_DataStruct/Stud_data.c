#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Student {
    char name[50];
    char surname[50];
    int id;
    float grade;
    struct Student *next;
} Student;


void addStudent(Student **head);
void removeStudent(Student **head);
void searchStudent(Student *head);
void displayStudents(Student *head);
void displayAverageGrade(Student *head);
void saveToFile(Student *head, const char *filename);
void readFromFile(Student **head, const char *filename);
void freeMemory(Student *head);


int main() {
    Student *head = NULL;
    int choice;
    const char *filename = "group_details.csv";

    do {
        printf("\nStudent Management System\n");
        printf("1. Add a new student\n");
        printf("2. Remove a student by ID\n");
        printf("3. Search a student by ID\n");
        printf("4. Display all student details\n");
        printf("5. Display average grade of all students\n");
        printf("6. Save student details to file\n");
        printf("7. Read student details from file\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                addStudent(&head);
                break;
            case 2:
                removeStudent(&head);
                break;
            case 3:
                searchStudent(head);
                break;
            case 4:
                displayStudents(head);
                break;
            case 5:
                displayAverageGrade(head);
                break;
            case 6:
                saveToFile(head, filename);
                break;
            case 7:
                readFromFile(&head, filename);
                break;
            case 8:
                freeMemory(head);
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 8);

    return 0;
}

void addStudent(Student **head) {
    Student *newStudent = (Student *)malloc(sizeof(Student));
    if (!newStudent) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Enter name: ");
    fgets(newStudent->name, sizeof(newStudent->name), stdin);
    newStudent->name[strcspn(newStudent->name, "\n")] = '\0';

    printf("Enter surname: ");
    fgets(newStudent->surname, sizeof(newStudent->surname), stdin);
    newStudent->surname[strcspn(newStudent->surname, "\n")] = '\0';

    printf("Enter ID: ");
    scanf("%d", &newStudent->id);
    getchar();

    printf("Enter grade: ");
    scanf("%f", &newStudent->grade);
    getchar();

    newStudent->next = *head;
    *head = newStudent;
    printf("Student added successfully.\n");
}

void removeStudent(Student **head) {
    int id;
    printf("Enter ID of the student to remove: ");
    scanf("%d", &id);
    getchar();

    Student *current = *head, *prev = NULL;
    while (current) {
        if (current->id == id) {
            if (prev) {
                prev->next = current->next;
            } else {
                *head = current->next;
            }
            free(current);
            printf("Student removed successfully.\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Student with ID %d not found.\n", id);
}

void searchStudent(Student *head) {
    int id;
    printf("Enter ID of the student to search: ");
    scanf("%d", &id);
    getchar();

    Student *current = head;
    while (current) {
        if (current->id == id) {
            printf("Name: %s, Surname: %s, ID: %d, Grade: %.2f\n",
                   current->name, current->surname, current->id, current->grade);
            return;
        }
        current = current->next;
    }
    printf("Student with ID %d not found.\n", id);
}


void displayStudents(Student *head) {
    if (!head) {
        printf("No students to display.\n");
        return;
    }

    Student *current = head;
    while (current) {
        printf("Name: %s, Surname: %s, ID: %d, Grade: %.2f\n",
               current->name, current->surname, current->id, current->grade);
        current = current->next;
    }
}


void displayAverageGrade(Student *head) {
    if (!head) {
        printf("No students to calculate average grade.\n");
        return;
    }

    int count = 0;
    float total = 0.0;
    Student *current = head;
    while (current) {
        total += current->grade;
        count++;
        current = current->next;
    }
    printf("Average grade: %.2f\n", total / count);
}

void saveToFile(Student *head, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Failed to open file for writing.\n");
        return;
    }

    Student *current = head;
    while (current) {
        fprintf(file, "%s,%s,%d,%.2f\n",
                current->name, current->surname, current->id, current->grade);
        current = current->next;
    }

    fclose(file);
    printf("Student details saved to file successfully.\n");
}

void readFromFile(Student **head, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Failed to open file for reading.\n");
        return;
    }

    freeMemory(*head);
    *head = NULL;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Student *newStudent = (Student *)malloc(sizeof(Student));
        if (!newStudent) {
            printf("Memory allocation failed.\n");
            fclose(file);
            return;
        }

        sscanf(line, "%49[^,],%49[^,],%d,%f",
               newStudent->name, newStudent->surname, &newStudent->id, &newStudent->grade);
        newStudent->next = *head;
        *head = newStudent;
    }

    fclose(file);
    printf("Student details loaded from file successfully.\n");
}

void freeMemory(Student *head) {
    while (head) {
        Student *temp = head;
        head = head->next;
        free(temp);
    }
}
