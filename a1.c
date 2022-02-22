#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
struct studentNode
{
    int roll;
    char name[20];
    char univName[50];
    char branchName[10];
    float cgpa;
    int selectedBranchCode;
    struct studentNode *next;
};
struct studentlcpa
{
    int roll;
    char name[20];
    char univName[50];
    char branchName[10];
    float cgpa;
    int selectedBranchCode;
    struct studentNode *next;
};
struct studentHeader
{
    int st_data;
    struct studentNode *next;
};
struct branchNode
{
    int branchID;
    int univID;
    char branchName[5];
    int seatsAvailable;
    float minCgpa;
    struct branchNode *next;
};
struct branchHeader
{
    int branch_data;
    struct branchNode *next;
};
struct univNode
{
    int univID;
    char univName[50];
    char univLoc[80];
    int yos;
    char b1[10], b2[10], b3[10], b4[10], b5[10];
    struct univNode *next;
};
struct univHeader
{
    int univ_data;
    struct univNode *next;
};

struct lessCgpaHeader
{
    int l_data;
    struct studentNode *next;
};
struct moreCgpaHeader
{
    int m_data;
    struct studentNode *next;
};
void printUniversityAscending(struct univHeader *univhead);
void displayAvailableBranch(struct univHeader *univhead);
void displayCseStudents(struct studentHeader *stuhead);
void displayKiitStudents(struct studentHeader *stuhead);
void displayList(struct studentHeader *stuhead, struct univHeader *univhead, struct branchHeader *branchhead);
struct univHeader *createUniv(struct univHeader *univhdrptr);
struct studentHeader *createStu(struct studentHeader *stuhdrptr);
struct branchHeader *createBranch(struct branchHeader *branchhdrptr, struct univHeader *univhdrptr);
void display(struct univHeader *univhdrptr, struct branchHeader *branchhdrptr, struct studentHeader *stuhdrptr);
char *uppercase(char word[80]);
int categorizeStudent(struct studentHeader *stuhdrptr, struct lessCgpaHeader *lesscgpahead, struct moreCgpaHeader *morecgpahead);
void dispsub(struct studentHeader *stuhead);
int main()
{
    struct studentHeader *stuhead = (struct studentHeader *)malloc(sizeof(struct studentHeader));
    stuhead->st_data = 0;
    stuhead->next = NULL;
    struct univHeader *univhead = (struct univHeader *)malloc(sizeof(struct univHeader));
    univhead->univ_data = 0;
    univhead->next = NULL;
    struct branchHeader *branchhead = (struct branchHeader *)malloc(sizeof(struct branchHeader));
    branchhead->branch_data = 0;
    branchhead->next = NULL;
    struct lessCgpaHeader *lesscgpahead = (struct lessCgpaHeader *)malloc(sizeof(struct lessCgpaHeader));
    lesscgpahead->l_data = 0;
    lesscgpahead->next = NULL;
    struct moreCgpaHeader *morecgpahead = (struct moreCgpaHeader *)malloc(sizeof(struct moreCgpaHeader));
    morecgpahead->m_data = 0;
    morecgpahead->next = NULL;

    int num = 1, pass;
    while (num != 0)
    {
        printf("\nLogin Mode:\n0.Exit\n1.Student Login\n2.Admin Login\n\nEnter choice: ");
        scanf("%d", &num);
        if (num == 0)
            break;
        else if (num == 2)
        {
            int choice = 1;
            printf("\nEnter password: ");
            scanf("%d", &pass);
            if (pass == 2021)
            {
                while (choice == 1)
                {
                    printf("\nWelcome,Here are the available services:\n1.Update University List\n2.Update Branch List\n3.Update Student List\n4.Display Services\n5.Categorize Students");
                    printf("\n6)Display list\n7)Display KIIT students\n8)Display KIIT CSE students\n9)Display Available Branches\n ");
                    printf("10)Print in Ascending order of Year of Starting\n11)Search with subdat\n12)List < 6cpa students\nEnter choice: ");
                    scanf("%d", &num);
                    switch (num)
                    {
                    case 1:
                        univhead = createUniv(univhead);
                        break;
                    case 2:
                        branchhead = createBranch(branchhead, univhead);
                        break;
                    case 3:
                        stuhead = createStu(stuhead);
                        break;
                    case 4:
                        display(univhead, branchhead, stuhead);
                        break;
                    case 5:
                        categorizeStudent(stuhead, lesscgpahead, morecgpahead);
                        break;
                    case 6:
                        displayList(stuhead, univhead, branchhead);
                        break;
                    case 7:
                        displayKiitStudents(stuhead);
                        break;
                    case 8:
                        displayCseStudents(stuhead);
                        break;
                    case 9:
                        displayAvailableBranch(univhead);
                        break;
                    case 10:
                        printUniversityAscending(univhead);
                        break;
                    case 11:
                        dispsub(stuhead);
                        break;
                    
                    }
                    printf("\nPress 1 to use this service again, else press 0: ");
                    scanf("%d", &choice);
                }
            }
        }

        else if (num == 1)
        {
            int branchCode;
            int roll;
            int checker = 0;
            struct studentNode *stuptr = stuhead->next;
            printf("Welcome,\nPlease enter your Roll No.: ");
            scanf("%d", &roll);
            if (stuptr == NULL)
            {
                printf("\nNo database entry found for your Roll.\nPlease ask admin to update\n");
                continue;
            }
            while (stuptr->roll != roll)
            {
                stuptr = stuptr->next;
            }
            
            //check if stuptr is NULL.

            struct branchNode *ptr = branchhead->next;
            while (ptr != NULL)
            {
                if (ptr->minCgpa >= stuptr->cgpa)
                {
                    printf("\nBranch Name: %s", ptr->branchName);
                    printf("\nBranch ID: %d", ptr->branchID);
                    printf("\nUniversity ID: %d", ptr->univID);
                    printf("\nAvailable seats: %d", ptr->seatsAvailable);
                    printf("\n\n");
                }
                ptr = ptr->next;
            }
            printf("\nEnter your preffered branch ID: ");
            scanf("%d", &branchCode);
            ptr = branchhead->next;
            while (ptr != NULL)
            {
                if (ptr->branchID == branchCode && ptr->seatsAvailable > 0)
                {
                    stuptr->selectedBranchCode = ptr->branchID;
                    printf("\nYou, have booked the seat.");
                    ptr->seatsAvailable--;
                    printf("\nStudent Roll: %d", stuptr->roll);
                    printf("\nBranch Selected: %d", ptr->branchID);
                    checker = 1;
                    break;
                }
                ptr = ptr->next;
            }
            if (checker == 0)
            {
                printf("\nSeat not booked,either branchID not found or no seat available.");
            }
        }
    }
}

