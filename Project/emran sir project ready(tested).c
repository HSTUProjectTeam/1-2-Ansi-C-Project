#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>

int work_day=0,student_no;
char name_ins[60],name_dept[35],semester[5],course_tittle[30],course_code[10],file_name[30],student_num[40],stu_information[50],ins_information[50],table[50];
int level,session;


float course_credit;
FILE *fp_input,*fp_information;
struct student
{
    char name[30];
    int id,cnt;
    float parcent,marks;
};
struct student stu[100000];

void get_data(int m) //only get the student id and attendance.
{
    FILE *fp;
    fp=fopen(stu_information,"r");
    for(int i=0; i<m; i++)
    {
        fscanf(fp,"%d\n",&stu[i].id);
        fscanf(fp,"%d\n",&stu[i].cnt);
        //printf("ID=%d cnt=%d\n",stu[i].id,stu[i].cnt);
    }
    fscanf(fp,"%d\n",&work_day);
    //printf("work_day=%d\n",work_day);
    fclose(fp);
}
void put_data(int m) //putting the student ID and attendance in file input.
{
    FILE *fp;
    fp=fopen(stu_information,"w");
    for(int i=0; i<m; i++)
    {
        //printf("%d %d\n",stu[i].id,stu[i].cnt);
        fprintf(fp,"%d\n",stu[i].id);
        fprintf(fp,"%d\n",stu[i].cnt);
    }
    //printf("%d\n",work_day);
    fprintf(fp,"%d\n",work_day);
    fclose(fp);
}
void input_present(int n)
{
    int temp=n;
    printf("\n\t\t\t\tPlease enter today's date:\n\t\t\t\tN:B: The format is: DD/MM/YYYY\n");
    int day,month,year;
    char a,b;
    printf("\t\t\t\t");
    scanf("%d %c %d %c %d",&day,&a,&month,&b,&year);
    get_data(temp);//call the function get data which takes data from file input.
    printf("\n\t\t\t\tPlease follow the instructions:\n\t\t\t\tWe will show you the student ID of each student.\n\t\t\t\tPress-\n");
    printf("\t\t\t\t           1 : If the student is present,\n\t\t\t\t0 or any key : If the student is not present.\n");
    for(int i=0; i<n; i++)
    {
        printf("\n\t\t\t\tID:%d:",stu[i].id);
        int press;
        //printf("\t\t\t\t\t\t\t\t\t\t");
        scanf("%d",&press);
        if(press==1)
        {
            stu[i].cnt++;
        }
    }
    work_day=work_day+1;
    put_data(n);
}

