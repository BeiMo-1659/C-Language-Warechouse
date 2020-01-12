#include <stdio.h>  
#include <string.h> 
#include<math.h>
#include <stdlib.h>  
#include <windows.h>  
#define L 64
#define N  21
#define M 1024
#define LEN sizeof(struct student)
int count=0,j,i,k;
struct student
 {
     char stu_name [L];                          ///姓名
     char sex[4];                                ///性别
     char stu_num[L];                            ///学号
     float stu_ach[N];                           ///成绩数组
     float total;                                ///总分
     struct student *next;
     char linefeed;
 }stu_info[M];//结构体变量							
char *wipeoff(char *s);
int Read_StuFile(int m,int n,char filename[L]);     ///用来去掉传入路径的双引号的函数
int Add_StuInfo(int m,int n,char filename[L]);		///查看存储学生信息文件的信息
int Stu_NumQuery(int m,int n,char filename[L]);		///添加学生的信息及成绩
int Stu_NameQuery(int m,int n,char filename[L]);	///按学号查询学生信息及成绩 
int Stu_print(int m,int n,char filename[L]);		///按姓名查找学生信息及成绩
int Delete_StuInfo(int m,int n,char filename[L]);	///把学生信息及成绩输出到屏幕
int Update_StuInfo(int m,int n,char filename[L]);	///删除学生的信息及成绩
int Stu_Ascending(int m,int n,char filename[L]);	///修改学生的成绩，不可修改信息 
int Stu_Descending(int m,int n,char filename[L]);	///学生总成绩升序排序
int Stu_AchAna(int m,int n,char filename[L]);		///学生总成绩降序排序
int Average_Scort(int m,int n,char filename[L]);	///学生成绩等级分析
int Stu_PerAna(int m,int n,char filename[L]);		///各课总成绩和平均分
int Derive_Stu_into(int m,int n,char filename[L]);	///各学生的总成绩和平均分
													/// 把学生所有信息及成绩到文本文件，文本文件的命名方式为存储信息文件的.txt文件
 char *wipeoff(char *s){
    int i,len;
    len=strlen(s);
    for(i=1;i<len-1;i++){
        s[i-1]=s[i];
    }
    s[i-1]='\0';
    return s;
}
int Read_StuFile(int m,int n,char filename[L]){
struct student card;
	FILE *fp;
	count=0;
	fp=fopen(filename,"rb");
	if(fp==NULL){
		printf("=====文件打开失败！=====\n");                                  ///打开失败则提示打开失败
        return 0;
	}
	 printf("=====文件打开成功！=====\n\n");                                ///成功则提示成功
        
          /*读取信息文件存入结构体数组*/
         while((fread(&card,LEN,1,fp))!=(int)NULL)
         {
             strcpy(stu_info[i].stu_num,card.stu_num);
             strcpy(stu_info[i].stu_name,card.stu_name);
             for(j=0;j<n;j++)
                 stu_info[i].stu_ach[j]=card.stu_ach[j];
            stu_info[i].total=card.total;
             count++;
         }
         /*判断文件中的学生的个数，并输出相应的提示信息*/
         if(count<m)

             printf("=====已经录入学生信息的有%d人，还需录入%d人的信息=====\n",count,m-count);
         else if(count==m)
             printf("=====已经录入学生信息的有%d人，已经将所有成绩信息录入完毕=====\n",count);
             else
             {
                 printf("=====录入学生信息大于输入的学生总数，系统将自行关闭，请检查信息后再次进入！=====");
                 getchar();
                 exit(1);
             }
         fclose(fp);
         return count;
	
}
int Add_StuInfo(int m,int n,char filename[L]){
	    struct student vessel;
		FILE *fp;
		count=0;
		fp=fopen(filename,"ab+");
	    if(fp==NULL){
		printf("=====文件%s打开失败！=====\n",filename);                                  ///打开失败则提示打开失败
        return 0;
	   }
		while((fread(&vessel,LEN,1,fp))!=(int)NULL)
         {   
             strcpy(stu_info[i].stu_num,vessel.stu_num);
             strcpy(stu_info[i].stu_name,vessel.stu_name);
			 strcpy(stu_info[i].sex,vessel.sex);
			 stu_info[i].linefeed=vessel.linefeed;
             for(j=0;j<n;j++)
                 stu_info[i].stu_ach[j]=vessel.stu_ach[j];
            stu_info[i].total=vessel.total;
             count++;
         }
		 if(count<m)
         {
             printf("=====已经录入学生信息的有%d人，还需录入%d人的信息=====\n",count,m-count);
             printf("<<<< 注：录入信息时，如果想中途停止输入,以后再进行补录，请将学号输为-1,谢谢!\n");
         }
         else  if(count==m)
             printf("=====已经录入学生信息的有%d人，已经将所有成绩信息录入完毕=====\n",count);
             else
             {
                 printf("=====录入学生信息大于输入的学生总数，系统将自行关闭，请检查信息后再次进入！=====");
                 getchar();
                 exit(1);
             }
		printf("请依次输入学生的信息......\n");
		for(count;count<m;count ++)
         {
             printf("<<<< 请输入该学生的学号：\n");
             scanf("%s",&stu_info[count].stu_num);
             if(strcmp(stu_info[count].stu_num,"-1")==0){
				 fclose(fp);
				 printf("学生的信息已经保存到%s文件中,未录学生还剩下%d人,请下次再录入!!!!!\n",filename,m-count);
				 getchar();
                 return 0;
			 }
             for(j=0;j<count;j++)
             {
                 if(strcmp(stu_info[j].stu_num,stu_info[count].stu_num)==0)
                 {
                     printf("=====学号输入重复，输入错误，请检查后再进行录入=====\n");
                     count --;
                     return 0;
                 }
             }
             stu_info[count].total=0;
             printf("<<<< 请输入该学生的姓名：\n");
             getchar();
			 scanf("%s",&stu_info[count].stu_name);
			 printf("<<<< 请输入该学生的性别：\n");
             getchar();
			 scanf("%s",&stu_info[count].sex);
             for(j=1;j<=n;j++)
             {
                 printf("<<<< 请输入该学生第%d门功课的成绩：",j);
                 scanf("%f",&stu_info[count].stu_ach[j-1]);
                 stu_info[count].total=stu_info[count].total+stu_info[count].stu_ach[j-1];
             }
			 stu_info[count].linefeed='\n';
             fwrite(&stu_info[count],LEN,1,fp);
         }
     printf("\n=====学生信息已成功录入二进制文件 %s 中，谢谢=====\n",filename);
     fclose (fp);
	
   return 0;
 }