char *uppercase(char word[80])
{
    int j = 0;
    char ch;
    char *str = (char *)malloc(80 * sizeof(char));
    while (word[j])
    {
        ch = word[j];
        *(str + j) = toupper(ch);
        j++;
    }
    *(str + j) = '\0';
    return str;
}

struct univHeader *createUniv(struct univHeader *univhdrptr)
{
    char univName[50], univLoc[80];
    char b1[10], b2[10], b3[10], b4[10], b5[10];
    int count = 1;
    struct univNode *temp = NULL;
    do
    {

        struct univNode *new123 = (struct univNode *)malloc(sizeof(struct univNode));
        printf("\nEnter the University name : ");
        fflush(stdin);
        scanf("%s", univName);
        strcpy(univName, uppercase(univName));
        strcpy(new123->univName, univName);

        printf("\nEnter Branch 1 name : ");
        fflush(stdin);
        scanf("%s", b1);
        strcpy(b1, uppercase(b1));
        strcpy(new123->b1, b1);
        printf("\nEnter Branch 2 name : ");
        fflush(stdin);
        scanf("%s", b2);
        strcpy(b2, uppercase(b2));
        strcpy(new123->b2, b2);
        printf("\nEnter Branch 3 name : ");
        fflush(stdin);
        scanf("%s", b3);
        strcpy(b3, uppercase(b3));
        strcpy(new123->b3, b3);
        printf("\nEnter Branch 4 name : ");
        fflush(stdin);
        scanf("%s", b4);
        strcpy(b4, uppercase(b4));
        strcpy(new123->b4, b4);
        printf("\nEnter Branch 5 name : ");
        fflush(stdin);
        scanf("%s", b5);
        strcpy(b5, uppercase(b5));
        strcpy(new123->b5, b5);

        printf("\nEnter the University ID : ");
        scanf("%d", &new123->univID);
        printf("\nEnter the Univerity Location : ");
        fflush(stdin);
        scanf("%s", univLoc);
        strcpy(univLoc, uppercase(univLoc));
        strcpy(new123->univLoc, univLoc);
        printf("\nEnter the Year of Start : ");
        scanf("%d", &new123->yos);
        new123->next = NULL;

        if (univhdrptr->next == NULL)
        {
            univhdrptr->next = new123;
            temp = new123;
            (univhdrptr->univ_data)++;
        }
        else
        {
            struct univNode *dup = univhdrptr->next;
            while (dup != NULL)
            {
                if (dup->univID == new123->univID)
                {
                    printf("Duplicate University ID found,enter new ID: ");
                    scanf("%d", &new123->univID);
                }
                else if (dup->univName == new123->univName)
                {
                    printf("Duplicate University Name found,enter new name: ");
                    scanf("%s", new123->univName);
                }
                else if (dup->yos == new123->yos)
                {
                    printf("Duplicate University YOS, enter new YOS: ");
                    scanf("%d", &new123->yos);
                }
                dup = dup->next;
            }
            temp->next = new123;
            temp = new123;
            (univhdrptr->univ_data)++;
        }
        printf("\n\nPress 1 to continue else 0 to exit: ");
        scanf("%d", &count);
    } while (count != 0);
    return univhdrptr;
}

