#ifndef STUDENT_H
#define STUDENT_H

#define MAX_NAME_LEN 50
#define MAX_COURSE_LEN 30
#define FILENAME "students.dat"

// Student structure
typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    int age;
    char course[MAX_COURSE_LEN];
    float grade;
} Student;

// Function prototypes
void addStudent();
void displayAllStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void sortStudents();
void calculateStatistics();
void clearScreen();
void saveToFile(Student s);
void loadFromFile();
int getNextId();

#endif