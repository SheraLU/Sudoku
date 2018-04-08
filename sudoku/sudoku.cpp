#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<stdio.h>
#include<string>
#include<string.h>
#include<algorithm> 
#include<fstream>

using namespace std;

int flag;//可行解求出
int map[9][9];
int num[3][9][9];//0：每行可填解，1,：每列可填解，2：每框可填解
int ini[9] = { 3,1,2,4,5,6,7,8,9 };
int row1[8] = { 3,6,2,5,8,1,4,7 };//以3为基数进行移动

void creat(int n) 
{
	int i = 0, j = 0, k = 0;
	int rows[9];
	ofstream output;
	output.open("../BIN/sudoku.txt");
	while (next_permutation(ini+1, ini+9)&&n)//首行除首元素以外全排列 8!=40320
	{
		for (i = 0; i <= 7; i++)
			output << ini[i] << ' ';
		output << ini[8] << endl;
		for (j = 0; j < 8; j++)//其余八行通过首行移动得到
		{
			for (k = 0; k < 8; k++)
			{
				rows[k] = ini[(k + row1[j]) % 9];
				output << rows[k] << ' ';
			}
			rows[8] = ini[(8 + row1[j]) % 9];//每行最后无空格
			output << rows[8] << endl;
		}
		if (n != 1)
		output << endl;//最后一个终局后不换行
		n--;

		while (next_permutation(row1 + 2, row1 + 5)&&n)
			while(next_permutation(row1 + 5, row1 + 8)&&n)
			{
				for (i = 0; i <= 7; i++)
					output << ini[i] << ' ';
				output << ini[8] << endl;
				for (j = 0; j < 8; j++)
				{
					for (k = 0; k < 8; k++)
					{
						rows[k] = ini[(k + row1[j]) % 9];
						output << rows[k] << ' ';
					}
					rows[8] = ini[(8 + row1[j]) % 9];//每行最后无空格
					output << rows[8] << endl;
				}
					output << endl;
					n--;
			}
	}
	output.close();
}

void search(int x,int y)
{
	int i, j;
	if (y == 9)
	{
		x++;
		y = 0;
	}
	if (x > 8)
	{
		ofstream output;
		output.open("../BIN/sudoku.txt", ios::app);
		flag = 1;
		for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 8; j++)
				output << map[i][j] << " ";
			output << map[i][8] << endl;
		}
		output << endl;
		return;
	}
	if (map[x][y] == 0)
	{
		for (i = 1; i <= 9; i++)
		{
			if (num[0][x][i] == 0 && num[1][y][i] == 0 && num[2][3 * (y / 3) + (x / 3)][i] == 0)
			{
				map[x][y] = i;
				if (flag)break;
				num[0][x][i] = 1;
				num[1][y][i] = 1;
				num[2][3 * (y / 3) + (x / 3)][i] = 1;
				search(x, y + 1);
				num[0][x][i] = 0;
				num[1][y][i] = 0;
				num[2][3 * (y / 3) + (x / 3)][i] = 0;
			}
		}
	}
	else
		search(x, y + 1);
}

void solve(char path[])
{
	ifstream input;
	input.open(path);
	ofstream output;
	output.open("../BIN/sudoku.txt");
	output.close();
	int i, j;
	while (!input.eof())
	{
		flag = 0;
		memset(num, 0, sizeof(num));
		for (i = 0; i < 9; i++)
			for (j = 0; j < 9; j++)
			{
				input >> map[i][j];
				if (map[i][j])
				{
					num[0][i][map[i][j]] = 1;
					num[1][j][map[i][j]] = 1;
					num[2][3 * (j / 3) + (i / 3)][map[i][j]] = 1;
				}
			}
		search(0, 0);
	}
	input.close();
}

int main(int argc, char* argv[])
{
	int n;
	char c[5], path[200];
	if (argc>2)
	{
		strcpy(c, argv[1]);
		if (c[1] == 'c')
		{//检测命令行参数-c
			n = atoi(argv[2]);//生成终局数
			if (n)
			{
				creat(n);
			}
			else
				cout << "wrong input" << endl;
		}
		else if (c[1] == 's')
		{//检测命令行参数-s
			strcpy(path, argv[2]);
			solve(path);
		}
		else
			cout << "wrong input" << endl;
	}
	else
		cout << "wrong input" << endl;
}