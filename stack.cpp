#include "stack.h"

#include <stdlib.h>
#include <assert.h>

//��ʼ��ջ 
SEQ_STACK *init_seqstack()
{
	SEQ_STACK *p = (SEQ_STACK *)malloc(sizeof(SEQ_STACK));
	assert(p != NULL);

	p->top = 0;

	return p;
}

//����ջ 
bool destory_seqstack(SEQ_STACK *p)
{
	if (p == NULL)
	{
		return false;
	}

	free(p);

	return true;
}

//���ջ 
bool clear_sqestack(SEQ_STACK *p)
{
	if (p == NULL)
	{
		return false;
	}
	p->top = 0;
	return true;
}

//�ж��Ƿ�Ϊ��ջ 
bool is_empty(SEQ_STACK *p)
{
	if (p == NULL)
	{
		return false;
	}

	return p->top == 0;
}

//��ȡջ�Ĵ�С 
int get_length(SEQ_STACK *p)
{
	return p->top;
}

//��ȡջ��Ԫ�أ�����ջ 
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
//��ջ 
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

//��ջ 
bool pop(SEQ_STACK *p, elem_type *e)
{
	if (p == NULL || is_empty(p))
	{
		return false;
	}

	*e = p->data[--p->top];
	return true;
}
