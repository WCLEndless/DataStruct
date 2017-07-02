#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"heap_and_mager_sort.h"

void heap_part_adjust(elem_type*str, int start, int len)
{
	elem_type tmp = str[start];
	int tmp_start = start;
	while (tmp_start <= len/2-1)
	{
		int left_child = tmp_start * 2 + 1;
		int right_child = left_child + 1;
		int max = left_child;

		if (right_child < len && str[left_child] < str[right_child])
		{
			max = right_child;
		}
		if (tmp < str[max])
		{
			str[tmp_start] = str[max];
			tmp_start = max;
		}
		else
		{
			break;
		}
	}
	str[tmp_start] = tmp;
}

 void heap_adjust(elem_type *str, int len)
{
	for (int start = len / 2 - 1; start >= 0; start--)
	{
		heap_part_adjust(str, start, len);
	}
}

static void swap(elem_type*p1, elem_type *p2)
{
	elem_type tmp=*p1;
	*p1 = *p2;
	*p2 = tmp;
}
void heap_sort(elem_type*str, int len)//¶ÑÅÅÐò
{
	heap_adjust(str, len);
	swap(&str[0], &str[len - 1]);
	for (int tmp_len = len-1; tmp_len > 0; tmp_len--)
	{
		heap_part_adjust(str,0,tmp_len);
		swap(&str[0], &str[tmp_len-1]);
	}
}

void show(elem_type *str, int len,void(*pfunc)(elem_type e))
{
	for (int i = 0; i < len; i++)
	{
		pfunc(str[i]);
	}
	printf("\n");
}

static void sort(elem_type*arr, int gap, int len)
{
	elem_type *buff = (elem_type*)malloc(sizeof(elem_type)*len);
	int left1 = 0;
	int right1 = left1 + gap - 1;
	int left2 = right1 + 1;
	int right2 = left2 + gap - 1 >= len ? len - 1 : left2 + gap - 1;
	int k = 0;
	while (left2 < len)
	{
		while (left1 <= right1 && left2 <= right2)
		{
			if (arr[left1] <= arr[left2])
			{
				buff[k++] = arr[left1++];
			}
			else
			{
				buff[k++] = arr[left2++];
			}
		}
		while (left1 <= right1)
		{
			buff[k++] = arr[left1++];
		}
		while (left2 <= right2)
		{
			buff[k++] = arr[left2++];
		}
		left1 = right2 + 1;
		right1 = left1 + gap - 1;
		left2 = right1 + 1;
		right2 = left2 + gap - 1 >= len ? len - 1 : left2 + gap - 1;
	}
	while (left1 < len)
	{
		buff[k++] = arr[left1++];
	}
	for (int i = 0; i < len; i++)
	{
		arr[i] = buff[i];
	}
	free(buff);
}

void mager_sort(elem_type *arr, int len)//¹é²¢ÅÅÐò
{
	for (int gap = 1; gap < len; gap=gap*2)
	{
		sort(arr,gap,len);
	}
}


int* init_array(int len)
{
	int *p = (int *)malloc(sizeof(int)*len);
	srand((unsigned)(time(NULL)));
	for (int i = 0; i < len;i++)
	{
		p[i] = rand() % len;
	}
	return p;
}