struct branchHeader *createBranch(struct branchHeader *branchhdrptr, struct univHeader *univhdrptr)
{

    int count = 1;
    struct branchNode *temp = NULL;
    do
    {
        int checker = 0;
        struct univNode *uniptr = univhdrptr->next;
        char branchName[8];
        struct branchNode *new123 = (struct branchNode *)malloc(sizeof(struct branchNode));
        new123->next = NULL;
        printf("\nEnter the Branch name : ");
        fflush(stdin);
        scanf("%s", branchName);
        strcpy(branchName, uppercase(branchName));
        strcpy(new123->branchName, branchName);
        printf("\nEnter the Branch ID : ");
        scanf("%d", &new123->branchID);
        printf("\nEnter the Univerity ID : ");
        scanf("%d", &new123->univID);
        printf("\nEnter seats available: ");
        scanf("%d", &new123->seatsAvailable);
        printf("\nEnter minimum cgpa: ");
        scanf("%f", &new123->minCgpa);
        while (uniptr != NULL)
        {
            if (uniptr->univID == new123->univID)
            {
                checker = 1;
                break;
            }
            uniptr = uniptr->next;
        }
        if (checker == 1)
        {
            if (branchhdrptr->next == NULL)
            {
                branchhdrptr->next = new123;
                temp = new123;
                (branchhdrptr->branch_data)++;
            }
            else
            {
                struct branchNode *dup = branchhdrptr->next;
                while (dup != NULL)
                {
                    if (dup->branchName == new123->branchName)
                    {
                        printf("Duplicate University Name found,enter new name: ");
                        scanf("%s", new123->branchName);
                    }
                    else if (dup->branchID == new123->branchID)
                    {
                        printf("Duplicate Branch ID, enter new ID: ");
                        scanf("%d", &new123->branchID);
                    }
                    dup = dup->next;
                }
                temp->next = new123;
                temp = new123;
                (branchhdrptr->branch_data)++;
            }
        }
        else
        {
            printf("\nNo such University Code found in daatbase");
        }
        printf("\n\nPress 1 to continue else 0 to exit");
        scanf("%d", &count);
    } while (count != 0);
    return branchhdrptr;
}

