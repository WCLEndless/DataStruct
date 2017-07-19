#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>

#include"file_sort.h"



static int  put_suitable_position(int *p, int head, int tail)
{
	//int head = 0;
	//int tail = len - 1;
	int tmp = p[head];
	while (head < tail)
	{
		while (p[tail] >= tmp && head < tail)
		{
			tail--;
		}
		p[head] = p[tail];
		while (p[head] <= tmp&&head<tail)
		{
			head++;
		}
		p[tail] = p[head];
	}
	p[head] = tmp;
	return head;
}
static void sort(int *p, int head, int tail)//递归实现快速排序
{
	if (head < tail)
	{
		int base = put_suitable_position(p, head, tail);
		sort(p, head, base - 1);
		sort(p, base + 1, tail);//这个tail是上一次的尾，这个递归从左边递归结束一直到右边递归结束完成整个递归排序
	}
}
void quick_sort(int *p, int len)
{
	sort(p, 0, len - 1);
}

void part_sort(char*wait_to_sort_file)
{
	FILE*fr = fopen(wait_to_sort_file, "rb");
	FILE*tmp = fopen("f://tmp.txt","wb");
	elem_type *buff = (elem_type*)malloc(sizeof(elem_type)*MEM_SIZE);
	assert(fr != NULL && buff != NULL);
	int count = 0;
	while ((count = fread(buff, sizeof(elem_type), MEM_SIZE, fr)) != NULL)
	{
		quick_sort(buff, count);
		//fwrite(buff,count,1,tmp);
		//int tmp_count = (FILE_ARR_SIZE - i) > MEM_SIZE ? MEM_SIZE : (FILE_ARR_SIZE - i);
		fwrite(buff, sizeof(elem_type), count, tmp);
	}
	
	fclose(fr);
	fclose(tmp);
	remove(wait_to_sort_file);//先关闭文件才能改名称或者删除
	rename("f://tmp.txt", wait_to_sort_file);
	free(buff);
}

void init_file(char*wait_to_sort_file)
{
	FILE*fw = fopen(wait_to_sort_file,"wb");
	int *buff = (elem_type*)malloc(MEM_SIZE*sizeof(elem_type));
	assert(fw!=NULL&&buff!=NULL);
	srand((unsigned)(time(NULL)));
	for (int i = 0; i < FILE_ARR_SIZE; i += MEM_SIZE)
	{
		int count = (FILE_ARR_SIZE - i) > MEM_SIZE ?MEM_SIZE : (FILE_ARR_SIZE-i);
		for (int j = 0; j < count; j++)
		{	
			buff[j] = rand() % FILE_ARR_SIZE;
		}
		fwrite(buff, sizeof(elem_type), count, fw);
	}
	fclose(fw);
	free(buff);
}



