
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "link_queue_stack.h"

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
bool insert_tail(NODE*phead,elem_type e)
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

bool push_queue(NODE*phead, elem_type e)
{
	if (phead==NULL)
	{
		return false;
	}
	insert_tail(phead, e);
	return true;
}

bool pop_queue(NODE*phead, elem_type *e)
{
	if (phead == NULL)
	{
		return false;
	}
	elem_type tmp;
	delete_head(phead,&tmp);
	*e = tmp;
	return true;
}

bool show(NODE*phead,void (*pfunc)(elem_type))
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

NODE*p = init_link_list_ex();
NODE*s = init_link_list_ex();

void  push(elem_type e)
{

	if (is_empty(p) != true)
	{
		insert_tail(p, e);
	}
	else
	{
		insert_tail(s, e);
	}
}

elem_type pop()
{
	elem_type result;
	if (is_empty(p) != true)
	{
		while (p->next == NULL)
		{
			elem_type tmp;
			delete_head(p, &tmp);
			insert_tail(s, tmp);
			p = p->next;
		}
		result = p->data;
		if (is_empty(s) != true)
		{
			while (s->next == NULL)
			{
				elem_type tmp;
				delete_head(s, &tmp);
				insert_tail(p, tmp);
				s = s->next;
			}
			result = s->data;
		}
	
	}
	return result;
}