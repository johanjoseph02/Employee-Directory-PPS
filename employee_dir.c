//======================================================================//
//                                                                      //
//  Author: JOHAN MATHEW JOSEPH                                         //
//  Reg. No: RA2111026010309                                            //
//  Section: R2                                                         //
//  Branch: CSE with specialization in AI and ML                        //
//  Project: Employee Directory (PPS Mini Project)                      //
//  Version: v1.0                                                       //
//  NLOC: 350                                                           //
//                                                                      //
//======================================================================//

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h> // Windows related functions
#include <string.h>

// structure: coordinates
COORD coord = {0,0}; // top-left corner of window

void gotoxy(int x,int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

//==============================================================================================================

// Login function

void login()
{
    system("color 07");
	int a=0,i=0;
    char uname[10],c=' ';
    char pword[10],code[10];
    char user[10]="admin";
    char pass[10]="admin101";
    do
    {
        system("color 07");
        printf("\n  #--------------------------  LOGIN  --------------------------#  ");
        printf("\n\n                          Enter Username: ");
        scanf("%s", &uname);
        printf("\n                          Enter Password: ");
        while(i<10)
        {
            pword[i]=getch();
            c=pword[i];
            if(c==13) break;
            else printf("*");
            i++;
        }
        pword[i]='\0';
        i=0;
        if(strcmp(uname,user)==0 && strcmp(pword,pass)==0)
        {
            printf("\n\n\n  >>                     Login successful                      <<");
            system("color 0A");
            Sleep(700);
            system("cls");
            system("color 2F");
            printf("\n  ---------------------------------------------------------  ");
            printf("\n  >>>>>>>>>>>>  WELCOME TO EMPLOYEE DIRECTORY  <<<<<<<<<<<<  ");
            printf("\n  ---------------------------------------------------------  ");

            printf("\n\n                LOADING Please wait ");
            for(i=1; i<=9; i++)
            {
                printf(".");
                Sleep(300);
            }
            printf("\n\n                Press any key to continue ...");
            getch();
            break;
        }
        else
        {
            system("color 0C");
            printf("\n\n\n  !!                     Login unsuccessful                    !!");
            printf("\n                     Press any key to try again                  ");
            a++;
            getch();
            system("cls");
        }
    }
	while(a<=2);
	{
        if (a>2)
        {
            system("color 4F");
            printf("\n  #--------------------------  ERROR  --------------------------# ");
            printf("\n  !!!                                                         !!! ");
            printf("\n  !!!        Directory Locked, too many wrong attempts        !!! ");
            printf("\n  !!!                Please read README.txt and               !!! ");
            printf("\n  !!!                  re-execute the program                 !!! ");
            printf("\n  !!!                                                         !!! ");
            printf("\n  #-------------------------------------------------------------# \n");

            printf("\n\n  Press any key to EXIT...");
            getch();
            exit(1); // unsuccessful exit
        }
	}
    system("cls");
}

//==============================================================================================================

// Main function

int main()
{
	int i=0;
	login();
    FILE *fp, *ft; // file pointers
    char another, choice;

    // structure: employee details
    struct emp
    {
        char name[40];
        int age;
        char address[20];
        float bs;
    };

    struct emp e;

    char empname[40];
    long int recsize; // to store size of each record of employee

    //opening file
    fp = fopen("EMP.DAT","rb+");
    if(fp == NULL)
    {
        fp = fopen("EMP.DAT","wb+");
        if(fp == NULL)
        {
            printf("Cannot open file");
            exit(1); // unsuccessful exit
        }
    }

    recsize = sizeof(e); // size of each record i.e. size of structure variable e

    while(1)
    {
        system("cls");
        system("color 1F");
        printf("\n  #==========================================================================#  ");
        printf("\n  |                                                                          |  ");
        printf("\n  |                            EMPLOYEE DIRECTORY                            |  ");
        printf("\n  |                                                                          |  ");
        printf("\n  #==========================================================================# \n");
        gotoxy(30,9);
		printf("1. Add Employee Records");
        gotoxy(30,11);
        printf("2. List Employee Records");
        gotoxy(30,13);
        printf("3. Modify Employee Records");
        gotoxy(30,15);
        printf("4. Delete Employee Records");
        gotoxy(30,17);
        printf("5. Empty Employee Directory");
        gotoxy(30,19);
        printf("6. EXIT");
        gotoxy(30,21);
        printf("--> ");
        fflush(stdin);      // flush the input buffer
        choice  = getche(); // get the input from keyboard

        switch(choice)
        {
            // ADD EMPLOYEE RECORDS ==============================================================
            case '1':
                system("cls");
                system("color 1B");
                printf("\n  ------------  ADD EMPLOYEE RECORDS ------------  \n");
                fseek(fp,0,SEEK_END); // search the file and move cursor to end of the file

                another = 'y';
                while(another == 'y')
                {
                    printf("\n  Enter name: ");
                    scanf(" %s",e.name);
                    printf("\n  Enter age: ");
                    scanf(" %d", &e.age);
                    printf("\n  Enter address: ");
                    scanf(" %s",e.address);
                    printf("\n  Enter basic salary: ");
                    scanf(" %f", &e.bs);
                    printf("\n  -----------------------------------------------  \n");

                    fwrite(&e,recsize,1,fp); // write the record in the file

                    printf("\n  Add another record? (y/n): ");
                    fflush(stdin);      // flush the input buffer
                    another = getche(); // get the input from keyboard
                }
                printf("\n\n  Press any key to return to main menu...");
                getch();
                break;

            // LIST EMPLOYEE RECORDS =============================================================
            case '2':
                system("cls");
                system("color 1B");
                printf("\n  ------------  ALL EMPLOYEE RECORDS ------------  \n");
                rewind(fp); // move cursor to start of the file

                int n = 1;
                while(fread(&e,recsize,1,fp)==1)  // read the file and fetch one record
                {
                    printf("\n  >> RECORD %d", n);
                    printf("\n  Name: %s",e.name);
                    printf("\n  Age: %d",e.age);
                    printf("\n  Address: %s",e.address);
                    printf("\n  Basic salary: %.2f",e.bs);
                    printf("\n\n  ----------------------------------------------  \n");
                    n++;
                }
                printf("\n  Press any key to return to main menu...");
                getch();
                break;

            // MODIFY EMPLOYEE RECORDS ===========================================================
            case '3':
                system("cls");
                system("color 1B");
                printf("\n  ------------  MODIFY EMPLOYEE RECORDS ------------  \n");

                another = 'y';
                while(another == 'y')
                {
                    printf("\n  Enter the employee name to modify: ");
                    scanf("%s", empname);
                    rewind(fp);                       // move cursor to start of the file
                    while(fread(&e,recsize,1,fp)==1)  // read the file and fetch one record
                    {
                        if(strcmp(e.name,empname) == 0)
                        {
                            printf("\n  Enter new name: ");
                            scanf("%s",e.name);
                            printf("\n  Enter new age: ");
                            scanf("%d", &e.age);
                            printf("\n  Enter new address:");
                            scanf("%s",e.address);
                            printf("\n  Enter new basic salary: ");
                            scanf("%f", &e.bs);
                            printf("\n  --------------------------------------------------  \n");

                            fseek(fp,-recsize,SEEK_CUR); // move the cursor 1 step back
                            fwrite(&e,recsize,1,fp);     // overwrite the record
                            break;
                        }
                    }
                    printf("\n  Modify another record? (y/n): ");
                    fflush(stdin);      // flush the input buffer
                    another = getche(); // get the input from keyboard
                }
                printf("\n\n  Press any key to return to main menu...");
                getch();
                break;

            // DEL EMPLOYEE RECORDS ==============================================================
            case '4':
                system("cls");
                system("color 1B");
                printf("\n  ------------  DELETE EMPLOYEE RECORDS ------------  \n");

                another = 'y';
                while(another == 'y')
                {
                    printf("\n  Enter name of employee to delete: ");
                    scanf("%s",empname);
                    printf("\n  --------------------------------------------------  \n");
                    ft = fopen("Temp.dat","wb");        // create temporary file
                    rewind(fp);                         // move cursor to start of the file
                    while(fread(&e,recsize,1,fp) == 1)  // read the file and fetch one record
                    {
                        if(strcmp(e.name,empname) != 0)
                        {
                            fwrite(&e,recsize,1,ft); // write all records except the one that is to be deleted to temp file
                        }
                    }
                    fclose(fp);                   // close original file
                    fclose(ft);                   // close temp file
                    remove("EMP.DAT");            // delete original file
                    rename("Temp.dat","EMP.DAT"); // rename temp file to original file name
                    fp = fopen("EMP.DAT", "rb+"); // open temp file (now original) as fp

                    printf("\n  Delete another record? (y/n): ");
                    fflush(stdin);      // flush the input buffer
                    another = getche(); // get the input from keyboard
                }
                printf("\n\n  Press any key to return to main menu...");
                getch();
                break;

            // EMPTY EMPLOYEE DIR ================================================================
             case '5':
                system("cls");
                system("color 1B");
                printf("\n  ------------  EMPTY EMPLOYEE DIRECTORY ------------  \n");
                another = 'n';

                printf("\n  Are you sure you wish to erase the directory? (y/n): ");
                fflush(stdin);
                another = getche();

                if(another == 'y')
                {
                    ft = fopen("Temp.dat","wb");  // create temporary file
                    fclose(fp);                   // close original file
                    fclose(ft);                   // close temp file
                    remove("EMP.DAT");            // delete original file
                    rename("Temp.dat","EMP.DAT"); // rename temp file to original file name
                    fp = fopen("EMP.DAT", "rb+"); // open temp file (now original) as fp
                }

                printf("\n\n  Press any key to return to main menu...");
                getch();
                break;

            // EXIT ===============================================================================
            case '6':
                system("cls");
                system("color 0A");
                printf("\n  @--------------------------------------------------------------------------@  ");
                printf("\n  |                                                                          |  ");
                printf("\n  |                  Thank you for using EMPLOYEE DIRECTORY                  |  ");
                printf("\n  |                                                                          |  ");
                printf("\n  |                     Developed by JOHAN MATHEW JOSEPH                     |  ");
                printf("\n  |                     Reg. No: RA2111026010309                             |  ");
                printf("\n  |                     Section: R2                                          |  ");
                printf("\n  |                     Branch: CSE with AI and ML                           |  ");
                printf("\n  |                                                                          |  ");
                printf("\n  @--------------------------------------------------------------------------@ \n");
                fclose(fp);  // close file

                printf("\n\n  Press any key to EXIT...");
                getch();
                exit(0); // successful exit
        }
    }
    return 0;
}
//END OF CODE
