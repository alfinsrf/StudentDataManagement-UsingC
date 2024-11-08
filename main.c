#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Project Name: Student Data Management
Group Name: Rawrrr Team
Member: 
1. Alfin Syaghaf Rifai - 2602181364
2. Audric Nagata - 2602090435
3. Yassar Annabil - 2602207363
*/

//structure data
typedef struct Student {
    long long int idNumber; 
    char name[50]; 
    char gender; 
    char className[20]; 
    long long int phoneNumber; 
    struct Student* left; 
    struct Student* right; 
} Student;

// Fungsi untuk membuat data baru mahasiswa
Student* createStudent(long long int idNumber, char name[], char gender, char className[], long long int phoneNumber) {
    Student* newStudent = (Student*)malloc(sizeof(Student)); 

    newStudent->idNumber = idNumber;
    strcpy(newStudent->name, name);
    newStudent->gender = gender;
    strcpy(newStudent->className, className);
    newStudent->phoneNumber = phoneNumber;
    newStudent->left = NULL;
    newStudent->right = NULL;

    return newStudent; //return struct pointer NewStudent
}

// Insertion data ke dalam BST
Student* insertStudent(Student* root, long long int idNumber, char name[], char gender, char className[], long long int phoneNumber) {
    
    if (root == NULL) {
        return createStudent(idNumber, name, gender, className, phoneNumber);
    }

    if (idNumber < root->idNumber) {
        root->left = insertStudent(root->left, idNumber, name, gender, className, phoneNumber);
    } else {
        root->right = insertStudent(root->right, idNumber, name, gender, className, phoneNumber);
    }

    return root;
}


Student* searchStudent(Student* root, long long int idNumber) {
    if (root == NULL || idNumber == root->idNumber) {
        return root;
    }

    if (idNumber < root->idNumber) {
        return searchStudent(root->left, idNumber);
    } else { 
        return searchStudent(root->right, idNumber);
    }
}

// save data mahasiswa ke dalam textfile
void saveStudentDataToFile(Student* root, FILE* file) {
    if (root != NULL) {
        saveStudentDataToFile(root->left, file);
        fprintf(file, "%lld %s, %c %s, %lld\n", root->idNumber, root->name, root->gender, root->className, root->phoneNumber);
        saveStudentDataToFile(root->right, file);
    }
}

// load data mahasiswa dari dalam textfile
Student* loadStudentDataFromFile(Student* root, FILE* file) {
    long long int idNumber;
    char name[50];
    char gender;
    char className[20];
    long long int phoneNumber;

    while (fscanf(file, "%lld %[^,], %c %[^,], %lld\n", &idNumber, name, &gender, className, &phoneNumber) != EOF) {
        root = insertStudent(root, idNumber, name, gender, className, phoneNumber);
    }

    return root;
}

Student* addStudent(Student* root) {
    long long int idNumber;
    char name[50];
    char gender;
    char className[20];
    long long int phoneNumber;

    printf("Enter student id(10 digit): ");
    scanf("%lld", &idNumber); getchar();
    printf("Enter student name: ");
    scanf("%[^\n]", name); getchar();
    printf("Enter gender (M/F): ");
    scanf("%c", &gender); getchar();
    printf("Enter class name: ");
    scanf("%[^\n]", className); getchar();
    printf("Enter phone number(+62): ");
    scanf("%lld", &phoneNumber); getchar();

    root = insertStudent(root, idNumber, name, gender, className, phoneNumber);
    printf("\nSystem: Student data successfully added.\n");
    system("pause");
    system("cls");

    return root;
}

void searchStudentMenu(Student* root) {
    long long int idNumber;

    printf("Enter the id of the student\n");
    printf("Example: 2602346785\n");
    printf("=> ");
    scanf("%lld", &idNumber); getchar();

    Student* result = searchStudent(root, idNumber);

    if (result == NULL) {
        printf("\nSystem: Student data not found.\n");
        system("pause");
        system("cls");
    } else {
        system("cls");
        printf("||======================| Student Data Found |======================\n");
        printf("|| Student ID	: %lld\n", result->idNumber);
        printf("|| Name		: %s\n", result->name);
        printf("|| Gender	: %c\n", result->gender);
        printf("|| Class	: %s\n", result->className);
        printf("|| Phone Number	: %lld\n", result->phoneNumber);
        printf("||==================================================================\n");
        printf("\n");
        system("pause");
        system("cls");
    }
}

void updateStudent(Student* root) {
    long long int upIdNumber;
    char newName[50];
    char newGender;
    char newClassName[20];
    long long int newPhoneNumber;

    printf("Enter student id you want to update\n");
    printf("Example: 2602346785\n");
    printf("=> ");
    scanf("%lld", &upIdNumber); getchar();

    Student* update = searchStudent(root, upIdNumber);

    if (update == NULL) {
        printf("\nSystem: Student data not found.\n");
        system("pause");
        system("cls");
    } else {
        printf("Enter new name: ");
        scanf("%[^\n]", newName); getchar();
        printf("Enter new gender (M/F): ");
        scanf("%c", &newGender); getchar();
        printf("Enter new class: ");
        scanf("%[^\n]", newClassName); getchar();
        printf("Enter new phone number(+62): ");
        scanf("%lld", &newPhoneNumber); getchar();

        printf("\nSystem: Student data updated successfully.\n");
        system("pause");
        system("cls");
    
        update->idNumber = upIdNumber;
        strcpy(update->name, newName);
        update->gender = newGender;
        strcpy(update->className, newClassName);
        update->phoneNumber = newPhoneNumber;
    }
}

