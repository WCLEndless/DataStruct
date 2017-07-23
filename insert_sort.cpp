#include<stdio.h>
#include"insert_sort.h"


void my_print(int *p, int len)//打印函数
{
	for (int i = 0; i < len; i++)
	{
		printf("%d ", p[i]);
	}
	printf("\n");
}

void insert_sort(int *p,int len)//插入排序
{
	int j;
	int tmp ;
	for (int i = 1; i < len; i++)
	{
		tmp = p[i];
		for ( j = i - 1; j >= 0; j--)
		{
			if (p[j] > tmp)
			{
				p[j + 1] = p[j];
			}
			else
			{
				break;
			}
		}
		p[j+1] = tmp;
	}
}

void shell_sort(int *p, int len)//希尔排序
{
	int j;
	int gap = 3;
	for (int i = 0; i < len; i++)
	{
		int tmp = p[i];
		for ( j = i - gap; j >= 0; j -= gap)
		{
			if (tmp < p[j])
			{
				p[j + gap] = p[j];
			}
			else
			{
				break;
			}
		}
		p[j + gap] = tmp;
	}
	insert_sort(p, len);
}



static int  put_suitable_position(int *p, int head,int tail)
{
	//int head = 0;
	//int tail = len - 1;
	int tmp = p[head];
	while (head < tail)
	{
		while (p[tail]>=tmp && head < tail)
		{
			tail--;
		}
		p[head] = p[tail];
		while (p[head] <= tmp&&head<tail)
		{
			head++;
		}
		p[tail] = p[head];
	}
	p[head] = tmp;
	return head;
}
static void sort(int *p, int head, int tail)//递归实现快速排序
{
	if (head < tail)
	{
		int base = put_suitable_position(p,head,tail);
		sort(p,head,base-1);
		sort(p, base + 1, tail);//这个tail是上一次的尾，这个递归从左边递归结束一直到右边递归结束完成整个递归排序
	}
}
void quick_sort(int *p, int len)
{
	sort(p,0,len-1);
}

void quick_sort_loop(int *p, int len)//循环实现快速排序
{
	int head = 0;
	int tail = len - 1;
	int tmp[100];
	int count = 0;

	tmp[count++] = 0;
	tmp[count++] = len - 1;
	while (count>0)
	{
		tail= tmp[--count];
		head = tmp[--count];
		if (head < tail)
		{
			int base = put_suitable_position(p,head,tail);
			tmp[count++] = head;
			tmp[count++] = base - 1;
			tmp[count++] = base + 1;
			tmp[count++] = tail;
		}
	}
}

