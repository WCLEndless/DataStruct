#include"kill.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
static NODE* alloc_node(elem_type e)
{
	NODE*p = (NODE*)malloc(sizeof(NODE));
	assert(p != NULL);
	p->id = e;
	p->next = NULL;
	p->prio = NULL;
	return p;
}
void my_print(elem_type e)
{
	printf("%d±»É±£¡\n", e);
}
NODE *CreateLoopList(elem_type e)
{
	if (e == 0)
	{
		return NULL;
	}

	NODE *p = alloc_node(e);
	NODE*s = p;
	elem_type num = e - 1;
	while (num>=1)
	{
		insert_head(&p,num);
		num--;
	}
	s->next = p;
	p->prio = s;
	
	return p;
}



bool insert_head(NODE** p,elem_type e)
{
	if (*p == NULL)
	{
		return false;
	}
	NODE*tmp = alloc_node(e);
	(*p)->prio = tmp;
	
	tmp -> next = *p;
	tmp->prio = NULL;
	*p = tmp;
	
	return true;
}
bool show(NODE*p,void(*pfunc)(elem_type e))
{
	if (pfunc == NULL)
	{
		return false;
	}
	pfunc(p->id);
	return true;
}
bool del_value_by_pos( NODE*pos)
{
	if (pos==NULL)
	{
		return false;
	}
	NODE*tmp = pos;
	pos->prio->next = pos->next;
	pos->next->prio = pos->prio;
	show(tmp,my_print);
	free(tmp);
	
	return true;
}

int Kill(NODE **r, int gap)
{

	NODE *p = *r;


	while (p->next != p  )
	{
		for (int i = 0; i<gap - 1; i++)
		{
			p = p->next;
		}
		NODE*tmp = p;
		p = p->next;
		del_value_by_pos(tmp);
		
	}

	int rs = p->id;
	free(p);
	*r = NULL;

	return rs;
}
