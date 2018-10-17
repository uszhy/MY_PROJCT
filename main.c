#include<stdio.h>
#include"stu.h"

int main()
{
    FILE *sf,*cf;
    int i,j,n,sno,cno,flag,start;
    Course *chead,*cp,*cc;
    Student *shead,*sp,*ss;
    system("clear");
    start=1;
    while(start == 1)
    {

        system("clear");
        chead=coutput();
        shead=soutput();
        printf("which part do you want to do\n1:student\n2:course\n");
        scanf("%d",&n);
        if(n == 1)
        {   
            system("clear");
            printf("what are you want to do?\n1:input\n2:delete\n3:find\n4:change\n");
            scanf("%d",&i);
            if(i == 1 )
            { 
                system("clear");

                sp=sinput(chead);

                puttxt(sp);
                shead=soutput();
            }
            else if(i == 2)
            {
                system("clear");
                flag=sdelet(shead,chead);
                if(flag == 1)
                    printf("success!\n");
                else
                    printf("failed!\n");
            } 
            else if(i == 3)
            {
                system("clear");
                ss=sfind(shead);
                if(ss == NULL)
                    printf("not find!\n");
                else
                {
                    printf("sno\tname\tcredit\tcourse\t\n");
                    printf("%d\t%s\t%d\t",ss->sno,ss->name,ss->credit);
                    for(i=0;i<ss->number;i++)
                    {
                        printf("%s\t",ss->course[i]);
                    }
                    printf("\n");
                }
            }
            else if(i == 4)
            {
                system("clear");
                flag=schange(shead,chead);
                if(flag==1)
                    printf("success!\n");
                else
                    printf("faile!\n");

            }
            else
                printf("input error!\n");
        } 
        else if(n == 2)
        {
            system("clear");
            printf("what are you want to do?\n1:input\n2:delete\n3:find\n4:change\n");
            scanf("%d",&j);
            if(j == 1)
            { 
                system("clear");
                cp=cinput();
                cput(cp);
                chead = coutput();

            }
            else if(j==2)
            {
                system("clear");
                flag=cdelet(chead,shead);
                if(flag == 1)
                    printf("success!\n");
                else
                    printf("failed!\n");
            }
            else if(j == 3)
            {
                system("clear");
                cc=cfind(chead);
                if(cc == NULL)
                    printf("not find!\n");
                else
                {

                    printf("cno\tcname\tcredit\tproperty\ttime\treserved\tmaxnumber\t\n");
                    printf("\t%d \t%s \t%d \t%d \t%d \t%d \t%d ",cc->cno,cc->cname,cc->credit,cc->property,cc->time,cc->reserved,cc->maxnumber);

                    printf("\n");
                } 
            }
            else if(j == 4)
            {
                system("clear");
                flag=change(chead,shead);
                if(flag == 1)
                    printf("success!\n");
                else
                    printf("failed!\n");
            }
            else 
                printf("input error!\n");
        }  
        else 
            printf("input error!\n");
        printf("do you want to start again?(1/0)\n");
        scanf("%d",&start);
    

        if((cf = fopen("course.txt","w")) == NULL)
        { 

            printf("open the failure\n");
            return 0;
        }
        cp=chead->next;
        while(cp != NULL)
        { 
            fprintf(cf,"\t%d \t%s \t%d \t%d \t%d \t%d \t%d ",cp->cno,cp->cname,cp->credit,cp->property,cp->time,cp->reserved,cp->maxnumber);
            fprintf(cf,"\n");
            cp=cp->next;
        }
        fclose(cf);
        if((sf = fopen("student.txt","w")) == NULL)
        {  

            printf("open the failure\n");
            return 0;
        }
        sp=shead->next;
        while(sp != NULL)
        {
            fprintf(sf,"\t%d \t%s \t%d \t%d",sp->sno,sp->name,sp->credit,sp->number);
            for(i=0 ; i< sp->number ; i++)
            {

                fprintf(sf,"\t%s ",sp->course[i]);
            }
            fprintf(sf,"\n");
            sp=sp->next;
        }
        fclose(sf);
    }
    return 0;
}
