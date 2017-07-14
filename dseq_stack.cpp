#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"dseq_stack.h"
DSEQ_STACK *init_seqstack()
{
	DSEQ_STACK*p = (DSEQ_STACK*)malloc(sizeof(DSEQ_STACK));
	assert(p != NULL);
	elem_type *tmp = (elem_type *)malloc(sizeof(elem_type)*MAX_SIZE);
	assert(tmp != NULL);
	p->top = 0;
	p->total_size = MAX_SIZE;
	p->data = tmp;
	return p;
}

//销毁栈 
bool destory_seqstack(DSEQ_STACK *p)
{
	if (p == NULL)
	{
		return false;
	}
	free(p->data);
	free(p);
	return true;
}

//清空栈 
bool clear_sqestack(DSEQ_STACK *p)
{
	if (p == NULL)
	{
		return false;
	}
	p->top = 0;
	return true;

}

//判断是否为空栈 
bool is_empty(DSEQ_STACK *p)
{

	if (p == NULL)
	{
		return false;
	}
	return p->top == 0;
}

//获取栈的大小 
int get_length(DSEQ_STACK *p)
{
	if (p == NULL)
	{
		return ERROR;
	}
	return p->top;
}

//获取栈顶元素 
bool get_top(DSEQ_STACK *p, elem_type *e)
{
	if (p == NULL)
	{
		return false;
	}
	p->top--;
	*e = p->top;
	return true;
}
static bool is_full(DSEQ_STACK*p)
{
	if (p == NULL)
	{
		return false;
	}

	return p->top == p->total_size ;
}
static bool auto_increate(DSEQ_STACK*p)
{
	if (p == NULL)
	{
		return false;
	}
	p->data = (elem_type*)realloc(p->data,sizeof(elem_type)*p->total_size*2);
	p->total_size=p->total_size * 2;
	return true;
}
//入栈 
bool push(DSEQ_STACK *p, elem_type e)
{
	if (p == NULL)
	{
		return false;
	}
	if (is_full(p))
	{
		auto_increate(p);
	}
	p->data[p->top] = e;
	p->top++;
	return true;

}

//出栈 
bool pop(DSEQ_STACK *p, elem_type *e)
{
	if (p == NULL||p->top==0)
	{
		return false;
	}
	*e = p->data[--p->top];
	return true;
}


bool my_itoa(int num, char *str, int radix)
{
	DSEQ_STACK *stack = init_seqstack();
	char index[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	while (num != 0)
	{
		push(stack, num%radix);
		num = num / radix;
	}

	int tmp;
	while (!is_empty(stack))
	{
		pop(stack, &tmp);
		//printf("%d ", tmp);
		*str = index[tmp];
		str++;
	}
	*str = 0;

	destory_seqstack(stack);
	return true;
}
