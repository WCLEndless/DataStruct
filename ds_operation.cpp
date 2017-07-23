#include <stdio.h>
#include <stdlib.h>
#include<assert.h>
#include<string.h>

#include"stack.h"
#include"ds_operation.h"



enum
{
	OUT = 0, IN = 1
};    

int get_prio(char oper, int st)
{
	if (st == OUT)
	{
		switch (oper)
		{
		case '+':
			return ADD_OUT;
		case '-':
			return SUB_OUT;
		case '*':
			return MUL_OUT;
		case '/':
			return DIV_OUT;
		case '(':
			return LEFT_OUT;
		case ')':
			return RIGHT_OUT;
		default:
			return ERROR;
		}
	}
	else if (st == IN)
	{
		switch (oper)
		{
		case '+':
			return ADD_IN;
		case '-':
			return SUB_IN;
		case '*':
			return MUL_IN;
		case '/':
			return DIV_IN;
		case '(':
			return LEFT_IN;
		case ')':
			return RIGHT_IN;//error
		default:
			return ERROR;
		}
	}
	else
	{
		return ERROR;
	}
}

void tran_last(char *mid_expr, char *last_expr)
{
	SEQ_STACK *stack = init_seqstack();
	char *p = mid_expr;
	char *s = last_expr;

	char oper1 = 0;//栈外操作符  +
	char oper2 = 0;//栈内操作符  +

	int op1_prio = 0;
	int op2_prio = 0;

	while (*p != '\0')
	{
		if (*p == '+' || *p == '-' || *p == '*' || *p == '/' || *p == '(' || *p == ')')
		{
			if (is_empty(stack))
			{
				push(stack, *p);
				p++;
			}
			else//栈内不为空
			{
				oper1 = *p;
				get_top(stack, &oper2);
				op1_prio = get_prio(oper1, OUT);
				op2_prio = get_prio(oper2, IN);
				if (op1_prio > op2_prio)//栈外》栈内  ，入栈
				{
					push(stack, *p);
					p++;
					*s++ = ' ';
				}
				else if (op1_prio < op2_prio)//栈外《栈内  ，栈内出栈，P不动
				{
					pop(stack, s);
					s++;
					*s++ = ' ';
				}
				else//一样，屏蔽括号
				{
					pop(stack, &oper2);
					p++;
				}
			}
		}
		else if (*p >= '0' && *p <= '9'||*p=='.')
		{ 
			*s++ = *p++;
		}
		else if (*p == ' ')
		{
			p++;
			*s++ = ' ';
		}
		else
		{
			printf("中缀表达式输入错误，请重新输入\n");
			exit(-1);
		}
	}

	while (!is_empty(stack))
	{
		pop(stack, s);
		s++;
	}

	*s = 0;
	destory_seqstack(stack);
}



elem_ty get_last(char *mid_expr)
{
	char last_expr[128] = "";

	tran_last(mid_expr, last_expr);
	int len = strlen(last_expr);

	elem_ty *stack = (elem_ty *)malloc(sizeof(elem_ty) * len);
	//assert(stack != NULL);
	//int  stack[20] = { 0 };
	int top = 0;

	char *p = last_expr;

	elem_ty op1 = 0;
	elem_ty op2 = 0;

	while (*p != 0)
	{
		char tmp[20] = { 0 };
		char *ptmp = tmp;

		while (*p != 0 && (*p >= '0' && *p <= '9')||*p=='.')
		{
			*ptmp++ = *p++;
		}
		if (ptmp != tmp)
		{
			if (strchr(tmp, '.') != NULL)
			{
				stack[top++] = atof(tmp);
			}
			else
			{
				stack[top++] = atoi(tmp);
				//stack[top++] = *((int*)tmp);
			}
		}
		if (*p == '+' || *p == '-' || *p == '*' || *p == '/')
		{
			op2 = stack[--top];
			op1 = stack[--top];

			switch (*p)
			{
			case '+':
				stack[top++] = op1 + op2;
				break;
			case '-':
				stack[top++] = op1 - op2;
				break;
			case '*':
				stack[top++] = op1*op2;
				break;
			case '/':
				stack[top++] = op1 / op2;
				break;
			default:
				break;
			}
		}
		p++;
	}
	elem_ty tmp1 = stack[--top];
	free(stack);
	return tmp1;

}
