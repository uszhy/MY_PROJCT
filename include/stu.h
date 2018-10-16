#ifndef STUD
#define STUD
typedef struct stu{
    int sno;
    int number;
    int credit;
    char name[30];
    char course[10][20];

    struct stu *next;
}Student;
typedef struct cou{
    int cno;
    int time;
    int credit;
    int maxnumber;
    int property;
    int reserved;
    char cname[30];
    struct cou *next;
}Course;

Course *cinput();
void cput(Course *head);
Course *coutput();
Course *cfind(Course *head);
int cdelet(Course *chead,Student *shead);
int change(Course *chead,Student *shead);

Student *sinput(Course *chead);
void puttxt(Student *head);
Student *soutput();
Student *sfind(Student *head);
int sdelet(Student *shead,Course *chead);
int schange(Student *shead,Course *chead);

#endif