int Stu_NumQuery(int m,int n,char filename[L]){
     struct student vessel;
     char QueryNum[L];
	 int flag=0;
     FILE *fp;
     printf("=====请输入要查询信息的学生的学号：=====\n");
     scanf("%s",&QueryNum);
     fp=fopen(filename,"ab+");
     if(fp==NULL)
     {
         printf("\n=====文件%s打开失败=====\n",filename);
         return 0;
     }
     i=0;
     while((fread(&vessel,LEN,1,fp))!=(int)NULL)
         {   
             strcpy(stu_info[i].stu_num,vessel.stu_num);
             strcpy(stu_info[i].stu_name,vessel.stu_name);
			 strcpy(stu_info[i].sex,vessel.sex);
			 stu_info[i].linefeed=vessel.linefeed;
             for(j=0;j<n;j++)
                 stu_info[i].stu_ach[j]=vessel.stu_ach[j];
            stu_info[i].total=vessel.total;
             i++;
     }                                                                ///读入到结构体数组
     /*对学生的成绩进行排序*/
     for(k=0;k<=i;k++)
     {
         for(j=k+1;j<i;j++)
             if(stu_info[k].total<stu_info[j].total)
             {
                 vessel=stu_info[k];
                 stu_info[k]=stu_info[j];
                 stu_info[j]=vessel;
             }
     }  
	  printf("=====按学号查询学生排名及其考试成绩=====\n");
      for(j=0;j<i;j++)
     {
         if(strcmp(stu_info[j].stu_num,QueryNum )==0)   //判断是否存在该学生
         {   flag=1;
             printf("----------------------------------------------------\n");
            printf("名次:%d   学号：%s    姓名：%s	性别:%s\n",j+1,stu_info[j].stu_num,stu_info[j].stu_name,stu_info[j].sex);
             for(k=0;k<n;k++){
                 printf("第%d科：%.3f    ",k+1,stu_info[j].stu_ach[k]);
			     if((k+1)%3==0){
					 printf("\n");
				 }
			 }
             printf("\n总分%.3f      平均分%.3f\n",stu_info[j].total,stu_info[j].total/n);
         }
   }
	   printf("----------------------------------------------------\n");
	  if(flag==0){
		  printf("没有该学号!!!!!!!!!!!!!!!!!\n");
	      getchar();
		  return 0;
	  }
     fclose(fp);
     return 0;	                                                           
}
int Stu_NameQuery(int m,int n,char filename[L]){
	struct student vessel;
     char QueryName[L];
     FILE *fp;
     printf("=====请输入要查询信息的学生的姓名：=====\n");
     scanf("%s",&QueryName);
     fp=fopen(filename,"rb");
     if(fp==NULL)
     {
         printf("\n=====文件%s打开失败=====\n",filename);
         return 0;
     }
     i=0;
	 while((fread(&vessel,LEN,1,fp))!=(int)NULL)
         {   
             strcpy(stu_info[i].stu_num,vessel.stu_num);
             strcpy(stu_info[i].stu_name,vessel.stu_name);
			 strcpy(stu_info[i].sex,vessel.sex);
			 stu_info[i].linefeed=vessel.linefeed;
             for(j=0;j<n;j++)
                 stu_info[i].stu_ach[j]=vessel.stu_ach[j];
            stu_info[i].total=vessel.total;
			i++;
     }      
     for(k=0;k<=i;k++)
     {
         for(j=k+1;j<i;j++)
             if(stu_info[k].total<stu_info[j].total)
             {
                 vessel=stu_info[k];
                 stu_info[k]=stu_info[j];
                 stu_info[j]=vessel;
             }
     }     
     printf("=====按姓名查询学生排名及其考试成绩=====\n");
      for(j=0;j<i;j++)
     {
         if(strcmp(stu_info[j].stu_name, QueryName)==0)
         {
             printf("----------------------------------------------------\n");
            printf("名次:%d   学号：%s    姓名：%s	性别:%s\n",j+1,stu_info[j].stu_num,stu_info[j].stu_name,stu_info[j].sex);
             for(k=0;k<n;k++){
                 printf("第%d科：%.3f    ",k+1,stu_info[j].stu_ach[k]);
			     if((k+1)%3==0){
					 printf("\n");
				 }
			 }
             printf("\n总分%.3f      平均分%.3f\n",stu_info[j].total,stu_info[j].total/n);
         }
     }
     printf("----------------------------------------------------");
     fclose(fp);
     return 0;	  
}
int Stu_print(int m,int n,char filename[L]){
     struct student vessel;
     FILE *fp;
     fp=fopen(filename,"rb");
     if(fp==NULL)
     {
         printf("\n=====文件%s打开失败=====\n",filename);
         return 0;
     }
     i=0;
      while((fread(&vessel,LEN,1,fp))!=(int)NULL)
         {   
             strcpy(stu_info[i].stu_num,vessel.stu_num);
             strcpy(stu_info[i].stu_name,vessel.stu_name);
			 strcpy(stu_info[i].sex,vessel.sex);
			 stu_info[i].linefeed=vessel.linefeed;
             for(j=0;j<n;j++)
                 stu_info[i].stu_ach[j]=vessel.stu_ach[j];
            stu_info[i].total=vessel.total;
             i++;
     }         
     for(k=0;k<=i;k++)
     {
         for(j=k+1;j<i;j++)
             if(stu_info[k].total<stu_info[j].total)
             {
                 vessel=stu_info[k];
                 stu_info[k]=stu_info[j];;
                 stu_info[j]=vessel;
             }
     }
     printf("=====学生所有信息屏幕输出=====\n");
      for(j=0;j<i;j++)
     {
          printf("----------------------------------------------------\n");
          printf("名次:%d   学号：%s    姓名：%s	性别:%s\n",j+1,stu_info[j].stu_num,stu_info[j].stu_name,stu_info[j].sex);
          for(k=0;k<n;k++){
                 printf("第%d科：%.3f    ",k+1,stu_info[j].stu_ach[k]);
			     if((k+1)%3==0){
					 printf("\n");
				 }
			 }
          printf("\n总分%.3f      平均分%.3f\n",stu_info[j].total,stu_info[j].total/n);
     }
     printf("----------------------------------------------------");
     fclose(fp);
	 return 0;
}
int Delete_StuInfo(int m,int n,char filename[L]){
	FILE *fp;
	char DelNum[L];
	struct student vessel;
	printf("=====请输入要删除信息的学生的学号：=====\n");
    scanf("%s",&DelNum);
	fp=fopen(filename,"rb+");//读打开原文件
	if(fp==NULL){
         printf("\n=====文件%s第一次打开失败=====\n",filename);
         return 0;
    }
	  i=0;
      while((fread(&vessel,LEN,1,fp))!=(int)NULL)
         {   if(strcmp(vessel.stu_num,DelNum)!=0){
             strcpy(stu_info[i].stu_num,vessel.stu_num);
             strcpy(stu_info[i].stu_name,vessel.stu_name);
			 strcpy(stu_info[i].sex,vessel.sex);
			 stu_info[i].linefeed=vessel.linefeed;
             for(j=0;j<n;j++)
                 stu_info[i].stu_ach[j]=vessel.stu_ach[j];
            stu_info[i].total=vessel.total;
             i++;
	  }
     }      
	 fclose(fp);
	 fp=fopen(filename,"wb+");
	 if(fp==NULL){
         printf("\n=====文件%s第二次打开失败=====\n",filename);
         return 0;
    }
	 for(count=0;count<i;count++){
		 vessel=stu_info[count];
		 fwrite(&vessel,LEN,1,fp);
	 }
	fclose(fp);
	printf("已经删除学号为:%s的学生,还剩余%d个人\n",DelNum,i);
	return 0;
}
int Update_StuInfo(int m,int n,char filename[L]){
	FILE *fp;
	int flag=0;
	char UpadateNum[L];
	struct student vessel;
    printf("====================================================\n");
	printf("注意:\n只能更改学生的成绩信息，不可修改学号、姓名、性别等信息!!\n");
	printf("====================================================\n");
	printf("=====请输入要更新信息的学生的学号：=====\n");
    scanf("%s",&UpadateNum);
	fp=fopen(filename,"rb+");
	if(fp==NULL){
         printf("\n=====文件%s第一次打开失败=====\n",filename);
         return 0;
    }
    i=0;
     while((fread(&vessel,LEN,1,fp))!=(int)NULL)
         {   
             strcpy(stu_info[i].stu_num,vessel.stu_num);
             strcpy(stu_info[i].stu_name,vessel.stu_name);
			 strcpy(stu_info[i].sex,vessel.sex);
			 stu_info[i].linefeed=vessel.linefeed;
             for(j=0;j<n;j++)
                 stu_info[i].stu_ach[j]=vessel.stu_ach[j];
            stu_info[i].total=vessel.total;
             i++;
     }  
      for(count=0;count<i;count++){
        if(strcmp(stu_info[count].stu_num,UpadateNum)==0){   
             flag=1;
             printf("请对学号为：%s的学生进行成绩修改........\n",UpadateNum);
	         stu_info[count].total=0;
	         for(j=1;j<=n;j++){
                 printf("<<<< 请输入该学生第%d门功课的成绩：",j);
                 scanf("%f",&stu_info[count].stu_ach[j-1]);
                 stu_info[count].total=stu_info[count].total+stu_info[count].stu_ach[j-1];
             }
           }
       } 
       if(flag==0){
           printf("没有该学生，请检查学号是否输入正确!!!\n");
           return 0;
       } 
       fclose(fp);
       fp=fopen(filename,"wb+");
	 if(fp==NULL){
         printf("\n=====文件%s第二次打开失败=====\n",filename);
         return 0;
    }
	 for(count=0;count<i;count++){
		 vessel=stu_info[count];
		 fwrite(&vessel,LEN,1,fp);
	 }
	fclose(fp);
    printf("已经修改学号为:%s的学生的成绩信息\n",UpadateNum);
	return 0;
}
int Stu_Ascending(int m,int n,char filename[L]){
     FILE *fp;
	 struct student vessel;
     fp=fopen(filename,"rb");
     if(fp==NULL)
     {
         printf("\n=====文件%s打开失败=====\n",filename);
         return;
     }
     i=0;
     while((fread(&vessel,LEN,1,fp))!=(int)NULL)
         {   
             strcpy(stu_info[i].stu_num,vessel.stu_num);
             strcpy(stu_info[i].stu_name,vessel.stu_name);
			 strcpy(stu_info[i].sex,vessel.sex);
			 stu_info[i].linefeed=vessel.linefeed;
             for(j=0;j<n;j++)
                 stu_info[i].stu_ach[j]=vessel.stu_ach[j];
            stu_info[i].total=vessel.total;
             i++;
     }  
     for(k=0;k<=i;k++)
     {
         for(j=k+1;j<i;j++)
             if(stu_info[k].total<stu_info[j].total)
             {
                 vessel=stu_info[k];
                 stu_info[k]=stu_info[j];
                 stu_info[j]=vessel;
             }
     }
     printf("=====成绩升序排名为=====\n");
     for(j=0;j<i;j++)
     {    printf("----------------------------------------------------------------------------\n");
          printf("<<<< 名次；%d     学号：%s      姓名：%s     性别：%s     总分：%.3f\n",j+1,stu_info[j].stu_num,stu_info[j].stu_name,stu_info[j].sex,stu_info[j].total);
     }
	 printf("----------------------------------------------------------------------------\n");
     fclose (fp);
     return 0;
}
int Stu_Descending(int m,int n,char filename[L]){
     FILE *fp;
	 struct student vessel;
     fp=fopen(filename,"rb");
     if(fp==NULL)
     {
         printf("\n=====文件%s打开失败=====\n",filename);
         return;
     }
     i=0;
     while((fread(&vessel,LEN,1,fp))!=(int)NULL)
         {   
             strcpy(stu_info[i].stu_num,vessel.stu_num);
             strcpy(stu_info[i].stu_name,vessel.stu_name);
			 strcpy(stu_info[i].sex,vessel.sex);
			 stu_info[i].linefeed=vessel.linefeed;
             for(j=0;j<n;j++)
                 stu_info[i].stu_ach[j]=vessel.stu_ach[j];
            stu_info[i].total=vessel.total;
             i++;
     }  
     for(k=0;k<=i;k++)
     {
         for(j=k+1;j<i;j++)
             if(stu_info[k].total>stu_info[j].total)
             {
                 vessel=stu_info[k];
                 stu_info[k]=stu_info[j];
                 stu_info[j]=vessel;
             }
     }
     printf("=====成绩降序排名为=====\n");
     for(j=0;j<i;j++)
     {    printf("----------------------------------------------------------------------------\n");
          printf("<<<< 名次；%d     学号：%s      姓名：%s     性别：%s     总分：%.3f\n",i-j,stu_info[j].stu_num,stu_info[j].stu_name,stu_info[j].sex,stu_info[j].total);
     }
	 printf("----------------------------------------------------------------------------\n");
     fclose (fp);
     return 0;
}
int Stu_AchAna(int m,int n,char filename[L]){
	float a=0,b=0,c=0,d=0,e=0;
     struct student vessel;
	 FILE *fp;
	 fp=fopen(filename,"rb");
	  if(fp==NULL)
     {
         printf("\n=====文件%s打开失败=====\n",filename);
         return 0;
     }
	  i=0;
     while((fread(&vessel,LEN,1,fp))!=(int)NULL)
         {   
             strcpy(stu_info[i].stu_num,vessel.stu_num);
             strcpy(stu_info[i].stu_name,vessel.stu_name);
			 strcpy(stu_info[i].sex,vessel.sex);
			 stu_info[i].linefeed=vessel.linefeed;
             for(j=0;j<n;j++)
                 stu_info[i].stu_ach[j]=vessel.stu_ach[j];
            stu_info[i].total=vessel.total;
             i++;
     } 
	 fclose(fp);
     printf("===========================================各科目成绩分析=================================================\n总参考人数:%d\n考试科目数:%d\n",i,n);
     printf("   科目       优秀（比例）        良好（比例）       中等（比例）       及格（比例）       不及格（比例）\n");
     printf("              <90-100>             <80-89>            <70-79>            <60-69>            <0-59>\n");
	 for(k=0;k<n;k++)       ///课程
     {
         a=0,b=0,c=0,d=0,e=0;
         for(j=0;j<m;j++)    ///学生
         {
             if((stu_info[j].stu_ach[k]<=100)&&(stu_info[j].stu_ach[k]>=90))
                 a++;
             else if((stu_info[j].stu_ach[k]<=89)&&(stu_info[j].stu_ach[k]>=80))
                     b++;
                 else if((stu_info[j].stu_ach[k]<=79)&&(stu_info[j].stu_ach[k]>=70))
                         c++;
                     else if((stu_info[j].stu_ach[k]<=69)&&(stu_info[j].stu_ach[k]>=60))
                             d++;
                         else if((stu_info[j].stu_ach[k]<=59)&&(stu_info[j].stu_ach[k]>=0))
                                 e++;
         }
		 printf("--------------------------------------------------------------------------------------------------------------\n");
		 printf("   第%d科     %.0f人（%.3f%%）    %.0f人（%.3f%%）    %.0f人（%.3f%%）    %.0f人（%.3f%%）    %.0f人（%.3f%%）\n",k+1,a,a/m*100,b,b/m*100,c,c/m*100,d,d/m*100,e,e/m*100);
     }
	  printf("--------------------------------------------------------------------------------------------------------------\n");
	  return 0;
}
int Average_Scort(int m,int n,char filename[L]){
	 struct student vessel;
	 FILE *fp;
	 float sum[N]={0};
	 fp=fopen(filename,"rb");
	  if(fp==NULL)
     {
         printf("\n=====文件%s打开失败=====\n",filename);
         return 0;
     }
	  i=0;
     while((fread(&vessel,LEN,1,fp))!=(int)NULL)
         {   
             for(j=0;j<n;j++){
				 stu_info[i].stu_ach[j]=vessel.stu_ach[j];
				 sum[j]=sum[j]+stu_info[i].stu_ach[j];
			 }  
			 stu_info[i].total=vessel.total;
			 i++;
     } 
	 fclose(fp);
	 printf("=====课程总成绩与各科的平均分为=====\n");
	 for(j=0;j<n;j++){
		 printf("----------------------------------------------------\n");
		 printf("<<<<  第%d门课程的总成绩为%.3f    平均分为%.3f\n",j+1,sum[j],sum[j]/i);
	 }
	     printf("----------------------------------------------------\n");
	 return 0;
}
int Stu_PerAna(int m,int n,char filename[L]){
	struct student vessel;
	 FILE *fp;
	 float sum[N]={0};
	 char name[M][L];
	 fp=fopen(filename,"rb");
	  if(fp==NULL)
     {
         printf("\n=====文件%s打开失败=====\n",filename);
         return 0;
     }
	  i=0;
     while((fread(&vessel,LEN,1,fp))!=(int)NULL)
         {   
			 strcpy(stu_info[i].stu_num,vessel.stu_num);
             strcpy(stu_info[i].stu_name,vessel.stu_name);
			 strcpy(stu_info[i].sex,vessel.sex);
			 stu_info[i].linefeed=vessel.linefeed;
             for(j=0;j<n;j++)
                 stu_info[i].stu_ach[j]=vessel.stu_ach[j];
             stu_info[i].total=vessel.total;
             i++;
     } 
	  fclose(fp);
	  printf("====================学生个人课程总成绩与平均分为======================\n");
	  for(j=0;j<i;j++){
		  printf("---------------------------------------------------------------------\n");
		  printf("学号：%s    姓名:%s     平均分为：%.2f，总分为：%.2f\n",stu_info[j].stu_num,stu_info[j].stu_name,stu_info[j].total/n,stu_info[j].total);
	  }
	  printf("---------------------------------------------------------------------\n");
	  return 0;
}
int Derive_Stu_into(int m,int n,char filename[L]){
	char  output[L]={0};
	struct student vessel;
     FILE *fp1,*fp2;
     fp1=fopen(filename,"ab+");
     printf("\n<<<< 请输入要输出到文件的名字(注可输入学生数据文件的路径)：\n");                   ///提示输入文件名
     getchar();
     gets(output);                                                          ///接收输入
	 if(strcmp(wipeoff(output),filename)==0){
		 strcpy(output,strtok(output,"."));
		 strcat(output,".txt");
	 }
     fp2=fopen(output,"a+");
     if(fp1==NULL)
     {
         printf("\n=====文件%s打开失败=====\n",filename);
         return 0;
     }
     if(fp2==NULL)
     {
         printf("\n=====文件%s打开失败=====\n",output);
         return 0;
     }
     i=0;
     while((fread(&vessel,LEN,1,fp1))!=(int)NULL)
         {   
             strcpy(stu_info[i].stu_num,vessel.stu_num);
             strcpy(stu_info[i].stu_name,vessel.stu_name);
			 strcpy(stu_info[i].sex,vessel.sex);
			 stu_info[i].linefeed=vessel.linefeed;
             for(j=0;j<n;j++)
                 stu_info[i].stu_ach[j]=vessel.stu_ach[j];
            stu_info[i].total=vessel.total;
             i++;
     } 
	 fclose(fp1);
	 printf("=====学生所有信息输出到%s文件=====\n",output);
      for(j=0;j<i;j++)
     {
          fprintf(fp2,"----------------------------------------------------\n");
          fprintf(fp2,"名次:%d   学号：%s    姓名：%s	性别:%s\n",j+1,stu_info[j].stu_num,stu_info[j].stu_name,stu_info[j].sex);
          for(k=0;k<n;k++){
                 fprintf(fp2,"第%d科：%.3f    ",k+1,stu_info[j].stu_ach[k]);
			     if((k+1)%3==0){
					 fprintf(fp2,"\n");
				 }
			 }
          fprintf(fp2,"总分%.3f      平均分%.3f\n",stu_info[j].total,stu_info[j].total/n);
     }
     fprintf(fp2,"----------------------------------------------------");
     fclose(fp2);
	 printf("\n=====学生信息写入到文件%s成功，请注意接收！=====\n",output);
	 return 0;
}
int main()
 {   int m,n;
     char filename[L]={0};
     int num=5;
	 int Fun_key;
    char passwd[L];
	r0: system("cls");
    system("color F2");
    printf("***********************  欢迎使用学生信息管理平台 *************************\n");  
    printf("*\t\t\t\t\t\t\t\t\t  *\n");  
    printf("*\t\t\t\t\t\t\t\t\t  *\n");    
    printf("*                     >>系  统  权  限  认  证 <<                         *\n");
    printf("*>>>>>>>>>>>>>>>>>>请提供管理员权限，输入系统启动密码<<<<<<<<<<<<<<<<<<<<<*\n");
    printf("*                                                                         *\n");
	printf("*\t\t\t\t\t\t\t\t\t  *\n");  
    printf("*\t\t\t\t\t\t\t\t\t  *\n");
	printf("***************************************************************************\n");
	printf("\n>>>>>>    密  码：   ");
     scanf("%s",
		 &passwd);
     num --;
     for(;strcmp(passwd,"ZYS1997")!=0;)
     {
         if(num==0)
         {
             printf("对不起，程序即将关闭，谢谢使用");
             getchar();
             getchar();
             exit (1);
         }
         else
         {
             printf("对不起，密码错误，请重新输入（你还有%d次输入机会）",num);
             getchar();
             getchar();
             goto r0;
         }
     }
     system("CLS");
     system("color  F2");
     printf("--------------------------------------------------------------------------------\n");
     printf("|                        WELCOME  TO  USE  THE  SYSTEM                         |\n");
     printf("|------------------------------------------------------------------------------|\n");
	 printf("|建议：                                                                        |\n");
	 printf("|       1.使用本系统时需要首先输入班级总人数、总科目数、录入信息文件           |\n");
     printf("|       2. 如果您已经有输入文件，建议请先选择选项1，用于检查文件信息总数       |\n");
     printf("|          与录入人数、科目数是否一致，避免计算出错                            |\n");
     printf("|       3. 如果您是初次使用本系统请先选择选项2用于创建学生信息文件，录入       |\n");
     printf("|          信息时填写数据较多，并耐心仔细地录入学生信息                        |\n");
     printf("--------------------------------------------------------------------------------\n\n");
     printf("<<<< 请输入班级的总人数：     \n");
     scanf("%d",&m);
     printf("<<<< 请输入课程总数：     \n");
     scanf("%d",&n);
     printf("<<<< 请输入要读取或录入信息的文件的名字：     \n");                   ///提示输入文件名
	 getchar();
     gets(filename);///接收输入                                                 
	 if(filename[0]=='"'){
		 strcpy(filename,wipeoff(filename));
	 }
	 while(1)
     {
         char  xuanze[3]={0};
         printf("\n\n>>>>>>>>如果想进行清屏操作请输入yes,如果想跳过清屏直接继续请按任意键！<<<<<<<<\n");
         getchar();
         gets(xuanze);
         if(strcmp(xuanze,"yes")==0)    system("CLS");
         printf("*********************************************************\n");
    printf("*\t\t\t\t\t\t\t*\n");
	printf("*\t\t\t\t\t\t\t*\n");
	printf("*>>>>>>>>>>>>>>>欢迎使用学生信息管理系统<<<<<<<<<<<<<<<<*\n");
	printf("*\t\t\t\t\t\t\t*\n");
	printf("*\t\t\t\t\t\t\t*\n");
	printf("*              1.读取学生的数据信息文件                 *\n");
	printf("*\t\t\t\t\t\t\t*\n");
	printf("*              2.添加学生信息及成绩                     *\n");
	printf("*\t\t\t\t\t\t\t*\n");
	printf("*              3.按学号查询学生信息及成绩               *\n");
	printf("*\t\t\t\t\t\t\t*\n");
	printf("*              4.按名字查询学生信息及成绩               *\n");
	printf("*\t\t\t\t\t\t\t*\n");
	printf("*              5.显示学生信息及成绩                     *\n");
	printf("*\t\t\t\t\t\t\t*\n");
	printf("*              6.删除学生信息及成绩                     *\n");
	printf("*\t\t\t\t\t\t\t*\n");
	printf("*              7.修改学生信息及成绩                     *\n");
	printf("*\t\t\t\t\t\t\t*\n");
	printf("*              8.按总成绩升序排名                       *\n");
	printf("*\t\t\t\t\t\t\t*\n");
	printf("*              9.按总成绩降序排名                       *\n");
	printf("*\t\t\t\t\t\t\t*\n");
	printf("*              10.各科成绩等级分析                      *\n");
	printf("*\t\t\t\t\t\t\t*\n");
	printf("*              11.各科总成绩与平均分                    *\n");
	printf("*\t\t\t\t\t\t\t*\n");
	printf("*              12.学生总成绩与平均分                    *\n");
	printf("*\t\t\t\t\t\t\t*\n");
	printf("*              13.导出学生信息到文本文件                *\n");
	printf("*\t\t\t\t\t\t\t*\n");
	printf("*              14.退出系统(任意键退出)                  *\n");
	printf("*\t\t\t\t\t\t\t*\n");
	printf("*\t\t\t\t\t\t\t*\n");
	printf("*********************************************************\n");    
    printf("请选择你所需的功能:\n");
    scanf("%d",&Fun_key);
    switch(Fun_key){
         case 1:Read_StuFile(m,n,filename);     break;
         case 2:Add_StuInfo(m,n,filename);      break;
         case 3:Stu_NumQuery(m,n,filename);     break;
         case 4:Stu_NameQuery(m,n,filename);    break;
         case 5:Stu_print(m,n,filename);        break;
         case 6:Delete_StuInfo(m,n,filename);   break;
		 case 7:Update_StuInfo(m,n,filename);   break;
		 case 8:Stu_Ascending(m,n,filename);    break;
		 case 9:Stu_Descending(m,n,filename);   break;
		 case 10:Stu_AchAna(m,n,filename);      break;
		 case 11:Average_Scort(m,n,filename);   break;
		 case 12:Stu_PerAna(m,n,filename);      break;
		 case 13:Derive_Stu_into(m,n,filename); break;
         default:system("cls");printf("\n\n=====谢谢使用本系统，祝您生活愉快！=====\n\n");
	      getchar();
	      getchar();
		  exit(0);
     }     
  }
	 return 0;
}

