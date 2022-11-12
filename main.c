#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct Student{
    char firstname[20];
    char lastname[20];
    char email[30];
    int phone;
    int age;
    int id;
} Student;

typedef struct Course{
    char name[20];
    int id;
    int credits;
} Course;

typedef struct Enrollment{
    int studentId;
    int courseId;
    int grade;
} Enrollment;

void PrintMenu();
void listStudent(Student [], int);
void listCourse(Course [], int);
void listEnrollment(Enrollment [], int, Student [], int, Course [], int);
void studentReport(Enrollment [], int, Course [], int);
void saveData(Student [], int, Course [], int, Enrollment [], int);
int initStudent(Student [],int);
int initCourse(Course [],int);
int initEnrollment(Enrollment [],int);
Student createStudent();
Course createCourse();
Enrollment createEnrollment();

int main( )
{
    Student studentList[1000];
    Course courseList[1000];
    Enrollment enrollmentList[1000];
    char error[] = "Invalid input. Please try again.";
    char input;
    int studentCount = initStudent(studentList, 1000);
    int courseCount = initCourse(courseList, 1000);
    int enrollmentCount = initEnrollment(enrollmentList, 1000);
    while (1){
        PrintMenu();
        int x = scanf_s("%c", &input);
        switch (input) {
            case 'a':
            {
                Student student = createStudent();
                studentList[studentCount] = student;
                studentCount++;
                break;
            }
            case 'b':
            {
                Course course = createCourse();
                courseList[courseCount] = course;
                courseCount++;
                break;
            }
            case 'c':
            {
                Enrollment enrollment = createEnrollment();
                enrollmentList[enrollmentCount] = enrollment;
                enrollmentCount++;
                break;
            }
            case 'd':
                listStudent(studentList, studentCount);
                getchar();
                break;
            case 'e':
                listCourse(courseList, courseCount);
                getchar();
                break;
            case 'f':
                listEnrollment(enrollmentList, enrollmentCount, studentList, studentCount, courseList, courseCount);
                getchar();
                break;
            case 'g':
                studentReport(enrollmentList, enrollmentCount, courseList, courseCount);
                getchar();
                break;
            case 's':
                saveData(studentList, studentCount, courseList, courseCount, enrollmentList, enrollmentCount);
                getchar();
                break;
            default:
                system("cls");
                break;
        }
        if (x == 1){
            printf("%s\n", error);
            continue;
        }
    }

}


void PrintMenu(){
    printf("a. Add a student\n");
    printf("b. Add a course\n");
    printf("c. Add an enrollment\n");
    printf("d. List all student\n");
    printf("e. List all course\n");
    printf("f. List all enrollment\n");
    printf("g. Student report\n");
    printf("s. Save data\n");
    printf("Enter your choice:");
}

Student createStudent(){

    struct Student st;
    printf("Enter the student's firstname: ");
    scanf_s("%s", st.firstname);
    printf("Enter the student's lastname: ");
    scanf_s("%s", st.lastname);
    printf("Enter the student's id: ");
    scanf_s("%d", &st.id);
    printf("Enter the student's email: ");
    scanf_s("%s", st.email);
    printf("Enter the student's phone: ");
    scanf_s("%d", &st.phone);
    printf("Enter the student's age: ");
    scanf_s("%d", &st.age);
    return st;

}

int initStudent(Student *studentList, int count){
    int studentCount = 0;
    FILE *fp;
    fp = fopen("C:\\Users\\ketch\\Documents\\Informatique S5\\C\\StudentManager\\file\\student.csv", "r");
    if (fp == NULL){
        printf("Error opening file");
        return 0;
    }
    char line[count];
    while (fgets(line, count, fp) != NULL){
        char *token = strtok(line, ",");
        int i = 0;
        while (token != NULL){
            switch (i) {
                case 0:
                    strcpy(studentList[studentCount].firstname, token);
                    break;
                case 1:
                    strcpy(studentList[studentCount].lastname, token);
                    break;
                case 2:
                    studentList[studentCount].id = atoi(token);
                    break;
                case 3:
                    strcpy(studentList[studentCount].email, token);
                    break;
                case 4:
                    studentList[studentCount].phone = atoi(token);
                    break;
                case 5:
                    studentList[studentCount].age = atoi(token);
                    break;
                default:
                    break;
            }
            token = strtok(NULL, ",");
            i++;
        }
        studentCount++;
    }
    fclose(fp);
    return studentCount;
}

void saveStudent(Student studentList[], int studentCount){
    FILE *fp;
    fp = fopen("C:\\Users\\ketch\\Documents\\Informatique S5\\C\\StudentManager\\file\\student.csv", "w");
    if (fp == NULL){
        printf("Error opening file");
        return;
    }
    for (int i = 0; i < studentCount; i++) {
        fprintf(fp, "%s,%s,%d,%s,%d,%d", studentList[i].firstname, studentList[i].lastname, studentList[i].id,
                studentList[i].email, studentList[i].phone, studentList[i].age);
    }
    fclose(fp);
}

void listStudent(Student studentList[], int studentCount){

    printf("Student List\nStudent ID\tFirst Name\tLast Name\tEmail\tPhone\tAge\n");
    for (int i = 0; i < studentCount; i++){
        printf("%d \t %s \t %s \t %s \t %d \t %d\n", studentList[i].id, studentList[i].firstname, studentList[i].lastname, studentList[i].email, studentList[i].phone, studentList[i].age);
    }
}

Course createCourse(){
    struct Course c;
    printf("Enter the course's name: ");
    scanf_s("%s", c.name);
    printf("Enter the course's id: ");
    scanf_s("%d", &c.id);
    printf("Enter the course's credits: ");
    scanf_s("%d", &c.credits);
    return c;
}

