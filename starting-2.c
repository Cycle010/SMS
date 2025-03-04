#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#ifdef _WIN32
#include<conio.h>
#else
#include<termios.h>
#endif
#include<time.h>
#include<unistd.h>
#include<windows.h>

#define MAX_USERS 10
#define MAX_CREDENTIALS 30
#define MAX_STUDENTS 100
    typedef struct{
        char username[MAX_CREDENTIALS];
        char password[MAX_CREDENTIALS];
    }user;

    user users[MAX_USERS];
    int user_count = 0;
    int user_index = 0;

    typedef struct{
        char Name[20];
        char ID[15];
        int RollNo;
        char Section[5];
        char Program[10];
        char Branch[5];
        char Email[35];
        char Phone[20];
        int Semester;
    }student;

    student students[MAX_STUDENTS];
    int total_students=0;

    
    char* get_time();
    void register_user();
    int  login_user();
    void fix_fgets_input(char*);
    void input_credentials(char* username, char* password);
    void masked_password_input(char*);
    void clear_screen();
    void student_managment_interface(int);
    void addstudentInfo();
    void displayAllStudents();
    void deleteStudentInfo();
    void deleteAllStudents();
    void updateStudentInfo();
    void searchStudent();
    int testdataentry();
    void studentList();
    int finddigits(int *);
    void themeMenu();

    int main(){
        while(1){
            char option=0;
            total_students = testdataentry();
        printf("\033[0m\n\t\t\t\t\tHold [F11] for Full Screen, Windowed Mode UI Work In Progress...\n\n\n\n\n\n");
        printf("\n\t\t\t\t\t1. Register");
        printf("\n\t\t\t\t\t2. Login");
        printf("\n\t\t\t\t\t3. Exit");
        printf("\n\t\t\t\t\tSelect an option: ");
        option = getch();
        printf("%c",option);
        Beep(261, 10);
        switch(option){
            case '1':
            register_user();
            break;
            case '2':
            user_index=login_user();
            if (user_index>=0){
                printf("\033[92;40mEntry In: ");
                get_time();
                printf("\nLogin Successful, Welcome %s!",users[user_index].username);
                student_managment_interface(user_index);
            }
            else{
                printf("Login failed");
            }
            break;
            case '3':
            clear_screen();
            printf("Shutting down....\nDone");
            exit(0);
            default:
            clear_screen();
            printf("(+_+) Invalid Option!\nTry again\n");

        }
        }
        return 0;
    }

    char* get_time(){
        time_t start_time;
        struct tm * current_time;
        char entry[20];

        time(&start_time);
        current_time = localtime(&start_time);
        strftime(entry,sizeof(entry),"%I:%M:%S %p",current_time);
        printf("%s", entry);
    }

    void register_user(){
        clear_screen();
        if(user_count == MAX_USERS){
            printf("Max user limit exceed %d,",user_count);
            return;
        }

            int new_index=user_count;
            printf("\nRegister new user");
            input_credentials(users[new_index].username, users[new_index].password);
            user_count++;
            printf("\nRegistraton Successful");
    }

    int login_user(){
        clear_screen();
        char username[MAX_CREDENTIALS];
        char password[MAX_CREDENTIALS];
        printf("User Login");
        input_credentials(username, password);

        for(int i=0; i< user_count;i++){
            if(strcmp(username,users[i].username)==0 &&
            strcmp(password,users[i].password) == 0){
                return i;
            }
        }
        return -1;
    }
    void input_credentials(char* username, char* password){
        printf("\n\n\n\n\n\n\n\n\t\t\t\t\tEnter username: ");
        fgets(username,MAX_CREDENTIALS,stdin);
        fix_fgets_input(username);
        printf("\t\t\t\t\tEnter password: ");
        masked_password_input(password);
        //fgets(password, MAX_CREDENTIALS,stdin);
        //fix_fgets_input(password);
        clear_screen();
    }
    void masked_password_input(char* password){
        char ch;
        int i = 0;
        #ifdef _WIN32
        while((ch = _getch())!=13){
            if((ch == '\b' || ch == 127)){
                if(i>0){
                i--;
                printf("\b \b");
                }
            }
            else{
            password[i++]=ch;
            printf("*");
            }
        }
        password[i]='\0';
        #else
        struct termios orgi_value, new_value;
        new_value = orgi_value;
        new_value.c_lflag = ~(ECHO || ICANON);
        tcsetattr(STDIN_FILENO, TCSANOW, &new_value);
        while((ch = getch())!=13){
            if((ch == '\b' || ch == 127)){
                if(i>0){
                i--;
                printf("\b \b");
                }
            }
            else{
            password[i++]=ch;
            printf("*");
            }
        }
        password[i]='\0';
        tcsetattr(STDIN_FILENO, TCSANOW, &orgi_value);
        #endif
    }
    void fix_fgets_input(char* string){
        int index =strcspn(string,"\n");
        string[index] = '\0';
    }
    void clear_screen(){
        #ifdef _WIN32
        system("cls");
        #else
        system("clear");
        #endif
    }
    void student_managment_interface(int user_index){
        while(1){
            char option=0;
        printf("\n\t\t\t\t\tHold [F11] for Full Screen, Windowed Mode UI Work In Progress...\n\n\n\n\n\n");
        printf("\n\n\n\n\n\t\t\t\t1. Add a New Student");
        printf("\n\t\t\t\t2. Display All Students");
        printf("\n\t\t\t\t3. Delete a Student Info");
        printf("\n\t\t\t\t4. Delete all Students");
        printf("\n\t\t\t\t5. Update Student Info");
        printf("\n\t\t\t\t6. Search Student");
        printf("\n\t\t\t\t7. Students List");
        printf("\n\t\t\t\t8. Filter by Grades");
        printf("\n\t\t\t\t9. Change Theme");
        printf("\n\t\t\t\tA. Exit");
        printf("\n\t\t\t\tSelect an option: ");
        option = getch();
        printf("%c",option);
        Beep(261, 10);
        if(option=='A') option='a';
        switch (option)
        {
            case '1':
            clear_screen();
            addstudentInfo();
            
            break;
            case '2':
            clear_screen();
            displayAllStudents();
            
            break;
            case '3':
            clear_screen();
            deleteStudentInfo();
            
            break;
            case '4':
            printf("\033[1;33;41m");
            clear_screen();
            deleteAllStudents();
            
            break;
            case '5':
            clear_screen();
            updateStudentInfo();
            
            break;
            case '6':
            clear_screen();
            searchStudent();

            break;
            case '7':
            clear_screen();
            printf("Work in progress...... ");
            //studentList();
            
            break;
            case '8':
            clear_screen();
            printf("Work in progress...... ");
            
            break;
            case '9':
            clear_screen();
            themeMenu();
            
            break;
            case 'a':
            clear_screen();
            //printf("\nLogout Successful, Goodbye %s!",users[user_index].username);
            //printf("\nExiting Program");
            for(int i=0;i<6;i++){ printf("Entry Out: ");get_time();
                printf("\nLogout Successful, Goodbye %s!",users[user_index].username);printf("\nExiting Program ");
                if(i%2==0)printf("<(^-^)\\");else printf("<(^-^)/");sleep(1);clear_screen();}
            clear_screen();
            main();
            
            break;
            default:
            clear_screen();
            printf("(+_+) Invalid Input\n");

            break;
        }
    }
    }

    void addstudentInfo(){
        printf("\n\t\t\t\t\tAdd A New Student ('0' to Skip to Menu)\n");
        printf("\n\t\t\t\t\tEnter Student Name: ");
        scanf("%[^\n]s",students[total_students].Name);
        getchar();
        while(strlen(students[total_students].Name)<1){
            clear_screen();
        printf("\n\t\t\t\t\tAdd A New Student ('0' to Skip to Menu)\n");
        printf("\n\t\t\t\t\tEnter Student Name: ");
        scanf("%[^\n]s",students[total_students].Name);
        getchar();}
        if(students[total_students].Name[0]=='0')
        {goto skip;}
        printf("\t\t\t\t\tEnter Student ID: ");
        scanf("%[^\n]s",students[total_students].ID);
        getchar();
        while(strlen(students[total_students].ID)<8){
            clear_screen();
        printf("\n\t\t\t\t\tAdd A New Student ('0' to Skip to Menu)\n");
        printf("\n\t\t\t\t\tEnter Student Name: %s",students[total_students].Name);
        printf("\n\t\t\t\t\tEnter Student ID: ");
        scanf("%[^\n]s",students[total_students].ID);
        getchar();}
        if(students[total_students].ID[0]=='0')
        {goto skip;}
        printf("\t\t\t\t\tEnter Student Program: ");
        scanf("%[^\n]s",students[total_students].Program);
        getchar();
        if(students[total_students].Program[0]=='0')
        {goto skip;}
        printf("\t\t\t\t\tEnter Student Branch: ");
        scanf("%[^\n]s",students[total_students].Branch);
        getchar();
        if(students[total_students].Branch[0]=='0')
        {goto skip;}
        printf("\t\t\t\t\tEnter Student Semester: ");
        scanf("%d",&students[total_students].Semester);
        getchar();
        if(students[total_students].Semester==0)
        {goto skip;}
        printf("\t\t\t\t\tEnter Student Section: ");
        scanf("%[^\n]s",students[total_students].Section);
        getchar();
        if(students[total_students].Section[0]=='0')
        {goto skip;}
        printf("\t\t\t\t\tEnter Student Roll No: ");
        scanf("%d",&students[total_students].RollNo);
        getchar();
        if(students[total_students].RollNo==0)
        {goto skip;}
        printf("\t\t\t\t\tEnter Student Email: ");
        scanf("%[^\n]s",students[total_students].Email);
        getchar();
        if(students[total_students].Email[0]=='0')
        {goto skip;}
        printf("\t\t\t\t\tEnter Student Phone No. : ");
        scanf("%[^\n]s",students[total_students].Phone);
        getchar();
        total_students++;
        clear_screen(); return;
        skip:
        strcpy(students[total_students].Name,"\0");
        strcpy(students[total_students].ID,"\0");
        strcpy(students[total_students].Program,"\0");
        strcpy(students[total_students].Branch,"\0");
        strcpy(students[total_students].Section,"\0");
        students[total_students].RollNo = 0;
        students[total_students].Semester = 0;
        strcpy(students[total_students].Email,"\0");
        strcpy(students[total_students].Phone,"\0");
        clear_screen();

    }
    void displayAllStudents(){
        if(total_students==0) printf("\n\n\t\t\t\t\t\t\t\t*********No Record Found!*********\n\n\n\n\n\n");
        else{
        printf("\t|========|============|===================|================================|=================|===========|==========|==========|===========|===========|\n");
        printf("\t|  S.No  |     ID     |        Name       |              Email             |      Phone      |  Program  |  Branch  | Semester |  Section  |  Roll No. |\n");
        printf("\t|========|============|===================|================================|=================|===========|==========|==========|===========|===========|\n");
        for(int i=0;i<total_students;i++){
            printf("\t|");
            printf("%d.",i+1);
            int j=i+1;
            while(j<1000000){
                printf(" ");
                j*=10;
            }
            printf("|");
            printf("%s",students[i].ID);
            for(int j = strlen(students[i].ID);j<=11;j++){
                printf(" ");
            }
            printf("|");
            printf("%s",students[i].Name);
            for(int j = strlen(students[i].Name);j<=18;j++){
                printf(" ");
            }
            printf("|");
            printf("%s",students[i].Email);
            for(int j = strlen(students[i].Email);j<=31;j++){
                printf(" ");
            }
            printf("|");
            printf("%s",students[i].Phone);
            for(int j = strlen(students[i].Phone);j<=16;j++){
                printf(" ");
            }
            printf("|");
            printf("%s",students[i].Program);
            for(int j = strlen(students[i].Program);j<=10;j++){
                printf(" ");
            }
            printf("|");
            printf("%s",students[i].Branch);
            for(int j = strlen(students[i].Branch);j<=9;j++){
                printf(" ");
            }
            printf("|");
            printf("%d",students[i].Semester);
            for(int j = finddigits(&students[i].Semester);j<=9;j++){
                printf(" ");
            }
            printf("|");
            printf("%s",students[i].Section);
            for(int j = strlen(students[i].Section);j<=10;j++){
                printf(" ");
            }
            printf("|");
            printf("%d",students[i].RollNo);
            for(int j = finddigits(&students[i].RollNo);j<=10;j++){
                printf(" ");
            }
            printf("|");
        printf("\n\t|========|============|===================|================================|=================|===========|==========|==========|===========|===========|\n");  
        }
        }
        printf("\n\nPress 'Enter' to Goto Menu >(^-^)>\n");
            getchar();
            clear_screen();
    }
    int finddigits(int * p){
        if(*p==0) return 1;
        int n = *p,c=0; 
        while(n!=0){
            n/=10;
            c++;
        }
        return c;
    }
    void deleteStudentInfo(){
        if(total_students==0){
            printf("\n\n\n\n\n\n\t\t\t\t\t****Nothing Left To Search****\n");
            printf("\n\t\t\t\t\t Records Are Completely Empty\n\n\n\n");
            goto skip;
        }
        while(1){
        char option=0;
        int i=0;
        char student[15];
        printf("\n\n\n\n\n\n\t\t\t\t\tDeleting Record of Student\n");
        printf("\n\t\t\t\t\t1. Delete by Student ID");
        printf("\n\t\t\t\t\t2. Delete by Student Name");
        printf("\n\t\t\t\t\t3. Exit to Main Menu");
        printf("\n\t\t\t\t\tSelect an option: ");
        option = getch();
        printf("%c",option);
        Beep(261, 10);
        switch(option){
            case '1':
            clear_screen();
            printf("\n\n\n\n\n\n\t\t\t\t\tEnter Student ID: ");
            scanf("%[^\n]s",&student);
            getchar();
            while(strcmp(student,students[i].ID)!=0){
                i++;
                if(i==total_students)
                break;
            }
            if(i==total_students){
            printf("\n\nStudent Record Not Found.");
            }
            else
            {
            for(i;i<total_students;i++){
                students[i]=students[i+1];
            }
            total_students--;
            printf("\n\nStudent Record Successfully Removed.");
            }
            goto skip;

            case '2':
            clear_screen();
            printf("\n\n\n\n\n\n\t\t\t\t\tEnter Student Name: ");
            scanf("%[^\n]s",&student);
            getchar();
            int same[10];
            int j=0;
            while(i!=total_students){
               if(strcmpi(student,students[i].Name)==0){
                printf("\n\t\t\t\t\t%d. %s (%s)\n\t\t\t\t\tProgram: %s\n\t\t\t\t\tSection: %s\n\t\t\t\t\tRoll No: %d\n",j+1,students[i].Name,students[i].ID,students[i].Program,students[i].Section,students[i].RollNo);
                same[j]=i;
                j++;
               }
               i++;
               }
               if(j==0){
                printf("\n\nFound No Existing Record Of Student Named: %s",student);
                goto skip;
                }
                else{
                if(j!=1)
                {
                printf("\nFound Students with Similar Name\nSelect the Desired Student for Record Deletion: ");
                scanf("%d",&i);
                getchar();
                i=same[i-1];
                }
                else
                {
                printf("\nStudent Found!",&student);
                i=same[0];
                }
                for(i;i<total_students;i++){
                students[i]=students[i+1];
                }
                total_students--;
                printf("\nStudent Record Successfully Removed.");
                goto skip;
            }
            case '3':
            clear_screen();
            return;

            default:
            clear_screen();
            printf("(+_+) Invalid Input!\n");
            break;   
        }
        }
        skip:
        printf("\n\nPress 'Enter' to Goto Menu >(^-^)>\n");
        getchar();
        clear_screen();   
}


    
    void deleteAllStudents(){
        while(1){
        char option;
        printf("Are You Sure Want to Delete all Students (Y/N): ");
        option=getch();
        Beep(261, 10);
        if(option=='Y' || option=='y'){
            char password[30];
            printf("Y\nThis will clear all records");
            printf("\n\nEnter Your Password: ");
            masked_password_input(password);
            if(strcmp(password,users[user_index].password)==0){
                while(1){
                    strcpy(students[total_students].Name,"\0");
                    strcpy(students[total_students].ID,"\0");
                    strcpy(students[total_students].Program,"\0");
                    strcpy(students[total_students].Branch,"\0");
                    strcpy(students[total_students].Section,"\0");
                    students[total_students].RollNo = 0;
                    students[total_students].Semester = 0;
                    strcpy(students[total_students].Email,"\0");
                    strcpy(students[total_students].Phone,"\0");
                    if(total_students == 0) break;
                    total_students--;
                }
                printf("\n\nCorrect Password!\nAll records have been cleared");
                break;
            }
            else{
                printf("\n\nIncorrect Password!\n");
                break;
            }

        }
        else if(option=='N'|| option=='n'){
            printf("N\nNothing Changed");
            break;
        }
        else
           clear_screen();
        }
        printf("\nPress 'Enter' to Goto Menu >(^-^)>\n");
        getchar();
        printf("\033[0m");
        clear_screen();
    }
    
    void updateStudentInfo(){
        if(total_students==0){
            printf("\n\n\n\n\n\n\t\t\t\t\t****Nothing Left To Search****\n");
            printf("\n\t\t\t\t\t Records Are Completely Empty\n\n\n\n");
            goto skip;
        }
        char studentInfo[30];
        int i=0;
        printf("\t\t\t\t\tEnter Student ID for Updation: ");
        scanf("%[^\n]s",studentInfo);
        getchar();
        while(strcmp(studentInfo,students[i].ID)){
            i++;
            if(i==total_students)
                break;
        }
        if(i==total_students)
        printf("\nNo Record Found!\nEnter a Valid ID\n");
        else{
            studentInfo[0]='\0';
            printf("\t\t\t\t\tEnter NEW Name (0 for skip): ");
            scanf("%[^\n]s",studentInfo);
            getchar();
            if(!(studentInfo[0]=='0')) strcpy(students[i].Name,studentInfo);
            studentInfo[0]='\0';
            printf("\t\t\t\t\tEnter NEW Program (0 for skip): ");
            scanf("%[^\n]s",studentInfo);
            getchar();
            if(!(studentInfo[0]=='0')) strcpy(students[i].Program,studentInfo);
            studentInfo[0]='\0';
            printf("\t\t\t\t\tEnter NEW Branch (0 for skip): ");
            scanf("%[^\n]s",studentInfo);
            getchar();
            if(!(studentInfo[0]=='0')) strcpy(students[i].Branch,studentInfo);
            studentInfo[0]='\0';
            printf("\t\t\t\t\tEnter NEW Section (0 for skip): ");
            scanf("%[^\n]s",studentInfo);
            getchar();
            if(!(studentInfo[0]=='0')) strcpy(students[i].Section,studentInfo);
            int studentInfodigit = 0;
            printf("\t\t\t\t\tEnter NEW RollNo. (0 for skip): ");
            scanf("%d",&studentInfodigit);
            getchar();
            if(!(studentInfodigit==0)) students[i].RollNo = studentInfodigit;
            studentInfodigit = 0;
            printf("\t\t\t\t\tEnter NEW Semester (0 for skip): ");
            scanf("%d",&studentInfodigit);
            getchar();
            if(!(studentInfodigit==0)) students[i].Semester = studentInfodigit;
            studentInfo[0]='\0';
            printf("\t\t\t\t\tEnter NEW Email (0 for skip): ");
            scanf("%[^\n]s",studentInfo);
            getchar();
            if(!(studentInfo[0]=='0')) strcpy(students[i].Email,studentInfo);
            studentInfo[0]='\0';
            printf("\t\t\t\t\tEnter NEW Phone No. (0 for skip): ");
            scanf("%[^\n]s",studentInfo);
            getchar();
            if(!(studentInfo[0]=='0')) strcpy(students[i].Phone,studentInfo);
            printf("\nDone...");
            
        }
        skip:
        printf("\nPress 'Enter' to Goto Menu >(^-^)>\n");
        getchar();
        clear_screen();
    }
    void searchStudent(){
        if(total_students==0){
            printf("\n\n\n\n\n\n\t\t\t\t\t****Nothing Left To Search****\n");
            printf("\n\t\t\t\t\t Records Are Completely Empty\n\n\n\n");
            goto skip;
        }
        char student[30];
        int i = 0;
        
        printf("\t\t\t\t\tEnter Student Name or ID : ");
        scanf("%[^\n]s",student);
        getchar();
            int j=0;
            while(i!=total_students){
               if(strcasecmp(student,students[i].Name)==0 || strcasecmp(student,students[i].ID)==0){
                printf("\n\t\t\t\t\t%d.%s (%s)\n\t\t\t\t\tProgram: %s\n\t\t\t\t\tBranch: %s\n\t\t\t\t\tSemester: %d\n\t\t\t\t\tSection: %s\n\t\t\t\t\tRoll No: %d\n\t\t\t\t\tEmail: %s\n\t\t\t\t\tPhone No: %s\n",j+1,students[i].Name,students[i].ID,students[i].Program,students[i].Branch,students[i].Semester,students[i].Section,students[i].RollNo,students[i].Email,students[i].Phone);
                j++;
               }
               i++;
            }
               if(j==0){
                printf("\n\n\nFound No Existing Record Of Student having Name or ID: %s",&student);
                }
                else if(j==1)
                {
                printf("\nStudent Found!");
                }
                else
                printf("\nFound Multiple Students having Same Name");
                skip :
                printf("\nPress 'Enter' to Goto Menu >(^-^)>\n");
                getchar();
                clear_screen();
    }
        void studentList(){
            while(1){
            int option = 0;
            printf("\n1. List By Name");
            printf("\n2. List By Section");
            printf("\n3. List By Program");
            printf("\n4. List By Semester");
            scanf("%d",&option);
            break;
            switch (option)
            {
            case 1:
                
                break;
            case 2:
                
                break;
            case 3:
                
                break;
            case 4:
                
                break;
            
            default:

                break;
            }
        }
    }
    void themeMenu(){
        printf("\033[0m");
        clear_screen();
        char themeMode = '1', temp = '0';
        int flag=0;
        while(themeMode!='d'){
        printf("\t\t\t\t************I am Colour Blind So My Selected Colour Combinations Maybe be Tasteless I Know!************");
        printf("\n\033[37;40m1. Dark Theme .\033[0m");
        printf("\n\033[30;47m2. Light Theme .\033[0m");
        printf("\n\033[93;48;5;8m3. Grey Theme .\033[0m");
        printf("\n\033[93;44m4. Midnight Glow .\033[0m");
        printf("\n\033[90;101m5. Shadow & Blood .\033[0m");
        printf("\n\033[96;100m6. Steel & Neon .\033[0m");
        printf("\n\033[93;41m7. Golden Sunset .\033[0m");
        printf("\n\033[94;43m8. Electric Blue .\033[0m");
        printf("\n\033[96;45m9. Cyberpunk Neon .\033[0m");
        printf("\n\033[37;44mA. Turbo C .\033[0m");
        printf("\n\033[92;40mB. Hacker Green .\033[0m");
        printf("\n\033[91;104mC. Fire & Ice .\033[0m");
        printf("\nD. Exit to Main Menu");
        printf("\n0. Apply Current Theme");
        printf("\nX. \033[1;31mScr\033[1;32mee\033[1;33mn S\033[1;34mh\033[1;35mo\033[1;36mw\033[0m");
        printf("\nSelect an option: ");
        temp= themeMode;
        themeMode= getch();
        printf("%c",themeMode);
        if(themeMode=='0'){
            themeMode=temp;
            flag=1;
        }
        if(themeMode=='A') themeMode='a';
        if(themeMode=='B') themeMode='b';
        if(themeMode=='C') themeMode='c';
        if(themeMode=='D') themeMode='d';
        if(themeMode=='X') themeMode='x';
        Beep(261, 10);
        switch (themeMode)
        {
        case '1':
            printf("\033[1;37;40m");
            clear_screen();
            break;

        case '2':
        printf("\033[1;30;47m");
            clear_screen();
            break;

        case '3':
        printf("\033[1;93;48;5;8m");
            clear_screen();
            break;
        case '4':
            printf("\033[1;93;44m");
            clear_screen();
            break;
        case '5':
        printf("\033[1;90;101m");
            clear_screen();
            break;
        case '6':
        printf("\033[1;96;100m");
            clear_screen();
            break;    
        case '7':
            printf("\033[1;93;41m");
            clear_screen();
            break;
        case '8':
        printf("\033[1;94;43m");
            clear_screen();
            break;
        case '9':
        printf("\033[1;96;45m");
            clear_screen();
            break;
        case 'a':
        printf("\033[1;37;44m");
            clear_screen();
            break;
        case 'b':
        printf("\033[1;92;40m");
            clear_screen();
            break;
        case 'c':
            printf("\033[1;91;104m");
            clear_screen();
            break;
            case 'x':
            for(int j=0;j<3;j++)
            for(int i='1';i<='D';i++){
                if(i=='1') {printf("\033[91;104m");clear_screen();}
                if(i=='2') {printf("\033[30;47m");clear_screen();}
                if(i=='3') {printf("\033[93;48;5;8m");clear_screen();}
                if(i=='4') {printf("\033[95;44m");clear_screen();}
                if(i=='5') {printf("\033[90;101m");clear_screen();}
                if(i=='6') {printf("\033[96;100m");clear_screen();}
                if(i=='7') {printf("\033[93;41m");clear_screen();}
                if(i=='8') {printf("\033[94;43m");clear_screen();}
                if(i=='9') {printf("\033[96;45m");clear_screen();}
                if(i=='A') {printf("\033[37;44m");clear_screen();}
                if(i=='B') {printf("\033[92;40m");clear_screen();}
                if(i=='C') {printf("\033[37;40m");clear_screen();;}
                sleep((float)0.1);
            }
            clear_screen();
            break;    
        default:
            printf("(+_+) Invalid Input!\n");
            clear_screen();
            break;
        }
        if(flag==1) break;
        }
        clear_screen();
    }




















































    int testdataentry(){
        //My name is "Akhil"
        //I know I am crazy!!!
        int i = 0;
        strcpy(students[i].Name,"Abhishek Chamoli");
        strcpy(students[i].ID,"240111412");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 01;
        strcpy(students[i].Email,"abhishekchamoli57@gmail.com");
        strcpy(students[i++].Phone,"+91 75003 50710");

        strcpy(students[i].Name,"Abhishek Rana");
        strcpy(students[i].ID,"24011071");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 02;
        strcpy(students[i].Email,"ranaabhishek449@gmail.com");
        strcpy(students[i++].Phone,"+91 78956 18994");

        strcpy(students[i].Name,"Abhishek S. Bisht");
        strcpy(students[i].ID,"24021829");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 03;
        strcpy(students[i].Email,"abhishekbisht425@gmail.com");
        strcpy(students[i++].Phone,"+91 74548 27547");

        strcpy(students[i].Name,"Adarsh Gairola");
        strcpy(students[i].ID,"240111795");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 04;
        strcpy(students[i].Email,"adarshgairola5@gmail.com");
        strcpy(students[i++].Phone,"+91 87919 56005");
        
        strcpy(students[i].Name,"Aditya Bisht");
        strcpy(students[i].ID,"240111866");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 05;
        strcpy(students[i].Email,"aditya.5306b@gmail.com");
        strcpy(students[i++].Phone,"+91 81780 21678");

        strcpy(students[i].Name,"Aditya Dobriyal");
        strcpy(students[i].ID,"240111819");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 06;
        strcpy(students[i].Email,"adityadobriyal95@gmail.com");
        strcpy(students[i++].Phone,"+91 ");

        strcpy(students[i].Name,"Aditya Tomar");
        strcpy(students[i].ID,"24011006");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 07;
        strcpy(students[i].Email,"aditya25120005@gmail.com");
        strcpy(students[i++].Phone,"+91 95203 55639");

        strcpy(students[i].Name,"Akansha");
        strcpy(students[i].ID,"24012084");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 8;
        strcpy(students[i].Email,"akanshariya604@gmail.com");
        strcpy(students[i++].Phone,"+91 82188 90552");

        strcpy(students[i].Name,"*AKHIL RANA*");
        strcpy(students[i].ID,"24011493");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 9;
        strcpy(students[i].Email,"aakhil1490497@gmail.com");
        strcpy(students[i++].Phone,"+91 7466013903");
        
        strcpy(students[i].Name,"Akshat Gairola");
        strcpy(students[i].ID,"240211637");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 10;
        strcpy(students[i].Email,"akashatgairola686@gmail.com");
        strcpy(students[i++].Phone,"+91 78199 10388");

        strcpy(students[i].Name,"Akshat Upadhyay");
        strcpy(students[i].ID,"24011036");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 11;
        strcpy(students[i].Email,"akshat221205@gmail.com");
        strcpy(students[i++].Phone,"+91 ");

        strcpy(students[i].Name,"Akshay P. Singh");
        strcpy(students[i].ID,"24011086");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 12;
        strcpy(students[i].Email,"akshaysingh9183@gmail.com");
        strcpy(students[i++].Phone,"+91 95699 19402");

        strcpy(students[i].Name,"Amaan Ansari");
        strcpy(students[i].ID,"240111390");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 13;
        strcpy(students[i].Email,"amaanansari7300@gmail.com");
        strcpy(students[i++].Phone,"+91 74548 27547");

        strcpy(students[i].Name,"Aman K. Singh");
        strcpy(students[i].ID,"240111420");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 14;
        strcpy(students[i].Email,"amansinha7251@gmail.com");
        strcpy(students[i++].Phone,"+91 82995 39210");
        
        strcpy(students[i].Name,"Anshika Mewar");
        strcpy(students[i].ID,"24012093");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 15;
        strcpy(students[i].Email,"anshikamewar10@gmail.com");
        strcpy(students[i++].Phone,"+91 78954 45698");

        strcpy(students[i].Name,"Anshul Deshwal");
        strcpy(students[i].ID,"240111386");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 16;
        strcpy(students[i].Email,"anshuldeshwal001@gmail.com");
        strcpy(students[i++].Phone,"+91 93890 88175");

        strcpy(students[i].Name,"Anshul Negi");
        strcpy(students[i].ID,"240111041");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 17;
        strcpy(students[i].Email,"anshul032111@gmail.com");
        strcpy(students[i++].Phone,"+91 74538 02344");

        strcpy(students[i].Name,"Aradhya Sharma");
        strcpy(students[i].ID,"24011080");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 18;
        strcpy(students[i].Email,"aradhyash2709@gmail.com");
        strcpy(students[i++].Phone,"+91 70178 51051");

        strcpy(students[i].Name,"Ayush Garg");
        strcpy(students[i].ID,"240111837");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 19;
        strcpy(students[i].Email,"ayyushg21@gmail.com");
        strcpy(students[i++].Phone,"+91 70177 58515");
        
        strcpy(students[i].Name,"Ayush Kapri");
        strcpy(students[i].ID,"240111210");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 20;
        strcpy(students[i].Email,"ayushkapri582@gmail.com");
        strcpy(students[i++].Phone,"+91 95480 55567");

        strcpy(students[i].Name,"Devansh Bhandari");
        strcpy(students[i].ID,"24011082");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 21;
        strcpy(students[i].Email,"devanshbhandari1126@gmail.com");
        strcpy(students[i++].Phone,"+91 70172 21557");

        strcpy(students[i].Name,"Diyanshi Uniyal");
        strcpy(students[i].ID,"24012090");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 22;
        strcpy(students[i].Email,"01diyanshi@gmail.com");
        strcpy(students[i++].Phone,"+91 82798 33628");

        strcpy(students[i].Name,"Gaurav S. Rawat");
        strcpy(students[i].ID,"240111414");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 23;
        strcpy(students[i].Email,"gaurav0206rawat@gmail.com");
        strcpy(students[i++].Phone,"+91 92590 91205");

        strcpy(students[i].Name,"Harsh Srivastava");
        strcpy(students[i].ID,"240111385");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 24;
        strcpy(students[i].Email,"harsh1209srivastava@gmail.com");
        strcpy(students[i++].Phone,"+91 70809 23074");
        
        strcpy(students[i].Name,"Harsimran Singh");
        strcpy(students[i].ID,"240111835");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 25;
        strcpy(students[i].Email,"Simarsingh54360@gmail.com");
        strcpy(students[i++].Phone,"+91 82793 82192");

        strcpy(students[i].Name,"Ishika Bhatt");
        strcpy(students[i].ID,"24012106");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 26;
        strcpy(students[i].Email,"ishikabhatt252005@gmail.com");
        strcpy(students[i++].Phone,"+91 80593 03325");

        strcpy(students[i].Name,"karan Kumar");
        strcpy(students[i].ID,"240211715");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 27;
        strcpy(students[i].Email,"kumar224.karan@gmail.com");
        strcpy(students[i++].Phone,"+91 93110 74022");

        strcpy(students[i].Name,"Karan S. Jalal");
        strcpy(students[i].ID,"240111803");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 28;
        strcpy(students[i].Email,"jalalkaran5@gmail.com");
        strcpy(students[i++].Phone,"+91 70600 60549");

        strcpy(students[i].Name,"Kartikey C. Pandey");
        strcpy(students[i].ID,"240111401");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 29;
        strcpy(students[i].Email,"kartikey2224@gmail.com");
        strcpy(students[i++].Phone,"+91 73517 63191");
        
        strcpy(students[i].Name,"Manas Sharma");
        strcpy(students[i].ID,"240111391");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 30;
        strcpy(students[i].Email,"manassharma0705@gmail.com");
        strcpy(students[i++].Phone,"+91 79834 84802");

        strcpy(students[i].Name,"Manjul Singh");
        strcpy(students[i].ID,"240111798");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 31;
        strcpy(students[i].Email,"manjulsingh261@gmail.com");
        strcpy(students[i++].Phone,"+91 63970 82172");

        strcpy(students[i].Name,"Mona Pandey");
        strcpy(students[i].ID,"240121836");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 32;
        strcpy(students[i].Email,"monapandey30720005@gmail.com");
        strcpy(students[i++].Phone,"+91 89586 14335");

        strcpy(students[i].Name,"Nikhil Kumar");
        strcpy(students[i].ID,"240111424");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 33;
        strcpy(students[i].Email,"mouryanikhil322@gmail.com");
        strcpy(students[i++].Phone,"+91 73511 97479");

        strcpy(students[i].Name,"Nirmal Tewari");
        strcpy(students[i].ID,"240111435");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 34;
        strcpy(students[i].Email,"nirmaltewaridec2006@gmail.com");
        strcpy(students[i++].Phone,"+91 84499 85523");
        
        strcpy(students[i].Name,"Noor Ashraf");
        strcpy(students[i].ID,"240212002");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 35;
        strcpy(students[i].Email,"na2183785ashraf@gmail.com");
        strcpy(students[i++].Phone,"+91 72480 07228");

        strcpy(students[i].Name,"Parth Verma");
        strcpy(students[i].ID,"24011068");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 36;
        strcpy(students[i].Email,"parthverma2608@gmail.com");
        strcpy(students[i++].Phone,"+91 93068 47998");

        strcpy(students[i].Name,"Piyush Kharola");
        strcpy(students[i].ID,"240111822");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 37;
        strcpy(students[i].Email,"kharolapiyush@gmail.com");
        strcpy(students[i++].Phone,"+91 98189 30304");

        strcpy(students[i].Name,"Pranjal S. Badwal");
        strcpy(students[i].ID,"24011073");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 38;
        strcpy(students[i].Email,"pranjalbadwal60@gmail.com");
        strcpy(students[i++].Phone,"+91 78178 74613");

        strcpy(students[i].Name,"Prashansha Dobhal");
        strcpy(students[i].ID,"24012549");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 39;
        strcpy(students[i].Email,"Prashanshadobhal06@gmail.com");
        strcpy(students[i++].Phone,"+91 63989 15336");
        
        strcpy(students[i].Name,"Prem Singh");
        strcpy(students[i].ID,"240111388");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 40;
        strcpy(students[i].Email,"premmehra87504@gmail.com");
        strcpy(students[i++].Phone,"+91 82732 5336");

        strcpy(students[i].Name,"Pritansh Patidar");
        strcpy(students[i].ID,"240211730");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 41;
        strcpy(students[i].Email,"pritanshpatidar24@gmail.com");
        strcpy(students[i++].Phone,"+91 62666 55426");

        strcpy(students[i].Name,"Priyanshi Uniyal");
        strcpy(students[i].ID,"24012085");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 42;
        strcpy(students[i].Email,"priyanshithe3@gmail.com");
        strcpy(students[i++].Phone,"+91 ");

        strcpy(students[i].Name,"Priyansu");
        strcpy(students[i].ID,"240111423");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 43;
        strcpy(students[i].Email,"priyanshuu2121@gmail.com");
        strcpy(students[i++].Phone,"+91 79831 24352");

        strcpy(students[i].Name,"Rabeena Koranga");
        strcpy(students[i].ID,"240152024");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 44;
        strcpy(students[i].Email,"rabeenakoranga21@gmail.com");
        strcpy(students[i++].Phone,"+91 76182 94287");
        
        strcpy(students[i].Name,"Rahul Negi");
        strcpy(students[i].ID,"240111387");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 45;
        strcpy(students[i].Email,"negirahul4700@gmail.com");
        strcpy(students[i++].Phone,"+91 76686 51808");

        strcpy(students[i].Name,"Ranveer Singh");
        strcpy(students[i].ID,"240111833");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 46;
        strcpy(students[i].Email,"ranveersingh54360@gmail.com");
        strcpy(students[i++].Phone,"+91 74570 72507");

        strcpy(students[i].Name,"Rishab Dimri");
        strcpy(students[i].ID,"24011047");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 47;
        strcpy(students[i].Email,"dimrir874@gmail.com");
        strcpy(students[i++].Phone,"+91 70605 70752");

        strcpy(students[i].Name,"Rishita Bijalwan");
        strcpy(students[i].ID,"24012077");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 48;
        strcpy(students[i].Email,"rishitabijalwan7@gmail.com");
        strcpy(students[i++].Phone,"+91 82182 26574");

        strcpy(students[i].Name,"Rudra Nautiyal");
        strcpy(students[i].ID,"240111812");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 49;
        strcpy(students[i].Email,"rudranautiyal8@gmail.com");
        strcpy(students[i++].Phone,"+91 75059 22708");
        
        strcpy(students[i].Name,"Saksham Nautiyal");
        strcpy(students[i].ID,"24011516");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 50;
        strcpy(students[i].Email,"Nautiyalsaksham0@gmail.com");
        strcpy(students[i++].Phone,"+91 86300 69892");

        strcpy(students[i].Name,"Samiksha Prajapati");
        strcpy(students[i].ID,"24022211");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 51;
        strcpy(students[i].Email,"Samiksha12805@gmail.com");
        strcpy(students[i++].Phone,"+91 ");

        strcpy(students[i].Name,"Sarthak Chhetri");
        strcpy(students[i].ID,"240111831");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 52;
        strcpy(students[i].Email,"sarthakchhetri06@gmail.com");
        strcpy(students[i++].Phone,"+91 78190 08017");

        strcpy(students[i].Name,"Shaurya Raj Rawat");
        strcpy(students[i].ID,"24011076");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 53;
        strcpy(students[i].Email,"shauryarajrawat2wo9ine@gmail.com");
        strcpy(students[i++].Phone,"+91 ");

        strcpy(students[i].Name,"Shikhar Joshi");
        strcpy(students[i].ID,"24011066");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 54;
        strcpy(students[i].Email,"joshixshikhar@gmail.com");
        strcpy(students[i++].Phone,"+91 63963 66769");
        
        strcpy(students[i].Name,"Shivam Rawat");
        strcpy(students[i].ID,"240111782");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 55;
        strcpy(students[i].Email,"shivamrawat25dec@gmail.com");
        strcpy(students[i++].Phone,"+91 89798 25312");
        
        strcpy(students[i].Name,"Shresth Krishali");
        strcpy(students[i].ID,"240111839");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 56;
        strcpy(students[i].Email,"shristkrishali@gmail.com");
        strcpy(students[i++].Phone,"+91 84330 41980");
        
        strcpy(students[i].Name,"Shreya Bhatt");
        strcpy(students[i].ID,"24022252");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 57;
        strcpy(students[i].Email,"bhattshreya270@gmail.com");
        strcpy(students[i++].Phone,"+91 89230 12270");

        strcpy(students[i].Name,"Shriyanshi Bhandari");
        strcpy(students[i].ID,"24022240");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 58;
        strcpy(students[i].Email,"shriyanshibhandari2020@gmail.com");
        strcpy(students[i++].Phone,"+91 92594 08792");
        
        strcpy(students[i].Name,"Shubham Mahara");
        strcpy(students[i].ID,"24011075");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 59;
        strcpy(students[i].Email,"shubhammahara54@gmail.com");
        strcpy(students[i++].Phone,"+91 80062 34737");
        
        strcpy(students[i].Name,"Sneha Sharma");
        strcpy(students[i].ID,"24022161");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 60;
        strcpy(students[i].Email,"snehasharmaa912@gmail.com");
        strcpy(students[i++].Phone,"+91 90580 64842");

        strcpy(students[i].Name,"Tarun Upadhyay");
        strcpy(students[i].ID,"240111805");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 61;
        strcpy(students[i].Email,"Upadhyaytarun713@gmail.com");
        strcpy(students[i++].Phone,"+91 80770 14179");
        
        strcpy(students[i].Name,"Vihaan S. Rawat");
        strcpy(students[i].ID,"240111779");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 62;
        strcpy(students[i].Email,"vihaanrawatuk07@gmail.com");
        strcpy(students[i++].Phone,"+91 90845 05641");

        strcpy(students[i].Name,"Vikram Shahi");
        strcpy(students[i].ID,"240211714");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 63;
        strcpy(students[i].Email,"shahivikram9899@gmail.com");
        strcpy(students[i++].Phone,"+91 77329 87011");
        
        strcpy(students[i].Name,"Vishu Stephen");
        strcpy(students[i].ID,"24011087");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 64;
        strcpy(students[i].Email,"vishustephen773@gmail.com");
        strcpy(students[i++].Phone,"+91 93690 69887");
        
        strcpy(students[i].Name,"Gargi Negi");
        strcpy(students[i].ID,"240122238");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 65;
        strcpy(students[i].Email,"garginegi024@gmail.com");
        strcpy(students[i++].Phone,"+91 79064 73257");

        strcpy(students[i].Name,"Mohammad Faiz");
        strcpy(students[i].ID,"240111916");
        strcpy(students[i].Program,"B.Tech");
        strcpy(students[i].Branch,"CSE");
        strcpy(students[i].Section,"J1");
        students[i].Semester = 02;
        students[i].RollNo = 66;
        strcpy(students[i].Email,"faizmohd0100@gmail.com");
        strcpy(students[i++].Phone,"+91 ");
        return i;
    }
    