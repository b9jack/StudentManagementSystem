#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_STUDENTS 100

typedef struct
{
    char *firstName;
    char *lastName;
    char gender;
    char *course;
    int studentId;
} Student;

void addStudent(Student *s);
void deleteStudent();
void editStudent();
void viewStudent();


int main(){

    Student students[MAX_STUDENTS];
    int studentCount = 0;

    int response;   
    Student s1;

    printf("\n************ STUDENT MANAGEMENT APP ************");
    printf("\n");
    do
    {
    printf("\n1. Add a student to the record");
    printf("\n2. Delete a student from the record");
    printf("\n3. Edit a students file");
    printf("\n4. View all students");
    printf("\n5. Exit the program");
    printf("\nWhat would you like to do?(1-5): ");
    scanf("%d", &response);

    switch (response)
    {
    case 1:
        if (studentCount < MAX_STUDENTS)
        {
            addStudent(&students[studentCount]);
            studentCount++;
        }else{
            printf("List is full.");
        }
        
        break;
    case 2:
        deleteStudent(students, &studentCount);
        break;
    case 3:
        editStudent(students, &studentCount);
        break;
    case 4:
        viewStudent(students, studentCount);
        break;
    default:
        break;
    }

    } while (response != 5);
    
    for(int i = 0; i < studentCount; i++){
        free(students[i].firstName);
        free(students[i].lastName);
        free(students[i].course);
    }
    return 0;
}

void addStudent(Student *s)

{  
    char confirmation = 'N';

    s->firstName = malloc(50 * sizeof(char)); // allocates the memory
    s->lastName = malloc(50 * sizeof(char)); 
    s->course = malloc(75 * sizeof(char)); 

    if (s->firstName == NULL || s->lastName == NULL || s->course == NULL ) {
        printf("Memory allocation failed!\n");
        return;
    }

    do
    {
        printf("Please input the forename of the new student: ");
        scanf("%49s", s->firstName);
        printf("\n%s", s->firstName);
        printf("\nPlease input the surname of the new student: ");
        scanf("%49s", s->lastName);
        printf("\n%s", s->lastName);
        printf("\nPlease input the gender of the new student(M/F): ");
        scanf(" %c", &s->gender);
        printf("\n%c", toupper(s->gender));
        while (getchar() != '\n'); //input buffer
        printf("\nPlease input the course the new student will be joining: ");
        fgets(s->course, 75, stdin);
        printf("\n%s", s->course);


            if(strlen(s->firstName) == 0 || strlen(s->lastName) == 0 || strlen(s->course) == 0 || s->gender == ' ')
            {
                printf("A field is missing.");
            }
    
        printf("\nFirst name: %s, \nLast name: %s, \nGender: %c, \nCourse: %s", s->firstName, s->lastName, s->gender, s->course);
        printf("\nIs this correct?: ");
        scanf(" %c", &confirmation);
        confirmation = toupper(confirmation);
        printf("Student added successfully");

    } while (confirmation != 'Y');
}

void viewStudent(Student students[], int studentCount)
{
    if (studentCount >= 1)
    {
        for (int i = 0; i < studentCount; i++) {
            printf("\n--- Student %d ---", i + 1);
            printf("\nFirst name: %s", students[i].firstName);
            printf("\nLast name: %s", students[i].lastName);
            printf("\nGender: %c", students[i].gender);
            printf("\nCourse: %s", students[i].course);
        }
    }else{
        printf("\nThe list is empty.");
    }
}

void deleteStudent(Student students[],int *studentCount)
{
    char studentName[50];
    char confirmStudent = 'N';

    do
    {
    printf("Please type the forename of the student you want to delete: ");
    scanf("%49s", studentName);
    for(int i = 0; i < *studentCount; i++){
        if(strcmp(students[i].firstName, studentName) == 0)
        {
            printf("\nName: %s %s", students[i].firstName, students[i].lastName);
            printf("\nGender: %c", students[i].gender);
            printf("\nCourse: %s", students[i].course);

            printf("Is this the student you want to delete from the record?(Y/N): ");
            scanf(" %c", &confirmStudent);
            confirmStudent = toupper(confirmStudent);
            if(confirmStudent == 'Y')
            {
                // free the student memory
                free(students[i].firstName);
                free(students[i].lastName);
                free(students[i].course);

                // Shift remaining students left to fill the gap
                for (int j = i; j < *studentCount - 1; j++)
                {
                students[j] = students[j + 1];
                }

                (*studentCount)--;
                printf("Student deleted successfully.\n");
                return;
            }else{
                printf("Student not deleted.");
            }
        }
    }
    printf("No student found with the name '%s'. Try again.\n", studentName);
    } while (confirmStudent != 'Y');
}

void editStudent(Student students[], int *studentCount)
{
    char studentName[50];
    char confirmStudent = 'N';
    int updated = 0;
    do
    {
    printf("Please type the forename of the student you want to edit: ");
    scanf("%49s", studentName);
    for(int i = 0; i < *studentCount; i++){
        if(strcmp(students[i].firstName, studentName) == 0)
        {
            printf("\nName: %s %s", students[i].firstName, students[i].lastName);
            printf("\nGender: %c", students[i].gender);
            printf("\nCourse: %s", students[i].course);

            printf("Is this the record you want to edit?: ");
            scanf(" %c", &confirmStudent);
            confirmStudent = toupper(confirmStudent);
            if(confirmStudent == 'Y')
            {
                do
                {
                // free the student memory
                free(students[i].firstName);
                free(students[i].lastName);
                free(students[i].course);
                
                // reallocate memory
                students[i].firstName = malloc(50 * sizeof(char)); 
                students[i].lastName = malloc(50 * sizeof(char)); 
                students[i].course = malloc(75 * sizeof(char)); 

                printf("Please input the forename of the student: ");
                scanf("%49s", students[i].firstName);
                printf("\nPlease input the surname of the student: ");
                scanf("%49s", students[i].lastName);
                printf("\nPlease input the course of the student: ");
                while (getchar() != '\n'); //input buffer
                fgets(students[i].course, 75, stdin);

                if(students[i].firstName != NULL && students[i].lastName != NULL && students[i].course != NULL)
                {
                    printf("Student updated successfully.");
                    updated = 1;
                }else{
                    printf("Missing input.");
                }
                } while (updated == 0);
        }
    }
}
    } while (confirmStudent != 'Y');
    
}
