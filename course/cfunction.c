#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include"stu.h"
Course *cinput()
{

    Course *head,*p,*s;
    int i;
    FILE *lp;
    s=(Course *)malloc(sizeof(Course));
    head=(Course *)malloc(sizeof(Course));
    p=head;
    printf("input cno (-1 end):");
    scanf("%d",&s->cno);
    while(s->cno != -1)
    { 
	if((lp = fopen("log.log","a")) == NULL)
    { 

        printf("open the failure!\n");
        exit(0);
    }  

        printf("input course name:");
        scanf("%s",s->cname);

        printf("input course time:");
        scanf("%d",&s->time);

        printf("input creadit:");
        scanf("%d",&s->credit);

        printf("input property(1/2)");
        scanf("%d",&s->property);

        printf("how many students are allowed to class:");
        scanf("%d",&s->maxnumber);

        printf("how mant student study that class now:");
        scanf("%d",&s->reserved);
	system("date >> log.log");
        fprintf(lp,"course input");
        fprintf(lp,"\t%d \t%s \t%d \t%d \t%d \t%d \t%d ",p->cno,p->cname,p->credit,p->property,p->time,p->reserved,p->maxnumber);
        fprintf(lp,"\n");
        fclose(lp);
        printf("input cno (-1 end):");
        p->next=s;
        p=p->next;
        s=(Course *)malloc(sizeof(Course));
        scanf("%d",&s->cno);

    }
    p->next = NULL;
    return head;
}
void cput(Course *head)
{

    char str[100];
    char ita[10];
    FILE *fp;
    int i;
    Course *p;
    p=head;
    p=p->next;
    if((fp = fopen("course.txt","a")) == NULL)
    { 

        printf("open the failure!\n");
        exit(0);
    } 
    while(p != NULL)
    { 

        i=0;
        fprintf(fp,"\t%d \t%s \t%d \t%d \t%d \t%d \t%d ",p->cno,p->cname,p->credit,p->property,p->time,p->reserved,p->maxnumber);
        fprintf(fp,"\n");
        p=p->next;

    }
    fclose(fp);
}  
Course *coutput()
{
    Course *head,*p,*s;
    FILE *fp;
    s=(Course *)malloc(sizeof(Course));
    head=(Course *)malloc(sizeof(Course));
    p=head;
    if((fp = fopen("course.txt","r")) == NULL)
    {
        printf("open the failure!\n");
        exit(0);
    }
    while(fscanf(fp,"%d%s%d%d%d%d%d",&s->cno,s->cname,&s->credit,&s->property,&s->time,&s->reserved,&s->maxnumber) != EOF )
    {
        p->next=s;
        p=p->next;
        s=(Course *)malloc(sizeof(Course));
    }
    p->next=NULL;
    fclose(fp);
    return head;
}

Course *cfind(Course *head)
{
    Course *p;
    char name[30];
    printf("what course you want to find?\n");
    scanf("%s",name);
    p=head->next;
    while(p !=NULL)
    {
        if(strcmp(p->cname,name) == 0)
        {
            return p;
        }
        p=p->next;
    }
    return NULL;
}

int cdelet(Course *chead,Student *shead)
{
    FILE *lp;
    Course *p,*s;
    Student *sp;
    char cname[30];
    int cno,i,j;
    printf("input the couse that you want delet:");
    scanf("%s",cname);
    p=chead;
    while(p->next != NULL)
    {
        if(strcmp(p->next->cname,cname) == 0)
        { 
            s=p->next;
            p->next = s->next;
            s->next = NULL;
            sp=shead->next;
            while(sp != NULL)
            {
                for(i=0;i<sp->number;i++)
                {
                    if(strcmp(sp->course[i],s->cname) == 0)
                    {
                        for(j=i+1;j<sp->number;j++)
                            strcpy(sp->course[j-1],sp->course[j]);
                        sp->number --;
                    }
                }
                sp=sp->next;
            } 
            if((lp = fopen("log.log","a")) == NULL)
            {

                printf("open the failure!\n");
                exit(0);
            }
            system("date >> log.log");
            fprintf(lp,"course delet");
            fprintf(lp,"\t%d \t%s ",s->cno,s->cname);
            fprintf(lp,"\n");

            fclose(lp);
            return 1;
        }
        p=p->next;
    }
    return 0;
}

int change(Course *chead,Student *shead)
{
    FILE *lp;
    int n,flag,cno,sno,i,j,credit;
    Course *cp;
    Student *sp;
    char name[30];
    char cname[30];
    flag=1;
    cp=chead->next;
    sp=shead->next;

    printf("what course?:");
    scanf("%s",cname);
    while(cp != NULL)
    {
        if(strcmp(cp->cname,cname) == 0)
        {
            if((lp = fopen("log.log","a")) == NULL)
            {


                printf("open the failure!\n");
                exit(0);
            }

            system("date >> log.log");
            fprintf(lp,"course change");
            fprintf(lp,"\t%d \t%s \t%d \t%d \t%d \t%d \t%d ",cp->cno,cp->cname,cp->credit,cp->property,cp->time,cp->reserved,cp->maxnumber);
            fprintf(lp,"\n");

            fclose(lp);
            break;
        }
        cp=cp->next;
    } 
    if(cp == NULL)
        return 0;
    printf("what do you want to do?(1 name)(2 credit)(3 time)(4 maxnumber):");
    scanf("%d",&n);
    if(n == 1)
    {
        printf("please input new course name:");
        scanf("%s",name);
        while(sp != NULL)
        {
            for(i=0;i<sp->number;i++)
            {
                if(strcmp(sp->course[i],cp->cname) == 0)
                {
                    strcpy(sp->course[i],name);
                    break;
                }
            }
            sp=sp->next;
        }
        strcpy(cp->cname,name);
        return 1;
    }
    else if(n == 2 )
    {
        printf("please input new course credit:");
        scanf("%d",&credit);
        while(sp != NULL)
        {
            for(i=0;i<sp->number;i++)
            {

                if(strcmp(sp->course[i],cp->cname) == 0)
                    sp->credit=sp->credit-cp->credit+credit;
                break;

            }
            sp=sp->next;
        }
        cp->credit = credit;
        return 1;
    }
    else if(n == 3)
    {

        printf("please input new time:");
        scanf("%d",&cp->time);
        return 1;

    }
    else if(n == 4)
    {

        printf("please input new maxnumber:");
        scanf("%d",&cp->maxnumber);
        return 1;
    }
    else
        printf("input error!\n");
    return 0;
}



