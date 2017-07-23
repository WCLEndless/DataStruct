#include "stack.h"

#include <stdlib.h>
#include <assert.h>

//初始化栈 
SEQ_STACK *init_seqstack()
{
	SEQ_STACK *p = (SEQ_STACK *)malloc(sizeof(SEQ_STACK));
	assert(p != NULL);

	p->top = 0;

	return p;
}

//销毁栈 
bool destory_seqstack(SEQ_STACK *p)
{
	if (p == NULL)
	{
		return false;
	}

	free(p);

	return true;
}

//清空栈 
bool clear_sqestack(SEQ_STACK *p)
{
	if (p == NULL)
	{
		return false;
	}
	p->top = 0;
	return true;
}

//判断是否为空栈 
bool is_empty(SEQ_STACK *p)
{
	if (p == NULL)
	{
		return false;
	}

	return p->top == 0;
}

//获取栈的大小 
int get_length(SEQ_STACK *p)
{
	return p->top;
}

//获取栈顶元素，不出栈 
bool get_top(SEQ_STACK *p, elem_type *e)
{
	if (p == NULL || is_empty(p))
	{
		return false;
	}

	*e = p->data[p->top - 1];

	return true;
}


bool is_full(SEQ_STACK *p)
{
	if (p == NULL)
	{
		return true;
	}

	return p->top == MAX_SIZE;
}
//入栈 
bool push(SEQ_STACK *p, elem_type e)
{
	if (p == NULL || is_full(p))
	{
		return false;
	}

	p->data[p->top++] = e;
	//p->top++;

	return true;
}

//出栈 
bool pop(SEQ_STACK *p, elem_type *e)
{
	if (p == NULL || is_empty(p))
	{
		return false;
	}

	*e = p->data[--p->top];
	return true;
}
