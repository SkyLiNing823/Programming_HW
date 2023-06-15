#include <iostream>
#include <conio.h>
#include <fstream> 
using namespace std;

void init(int p[][9][10]);
void update(int p[][9][10],int R,int C,int N);
void Sudoku_Read(int Qno, int Q[][9], int p[][9][10]);
void Sudoku_Print(int Q[][9],int A[][9],int R,int C);
int Sudoku_Check(int p[][9][10],int R,int C);
void MainUI(int Q[][9],int A[][9]);

int main()
{
	int r,c,n,modified = 1,flag = 0;
	int Q[9][9];
	int A[9][9],A2[9][9];
	int pool[9][9][10];
	init(pool);
	Sudoku_Read(1,Q,pool);
	for(r=0;r<9;r++)
		for(c=0;c<9;c++)
		{
			A[r][c] = Q[r][c];
			A2[r][c] = Q[r][c];
		}
	while(flag==0)
	{
		cout << endl;
		MainUI(Q,A2);
		while(modified==1)
		{
			modified = 0;
			for(r=0;r<9;r++)
			{
				for(c=0;c<9;c++)
				{
					if(A[r][c]==0)
					{
						n = Sudoku_Check(pool,r,c); //0-9
						if(n>0)
						{
							A[r][c] = n;
							update(pool,r,c,n);
							modified = 1;
						}
					}
				}
			}
		}	
		flag=1;
		for(r=0;r<9;r++)
		{
			for(c=0;c<9;c++)
			{
				if(A[r][c]!=A2[r][c])
					flag=0;
			}
		}
		if(flag==0)
			cout<<"Error"<<endl;
		system("pause");
	}
	cout<<"You Win"<<endl;
	//HW:check A and A2 equal

	return 0;
}

void MainUI(int Q[][9],int A[][9])
{
	int r=0,c=0;
	char c1,c2;
	do
	{
		Sudoku_Print(Q,A,r,c);
		c1 = getch();
		if(c1==-32)
		{
			c2 = getch();
			switch(c2)
			{
				case 72:
					r = (r+8)%9;
					break;
				case 75:
					c = (c+8)%9;
					break;
				case 77:
					c = (c+1)%9;
					break;
				case 80:
					r = (r+1)%9; 
					break;
			}	
		}
		if(c1>='0'&&c1<='9')
		{
			if(Q[r][c]==0)
				A[r][c] = c1-'0';
		}
	}while(c1!=13);
}

void init(int p[][9][10])
{
	int r,c,n;
	for(r=0;r<9;r++)
		for(c=0;c<9;c++)
			for(n=1;n<=9;n++)
				p[r][c][n] = 1;
}

void update(int p[][9][10],int R,int C,int N)
{
	int r,c,n;
	// the same row
	for(c=0;c<9;c++) 
		p[R][c][N] = 0;
	// the same col
	for(r=0;r<9;r++)
		p[r][C][N] = 0;
	// the same block
	for(r=R/3*3;r<=R/3*3+2;r++)
		for(c=C/3*3;c<=C/3*3+2;c++)
			p[r][c][N] = 0;
	p[R][C][N] = 1;
}

void Sudoku_Read(int Qno, int Q[][9], int p[][9][10])
{
	int r,c,n;
	ifstream fin;
	fin.open("Q1.txt");
	for(r=0;r<9;r++)
	{
		for(c=0;c<9;c++)
		{
			fin >> n;
			Q[r][c] = n;
			if(n>0)
				update(p,r,c,n);
		}
	}
	fin.close();
}

void Sudoku_Print(int Q[][9],int A[][9],int R,int C)
{
	//HW:finish
	int r,c;
	system("cls");
	char left[9][9],right[9][9];
	for(r=0;r<9;r++)
		for(c=0;c<9;c++)
		{
			left[r][c] = ' ';
			right[r][c] = ' ';
		}
	if(Q[R][C]==0)
	{
		left[R][C] = '<';
		right[R][C] = '>';
	}
	else
	{
		left[R][C] = '[';
		right[R][C] = ']';
	}
	for(r=0;r<9;r++)
	{
		for(c=0;c<9;c++)
		{
			cout<<left[r][c];
			if(A[r][c]==0)
				cout << " ";
			else
				cout << A[r][c];
			cout <<right[r][c];
			if(c==2||c==5)
				cout <<"|";
		}
		cout << endl;
		if(r==2||r==5)
			cout << "-----------------------------"<<endl;
	}
}

int Sudoku_Check(int p[][9][10],int R,int C)
{
	//HW:another rule
	int sum=0,n,a,r,c;
	for(n=1;n<=9;n++)
	{
		sum += p[R][C][n];
		if(p[R][C][n]==1)
			a = n;
	}
//	for(r=1;r<=9;r++)
//		for(c=1;c<=9;c++)
	if(sum==1)
		return a;
	else
		return 0;
}