void get_information(int m)//may have a problem
{
    FILE *fp;
    char x1,x2,x3,x4;
    fp=fopen(ins_information,"r");

    fscanf(fp,"%[^\n]",name_ins);
    //printf("name_ins=%s\n",name_ins);
    fscanf(fp,"%c",&x1);

    fscanf(fp,"%[^\n]",name_dept);
    //printf("name_dept=%s\n",name_dept);
    fscanf(fp,"%c",&x2);

    fscanf(fp,"%d",&level);
    //printf("level=%d\n",level);

    fscanf(fp,"%s",semester);
    //printf("semester=%s\n",semester);

    fscanf(fp,"%d",&session);
    //printf("session=%d\n",session);

    fscanf(fp,"%c",&x3);
    fscanf(fp,"%[^\n]",course_tittle);
    //printf("course_tittle=%s\n",course_tittle);

    fscanf(fp,"%c",&x4);
    fscanf(fp,"%[^\n]",course_code);
    //printf("course_code=%s\n",course_code);

    fscanf(fp,"%f",&course_credit);
    //printf("course_credit=%f\n",course_credit);

    for(int i=0; i<m; i++)
    {
        char x;
        fscanf(fp,"%c",&x);
        fscanf(fp,"%[^\n]",stu[i].name);
        //printf("name %d: %s\n",i+1,stu[i].name);
    }

    fclose(fp);
}
void calculation(int x)//may have a problem
{
    for(int i=0; i<x; i++)
    {
        stu[i].parcent=((float)stu[i].cnt/work_day)*100;
        stu[i].marks=(stu[i].parcent*((course_credit*50)/10))/100;
        if(work_day==0)
        {
            stu[i].parcent=0;
            stu[i].marks=0;
        }
    }
}
void show_table(int n)//may have a problem
{
    int tmp=n;
    get_information(tmp);
    get_data(tmp);
    calculation(tmp);

    FILE *fp_table;
    fp_table=fopen(table,"a");
    void loop1()
    {
        printf("\t     ");
        fprintf(fp_table,"     ");
        for(int i=0; i<90; i++)
        {
            printf("-");
            fprintf(fp_table,"-");
        }
        printf("\n");
        fprintf(fp_table,"\n");
    }
    void loop2()
    {
        printf("\t     ");
        fprintf(fp_table,"     ");
        for(int i=0; i<90; i++)
        {
            printf("_");
            fprintf(fp_table,"_");
        }
        printf("\n");
        fprintf(fp_table,"\n");
    }

    loop2();
    char table[]="Information table";
    printf("\t     |                                    %-52s|\n",table);
    fprintf(fp_table,"     |                                    %-52s|\n",table);

    loop1();
    printf("\t     | Institute Name : %-70s|\n",name_ins);
    fprintf(fp_table,"     | Institute Name : %-70s|\n",name_ins);

    loop1();
    printf("\t     | Department Name: %-70s|\n",name_dept);
    fprintf(fp_table,"     | Department Name: %-70s|\n",name_dept);

    loop1();
    printf("\t     | Level : %-18d| Semester : %-18s| Session : %-18d|\n",level,semester,session);
    fprintf(fp_table,"     | Level : %-18d| Semester : %-18s| Session : %-18d|\n",level,semester,session);

    loop1();
    printf("\t     | Course Tittle : %-71s|\n",course_tittle);
    fprintf(fp_table,"     | Course Tittle : %-71s|\n",course_tittle);

    loop1();
    printf("\t     | Course Code : %-28s| Course Credit : %-27.2f|\n",course_code,course_credit);
    fprintf(fp_table,"     | Course Code : %-28s| Course Credit : %-27.2f|\n",course_code,course_credit);

    loop1();
    printf("\t     | Total Class days : %-68d|\n",work_day);
    fprintf(fp_table,"     | Total Working day : %-67d|\n",work_day);

    loop1();
    char temp[]="\0";
    printf("\t     |%-88s|\n",temp);
    fprintf(fp_table,"     |%-88s|\n",temp);

    char s_inform[]="Student's Information";
    loop1();
    printf("\t     |                                  %-54s|\n",s_inform);
    fprintf(fp_table,"     |                                  %-54s|\n",s_inform);

    loop1();
    printf("\t     |SL No| Name Of The Student | Student ID | Total Present |Present Percentage |Total Mark |\n");
    fprintf(fp_table,"     |SL No| Name Of The Student | Student ID | Total Present |Present Percentage |Total Mark |\n");
    //fprintf(fp_table,"     | Name Of The Student     | Student ID   | Total Present | Present Percentage| Total Mark|\n");

    for(int i=0; i<n; i++)
    {
        loop1();
        printf("\t     | %-4d| %-20s| %-11d| %-14d| %-17.2f%%| %-10.2f|\n",i+1,stu[i].name,stu[i].id,stu[i].cnt,stu[i].parcent,stu[i].marks);
        fprintf(fp_table,"     | %-4d| %-20s| %-11d| %-14d| %-17.2f%%| %-10.2f|\n",i+1,stu[i].name,stu[i].id,stu[i].cnt,stu[i].parcent,stu[i].marks);
        //fprintf(fp_table,"     | %-24s| %-13d| %-14d| %-17.2f%%| %-10.2f|\n",stu[i].name,stu[i].id,stu[i].cnt,stu[i].parcent,stu[i].marks);
    }
    loop2();
}

