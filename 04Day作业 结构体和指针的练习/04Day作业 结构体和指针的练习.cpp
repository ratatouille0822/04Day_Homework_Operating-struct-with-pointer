#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Teacher
{
	char *tName; //导师名字，需要动态分配空间
	char **stu;  //三个学生，需要动态分配空间，堆区数组
	int age;
}Teacher;

//在createTeacher中分配空间
int createTeacher(Teacher **p/*out*/, int n1, int n2);

//给成员赋值
void initTeacher(Teacher *p, int n1, int n2);

//打印结构体成员信息
void printTeacher(Teacher *p, int n1, int n2);


//根据导师名字排序, 降序
void sortTeacher(Teacher *p, int n);


//释放空间，在函数内部把p赋值为NULL
void freeTeacher(Teacher **p, int n1, int n2);

int main(void)
{
	int ret = 0;
	int n1 = 3; //导师个数
	int n2 = 3; //学生
	Teacher *p = NULL;

	ret = createTeacher(&p, n1, n2);
	if (ret != 0)
	{
		printf("createTeacher err:%d\n", ret);
		return ret;
	}

	initTeacher(p, n1, n2); //给成员赋值

	//打印成员，排序前
	printf("排序前：\n");
	printTeacher(p, n1, n2);


	//根据导师名字排序, 降序
	sortTeacher(p, n1);

	//打印成员，排序后
	printf("\n排序后：\n");
	printTeacher(p, n1, n2);

	printf("--------------------------------------\n");

	//释放空间，在函数内部把p赋值为NULL
	freeTeacher(&p, n1, n2);

	return 0;
}

int createTeacher(Teacher **p/*out*/, int n1, int n2)
{
	if (p == NULL)
	{
		printf("EMPTY\n");
		return -1;
	}

	Teacher* pTeacher = (Teacher*)malloc(n1 * sizeof(Teacher));
	memset(pTeacher, 0, n1 * sizeof(Teacher));
	for (int i = 0; i < n1; i++)
	{
		pTeacher[i].tName = (char*)malloc(50);
		memset(pTeacher[i].tName, 0, 50);
		pTeacher[i].stu = (char**)malloc(n2 * sizeof(char*));
		memset(pTeacher[i].stu, 0, n2 * sizeof(char*));
		for (int j = 0; j < n2; j++)
		{
			(pTeacher[i].stu)[j] = (char*)malloc(50);
			memset((pTeacher[i].stu)[j], 0, 50);
		}
	}

	*p = pTeacher;
	return 0;
}


void initTeacher(Teacher *p, int n1, int n2)
{
	const char* name_list[3] = { "陈猛","张硕","刘宏涛" };
	const char* stu_list[3][3] = { "刘备","关羽","张飞","黄忠","赵云","马超","诸葛亮","魏延","徐庶" };
	
	if (p == NULL)
	{
		printf("EMPTY\n");
	}

	for (int i = 0; i < n1; i++)
	{
		p[i].age = 50 + i;
		strcpy(p[i].tName, name_list[i]);
		for (int j = 0; j < n2; j++)
		{
			sprintf((p[i].stu)[j], "%s",stu_list[i][j]);
		}
	}

}


void printTeacher(Teacher *p, int n1, int n2)
{
	if (p == NULL)
	{
		printf("EMPTY\n");
	}
	for (int i = 0; i < n1; i++)
	{
		printf("Teachar %s is %d years old\n", p[i].tName, p[i].age);
		printf("He has student %s, %s, and %s\n", (p[i].stu)[0], (p[i].stu)[1], (p[i].stu)[2]);
	}
}

void sortTeacher(Teacher *p, int n)
{
	if (p == NULL)
	{
		printf("EMPTY\n");
	}
	for (int i = 0; i < n-1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (strcmp(p[j].tName, p[j + 1].tName) < 0)
			{
				char* temp = p[j].tName;
				p[j].tName = p[j + 1].tName;
				p[j + 1].tName = temp;
			}
		}
	}

}

void freeTeacher(Teacher **p, int n1, int n2)
{
	Teacher * pTeacher = *p;
	for (int i = 0; i < n1; i++)
	{
		for (int j = 0; j < n2; j++)
		{
			free((pTeacher[i].stu)[j]);
			printf("Teacher %d stu %d is freed\n", i, j);
		}
		free(pTeacher[i].stu);
		printf("Teacher %d stu is freed\n", i);
		free(pTeacher[i].tName);
		printf("Teacher %d tName is freed\n", i);
		printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	}
	free(*p);
	printf("Teacher is freed\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
}









