#include "SEQ_QUEUE.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

SEQ_QUEUQ *init_queue()
{
	SEQ_QUEUQ *p = (SEQ_QUEUQ*)malloc(sizeof(SEQ_QUEUQ));
	assert(p != NULL);

	p->head = 0;
	p->tail = 0;
	return p;
}

bool destory_queue(SEQ_QUEUQ *p)
{
	if (p == NULL)
	{
		return false;
	}
	free(p);
	return true;
}

bool clear_queue(SEQ_QUEUQ *p)
{
	if (p == NULL)
	{
		return false;
	}

	p->head = 0;
	p->tail = 0;

	return true;
}


bool is_empty(SEQ_QUEUQ *p)
{
	if (p == NULL)
	{
		return false;
	}
	
	return p->head == p->tail;
}
bool is_full(SEQ_QUEUQ *p)
{
	if (p == NULL)
	{
		return false;
	}
	if (((p->tail+1) % MAX_SIZE) == p->head)
	{
		return true;
	}
	return false;
}

bool get_head(SEQ_QUEUQ *p, elem_type *e)
{
	if (p == NULL || is_empty(p))
	{
		return false;
	}

	*e = p->data[p->head];
	return true;
}

bool push(SEQ_QUEUQ *p, elem_type e)
{
	if (p == NULL || is_full(p))
	{
		return false;
	}
	p->data[p->tail] = e;
	p->tail=(p->tail+1) % MAX_SIZE;


	return true;
}
bool pop(SEQ_QUEUQ *p, elem_type *e)
{
	if (p == NULL || is_empty(p))
	{
		return false;
	}

	*e = p->data[p->head];
	p->head=(p->head+1)%MAX_SIZE;

	return true;
}

bool show(SEQ_QUEUQ *p)
{
	if (p == NULL || is_empty(p))
	{
		return false;
	}

	int i = p->head;
	while (i != p->tail)
	{
		printf("%d ", p->data[i]);
		i = (i + 1) % MAX_SIZE;
	}
	printf("\n");
	return true;
}