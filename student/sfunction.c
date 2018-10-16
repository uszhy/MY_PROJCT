#include<stdio.h>
#include"stu.h"
#include<stdlib.h>

#include<string.h>
Student *sinput(Course *chead)
{
    Course *cp;
    Student *head,*p,*s;
    FILE *lp;
    int i;
    cp=chead->next;
    s=(Student *)malloc(sizeof(Student));
    head=(Student *)malloc(sizeof(Student));
    p=head;
   
    printf("input sno (-1 end):");
    scanf("%d",&s->sno);
    while(s->sno != -1)
    {
	 if((lp = fopen("log.log","a")) == NULL)
    { 
        printf("open the failure!\n");
        exit(0);
    }
        s->credit = 0;
        printf("input name:");
        scanf("%s",s->name);

        printf("input course number");
        scanf("%d",&s->number);

        printf("please input course name:\n");
        for( i = 0 ; i < s->number ; i++ )
        {
            scanf("%s",s->course[i]);
            while(cp != NULL)
            {
                if(strcmp(s->course[i],cp->cname)== 0)
                {
                    s->credit+=cp->credit;
                    cp->reserved ++;
                    break;
                }
                cp=cp->next;
            }
            if(cp == NULL)
            {
                printf("course input error!\n");
                i--;
            } 

            cp=chead->next;
        }
        fprintf(lp,"student input");
        system("date >> log.log");
        fprintf(lp,"\t%d \t%s \t%d \t%d",s->sno,s->name,s->credit,s->number);
        for(i=0 ; i< s->number ; i++)
        {

            fprintf(lp,"\t%s ",s->course[i]);
        }
        fprintf(lp,"\n");
        fclose(lp);
        printf("input sno (-1)end:");
        p->next=s;
        p=p->next;
        s=(Student *)malloc(sizeof(Student));
        scanf("%d",&s->sno);
    }
    p->next=NULL;
    fclose(lp);

    return head;
}
void puttxt(Student *head)
{  
    char str[100];
    char ita[10];
    FILE *fp,*lp;
    int i;
    Student *p;
    p=head;
    p=p->next;

    if((fp = fopen("student.txt","a")) == NULL)
    {  
        printf("open the failure!\n");
        exit(0);
    } 
    while(p != NULL)
    {  

        i=0;
        fprintf(fp,"\t%d \t%s \t%d \t%d",p->sno,p->name,p->credit,p->number);
        for(i=0 ; i< p->number ; i++)
        {
            fprintf(fp,"\t%s ",p->course[i]);
        }
        fprintf(fp,"\n");
        p=p->next;

    }

    fclose(fp);
}
Student *soutput()
{
    Student *head,*p,*s;
    FILE *fp;
    int i;
    s=(Student *)malloc(sizeof(Student));
    head=(Student *)malloc(sizeof(Student));
    p=head;
    if((fp = fopen("student.txt","r")) == NULL)
    {
        printf("open the failure!\n");
        exit(0);
    }
    while(fscanf(fp,"%d%s%d%d",&s->sno,s->name,&s->credit,&s->number) != EOF )
    {
        for(i=0;i<s->number;i++)
        {
            fscanf(fp,"%s",s->course[i]);
        }
        p->next=s;
        p=p->next;
        s=(Student *)malloc(sizeof(Student));
    }
    p->next=NULL;
    fclose(fp);
    return head;
}

Student *sfind(Student *head)
{ 
    char name[30];
    Student *p;
    printf("what student you want to find?\n");
    scanf("%s",name);
    p=head->next;
    while(p !=NULL)
     {
        if(strcmp(p->name,name) == 0)
         {
            return p;
        }
        p=p->next;
    }
    return NULL;
}

int sdelet(Student *shead,Course *chead)
{  
    FILE *lp;
    Student *p,*s;
    Course *cp;
    char name[30];
    int sno,i;
    printf("input the name that you want delet:");
    scanf("%s",name);
    p=shead;
    while(p->next != NULL)
     {
        if(strcmp(p->next->name,name) == 0)
        { 
            s=p->next;
            p->next = s->next;
            s->next=NULL;
            cp = chead->next;
            for(i=0;i<s->number;i++)
            {
                while(cp !=NULL)
                {
                    if(strcmp(cp->cname,s->course[i]) == 0)
                        cp->reserved --;
                    cp=cp->next;
                }
                cp=chead->next;
            }
            if((lp = fopen("log.log","a")) == NULL)
            { 
                printf("open the failure!\n");
                exit(0);
            }
            system("date >> log.log");
            fprintf(lp,"student delet ");
            i=0;
            fprintf(lp,"\t%d \t%s \t%d \t%d",s->sno,s->name,s->credit,s->number);
            for(i=0 ; i< s->number ; i++)
            {

                fprintf(lp,"\t%s ",s->course[i]);
            }
            fprintf(lp,"\n");
            fclose(lp);
            return 1;
         }
        p=p->next;
    } 
    return 0;
} 

int schange(Student *shead,Course *chead)
{
    FILE *lp;
    int n,flag,cno,sno,i,j;
    Course *cp;
    Student *sp;
    char sname[30],cname[30];;
    flag=1;
    cp = chead->next;
    sp = shead->next;

    printf("who ?:");
    scanf("%s",sname);
    while(sp != NULL)
    { 

        if(strcmp(sp->name,sname) == 0)
        {
            if((lp = fopen("log.log","a")) == NULL)
            {

                printf("open the failure!\n");
                exit(0);
            }
            system("date >> log.log");
            fprintf(lp,"student changed ");
            i=0;
            fprintf(lp,"\t%d \t%s \t%d \t%d",sp->sno,sp->name,sp->credit,sp->number);
            for(i=0 ; i< sp->number ; i++)
            {


                fprintf(lp,"\t%s ",sp->course[i]);
            }
            fprintf(lp,"\n");
            fclose(lp);
            break;
        }
        sp=sp->next;
    } 
    if(sp == NULL)
        return 0;

    printf("what do you want to do?(1 delet course)(2 add course):");
    scanf("%d",&n);
    if(n == 1)
    {
        while(flag!=0)
        {
            printf("please input the course that you want delet:");
            scanf("%s",cname);
            while(cp != NULL)
            {

                if(strcmp(cname,cp->cname) == 0)
                { 
                    for(i=0;i<sp->number ;i++)
                     {

                        if(strcmp(sp->course[i],cp->cname) == 0)
                        {
                            for(j=i+1;j<sp->number;j++)
                                strcpy(sp->course[j-1],sp->course[j]);
                            sp->number --;
                            sp->credit=sp->credit - cp->credit;
                            break;
                        }
                    }
                    cp->reserved --;
                    break;
                }
                cp=cp->next;
            } 
            if(cp == NULL)
                return 0;
            cp=chead->next;
            printf("please input the cno that you want delet(0end):");
            scanf("%d",&cno);
            if(cno == 0)
                flag=0;
        }
        return 1;
    } 
    else if(n == 2)
    {   
        while(flag != 0)
        {
            printf("please input the course that you add:");
            scanf("%s",cname);
            while(cp !=NULL && strcmp(cp->cname,cname) != 0)
                cp=cp->next;
            if(cp == NULL)
                return 0;
            strcpy(sp->course[sp->number],cp->cname);
            sp->number ++;
            cp->reserved ++;
            sp->credit=sp->credit + cp->credit;
            cp=chead->next;
            printf("please input the cno that you want add(0 end): ");
            scanf("%d",&cno);
            if(cno == 0)
                flag=0;
         }
        return 1;
    }  
    else
    {
        printf("input error!\n");
    }
    return 0;
}