void scan_all_information()//taking all information from keyboard
{
    ///printf("\n\tWelcome to Digital Attendance Taking System...!!\n");
    printf("\t\t\t\tPlease enter the information correctly:\n\n\t\t\t\tInstitution name:");
    fp_information=fopen(ins_information,"w");
    char x1,x2,x3,x4,x5;
    scanf("%[^\n]",name_ins);
    scanf("%c",&x1);
    fprintf(fp_information,"%s",name_ins);
    //scanf("%c",&x1);
    fprintf(fp_information,"%c",x1);

    //scanf("%c",&x5);
    printf("\n\t\t\t\tDepartment name:");
    scanf("%[^\n]",name_dept);
    fprintf(fp_information,"%s",name_dept);
    scanf("%c",&x2);
    fprintf(fp_information,"%c",x2);

    printf("\n\t\t\t\tLevel:");
    scanf("%d",&level);
    fprintf(fp_information,"%d\n",level);

    printf("\n\t\t\t\tSemester:");
    scanf("%s",semester);
    fprintf(fp_information,"%s\n",semester);

    printf("\n\t\t\t\tSession:");
    scanf("%d",&session);
    fprintf(fp_information,"%d\n",session);

    printf("\n\t\t\t\tCourse tittle:");
    scanf("%c",&x3);
    scanf("%[^\n]",course_tittle);
    fprintf(fp_information,"%s",course_tittle);
    fprintf(fp_information,"%c",x3);

    scanf("%c",&x5);
    printf("\n\t\t\t\tCourse code:");
    scanf("%[^\n]",course_code);
    //scanf("%c",&x4);
    fprintf(fp_information,"%s\n",course_code);
    //fprintf(fp_information,"%c",x4);

    printf("\n\t\t\t\tCourse credit:");
    scanf("%f",&course_credit);
    fprintf(fp_information,"%f\n",course_credit);//end of taking information.



    FILE *fp_stu=fopen(student_num,"w");//extra file for student no.
    printf("\n\t\t\t\tNo of student:");
    scanf("%d",&student_no);
    fprintf(fp_stu,"%d\n",student_no);
    fclose(fp_stu);

    fp_input=fopen(stu_information,"w");//start taking input.
    printf("\n\t\t\t\tPlease give the information of each student.\n");
    printf("\t\t\t\tN:B: You must give the information of the student in ascending order.\n\t\t\t\tPlease input the information carefully,\n\t\t\t\tbecause there is no chance to correct the data later.\n");

    for(int i=0; i<student_no; i++)
    {
        printf("\n\t\t\t\tStudent No : %d\n",i+1);
        char x,x1;
        scanf("%c",&x1);
        printf("\t\t\t\tName:");
        scanf("%[^\n]",stu[i].name);
        fprintf(fp_information,"%s %c",stu[i].name,x1);//names are assign in information file
        scanf("%c",&x);

        printf("\t\t\t\tID:");
        scanf("%d",&stu[i].id);
        fprintf(fp_input,"%d\n",stu[i].id);
        stu[i].cnt=0;
        fprintf(fp_input,"%d\n",stu[i].cnt);//ID's and cnt are assign in input file
    }
    fprintf(fp_input,"0",work_day);
    //close file
    fclose(fp_information);
    fclose(fp_input);
}

