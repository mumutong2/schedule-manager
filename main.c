#include <stdio.h>
#include <string.h>
#include <time.h>
int n,year,month,day,y,m,d,f;
char anpai[100],newanpai[100],line[200],lines[100][200];
int main()
{
    printf("欢迎使用日程安排软件！请根据您的需求输入对应数字：\n添加：1   删除：2   修改：3   提醒：4   关闭：5\n");

while(1)
{
    n=0;
    //就逻辑上而言没有意义，但能减少冲突增加稳定性。
    scanf("%d",&n);
    system("cls");
    //-----
    //非法输入
    if(n>5||n<1)printf("请按照以下要求输入！\n添加：1   删除：2   修改：3   提醒：4   关闭：5\n");
    //-----
    //添加功能
    if(n==1)
    {
        printf("请按照年、月、日、安排的顺序输入三个数字与一句文本，中间用空格分隔。\n");
        scanf("%d %d %d %s",&year,&month,&day,anpai);
        system("cls");

        FILE*file=fopen("data.txt","a");
        fprintf(file,"%d %d %d:%s\n",year,month,day,anpai);
        fclose(file);

        printf("已完成添加！您还有其他需求吗？\n添加：1   删除：2   修改：3   提醒：4   关闭：5\n");
    }
    //-----
    //删除功能
    if(n==2)
    {
        shanchu:
        printf("请按照您要删除的日程安排的年、月、日的顺序输入三个数字，中间用空格分隔。\n输入0返回。\n");
        scanf("%d",&year);

        if(year==0)
        {
            system("cls");
            printf("已返回！您还有其他需求吗？\n添加：1   删除：2   修改：3   提醒：4   关闭：5\n");
            continue;
        }

        scanf("%d %d",&month,&day);
        system("cls");

        FILE*file=fopen("data.txt","r");
        line[0]='\0';
        anpai[0]='\0';
        lines[0][0]='\0';
        f=0;

        while(fgets(line,sizeof(line),file))
        {

            if(sscanf(line,"%d %d %d:%[^\n]",&y,&m,&d,anpai)==4)
            {

                if(y==year&&m==month&&d==day)
                {
                    strcpy(lines[f],line);
                    printf("%d:%s\n",f+1,anpai);
                    f++;
                }

            }

        }

        fclose(file);

        if(!f)
        {
            printf("此日无日程安排!");
            goto shanchu;
        }

        printf("删除单个安排：输入对应编号   全部删除：0   返回：-1\n");
        scanf("%d",&n);

        if(n==-1)
        {
            system("cls");
            printf("已返回！您还有其他需求吗？\n添加：1   删除：2   修改：3   提醒：4   关闭：5\n");
            continue;
        }

        file=fopen("data.txt","r");
        FILE*temp=fopen("temp.txt","w");
        line[0]='\0';
        anpai[0]='\0';
        f=0;

        while(fgets(line,sizeof(line),file))
        {

            if(sscanf(line,"%d %d %d:%[^\n]",&y,&m,&d,anpai)==4)
            {

                if(y==year&&m==month&&d==day)
                {
                    f++;

                    if(n==0||n==f)
                    {
                        printf("已删除:%s\n",anpai);
                        continue;
                    }

                }

            }
            fputs(line,temp);

        }

        fclose(file);
        fclose(temp);

        #ifdef _WIN32
        Sleep(100);
        #endif
        //“添加一个小的延迟，确保文件句柄被释放”反正就得加。

        remove("data.txt");
        rename("temp.txt","data.txt");
        printf("已删除！您还有其他需求吗？\n添加：1   删除：2   修改：3   提醒：4   关闭：5\n");
        n=0;
    }
    //-----
    //修改功能
    if(n==3)
    {
        xiugai:
        printf("请按照您要修改的日程安排的年、月、日的顺序输入三个数字，中间用空格分隔。\n输入0返回。\n");
        scanf("%d",&year);

        if(year==0)
        {
            system("cls");
            printf("已返回！您还有其他需求吗？\n添加：1   删除：2   修改：3   提醒：4   关闭：5\n");
            continue;
        }

        scanf("%d %d",&month,&day);
        system("cls");
        FILE*file=fopen("data.txt","r");
        line[0]='\0';
        anpai[0]='\0';
        lines[0][0]='\0';
        f=0;

        while(fgets(line,sizeof(line),file))
        {

            if(sscanf(line,"%d %d %d:%[^\n]",&y,&m,&d,anpai)==4)
            {

                if(y==year&&m==month&&d==day)
                {
                    strcpy(lines[f],line);
                    printf("%d:%s\n",f+1,anpai);
                    f++;
                }

            }

        }

        fclose(file);

        if(!f)
        {
            printf("此日无日程安排!");
            goto xiugai;
        }

        printf("修改安排：输入对应编号   返回：-1\n");
        scanf("%d",&n);

        if(n==-1)
        {
            system("cls");
            printf("已返回！您还有其他需求吗？\n添加：1   删除：2   修改：3   提醒：4   关闭：5\n");
            continue;
        }

        while(getchar()!='\n');
        //清空缓冲区

        printf("请输入新的安排内容：");
        newanpai[0]='\0';

        fgets(newanpai, sizeof(newanpai), stdin);
        // 使用 fgets
        // 移除 fgets 可能读取的换行符
        newanpai[strcspn(newanpai, "\n")] = 0;

        file=fopen("data.txt","r");
        FILE*temp=fopen("temp.txt","w");
        line[0]='\0';
        anpai[0]='\0';
        f=0;

        while(fgets(line,sizeof(line),file))
        {

            if(sscanf(line,"%d %d %d:%[^\n]",&y,&m,&d,anpai)==4)
            {

                if(y==year&&m==month&&d==day)
                {
                    f++;

                    if(n==f)
                    {
                        fprintf(temp,"%d %d %d:%s\n",y,m,d,newanpai);
                    }

                    else fputs(line,temp);
                }

                else fputs(line,temp);
            }

            else fputs(line,temp);
        }

        fclose(file);
        fclose(temp);

        #ifdef _WIN32
        Sleep(100);
        #endif
        //“添加一个小的延迟，确保文件句柄被释放”反正就得加。

        remove("data.txt");
        rename("temp.txt","data.txt");
        printf("已修改！您还有其他需求吗？\n添加：1   删除：2   修改：3   提醒：4   关闭：5\n");
        n=0;
    }
    //-----
    //提醒功能
    if(n==4)
    {
        tixing:
        printf("您需要：？\n提醒今日安排：1   提醒其他日期安排：2   返回：3\n");
        scanf("%d",&n);
        system("cls");

        if(n==1||n==2)
        {

            if(n==1)
            {
                time_t t=time(NULL);
                struct tm*now=localtime(&t);
                year=now->tm_year+1900;
                month=now->tm_mon+1;
                day=now->tm_mday;
            }
            //直接输入电脑日期

            if(n==2)
            {
                printf("请按照您要提醒的日程安排的年、月、日的顺序输入三个数字，中间用空格分隔。\n");
                scanf("%d %d %d",&year,&month,&day);
                system("cls");
            }
            //手动输入想要查找的日期

            FILE*file=fopen("data.txt","r");
            line[0]='\0';
            anpai[0]='\0';
            f=0;

            while(fgets(line,sizeof(line),file))
            {

                if(sscanf(line,"%d %d %d:%[^\n]",&y,&m,&d,anpai)==4)
                {

                    if(y==year&&m==month&&d==day)
                    {
                        f++;
                        printf("%d:%s\n",f,anpai);
                    }

                }

            }

            if(!f)
            {
                printf("此日无日程安排!");
                goto tixing;
            }

            printf("以上为此日日程安排！您还有其他需求吗？\n添加：1   删除：2   修改：3   提醒：4   关闭：5\n");
        }

        if(n==3)printf("已返回！您还有其他需求吗？\n添加：1   删除：2   修改：3   提醒：4   关闭：5\n");
    }
    //-----
    //退出
    if(n==5)break;
    //-----
}
return 0;
}
