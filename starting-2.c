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
    void studentList();
    int finddigits(int *);
    void themeMenu();

    int main(){
        while(1){
            char option=0;
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
    