struct studentHeader *createStu(struct studentHeader *stuhdrptr)
{

    int count = 1;
    struct studentNode *temp = NULL;
    do
    {
        char studentName[20];
        char univName[50];
        char branchName[10];
        struct studentNode *new123 = (struct studentNode *)malloc(sizeof(struct studentNode));
        new123->next = NULL;
        printf("\nEnter Roll number: ");
        scanf("%d", &new123->roll);
        printf("\nEnter Student Name: ");
        fflush(stdin);
        scanf("%s", studentName);
        strcpy(studentName, uppercase(studentName));
        strcpy(new123->name, studentName);
        printf("\nEnter Branch Name: ");
        fflush(stdin);
        scanf("%s", branchName);
        strcpy(branchName, uppercase(branchName));
        strcpy(new123->branchName, branchName);
        printf("\nEnter University Name: ");
        fflush(stdin);
        scanf("%s", univName);
        strcpy(univName, uppercase(univName));
        strcpy(new123->univName, univName);
        printf("\nEnter Branch ID: ");
        scanf("%d", &new123->selectedBranchCode);
        printf("\nEnter CGPA: ");
        scanf("%f", &new123->cgpa);

        if (stuhdrptr->next == NULL)
        {
            stuhdrptr->next = new123;
            temp = new123;
            (stuhdrptr->st_data)++;
        }
        else
        {
            struct studentNode *dup = stuhdrptr->next;
            while (dup != NULL)
            {
                if (dup->roll == new123->roll)
                {
                    printf("Duplicate Roll numver found,enter new Roll: ");
                    scanf("%d", &new123->roll);
                }
                dup = dup->next;
            }
            temp->next = new123;
            temp = new123;
            (stuhdrptr->st_data)++;
        }
        printf("\n\nPress 1 to continue else 0 to exit: ");
        scanf("%d", &count);
    } while (count != 0);
    return stuhdrptr;
}

void display(struct univHeader *univhdrptr, struct branchHeader *branchhdrptr, struct studentHeader *stuhdrptr)
{
    printf("\nDisplay Services:\n1.University List\n2.Branch List\n3.Student List\n\nEnter choice: ");
    int num;
    scanf("%d", &num);
    if (num == 1)
    {
        struct univNode *ptr = univhdrptr->next;
        while (ptr != NULL)
        {
            printf("\nUniversity Name: %s", ptr->univName);
            printf("\nUniversity ID: %d", ptr->univID);
            printf("\nUniversity Location: %s", ptr->univLoc);
            printf("\n\n");
            ptr = ptr->next;
        }
    }
    else if (num == 2)
    {
        struct branchNode *ptr = branchhdrptr->next;
        while (ptr != NULL)
        {
            printf("\nBranch Code: %d", ptr->branchID);
            printf("\nBranch Name: %s", ptr->branchName);
            printf("\nUniversity ID: %d", ptr->univID);
            printf("\nSeats Available: %d", ptr->seatsAvailable);
            printf("\n\n");
            ptr = ptr->next;
        }
    }

    else if (num == 3)
    {
        struct studentNode *ptr = stuhdrptr->next;
        while (ptr != NULL)
        {
            printf("\nName: %s", ptr->name);
            printf("\nRoll: %d", ptr->roll);
            printf("\nCGPA: %f", ptr->cgpa);
            printf("\nSelected branch: %d", ptr->selectedBranchCode);
            printf("\n\n");
            ptr = ptr->next;
        }
    }
}