void meger(int gap, char*file_arr)//gap = ITEM*2
{
	char*tmp_file = "f://tmp.txt";
	FILE *fr = fopen(file_arr, "rb");
	FILE *fw = fopen(tmp_file, "wb");
	int *arr = (int *)malloc(sizeof(int) * MEM_SIZE);
	int *brr = (int *)malloc(sizeof(int) * MEM_SIZE);
	int *crr = (int *)malloc(sizeof(int) * MEM_SIZE);
	assert(fw != NULL && fr != NULL && arr != NULL && brr != NULL && crr != NULL);

	int L1 = 0;
	int H1 = L1 + gap - 1;
	int L2 = H1 + 1;
	int H2 = L2 + gap- 1 < FILE_ARR_SIZE ? L2 + gap - 1 : FILE_ARR_SIZE - 1;

	

	while (L2 < FILE_ARR_SIZE )
	{
		int i = 0;
		int j = 0;
		int k = 0;
		fseek(fr, L1*sizeof(elem_type), SEEK_SET);
		fread(arr, sizeof(elem_type), MEM_SIZE, fr);
		fseek(fr, L2*sizeof(elem_type), SEEK_SET);//
		fread(brr, sizeof(elem_type), MEM_SIZE, fr);
		while (L1 <= H1 && L2 <= H2)
		{
			if (arr[i] <= brr[j])
			{
				crr[k++] = arr[i++];
				L1++;
			}
			else
			{
				crr[k++] = brr[j++];
				L2++;
			}
			if (k==MEM_SIZE)
			{
				fwrite(crr, sizeof(elem_type), MEM_SIZE, fw);
				k = 0;
			}
			if (i % (MEM_SIZE + 1) == MEM_SIZE)
			{
				fseek(fr, L1*sizeof(elem_type), SEEK_SET);
				fread(arr, sizeof(elem_type), (MEM_SIZE<(H1-L1+1)?MEM_SIZE:(H1-L1+1)), fr);
				i = 0;
			}
			if (j % (MEM_SIZE + 1) == MEM_SIZE )
			{
				fseek(fr, L2*sizeof(elem_type), SEEK_SET);
				fread(brr, sizeof(elem_type), (MEM_SIZE<(H2 - L2+1) ? MEM_SIZE : (H2 - L2+1)), fr);
				j = 0;
			}
		}
		fwrite(crr, sizeof(elem_type), k, fw);
		//elem_type*tmp = (elem_type*)malloc(sizeof(elem_type)*MEM_SIZE);
		while(L1 <= H1)//IO效率可以提升
		{
			int count = (H1 - L1+1) >= MEM_SIZE ? MEM_SIZE : (H1 - L1+1);
			fseek(fr, L1*sizeof(elem_type), SEEK_SET);
			fread(arr, sizeof(elem_type), count, fr);
			fwrite(arr, sizeof(elem_type), count, fw);
			L1 += count;
		}
		while(L2 <= H2)//IO效率可以提升
		{
			int count = (H2 - L2 + 1) >= MEM_SIZE ? MEM_SIZE : (H2 - L2 + 1);
			fseek(fr, L2*sizeof(elem_type), SEEK_SET);
			fread(brr, sizeof(elem_type), count, fr);
			fwrite(brr, sizeof(elem_type), count, fw);
			L2 += count;
		}

		 L1 = H2 + 1;
		 H1 = L1 + gap - 1;
		 L2 = H1 + 1;
		 H2 = L2 + gap - 1 < FILE_ARR_SIZE ? L2 + gap - 1 : FILE_ARR_SIZE - 1;
	}

	while(L1 <= FILE_ARR_SIZE - 1)
	{
		int count = (FILE_ARR_SIZE - L1) >= MEM_SIZE ? MEM_SIZE : (FILE_ARR_SIZE - L1);
		fseek(fr, L1*sizeof(elem_type), SEEK_SET);
		fread(crr, sizeof(elem_type), count , fr);
		fwrite(crr, sizeof(elem_type), count , fw);
		L1 += count;
	}
	
	free(arr);
	free(brr);
	free(crr);

	fclose(fw);
	fclose(fr);

	remove(file_arr);
	rename(tmp_file, file_arr);
}


void meger_file_arr(char*file_arr)
{
	part_sort(file_arr);
	for (int i = MEM_SIZE; i<FILE_ARR_SIZE; i = i * 2)
	{
		meger(i,file_arr);
	}
}


void show(char*file_arr, void(*pfunc)(elem_type e))
{
	FILE*fr = fopen(file_arr,"rb");
	elem_type *buff = (elem_type*)malloc(sizeof(elem_type)*MEM_SIZE);
	assert(fr != NULL && buff!=NULL);
	int count = 0;
	while ((count=fread(buff,sizeof(elem_type),MEM_SIZE,fr))!=NULL)
	{
		for (int i = 0; i < count; i++)
		{
			pfunc(buff[i]);
			if (i % 10 == 9)
			{
				printf("\n");
			}
		}
	}
	printf("\n");
	fclose(fr);
	free(buff);
}



int * init_array(int len)//获得len个长度的随机数组
{
	int *p = (int*)malloc(sizeof(int)*len);
	srand((unsigned)(time(NULL)));
	for (int i = 0; i < len; i++)
	{
		p[i] = rand() % len;
	}
	return p;
}