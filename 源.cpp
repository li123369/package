#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
struct student
{
	char ID[10]; //学号
	char name[20];//姓名
	double GPA; //绩点
	int major[7]; //志愿意向
	int Class; //班级
	int Major; //专业
}stu[451];
struct MAJOR
{
	int sum_max; //专业最大数量
	char member[500][20]; //储存学号
	int sum; //人数
	double GPA; //进入该专业最低GPA
	int sum_6; //第六志愿进入该专业的人数
	int sum_class; //该专业多少个班级
	int sum_first; //第一志愿进入该专业的人数
}major[7];
void write_file();
void read_file();
void sort();
void GPA_requirement();
void pick_major();
void pick_class();
void first_major();
void max_6();
void query();
void statistic();
void choice();
void menu();
void display_class_student();
void display_major_student();
void write_file()
{
	FILE* fp;
	fp = fopen("s1.txt", "w");

	for (int i = 1; i <= 450; i++)
	{
		fprintf(fp, "%s %s %d %d\n", stu[i].ID, stu[i].name, stu[i].Major, stu[i].Class);
	}
}
void read_file()
{
	FILE* fp;
	fp = fopen("f1.txt", "r");
	if (fp == NULL)
	{
		printf("文件打开错误\n");
	}
	for (int i = 1; i <= 450; i++)
	{
		fscanf(fp, "%s%s%lf%d%d%d%d%d%d", stu[i].ID, stu[i].name, &stu[i].GPA, &stu[i].major[1], &stu[i].major[2], &stu[i].major[3], &stu[i].major[4], &stu[i].major[5] ,&stu[i].major[6]);
	}
}
void sort()
{
	struct student temp; //中间结构体
	for(int i=1;i<=450;i++) //数据量不大，使用冒泡排序
		for (int j = 1; j < 450 ; j++)
		{
			if (stu[j].GPA < stu[j + 1].GPA)
			{
				temp = stu[j + 1];
				stu[j + 1] = stu[j];
				stu[j] = temp;
			}
		}
}
void pick_major()
{
	for (int i = 1; i <= 450; i++)
	{
		for (int j = 1; j <= 6; j++)
		{
			if (major[stu[i].major[j]].sum < major[stu[i].major[j]].sum_max) //判断该专业的人数是否满员
			{
				major[stu[i].major[j]].sum++; //人数+1
				if (j == 6) //判断是不是志愿6录取
				{ 
					major[stu[i].major[j]].sum_6++;
				}
				if (j == 1) //判断是不是志愿1录取
				{
					major[stu[i].major[j]].sum_first++;
				}
				if (major[stu[i].major[j]].sum == major[stu[i].major[j]].sum_max) //最后一个人的GPA，即为该专业的最低GPA要求
				{
					major[stu[i].major[j]].GPA = stu[i].GPA;
				}
				strcpy(major[stu[i].major[j]].member[major[stu[i].major[j]].sum], stu[i].ID); //将该学生的学号拷贝到该专业中去
				stu[i].Major = stu[i].major[j];
				break; //被分配后，不用管后续的志愿了
			}
		}
	}
}
void GPA_requirement()
{
	for (int i = 1; i <= 6; i++)
	{
		printf("专业%d的绩点要求是大于等于%.3lf\n", i, major[i].GPA);
	}
}
void display_major_student()
{
	for (int i = 1; i <= 6; i++) //每个专业都要循环
	{
		printf("专业%d的名单为：\n", i); //先输出该专业
		for (int j = 1; j <= major[i].sum_max; j++) 
		{
			for (int k = 1; k <= 450; k++) 
			{
				if (strcmp(stu[k].ID, major[i].member[j]) == 0) //判断该学生的学号是否在该专业的学号数组中
				{
					printf("姓名：%s\t\t学号:%d\n", stu[k].name, stu[k].ID); //输出姓名和学号
					break; //跳出循环
				}
			}
		}
	}
}
void pick_class()
{
	for (int i = 1; i <= 6; i++)
	{
		for (int j = 1; j <= major[i].sum_max; j+=major[i].sum_class) //1-3专业分配班级,循环依次加3;4-6专业分配班级，循环依次加2
		{
			int n = j; 
			for (int k = 1; k <= major[i].sum_class; k++)
			{
				for (int l = 1; l <= 450; l++)
				{
					if (strcmp(stu[l].ID, major[i].member[n]) == 0) //判断该学生是否是该专业
					{
						n++;
						stu[l].Class = k; //班级号
						break; //跳出循环
					}
				}
			}
		}
	}
}
void first_major()
{
	for (int i = 1; i <= 6; i++)
	{
		printf("专业%d的一志愿录取比列为%.2lf\n", i, double(major[i].sum_first) / double(major[i].sum_max));
	}
}
void max_6()
{
	int max = -1; //最大值
	int k; //记录专业
	for (int i = 1; i <= 6; i++)
	{
		if (major[i].sum_6 > max)
		{
			max = major[i].sum_6;
			k = i; //记录专业
		}
	}
	printf("%d专业六志愿最多\n", k);
}
void query()
{
	char name[20]; //储存姓名
	char ID[20]; //储存学号
	printf("输入姓名："); 
	scanf("%s", name);
	printf("输入学号：");
	scanf("%s", ID);
	for (int i = 1; i <= 540; i++)
	{
		if (strcmp(stu[i].name, name) == 0 && strcmp(stu[i].ID, ID) == 0) //判断学号和姓名是否相同，相同返回0，输出专业和班级
		{
			printf("专业：%d,班级:%d\n", stu[i].Major, stu[i].Class);
			break; //跳出循环
		}
	}
}
void statistic()
{
	for (int i = 1; i <= 6; i++)
	{
		for (int j = 1; j <= major[i].sum_class; j++)
		{
			double max_GPA = -1.0;
			double min_GPA = 9999.0;
			double sum=0;
			for (int k = 1; k <= major[i].sum_max; k++)
			{
				for (int l = 1; l <= 450; l++)
				{
					if (strcmp(stu[l].ID, major[i].member[k])==0 && stu[l].Class == j)
					{
						sum += stu[l].GPA;
						if (stu[l].GPA > max_GPA) max_GPA = stu[l].GPA;
						if (stu[l].GPA < min_GPA)   min_GPA = stu[l].GPA;

					}
				}
			}
			sum = sum / (major[i].sum_max / major[i].sum_class);
			printf("专业%d的%d班级最高绩点为：%.3lf，最低绩点为：%.3lf,平均绩点为：%.3lf\n", i, j, max_GPA, min_GPA, sum);
			
		}
	}
}
void popularity()
{
	int sum[7] = {0};
	int max_ = -1; //最大值判断
	int min_ = 9999; //最小值判断
	int max; //记录最多的专业
	int min;//记录最少的专业
	for (int i = 1; i <= 6; i++)
	{
		for (int j = 1; j <= 450; j++)
		{
			if (stu[j].major[i] == i)
				sum[i]++; //人数加1
		}
	}
	for (int i = 1; i <= 6; i++) //找出最大值和最小值
	{
		if (sum[i] > max_)
		{
			max_ = sum[i];
			max = i;
		}
		if (sum[i] < min_)
		{
			min_ = sum[i];
			min = i;
		}
	}
	for (int i = 1; i <= 6; i++) //输出信息
	{
		printf("第一志愿报名%d专业的人数为：%d\n", i, sum[i]);
	}
	printf("最受欢迎的专业是%d\n", max);
	printf("最不受欢迎的专业是%d\n",min);
}
void menu()
{
	printf("1.生成各个专业的学分绩点标准\n");
	printf("2.生成各个专业的学生名单\n");
	printf("3.生成各个班级的学生名单\n");
	printf("4.统计各个专业的受欢迎程度\n");
	printf("5.统计各个专业的一志愿录取比例\n");
	printf("6.生成各个班级的最高绩点、最低绩点、平均绩点\n");
	printf("7.分析哪个专业的六志愿最多\n");
	printf("8.查询\n");
	printf("请输入选项：");
}
void choice()
{
	int n;
	scanf("%d", &n);
	switch (n)
	{
	case 1:
	{
		GPA_requirement();
		system("pause");
		break;
	}
	case 2:
	{
		display_major_student();
		system("pause");
		break;
	}
	case 3:
	{
		display_class_student();
		system("pause");
		break;
	}
	case 4:
	{
		popularity();
		system("pause");
		break;
	}
	case 5:
	{
		first_major();
		system("pause");
		break;
	}
	case 6:
	{
		statistic();
		system("pause");
		break;
	}
	case 7:
	{
		max_6();
		system("pause");
		break;
	}
	case 8:
	{
		query();
		system("pause");
		break;
	}
	default:
		break;
	}
}
void display_class_student()
{
	for (int i = 1; i <= 6; i++)
	{
		for (int j = 1; j <= major[i].sum_class; j++)
		{
			printf("专业%d的%d班级人员名单为：\n", i, j);
			for (int k = 1; k <= major[i].sum_max; k++)
			{
				for (int l = 1; l <= 450; l++)
				{
					if (strcmp(stu[l].ID, major[i].member[k]) == 0 && stu[l].Class == j) //判断学号和班级是否相同，是则输出姓名和学号
					{
						printf("姓名：%s\t\t学号：%s\n", stu[l].name, stu[l].ID);
						break;//跳出循环

					}
				}
			}

		}
	}
}
int main()
{
	major[1].sum_max = 90;
	major[2].sum_max = 90;
	major[3].sum_max = 90;
	major[4].sum_max = 60;
	major[5].sum_max = 60;
	major[6].sum_max = 60;
	major[1].sum_class = 3;
	major[2].sum_class = 3;
	major[3].sum_class = 3;
	major[4].sum_class = 2;
	major[5].sum_class = 2;
	major[6].sum_class = 2;
	read_file();
	sort();
	pick_major();
	pick_class();
	write_file();
	while (1)
	{
		system("cls");
		menu();
		choice();
	}
	return 0;


}