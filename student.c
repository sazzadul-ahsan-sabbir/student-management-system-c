#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "student.h"

// Global variables
Student students[100];
int studentCount = 0;

// Clear screen function (works for Windows/Linux/Mac)
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Wait for user input
void waitForEnter() {
    printf("\nPress Enter to continue...");
    while(getchar() != '\n');
    getchar(); // Wait for Enter key
}

// Get next available ID
int getNextId() {
    int maxId = 0;
    for(int i = 0; i < studentCount; i++) {
        if(students[i].id > maxId) {
            maxId = students[i].id;
        }
    }
    return maxId + 1;
}

// Save student to file
void saveToFile(Student s) {
    FILE *file = fopen(FILENAME, "ab");
    if(file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fwrite(&s, sizeof(Student), 1, file);
    fclose(file);
}

// Load all students from file
void loadFromFile() {
    FILE *file = fopen(FILENAME, "rb");
    if(file == NULL) {
        return; // File doesn't exist yet
    }
    
    studentCount = 0;
    while(fread(&students[studentCount], sizeof(Student), 1, file) == 1) {
        studentCount++;
        if(studentCount >= 100) break;
    }
    fclose(file);
}

// Add a new student
void addStudent() {
    clearScreen();
    printf("═══════════════════════════════════════\n");
    printf("           ADD NEW STUDENT\n");
    printf("═══════════════════════════════════════\n\n");
    
    if(studentCount >= 100) {
        printf("Database full! Cannot add more students.\n");
        waitForEnter();
        return;
    }
    
    Student newStudent;
    newStudent.id = getNextId();
    
    // Get student details
    printf("Student ID: %d\n", newStudent.id);
    
    printf("Enter Name: ");
    getchar(); // Clear input buffer
    fgets(newStudent.name, MAX_NAME_LEN, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = 0; // Remove newline
    
    printf("Enter Age: ");
    scanf("%d", &newStudent.age);
    
    printf("Enter Course: ");
    getchar();
    fgets(newStudent.course, MAX_COURSE_LEN, stdin);
    newStudent.course[strcspn(newStudent.course, "\n")] = 0;
    
    printf("Enter Grade (0-100): ");
    scanf("%f", &newStudent.grade);
    
    // Validate grade
    if(newStudent.grade < 0 || newStudent.grade > 100) {
        printf("Invalid grade! Grade must be between 0 and 100.\n");
        waitForEnter();
        return;
    }
    
    // Add to array and save to file
    students[studentCount] = newStudent;
    studentCount++;
    saveToFile(newStudent);
    
    printf("\n✅ Student added successfully!\n");
    printf("\n═══════════════════════════════════════\n");
    printf("Student Details:\n");
    printf("ID: %d\n", newStudent.id);
    printf("Name: %s\n", newStudent.name);
    printf("Age: %d\n", newStudent.age);
    printf("Course: %s\n", newStudent.course);
    printf("Grade: %.2f\n", newStudent.grade);
    printf("═══════════════════════════════════════\n");
    
    waitForEnter();
}

// Display all students
void displayAllStudents() {
    clearScreen();
    printf("═══════════════════════════════════════\n");
    printf("         ALL STUDENTS RECORDS\n");
    printf("═══════════════════════════════════════\n\n");
    
    if(studentCount == 0) {
        printf("No students found in database.\n");
        waitForEnter();
        return;
    }
    
    printf("┌─────┬────────────────────┬─────┬────────────────────┬────────┐\n");
    printf("│ %-3s │ %-18s │ %-3s │ %-18s │ %-6s │\n", "ID", "Name", "Age", "Course", "Grade");
    printf("├─────┼────────────────────┼─────┼────────────────────┼────────┤\n");
    
    for(int i = 0; i < studentCount; i++) {
        printf("│ %-3d │ %-18s │ %-3d │ %-18s │ %-6.2f │\n",
               students[i].id,
               students[i].name,
               students[i].age,
               students[i].course,
               students[i].grade);
    }
    
    printf("└─────┴────────────────────┴─────┴────────────────────┴────────┘\n");
    printf("\nTotal Students: %d\n", studentCount);
    
    waitForEnter();
}

// Search for a student
void searchStudent() {
    clearScreen();
    printf("═══════════════════════════════════════\n");
    printf("           SEARCH STUDENT\n");
    printf("═══════════════════════════════════════\n\n");
    
    if(studentCount == 0) {
        printf("No students found in database.\n");
        waitForEnter();
        return;
    }
    
    int choice;
    printf("Search by:\n");
    printf("1. Student ID\n");
    printf("2. Student Name\n");
    printf("3. Course\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &choice);
    
    clearScreen();
    printf("═══════════════════════════════════════\n");
    printf("           SEARCH RESULTS\n");
    printf("═══════════════════════════════════════\n\n");
    
    int found = 0;
    
    switch(choice) {
        case 1: { // Search by ID
            int searchId;
            printf("Enter Student ID: ");
            scanf("%d", &searchId);
            
            for(int i = 0; i < studentCount; i++) {
                if(students[i].id == searchId) {
                    printf("\n✅ Student Found!\n");
                    printf("─────────────────────────────────────\n");
                    printf("ID: %d\n", students[i].id);
                    printf("Name: %s\n", students[i].name);
                    printf("Age: %d\n", students[i].age);
                    printf("Course: %s\n", students[i].course);
                    printf("Grade: %.2f\n", students[i].grade);
                    printf("─────────────────────────────────────\n");
                    found = 1;
                    break;
                }
            }
            break;
        }
        
        case 2: { // Search by Name
            char searchName[MAX_NAME_LEN];
            printf("Enter Student Name: ");
            getchar();
            fgets(searchName, MAX_NAME_LEN, stdin);
            searchName[strcspn(searchName, "\n")] = 0;
            
            printf("\nSearch Results for '%s':\n", searchName);
            printf("┌─────┬────────────────────┬─────┬────────────────────┬────────┐\n");
            printf("│ %-3s │ %-18s │ %-3s │ %-18s │ %-6s │\n", "ID", "Name", "Age", "Course", "Grade");
            printf("├─────┼────────────────────┼─────┼────────────────────┼────────┤\n");
            
            for(int i = 0; i < studentCount; i++) {
                if(strstr(students[i].name, searchName) != NULL) {
                    printf("│ %-3d │ %-18s │ %-3d │ %-18s │ %-6.2f │\n",
                           students[i].id,
                           students[i].name,
                           students[i].age,
                           students[i].course,
                           students[i].grade);
                    found = 1;
                }
            }
            printf("└─────┴────────────────────┴─────┴────────────────────┴────────┘\n");
            break;
        }
        
        case 3: { // Search by Course
            char searchCourse[MAX_COURSE_LEN];
            printf("Enter Course Name: ");
            getchar();
            fgets(searchCourse, MAX_COURSE_LEN, stdin);
            searchCourse[strcspn(searchCourse, "\n")] = 0;
            
            printf("\nStudents in '%s' course:\n", searchCourse);
            printf("┌─────┬────────────────────┬─────┬────────────────────┬────────┐\n");
            printf("│ %-3s │ %-18s │ %-3s │ %-18s │ %-6s │\n", "ID", "Name", "Age", "Course", "Grade");
            printf("├─────┼────────────────────┼─────┼────────────────────┼────────┤\n");
            
            for(int i = 0; i < studentCount; i++) {
                if(strstr(students[i].course, searchCourse) != NULL) {
                    printf("│ %-3d │ %-18s │ %-3d │ %-18s │ %-6.2f │\n",
                           students[i].id,
                           students[i].name,
                           students[i].age,
                           students[i].course,
                           students[i].grade);
                    found = 1;
                }
            }
            printf("└─────┴────────────────────┴─────┴────────────────────┴────────┘\n");
            break;
        }
        
        default:
            printf("Invalid choice!\n");
    }
    
    if(!found) {
        printf("\n❌ No students found matching your search criteria.\n");
    }
    
    waitForEnter();
}

// Update student record
void updateStudent() {
    clearScreen();
    printf("═══════════════════════════════════════\n");
    printf("           UPDATE STUDENT\n");
    printf("═══════════════════════════════════════\n\n");
    
    if(studentCount == 0) {
        printf("No students found in database.\n");
        waitForEnter();
        return;
    }
    
    int id, found = 0;
    printf("Enter Student ID to update: ");
    scanf("%d", &id);
    
    for(int i = 0; i < studentCount; i++) {
        if(students[i].id == id) {
            found = 1;
            Student oldStudent = students[i];
            
            printf("\nCurrent Details:\n");
            printf("─────────────────────────────────────\n");
            printf("1. Name: %s\n", students[i].name);
            printf("2. Age: %d\n", students[i].age);
            printf("3. Course: %s\n", students[i].course);
            printf("4. Grade: %.2f\n", students[i].grade);
            printf("─────────────────────────────────────\n");
            
            printf("\nEnter new details (press Enter to keep current):\n");
            getchar(); // Clear input buffer
            
            // Update Name
            printf("New Name [%s]: ", students[i].name);
            char newName[MAX_NAME_LEN];
            fgets(newName, MAX_NAME_LEN, stdin);
            if(strlen(newName) > 1) {
                newName[strcspn(newName, "\n")] = 0;
                strcpy(students[i].name, newName);
            }
            
            // Update Age
            printf("New Age [%d]: ", students[i].age);
            char ageInput[10];
            fgets(ageInput, 10, stdin);
            if(strlen(ageInput) > 1) {
                students[i].age = atoi(ageInput);
            }
            
            // Update Course
            printf("New Course [%s]: ", students[i].course);
            char newCourse[MAX_COURSE_LEN];
            fgets(newCourse, MAX_COURSE_LEN, stdin);
            if(strlen(newCourse) > 1) {
                newCourse[strcspn(newCourse, "\n")] = 0;
                strcpy(students[i].course, newCourse);
            }
            
            // Update Grade
            printf("New Grade [%.2f]: ", students[i].grade);
            char gradeInput[10];
            fgets(gradeInput, 10, stdin);
            if(strlen(gradeInput) > 1) {
                float newGrade = atof(gradeInput);
                if(newGrade >= 0 && newGrade <= 100) {
                    students[i].grade = newGrade;
                } else {
                    printf("Invalid grade! Keeping old grade.\n");
                }
            }
            
            // Save changes to file
            FILE *file = fopen(FILENAME, "wb");
            if(file != NULL) {
                for(int j = 0; j < studentCount; j++) {
                    fwrite(&students[j], sizeof(Student), 1, file);
                }
                fclose(file);
            }
            
            printf("\n✅ Student record updated successfully!\n");
            break;
        }
    }
    
    if(!found) {
        printf("\n❌ Student with ID %d not found!\n", id);
    }
    
    waitForEnter();
}

// Delete a student
void deleteStudent() {
    clearScreen();
    printf("═══════════════════════════════════════\n");
    printf("           DELETE STUDENT\n");
    printf("═══════════════════════════════════════\n\n");
    
    if(studentCount == 0) {
        printf("No students found in database.\n");
        waitForEnter();
        return;
    }
    
    int id, found = 0;
    printf("Enter Student ID to delete: ");
    scanf("%d", &id);
    
    for(int i = 0; i < studentCount; i++) {
        if(students[i].id == id) {
            found = 1;
            
            printf("\nStudent to be deleted:\n");
            printf("─────────────────────────────────────\n");
            printf("ID: %d\n", students[i].id);
            printf("Name: %s\n", students[i].name);
            printf("Age: %d\n", students[i].age);
            printf("Course: %s\n", students[i].course);
            printf("Grade: %.2f\n", students[i].grade);
            printf("─────────────────────────────────────\n");
            
            char confirm;
            printf("\nAre you sure you want to delete this student? (y/n): ");
            scanf(" %c", &confirm);
            
            if(confirm == 'y' || confirm == 'Y') {
                // Shift all elements after i one position left
                for(int j = i; j < studentCount - 1; j++) {
                    students[j] = students[j + 1];
                }
                studentCount--;
                
                // Save changes to file
                FILE *file = fopen(FILENAME, "wb");
                if(file != NULL) {
                    for(int j = 0; j < studentCount; j++) {
                        fwrite(&students[j], sizeof(Student), 1, file);
                    }
                    fclose(file);
                }
                
                printf("\n✅ Student deleted successfully!\n");
            } else {
                printf("\nDeletion cancelled.\n");
            }
            break;
        }
    }
    
    if(!found) {
        printf("\n❌ Student with ID %d not found!\n", id);
    }
    
    waitForEnter();
}

// Sort students
void sortStudents() {
    clearScreen();
    printf("═══════════════════════════════════════\n");
    printf("           SORT STUDENTS\n");
    printf("═══════════════════════════════════════\n\n");
    
    if(studentCount == 0) {
        printf("No students found in database.\n");
        waitForEnter();
        return;
    }
    
    int choice;
    printf("Sort by:\n");
    printf("1. ID (Ascending)\n");
    printf("2. Name (A-Z)\n");
    printf("3. Grade (High to Low)\n");
    printf("4. Age (Young to Old)\n");
    printf("Enter your choice (1-4): ");
    scanf("%d", &choice);
    
    // Bubble sort
    for(int i = 0; i < studentCount - 1; i++) {
        for(int j = 0; j < studentCount - i - 1; j++) {
            int shouldSwap = 0;
            
            switch(choice) {
                case 1: // Sort by ID
                    if(students[j].id > students[j + 1].id) shouldSwap = 1;
                    break;
                    
                case 2: // Sort by Name
                    if(strcmp(students[j].name, students[j + 1].name) > 0) shouldSwap = 1;
                    break;
                    
                case 3: // Sort by Grade (descending)
                    if(students[j].grade < students[j + 1].grade) shouldSwap = 1;
                    break;
                    
                case 4: // Sort by Age
                    if(students[j].age > students[j + 1].age) shouldSwap = 1;
                    break;
                    
                default:
                    printf("Invalid choice!\n");
                    waitForEnter();
                    return;
            }
            
            if(shouldSwap) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    
    // Save sorted data to file
    FILE *file = fopen(FILENAME, "wb");
    if(file != NULL) {
        for(int i = 0; i < studentCount; i++) {
            fwrite(&students[i], sizeof(Student), 1, file);
        }
        fclose(file);
    }
    
    printf("\n✅ Students sorted successfully!\n");
    
    // Display sorted results
    displayAllStudents();
}

// Calculate statistics
void calculateStatistics() {
    clearScreen();
    printf("═══════════════════════════════════════\n");
    printf("           STUDENT STATISTICS\n");
    printf("═══════════════════════════════════════\n\n");
    
    if(studentCount == 0) {
        printf("No students found in database.\n");
        waitForEnter();
        return;
    }
    
    float totalGrade = 0, highestGrade = 0, lowestGrade = 100;
    int highestIdx = 0, lowestIdx = 0;
    int passCount = 0, failCount = 0;
    
    // Course statistics
    char courses[20][MAX_COURSE_LEN];
    int courseCounts[20] = {0};
    float courseAverages[20] = {0};
    int uniqueCourses = 0;
    
    for(int i = 0; i < studentCount; i++) {
        totalGrade += students[i].grade;
        
        // Check highest and lowest grades
        if(students[i].grade > highestGrade) {
            highestGrade = students[i].grade;
            highestIdx = i;
        }
        if(students[i].grade < lowestGrade) {
            lowestGrade = students[i].grade;
            lowestIdx = i;
        }
        
        // Pass/Fail count
        if(students[i].grade >= 40) {
            passCount++;
        } else {
            failCount++;
        }
        
        // Course statistics
        int found = 0;
        for(int j = 0; j < uniqueCourses; j++) {
            if(strcmp(courses[j], students[i].course) == 0) {
                courseCounts[j]++;
                courseAverages[j] += students[i].grade;
                found = 1;
                break;
            }
        }
        
        if(!found && uniqueCourses < 20) {
            strcpy(courses[uniqueCourses], students[i].course);
            courseCounts[uniqueCourses] = 1;
            courseAverages[uniqueCourses] = students[i].grade;
            uniqueCourses++;
        }
    }
    
    // Calculate averages
    for(int i = 0; i < uniqueCourses; i++) {
        courseAverages[i] /= courseCounts[i];
    }
    
    float averageGrade = totalGrade / studentCount;
    
    // Display statistics
    printf("📊 OVERALL STATISTICS\n");
    printf("─────────────────────────────────────\n");
    printf("Total Students: %d\n", studentCount);
    printf("Average Grade: %.2f\n", averageGrade);
    printf("Passing Students: %d (%.1f%%)\n", passCount, (float)passCount/studentCount*100);
    printf("Failing Students: %d (%.1f%%)\n", failCount, (float)failCount/studentCount*100);
    printf("\n");
    
    printf("🏆 TOP PERFORMER\n");
    printf("─────────────────────────────────────\n");
    printf("Name: %s\n", students[highestIdx].name);
    printf("ID: %d\n", students[highestIdx].id);
    printf("Course: %s\n", students[highestIdx].course);
    printf("Grade: %.2f\n", students[highestIdx].grade);
    printf("\n");
    
    printf("📈 COURSE-WISE STATISTICS\n");
    printf("─────────────────────────────────────\n");
    printf("Course\t\t\tStudents\tAverage Grade\n");
    printf("─────────────────────────────────────\n");
    for(int i = 0; i < uniqueCourses; i++) {
        printf("%-20s\t%-8d\t%-12.2f\n", courses[i], courseCounts[i], courseAverages[i]);
    }
    
    waitForEnter();
}

// Display menu
void displayMenu() {
    clearScreen();
    printf("═══════════════════════════════════════\n");
    printf("    STUDENT MANAGEMENT SYSTEM v1.0\n");
    printf("═══════════════════════════════════════\n\n");
    
    printf("╔═══════════════════════════════════════╗\n");
    printf("║           MAIN MENU                   ║\n");
    printf("╠═══════════════════════════════════════╣\n");
    printf("║  1. Add New Student                   ║\n");
    printf("║  2. View All Students                 ║\n");
    printf("║  3. Search Student                    ║\n");
    printf("║  4. Update Student Record             ║\n");
    printf("║  5. Delete Student Record             ║\n");
    printf("║  6. Sort Students                     ║\n");
    printf("║  7. View Statistics                   ║\n");
    printf("║  8. Exit Program                      ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
    
    printf("Students in database: %d\n", studentCount);
    printf("\nEnter your choice (1-8): ");
}