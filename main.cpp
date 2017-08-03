#include<stdio.h>
#include<stdlib.h>

#include"maze.h"
#include"stack.h"

int main()
{
	char maze[][ARR_SIZE] =
	{
		"1111111110011",
		"1111111111111",
		"1011101111111",
		"1011101111111",
		"1000000000011",
		"10111111110!1",
		"1111111111111"
	};

	find_maze(maze, 1, 1);
	return 0;
}