int initCourse(Course *courseList, int count){
    int courseCount = 0;
    FILE *fp;
    fp = fopen("C:\\Users\\ketch\\Documents\\Informatique S5\\C\\StudentManager\\file\\course.csv", "r");
    if (fp == NULL){
        printf("Error opening file");
        return 0;
    }
    char line[count];
    while (fgets(line, count, fp) != NULL){
        char *token = strtok(line, ",");
        int i = 0;
        while (token != NULL){
            switch (i) {
                case 0:
                    strcpy(courseList[courseCount].name, token);
                    break;
                case 1:
                    courseList[courseCount].id = atoi(token);
                    break;
                case 2:
                    courseList[courseCount].credits = atoi(token);
                    break;
                default:
                    break;
            }
            token = strtok(NULL, ",");
            i++;
        }
        courseCount++;
    }
    fclose(fp);
    return courseCount;
}

void saveCourse(Course courseList[], int courseCount){
    FILE *fp;
    fp = fopen("C:\\Users\\ketch\\Documents\\Informatique S5\\C\\StudentManager\\file\\course.csv", "w");
    if (fp == NULL){
        printf("Error opening file");
        return;
    }
    for (int i = 0; i < courseCount; i++) {
        fprintf(fp, "%s,%d,%d", courseList[i].name, courseList[i].id, courseList[i].credits);
    }
    fclose(fp);
}

void listCourse(Course courseList[], int courseCount){
    printf("Course List\nCourse ID\tCourse Name\tCredits\n");
    for (int i = 0; i < courseCount; i++){
        printf("%d \t %s \t %d\n", courseList[i].id, courseList[i].name, courseList[i].credits);
    }
}

Enrollment createEnrollment(){
    struct Enrollment e;
    printf("Enter the student's id: ");
    scanf_s("%d", &e.studentId);
    printf("Enter the course's id: ");
    scanf_s("%d", &e.courseId);
    printf("Enter the grade: ");
    scanf_s("%d", &e.grade);
    return e;
}

int initEnrollment(Enrollment *enrollmentList, int count){
    int enrollmentCount = 0;
    FILE *fp;
    fp = fopen("C:\\Users\\ketch\\Documents\\Informatique S5\\C\\StudentManager\\file\\enrollment.csv", "r");
    if (fp == NULL){
        printf("Error opening file");
        return 0;
    }
    char line[count];
    while (fgets(line, count, fp) != NULL){
        char *token = strtok(line, ",");
        int i = 0;
        while (token != NULL){
            switch (i) {
                case 0:
                    enrollmentList[enrollmentCount].studentId = atoi(token);
                    break;
                case 1:
                    enrollmentList[enrollmentCount].courseId = atoi(token);
                    break;
                case 2:
                    enrollmentList[enrollmentCount].grade = atoi(token);
                    break;
                default:
                    break;
            }
            token = strtok(NULL, ",");
            i++;
        }
        enrollmentCount++;
    }
    fclose(fp);
    return enrollmentCount;
}

void saveEnrollment(Enrollment enrollmentList[], int enrollmentCount){
    FILE *fp;
    fp = fopen("C:\\Users\\ketch\\Documents\\Informatique S5\\C\\StudentManager\\file\\enrollment.csv", "w");
    if (fp == NULL){
        printf("Error opening file");
        return;
    }
    for (int i = 0; i < enrollmentCount; i++) {
        fprintf(fp, "%d,%d,%d", enrollmentList[i].studentId, enrollmentList[i].courseId, enrollmentList[i].grade);
    }
    fclose(fp);
}

void listEnrollment(Enrollment enrollmentList[], int enrollmentCount, Student studentList[], int studentCount, Course courseList[], int courseCount){
    printf("Enrollment List\nStudent Name\tCourse Name\tGrade\n");
    for (int i = 0; i < enrollmentCount; i++){
        char studentName[20];
        char courseName[20];
        for (int j = 0; j < studentCount; j++){
            if (enrollmentList[i].studentId == studentList[j].id){
                strcpy(studentName, studentList[j].firstname);
                strcat(studentName, " ");
                strcat(studentName, studentList[j].lastname);
                break;
            }
        }
        for (int j = 0; j < courseCount; j++){
            if (enrollmentList[i].courseId == courseList[j].id){
                strcpy(courseName, courseList[j].name);
                break;
            }
        }
        printf("%s \t %s \t %d\n", studentName, courseName, enrollmentList[i].grade);
    }
}

void studentReport(Enrollment enrollmentList[], int enrollmentCount, Course courseList[], int courseCount){
    printf("Enter the student's id: ");
    int studentId;
    scanf_s("%d", &studentId);
    printf("Student Report\nCourse Name\tGrade\n");
    double CGPA = 0;
    int creditCount = 0;
    int gradeCount = 0;
    for (int i = 0; i < enrollmentCount; i++){
        if (enrollmentList[i].studentId == studentId){
            char courseName[20];
            for (int j = 0; j < courseCount; j++){
                if (enrollmentList[i].courseId == courseList[j].id){
                    strcpy(courseName, courseList[j].name);
                    break;
                }
            }
            CGPA += enrollmentList[i].grade * courseList[i].credits;
            creditCount += courseList[i].credits;
            gradeCount++;
            printf("%s \t %d\n", courseName, enrollmentList[i].grade);
        }
    }
    CGPA = CGPA / creditCount;
    printf("CGPA: %f\n", CGPA);
}

void saveData(Student studentList[], int studentCount, Course courseList[], int courseCount, Enrollment enrollmentList[], int enrollmentCount){
    saveStudent(studentList, studentCount);
    saveCourse(courseList, courseCount);
    saveEnrollment(enrollmentList, enrollmentCount);
}
