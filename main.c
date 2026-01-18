#include <stdio.h>
#include <stdlib.h>
#include "student.h"

void waitForEnter(void);

void displayMenu(void) {
    printf("═══════════════════════════════════════\n");
    printf("    STUDENT MANAGEMENT SYSTEM\n");
    printf("═══════════════════════════════════════\n");
    printf("1. Add Student\n");
    printf("2. Display All Students\n");
    printf("3. Search Student\n");
    printf("4. Update Student\n");
    printf("5. Delete Student\n");
    printf("6. Sort Students\n");
    printf("7. Calculate Statistics\n");
    printf("8. Exit\n");
    printf("═══════════════════════════════════════\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;
    extern int studentCount;
    
    // Load existing data from file
    loadFromFile();
    
    do {
        displayMenu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayAllStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                sortStudents();
                break;
            case 7:
                calculateStatistics();
                break;
            case 8:
                clearScreen();
                printf("═══════════════════════════════════════\n");
                printf("        THANK YOU FOR USING\n");
                printf("    STUDENT MANAGEMENT SYSTEM\n");
                printf("═══════════════════════════════════════\n\n");
                printf("Goodbye! Data has been saved to '%s'\n", FILENAME);
                printf("Total students saved: %d\n", studentCount);
                printf("═══════════════════════════════════════\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
                waitForEnter();
        }
    } while(choice != 8);
    
    return 0;
}