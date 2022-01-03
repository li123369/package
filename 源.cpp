#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
struct student
{
	char ID[10]; //ѧ��
	char name[20];//����
	double GPA; //����
	int major[7]; //־Ը����
	int Class; //�༶
	int Major; //רҵ
}stu[451];
struct MAJOR
{
	int sum_max; //רҵ�������
	char member[500][20]; //����ѧ��
	int sum; //����
	double GPA; //�����רҵ���GPA
	int sum_6; //����־Ը�����רҵ������
	int sum_class; //��רҵ���ٸ��༶
	int sum_first; //��һ־Ը�����רҵ������
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
		printf("�ļ��򿪴���\n");
	}
	for (int i = 1; i <= 450; i++)
	{
		fscanf(fp, "%s%s%lf%d%d%d%d%d%d", stu[i].ID, stu[i].name, &stu[i].GPA, &stu[i].major[1], &stu[i].major[2], &stu[i].major[3], &stu[i].major[4], &stu[i].major[5] ,&stu[i].major[6]);
	}
}
void sort()
{
	struct student temp; //�м�ṹ��
	for(int i=1;i<=450;i++) //����������ʹ��ð������
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
			if (major[stu[i].major[j]].sum < major[stu[i].major[j]].sum_max) //�жϸ�רҵ�������Ƿ���Ա
			{
				major[stu[i].major[j]].sum++; //����+1
				if (j == 6) //�ж��ǲ���־Ը6¼ȡ
				{ 
					major[stu[i].major[j]].sum_6++;
				}
				if (j == 1) //�ж��ǲ���־Ը1¼ȡ
				{
					major[stu[i].major[j]].sum_first++;
				}
				if (major[stu[i].major[j]].sum == major[stu[i].major[j]].sum_max) //���һ���˵�GPA����Ϊ��רҵ�����GPAҪ��
				{
					major[stu[i].major[j]].GPA = stu[i].GPA;
				}
				strcpy(major[stu[i].major[j]].member[major[stu[i].major[j]].sum], stu[i].ID); //����ѧ����ѧ�ſ�������רҵ��ȥ
				stu[i].Major = stu[i].major[j];
				break; //������󣬲��ùܺ�����־Ը��
			}
		}
	}
}
void GPA_requirement()
{
	for (int i = 1; i <= 6; i++)
	{
		printf("רҵ%d�ļ���Ҫ���Ǵ��ڵ���%.3lf\n", i, major[i].GPA);
	}
}
void display_major_student()
{
	for (int i = 1; i <= 6; i++) //ÿ��רҵ��Ҫѭ��
	{
		printf("רҵ%d������Ϊ��\n", i); //�������רҵ
		for (int j = 1; j <= major[i].sum_max; j++) 
		{
			for (int k = 1; k <= 450; k++) 
			{
				if (strcmp(stu[k].ID, major[i].member[j]) == 0) //�жϸ�ѧ����ѧ���Ƿ��ڸ�רҵ��ѧ��������
				{
					printf("������%s\t\tѧ��:%d\n", stu[k].name, stu[k].ID); //���������ѧ��
					break; //����ѭ��
				}
			}
		}
	}
}
void pick_class()
{
	for (int i = 1; i <= 6; i++)
	{
		for (int j = 1; j <= major[i].sum_max; j+=major[i].sum_class) //1-3רҵ����༶,ѭ�����μ�3;4-6רҵ����༶��ѭ�����μ�2
		{
			int n = j; 
			for (int k = 1; k <= major[i].sum_class; k++)
			{
				for (int l = 1; l <= 450; l++)
				{
					if (strcmp(stu[l].ID, major[i].member[n]) == 0) //�жϸ�ѧ���Ƿ��Ǹ�רҵ
					{
						n++;
						stu[l].Class = k; //�༶��
						break; //����ѭ��
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
		printf("רҵ%d��һ־Ը¼ȡ����Ϊ%.2lf\n", i, double(major[i].sum_first) / double(major[i].sum_max));
	}
}
void max_6()
{
	int max = -1; //���ֵ
	int k; //��¼רҵ
	for (int i = 1; i <= 6; i++)
	{
		if (major[i].sum_6 > max)
		{
			max = major[i].sum_6;
			k = i; //��¼רҵ
		}
	}
	printf("%dרҵ��־Ը���\n", k);
}
void query()
{
	char name[20]; //��������
	char ID[20]; //����ѧ��
	printf("����������"); 
	scanf("%s", name);
	printf("����ѧ�ţ�");
	scanf("%s", ID);
	for (int i = 1; i <= 540; i++)
	{
		if (strcmp(stu[i].name, name) == 0 && strcmp(stu[i].ID, ID) == 0) //�ж�ѧ�ź������Ƿ���ͬ����ͬ����0�����רҵ�Ͱ༶
		{
			printf("רҵ��%d,�༶:%d\n", stu[i].Major, stu[i].Class);
			break; //����ѭ��
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
			printf("רҵ%d��%d�༶��߼���Ϊ��%.3lf����ͼ���Ϊ��%.3lf,ƽ������Ϊ��%.3lf\n", i, j, max_GPA, min_GPA, sum);
			
		}
	}
}
void popularity()
{
	int sum[7] = {0};
	int max_ = -1; //���ֵ�ж�
	int min_ = 9999; //��Сֵ�ж�
	int max; //��¼����רҵ
	int min;//��¼���ٵ�רҵ
	for (int i = 1; i <= 6; i++)
	{
		for (int j = 1; j <= 450; j++)
		{
			if (stu[j].major[i] == i)
				sum[i]++; //������1
		}
	}
	for (int i = 1; i <= 6; i++) //�ҳ����ֵ����Сֵ
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
	for (int i = 1; i <= 6; i++) //�����Ϣ
	{
		printf("��һ־Ը����%dרҵ������Ϊ��%d\n", i, sum[i]);
	}
	printf("���ܻ�ӭ��רҵ��%d\n", max);
	printf("��ܻ�ӭ��רҵ��%d\n",min);
}
void menu()
{
	printf("1.���ɸ���רҵ��ѧ�ּ����׼\n");
	printf("2.���ɸ���רҵ��ѧ������\n");
	printf("3.���ɸ����༶��ѧ������\n");
	printf("4.ͳ�Ƹ���רҵ���ܻ�ӭ�̶�\n");
	printf("5.ͳ�Ƹ���רҵ��һ־Ը¼ȡ����\n");
	printf("6.���ɸ����༶����߼��㡢��ͼ��㡢ƽ������\n");
	printf("7.�����ĸ�רҵ����־Ը���\n");
	printf("8.��ѯ\n");
	printf("������ѡ�");
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
			printf("רҵ%d��%d�༶��Ա����Ϊ��\n", i, j);
			for (int k = 1; k <= major[i].sum_max; k++)
			{
				for (int l = 1; l <= 450; l++)
				{
					if (strcmp(stu[l].ID, major[i].member[k]) == 0 && stu[l].Class == j) //�ж�ѧ�źͰ༶�Ƿ���ͬ���������������ѧ��
					{
						printf("������%s\t\tѧ�ţ�%s\n", stu[l].name, stu[l].ID);
						break;//����ѭ��

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