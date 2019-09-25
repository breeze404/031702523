#include <iostream>
#include<fstream>
#include <stdlib.h>
#include <string.h>
using namespace std;

int arr[11][11] = { 0 };
int xrr[11][11] = { 0 };//第一维是第几行，第二维是第几个数
int yrr[11][11] = { 0 };//第一维是第几列，第二维是第几个数
int mrr[11][11] = { 0 };//第一维是第几个宫，第二维是第几个数
ifstream fin("in.txt");
ofstream fout("out.txt");
int checkm(int x, int y,int a , int b)//找到当前格所在宫的编号
{
	int n, m;
	n = a / x;
	if ((a%x )!= 0)
		n++;
	m = b / y;
	if ((b%y)!= 0)
		m++;
	return (n - 1)*x + m;
}
void read(int x,int a,int b)//文件流输入
{
	int i,j,k;
	for (i=1;i<=x;i++)
		for (j = 1; j <=x; j++)
		{
			fin >> arr[i][j];
			k = arr[i][j];
			if (k != 0)
			{
				xrr[i][k] = 1;//把初始化时行上当前数字置为不可用
				yrr[j][k] = 1;//原理同上
				if (a != 1)
					mrr[checkm(a,b,i,j)][k] = 1;//原理同上
			}
		}
}
void print(int x)//输出数独
{
	int i, j;
	for (i = 1; i <=x; i++)
	{
		for (j = 1; j <=x; j++)
		{
			fout << arr[i][j]<<' ';
		}
		fout << endl;
	}
}
bool checkandwrite(int x,int y,int type,int a,int b)//找到空白的格子，找到并填入合适的数字
{
	if (x == type && y == (type + 1))//遍历完数独最后一个格子
		return true;
	else if (y == (type + 1))//遍历换行
	{
		x++;
		y = 1;
	}
	if ( arr[x][y] == 0 )//找到了空白格子
	{
		int num = checkm(a, b, x, y);
		for ( int n = 1; n <= type; n++ )
		{
			if (xrr[x][n] == 0 && yrr[y][n] == 0&&mrr[num][n]==0)
			{
				arr[x][y] = n;//填入数字，同时更新可用数字的三个数组
				xrr[x][n] = 1;
				yrr[y][n] = 1;
				if (a!=1)
					mrr[num][n] = 1;
				if ( checkandwrite(x, y + 1, type,a,b) == 0  )
				{
					arr[x][y] = 0;//当前位置无数可填，返回上一级，并重置为原来状态
					xrr[x][n] = 0;
					yrr[y][n] = 0;
					if (a!=1)
						mrr[num][n] = 0;
				}
				else
					return true;
			}
		}
		return false;
	}
	else
		return checkandwrite(x, y + 1, type,a,b);//当前格子已有数据，直接进行下一个格子
	
}
int main(int argc, char *argv[])
{
	int x=1, y=1,type = 1, n = 1,a=1,b=1;
	type = atoi(argv[2]);//文件流输入类型
	n = atoi(argv[4]);//文件流输入个数
	if (type == 4) {//宫判断参数
		a = 2;
		b = 2;
	}
	else if (type == 6) {
		a = 2;
		b = 3;
	}
	else if (type == 8) {
		a = 4;
		b = 2;
	}
	else if (type == 9) {
		a = 3;
		b = 3;
	}
	else {
		a = 1;
		b = 1;
	}
	for (int i = 0; i < n; i++)//运算出数独结果
	{
		read(type,a,b);
		if (checkandwrite(1, 1, type,a,b))
			print(type);
		memset(arr, 0, sizeof(arr));//重置数独和可用梳子表盘
		memset(xrr, 0, sizeof(xrr));
		memset(yrr, 0, sizeof(yrr));
		memset(mrr, 0, sizeof(mrr));
		fout << endl;
	}

	return 0;
}