int main()
{
    system("color 4F");
    printf("\n\n\n\n\t\t\t\tWelcome to Digital Attendance Taking System..!!\n");
main_1st:
    printf("\n\t\t\t\tPlease follow the instructions:\n");
    printf("\t\t\t\tPress:\n\t\t\t\t\t1 : To create a new file,\n\t\t\t\t\t2 : To work on a already created file,\n\t\t\t       or any key : To exit the program.\n");
    int press;
    printf("\t\t\t\t");
    scanf("%d",&press);
    if(press==1)
    {
        goto new_file;
    }
    else if(press==2)
    {
        goto search_file;
    }
    else{
        printf("\t\t\t\tThank you for being here..!!\n");
        exit(0);
    }
    new_file:
        {
            int cnt=0;
            FILE *fp;
            printf("\n\t\t\t\tPlease enter the filename, which you want to create.\n\t\t\t\tN:B: Space is not allowed.\n");
            exist_file:
            printf("\t\t\t\t");
            scanf("%s",file_name);
            char ch;
            scanf("%c",&ch);
            strcpy(ins_information,file_name);
            strcat(ins_information,"_ins_information.txt");
            strcpy(stu_information,file_name);
            strcat(stu_information,"_stu_information.txt");
            strcpy(student_num,file_name);
            strcat(student_num,"_student_no.txt");
            strcpy(table,file_name);
            strcat(table,"_table.txt");
            fp=fopen(stu_information,"r");
            fclose(fp);
            if(fp!=NULL)
            {
                printf("\t\t\t\tThis file is already exist..!\n");
                cnt++;
                if(cnt%5==0)
                {
                    printf("\n\t\t\t\t\aYou input wrong filename %d times.\n\t\t\t\tAre you want to go main menu?\n\tPress-\n\t\t\t\t\t1 : To go main menu,\n\t\t\t\t\t2 : To input filename again,\n\t\t\t       or any key : To exit the program.\n\n",cnt);
                    int press1;
                    printf("\t\t\t\t");
                    scanf("%d",&press1);
                    if(press1==1)
                    {
                        goto main_1st;
                    }
                    else if(press1==2)
                    {
                        printf("\n\t\t\t\tPlease input another filename:\n");
                        goto exist_file;
                    }
                    else{
                        printf("\t\t\t\tThanks for being here..!!\n");
                        exit(0);
                    }
                }
                printf("\n\t\t\t\tPlease input another filename.\n");
                goto exist_file;
            }
            else{
                printf("\t\t\t\tYour new file created successfully..!!\n");
                scan_all_information();
                printf("\t\t\t\tAll inputs are taken successfully..!\n");
                goto main_menu;
            }
        }
    search_file:
        {
            int cnt=0;
            FILE *fp;
            printf("\n\t\t\t\tPlease enter the filename, which you want to open.\n\t\t\t\tN:B: Space is not allowed.\n");
            again_filename:
            printf("\t\t\t\t");
            scanf("%s",file_name);
            char ch;
            scanf("%c",&ch);
            strcpy(ins_information,file_name);
            strcat(ins_information,"_ins_information.txt");
            strcpy(stu_information,file_name);
            strcat(stu_information,"_stu_information.txt");
            strcpy(student_num,file_name);
            strcat(student_num,"_student_no.txt");
            strcpy(table,file_name);
            strcat(table,"_table.txt");
            fp=fopen(stu_information,"r");
            fclose(fp);
            if(fp==NULL)
            {
                printf("\t\t\t\tThis file is not exist..!\n");
                cnt++;
                if(cnt%5==0)
                {
                    printf("\n\t\t\t\t\aYou input wrong filename %d times.\n\t\t\t\tAre you want to go main menu?\n\t\t\t\t\t\t\t\t\t\tPress-\n\t\t\t\t\t\t\t\t\t\t\t1 : To go main menu,\n\t\t\t\t\t\t\t\t\t\t\t2 : To search filename again.\n\t\t\t\t\t\t\t\t\t       or any key : To exit the program.\n",cnt);
                    int press1;
                    printf("\t\t\t\t");
                    scanf("%d",&press1);
                    if(press1==1)
                    {
                        goto main_1st;
                    }
                    else if(press1==2)
                    {
                        printf("\n\t\t\t\tPlease input the filename correctly:\n");
                        goto again_filename;
                    }
                    else{
                        printf("\t\t\t\tThanks for being here..!!\n");
                        exit(0);
                    }
                }
                printf("\n\t\t\t\tPlease input the filename correctly.\n");
                goto again_filename;
            }
            else{
                printf("\t\t\t\tYour file is exist..!\n");
                goto main_menu;
            }
        }
    main_menu:
        {
            printf("\n\t\t\t\tPlease follow the instructions:\n");
            printf("\t\t\t\tPress-\n\t\t\t\t\t1 : To take the attendance,\n\t\t\t\t\t2 : To see the student's table,\n\t\t\t\t\t3 : To add another attendance file,\n\t\t\t\t\t4 : To delete the file,\n\t\t\t       or any key : To exit the program.\n");
            int press2;
            printf("\t\t\t\t");
            scanf("%d",&press2);
            if(press2==1)
            {
                goto take_present;
            }
            else if(press2==2)
            {
                goto attendance_table;
            }
            else if(press2==3)
            {
                goto new_file;
            }
            else if(press2==4)
            {
                goto delete_file;
            }
            else{
                printf("\t\t\t\tThanks for being here..!!\n");
                exit(0);
            }
        }
    take_present:
        {
            FILE *fp;
            fp=fopen(student_num,"r");
            fscanf(fp,"%d\n",&student_no);
            fclose(fp);
            input_present(student_no);
            printf("\n\t\t\t\tAttendance is taken successfully..!!\n");
            printf("\t\t\t\tPlease follow the instructions:\n");
            printf("\t\t\t\tPress-\n\t\t\t\t\t1 : To show the attendance table,\n\t\t\t\t\t2 : To add new file,\n\t\t\t\t\t3 : To delete the file,\n\t\t\t       or any key : To exit the program\n");
            int press3;
            printf("\t\t\t\t");
            scanf("%d",&press3);
            if(press3==1)
            {
                goto attendance_table;
            }
            else if(press3==2)
            {
                goto new_file;
            }
            else if(press3==3)
            {
                goto delete_file;
            }
            else{
                printf("\t\t\t\tThanks for being here..!!\n");
                exit(0);
            }
        }
    attendance_table:
        {
            FILE *fp;
            fp=fopen(student_num,"r");
            fscanf(fp,"%d\n",&student_no);
            fclose(fp);
            show_table(student_no);
            printf("\n\t\t\t\tPlease follow the instructions:\n");
            printf("\t\t\t\tPress-\n\t\t\t\t\t1 : To take the attendance,\n\t\t\t\t\t2 : To add new file,\n\t\t\t\t\t3 : To delete the file,\n\t\t\t       or any key : To exit the program\n");
            int press3;
            printf("\t\t\t\t");
            scanf("%d",&press3);
            if(press3==1)
            {
                goto take_present;
            }
            else if(press3==2)
            {
                goto new_file;
            }
            else if(press3==3)
            {
                goto delete_file;
            }
            else{
                printf("\t\t\t\tThanks for being here..!!\n");
                exit(0);
            }
        }
    delete_file:
        {
            printf("\n\t\t\t\tN:B: All the data of the file will be removed..!\n\t\t\t\tAre you sure to delete the file?\n\tPress-\n\t\t\t\t\t1 : To sure delete this file,\n\t\t\t       or any key : To skip.\n");
            int press5;
            printf("\t\t\t\t");
            scanf("%d",&press5);
            if(press5==1)
            {
                remove(ins_information);
                remove(stu_information);
                remove(student_num);
                remove(table);
                printf("\t\t\t\tYou are successfully delete this file.\n");
            }
            else{
                printf("\t\t\t\tYour file is skipped...!!\n");
            }
            printf("\t\t\t\tPlease follow the instructions:\n");
            printf("\t\t\t\tPress-\n\t\t\t\t\t1 : To create a new file,\n\t\t\t\t\t2 : To go home menu,\n\t\t\t       or any key : To exit the program\n");
            int press3;
            printf("\t\t\t\t");
            scanf("%d",&press3);
            if(press3==1)
            {
                goto new_file;
            }
            else if(press3==2)
            {
                goto main_1st;
            }
            else{
                printf("\t\t\t\tThanks for being here..!!\n");
                exit(0);
            }
        }
        return 0;
}


