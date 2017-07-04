
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include<math.h>
#include"base_sort.h"

NODE *alloc_node(elem_type e)
{
	NODE *tmp = (NODE *)malloc(sizeof(NODE));
	if (tmp == NULL)
	{
		return false;
	}

	tmp->data = e;
	tmp->next = NULL;

	return tmp;
}



NODE *init_link_list_ex()
{
	NODE* tmp = (NODE*)malloc(sizeof(NODE));
	assert(tmp != NULL);
	tmp->next = NULL;
	return tmp;

}
bool destory_link_list_ex(NODE *phead)
{
	if (phead == NULL)
	{
		return false;
	}
	elem_type tmp;
	while (phead->next != NULL)
	{
		delete_head(phead, &tmp);
	}
	free(phead);
	return true;
}



bool is_empty(NODE *phead)
{
	return phead->next == NULL;
}



bool delete_head(NODE *phead, elem_type *e)
{
	if (phead == NULL || is_empty(phead))
	{
		return false;
	}

	NODE *p = phead->next;

	phead->next = p->next;

	*e = p->data;
	free(p);
	return true;
}
bool insert_tail(NODE*phead, elem_type e)
{
	if (phead == NULL)
	{
		return false;
	}
	NODE*p = phead;
	while (p->next != NULL)
	{
		p = p->next;
	}
	NODE*tmp = alloc_node(e);
	p->next = tmp;
	return true;
}

bool push(NODE*phead, elem_type e)
{
	if (phead == NULL)
	{
		return false;
	}
	insert_tail(phead, e);
	return true;
}

bool pop(NODE*phead, elem_type *e)
{
	if (phead == NULL)
	{
		return false;
	}
	elem_type tmp;
	delete_head(phead, &tmp);
	*e = tmp;
	return true;
}

bool show(NODE*phead, void(*pfunc)(elem_type))
{
	if (phead == NULL)
	{
		return false;
	}
	NODE*p = phead->next;
	while (p != NULL)
	{
		pfunc(p->data);
		p = p->next;
	}
	printf("\n");
	return true;
}
int get_base(int *arr, int len)
{
	int max = arr[0];
	for (int i = 1; i<len; i++)
	{
		if (max < arr[i])
		{
			max = arr[i];
		}
	}
	int count = 0;

	while (max != 0)
	{
		max /= 10;
		count++;
	}
	return count;
}



void base_sort(int *arr, int len, int radix)
{
	int base = get_base(arr, len);
	NODE *p = (NODE*)malloc(sizeof(NODE)*radix);
	assert(p != NULL);
	for (int a = 0; a < radix; a++)
	{
		p[a].next = NULL;
	}
	for (int j = 0; j < base; j++)
	{
		int *brr = arr;
		for (int i = 0; i < len; i++)
		{
			int b = brr[i] / (int)pow((double)radix,j) % radix;
			push(&p[b], brr[i]);//每次将数组中每个值根据最低位压入相应的队列中
		}
		for (int k = 0; k < radix; k++)
		{
			while (p[k].next != NULL)
			{
				pop(&p[k], brr);
				brr++;
			}
		}
	}

	free(p);
}
bool show_arr(elem_type *p, int len,void(*pfunc)(elem_type e))
{
	if (p == NULL)
	{
		return false;
	}
	for (int i = 0; i < len;i++)
	{
		pfunc(p[i]);
	}
	printf("\n");
	return true;
}