Student* deleteStudent(Student* root, long long int idNumber) {
    if (root == NULL) {
        return root;
    }

    if (idNumber < root->idNumber) {
        root->left = deleteStudent(root->left, idNumber);
    } else if (idNumber > root->idNumber) {
        root->right = deleteStudent(root->right, idNumber);
    } else {
        // kondisi tidak punya child atau hanya punya 1 child
        if (root->left == NULL) {
            Student* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Student* temp = root->left;
            free(root);
            return temp;
        }

        // kondisi punya 2 child
        Student* temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }

        root->idNumber = temp->idNumber;
        strcpy(root->name, temp->name);
        root->gender = temp->gender;
        strcpy(root->className, temp->className);
        root->phoneNumber = temp->phoneNumber;       
        root->right = deleteStudent(root->right, temp->idNumber);
    }

    return root;
}

Student* deleteStudentMenu(Student* root) {
    long long int idNumber;

    printf("Enter student id you want to delete\n");
    printf("Example: 2602346785\n");
    printf("=> ");
    scanf("%lld", &idNumber); getchar();

    Student* result = searchStudent(root, idNumber);
    
    if (result == NULL) {
        printf("System: Student data not found.\n");
        system("pause");
        system("cls");
    } else {
        root = deleteStudent(root, idNumber);
        printf("\nSystem: Student data successfully deleted.\n");
        system("pause");
        system("cls");
    }

    return root;
}

// untuk print data-data mahasiswanya
void printStudent(Student* student) {
    printf("|| %-14lld | %-25s |   %c    | %-4s  | %-12lld   ||\n", student->idNumber, student->name, student->gender, student->className, student->phoneNumber);
}

// Fungsi yang akan dipanggil saat print seluruh data mahasiswa
void printStudentData(Student* root) {
    if (root != NULL) {
        //print menggunakan Pre-Order Traversal
        printStudentData(root->left);
        printStudent(root);
        printStudentData(root->right);
    }
}

int main() {
    Student* studentData = NULL;
    long long int idNumber;
    
    //read data dari textfile
    FILE* file = fopen("studentdata.txt", "r");
    if (file != NULL) {
        studentData = loadStudentDataFromFile(studentData, file);
        fclose(file);
    }

    char choice;
    do {
        printf("====================================\n      Student Data Management\n====================================\n");
        printf("1. Add a New Student Data\n");
        printf("2. Update Student Data\n");
        printf("3. Search for a student data\n");
        printf("4. Delete a student data\n");
        printf("5. Print all student data\n");
        printf("6. Exit\n");
        printf("Choose: ");
        scanf(" %c", &choice); getchar();

        switch (choice) {
            case '1': { //insert new data
                system("cls");
                studentData = addStudent(studentData);

                file = fopen("studentdata.txt", "w");
                if (file != NULL) {
                    saveStudentDataToFile(studentData, file);
                    fclose(file);
                } else {
                    printf("Error: Unable to open file.\n");
                    system("pause");
                    system("cls");
                }
                break;
            }
            case '2': { //update data
                system("cls");
                updateStudent(studentData);

                file = fopen("studentdata.txt", "r+");
                if (file != NULL) {
                    saveStudentDataToFile(studentData, file);
                    fclose(file);
                } else {
                    printf("Error: Unable to open file.\n");
                    system("pause");
                    system("cls");
                }
                break;
            }
            case '3': { //search student
                system("cls");
                searchStudentMenu(studentData);
                break;
            }
            case '4': { //delete student data
                system("cls");
                studentData = deleteStudentMenu(studentData);

                file = fopen("studentdata.txt", "w+");
                if (file != NULL) {
                    saveStudentDataToFile(studentData, file);
                    fclose(file);
                } else {
                    printf("Error: Unable to open file.\n");
                    system("pause");
                    system("cls");
                }
                break;
            }
            case '5': { //print
                system("cls");
                printf("||==============================================================================||\n");
                printf("||                               All Student Data                               ||\n");
                printf("||==============================================================================||\n");
                printf("|| Student Number | Name                      | Gender | Class | Phone Number   ||\n");
                printStudentData(studentData);
                printf("||==============================================================================||\n");
                printf("\n");
                system("pause");
                system("cls");
                break;
            }
            case '6': { //exit
                printf("\nQuitting the program...\n");
                system("pause");
                system("cls");
                printf("System: Thank you. Have a nice day!\n");
                break;
            }
            default: {
                printf("System: Invalid choice. Choose the number that on the menu.\n");
                system("pause");
                system("cls");
            }
        }
    } while (choice != '6');

    return 0;
}
