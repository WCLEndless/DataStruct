#include <stdio.h>
#include <stdlib.h>
#include<assert.h>
#include<string.h>

#include"stack.h"
#include"maze.h"




void find_maze(char(*p)[ARR_SIZE], int x, int y)
{
	int count = 1;
	SEQ_STACK *phead = init_seqstack();
	while (count != 0)
	{
		count = 0;
		if (p[x - 1][y] == '0' || p[x - 1][y] == '!')
		{
			push(phead, x );
			push(phead, y);
			p[x][y] = '1';
			x -= 1;
			count++;
		}
		else if (p[x][y - 1] == '0' || p[x][y-1] == '!')
		{
			push(phead, x);
			push(phead, y);
			p[x][y] = '1';
			y -= 1;
			count++;
		}
		else if (p[x + 1][y] == '0' || p[x+ 1][y] == '!')
		{
			push(phead, x );
			push(phead, y);
			p[x][y] = '1';
			x += 1;
			count++;
		}
		else if (p[x][y + 1] == '0' || p[x][y+1] == '!')
		{
			push(phead, x);
			push(phead, y);
			p[x][y] = '1';
			y += 1;
			count++;
		}
		if (p[x][y] == '!')
		{
			printf("出口为%d,%d\n", x, y);
			//show_path(phead);
			//printf("(%d,%d)\n",x,y);
			destory_seqstack(phead);
			return;
		}
		else if (count == 0 && is_empty(phead) != true)
		{
			p[x][y] = '1';
			pop(phead, &y);
			pop(phead, &x);
			count++;
		}
	}
	printf("没有出口！\n");
	destory_seqstack(phead);
}






/*

void show()
{
for (int i = 0; i < 6; i++)
{
for (int j = 0; j < 13; j++)
{
printf("%c", maze[i][j]);
}
printf("\n");
}
printf("\n");
}

void find_maze(int x, int y)
{
if (maze[x][y] == '1' || maze[x][y] == '#')
{
return;
}
if (maze[x][y] == '!')
{
printf("出口为%d,%d\n", x, y);
return;
}
maze[x][y] = '#';
//show();

find_maze(x - 1, y);
find_maze(x, y - 1);
find_maze(x + 1, y);
find_maze(x, y + 1);
}*/