int categorizeStudent(struct studentHeader *stuhdrptr, struct lessCgpaHeader *lesscgpahead, struct moreCgpaHeader *morecgpahead)
{
    struct studentNode *ptr = stuhdrptr->next;
    if (stuhdrptr->next == NULL)
    {
        printf("\nNo data in Student list");
        return -1;
    }
    struct studentNode *temp1 = NULL;
    struct studentNode *temp2 = NULL;
    while (ptr != NULL)
    {
        struct studentNode *newL = (struct studentNode *)malloc(sizeof(struct studentNode));
        struct studentNode *newM = (struct studentNode *)malloc(sizeof(struct studentNode));
        if (ptr->cgpa < 6.0)
        {
            newL->cgpa = ptr->cgpa;
            newL->roll = ptr->roll;
            strcpy(newL->name, ptr->name);
            newL->selectedBranchCode = ptr->selectedBranchCode;
            if (lesscgpahead->next == NULL)
            {
                lesscgpahead->next = newL;
                temp1 = newL;
                (lesscgpahead->l_data)++;
            }
            else
            {
                temp1->next = newL;
                temp1 = newL;
                (lesscgpahead->l_data)++;
            }
        }

        else if (ptr->cgpa >= 6.0)
        {
            newM->cgpa = ptr->cgpa;
            newM->roll = ptr->roll;
            newM->selectedBranchCode = ptr->selectedBranchCode;
            strcpy(newM->name, ptr->name);
            if (morecgpahead->next = NULL)
            {
                morecgpahead->next = newM;
                temp2 = newM;
                (morecgpahead->m_data)++;
            }
            else
            {
                temp2->next = newM;
                temp2 = newM;
                (morecgpahead->m_data)++;
            }
        }
        ptr = ptr->next;
    }
    return 0;
}
void displayList(struct studentHeader *stuhead, struct univHeader *univhead, struct branchHeader *branchhead)
{
    //Displaying Student header list
    printf(".......STUDENT LIST........\n");
    printf("Roll Number\tName\tBranch Id\t\tCGPA\n");
    struct studentNode *ptr1 = stuhead->next;
    while (ptr1 != NULL)
    {
        printf("%d\t\t%s\t\t%d\t\t%f\n", ptr1->roll, ptr1->name, ptr1->selectedBranchCode, ptr1->cgpa);
        ptr1 = ptr1->next;
    }
    printf("\n\n");
    printf(".......UNIVERSITY LIST........\n");
    printf("University ID\tName\t\tLocation\t\tYear of Start\n");
    struct univNode *ptr2 = univhead->next;
    while (ptr2 != NULL)
    {
        printf("%d\t\t%s\t\t%s\t\t\t%d\n", ptr2->univID, ptr2->univName, ptr2->univLoc, ptr2->yos);
        ptr2 = ptr2->next;
    }
    printf("\n\n");
    printf(".......BRANCH LIST........\n");
    printf("Branch ID\tUniv ID\t\tBranch Name\n");
    struct branchNode *ptr3 = branchhead->next;
    while (ptr3 != NULL)
    {
        printf("%d\t\t%d\t\t%s\n", ptr3->branchID, ptr3->univID, ptr3->branchName);
        ptr3 = ptr3->next;
    }
}
void displayKiitStudents(struct studentHeader *stuhead)
{
    char arr[50] = "KIIT";
    struct studentNode *ptr = stuhead->next;
    printf(".......KIIT STUDENT LIST........\n");
    printf("Roll Number\tName\tBranch Id\t\tCGPA\n");
    while (ptr != NULL)
    {
        if (strcmp((ptr->univName), arr) == 0)
            printf("%d\t\t%s\t\t%d\t\t%f\n", ptr->roll, ptr->name, ptr->selectedBranchCode, ptr->cgpa);
        ptr = ptr->next;
    }
}
void displayCseStudents(struct studentHeader *stuhead)
{
    char arr1[10] = "CSE";
    char arr2[50] = "KIIT";
    struct studentNode *ptr = stuhead->next;
    printf(".......KIIT CSE STUDENT LIST........\n");
    printf("Roll Number\tName\tBranch Id\t\tCGPA\n");
    while (ptr != NULL)
    {
        if (strcmp((ptr->univName), arr2) == 0 && strcmp((ptr->branchName), arr1) == 0)
            printf("%d\t\t%s\t\t%d\t\t%f\n", ptr->roll, ptr->name, ptr->selectedBranchCode, ptr->cgpa);
        ptr = ptr->next;
    }
}
void displayAvailableBranch(struct univHeader *univhead)
{
    struct univNode *ptr = univhead->next;
    printf("\n.........BRANCHES OFFERED BY UNIVERSITY......\n\n");
    printf("Name\t   Branch 1\t   Branch 2\t   Branch 3\t   Branch 4\t   Branch 5\n");
    while (ptr != NULL)
    {
        printf("%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\n", ptr->univName, ptr->b1, ptr->b2, ptr->b3, ptr->b4, ptr->b5);
        ptr = ptr->next;
    }
}
struct univNode *deleteAndPrint(struct univNode *root, struct univNode *ptr)
{
    struct univNode *prev = root;
    struct univNode *ptr2 = root->next;
    if (root == ptr)
    {
        printf("%s\t\t%d\t\t%s\t\t\t%d\n", root->univName, root->univID, root->univLoc, root->yos);
        free(root);
        return ptr2;
    }
    else
    {
        while (ptr2 != NULL)
        {
            if (ptr2 == ptr)
            {
                prev->next = ptr2->next;
                printf("%s\t\t%d\t\t%s\t\t\t%d\n", ptr2->univName, ptr2->univID, ptr2->univLoc, ptr2->yos);
                free(ptr2);
                return root;
            }
            ptr2 = ptr2->next;
            prev = prev->next;
        }
    }
}
void printUniversityAscending(struct univHeader *univhead)
{
    struct univNode *ptr = univhead->next;
    struct univNode *ptr2 = NULL;
    struct univNode *root = NULL; //duplicate
    int year;
    printf(".............ASCENDING ORDER LIST.......\n");
    printf("Name\t\tID\t\tLocation\t\tYear of Start\n");
    while (ptr != NULL)
    {
        struct univNode *temp = (struct univNode *)malloc(sizeof(struct univNode));
        temp->next = NULL;
        strcpy(temp->univName, ptr->univName);
        temp->univID = ptr->univID;
        temp->yos = ptr->yos;
        strcpy(temp->univLoc, ptr->univLoc);
        if (root == NULL)
        {
            root = temp;
            ptr2 = root;
        }
        else
        {
            while (ptr2->next != NULL)
                ptr2 = ptr2->next;
            ptr2->next = temp;
        }
        ptr = ptr->next;
    }
    while (root != NULL)
    {
        struct univNode *ptr = root;
        year = ptr->yos;
        while (ptr != NULL)
        {
            if (ptr->yos < year)
                year = ptr->yos;
            ptr = ptr->next;
        }
        ptr = root;
        while (ptr != NULL)
        {
            if (year == ptr->yos)
            {
                root = deleteAndPrint(root, ptr);
            }
            ptr = ptr->next;
        }
    }
}
void dispsub(struct studentHeader *stuhead)
{
    struct studentNode *ptr = stuhead->next;
    char *sub;
    char str[100];
    printf("Enter the substring to print data\n");
    fflush(stdin);
    scanf("%s",str);
    sub = strstr(ptr->name, str);
    if(sub!=NULL)
        {
            printf("Roll Number\tName\tBranch Id\t\tCGPA\n");
            printf("%d\t\t%s\t\t%d\t\t%f\n", ptr->roll, ptr->name, ptr->selectedBranchCode, ptr->cgpa);
        }
    else{
        ptr=ptr->next;
    }
    
}