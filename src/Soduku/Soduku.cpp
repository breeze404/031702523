#include <iostream>
#include<fstream>
#include <stdlib.h>
#include <string.h>
using namespace std;

int arr[11][11] = { 0 };
int xrr[11][11] = { 0 };//��һά�ǵڼ��У��ڶ�ά�ǵڼ�����
int yrr[11][11] = { 0 };//��һά�ǵڼ��У��ڶ�ά�ǵڼ�����
int mrr[11][11] = { 0 };//��һά�ǵڼ��������ڶ�ά�ǵڼ�����
ifstream fin("in.txt");
ofstream fout("out.txt");
int checkm(int x, int y,int a , int b)//�ҵ���ǰ�����ڹ��ı��
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
void read(int x,int a,int b)//�ļ�������
{
	int i,j,k;
	for (i=1;i<=x;i++)
		for (j = 1; j <=x; j++)
		{
			fin >> arr[i][j];
			k = arr[i][j];
			if (k != 0)
			{
				xrr[i][k] = 1;//�ѳ�ʼ��ʱ���ϵ�ǰ������Ϊ������
				yrr[j][k] = 1;//ԭ��ͬ��
				if (a != 1)
					mrr[checkm(a,b,i,j)][k] = 1;//ԭ��ͬ��
			}
		}
}
void print(int x)//�������
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
bool checkandwrite(int x,int y,int type,int a,int b)//�ҵ��հ׵ĸ��ӣ��ҵ���������ʵ�����
{
	if (x == type && y == (type + 1))//�������������һ������
		return true;
	else if (y == (type + 1))//��������
	{
		x++;
		y = 1;
	}
	if ( arr[x][y] == 0 )//�ҵ��˿հ׸���
	{
		int num = checkm(a, b, x, y);
		for ( int n = 1; n <= type; n++ )
		{
			if (xrr[x][n] == 0 && yrr[y][n] == 0&&mrr[num][n]==0)
			{
				arr[x][y] = n;//�������֣�ͬʱ���¿������ֵ���������
				xrr[x][n] = 1;
				yrr[y][n] = 1;
				if (a!=1)
					mrr[num][n] = 1;
				if ( checkandwrite(x, y + 1, type,a,b) == 0  )
				{
					arr[x][y] = 0;//��ǰλ���������������һ����������Ϊԭ��״̬
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
		return checkandwrite(x, y + 1, type,a,b);//��ǰ�����������ݣ�ֱ�ӽ�����һ������
	
}
int main(int argc, char *argv[])
{
	int x=1, y=1,type = 1, n = 1,a=1,b=1;
	type = atoi(argv[2]);//�ļ�����������
	n = atoi(argv[4]);//�ļ����������
	if (type == 4) {//���жϲ���
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
	for (int i = 0; i < n; i++)//������������
	{
		read(type,a,b);
		if (checkandwrite(1, 1, type,a,b))
			print(type);
		memset(arr, 0, sizeof(arr));//���������Ϳ������ӱ���
		memset(xrr, 0, sizeof(xrr));
		memset(yrr, 0, sizeof(yrr));
		memset(mrr, 0, sizeof(mrr));
		fout << endl;
	}

	return 0;
}