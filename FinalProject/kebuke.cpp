#include <stdio.h>
#include <stdlib.h> 
#include <time.h>   
#include <iostream>
#include <string.h>
#include <conio.h>
#include <fstream>
#include <windows.h>
#include <mmsystem.h>
using namespace std;

struct user
{
	char account[13];
	char passwd[13];
	char username[13];
	int login_num;
	int money;
	int sudoku_win;
	int sudoku_lose;
	int guess_win;
	int guess_tie;
	int guess_lose;
};

struct guest
{
	char account[13];
};

struct userlist
{
	int user_num;
	user member[100];
}; 

userlist LoadUsers();
void logo();
void music();
int ordermain(int id,userlist users);
void orderMainScreen(int select,int id,userlist users,int cost);
int orderMainUI(int select,int id,userlist users,int cost);
int drinkcos(int select);
void reloaddrinks(int id,userlist users);
int searchmain(int id,userlist users);
int LoadOrders();
void order(int id,userlist users,int num);
int editmain(int id,userlist users,char pw[]);
int chatmain(int id,userlist users); 
int sudokumain(int id,userlist users);
void sudokuinit(int p[][9][10]);
void sudokuupdate(int p[][9][10],int R,int C,int N);
void sudokuRead(int Qno, int Q[][9], int p[][9][10]);
void sudokuPrint(int Q[][9],int A[][9],int R,int C,int chance);
int sudokuCheck(int p[][9][10],int R,int C);
void sudokuMainUI(int Q[][9],int A[][9],int chance);
int guessmain(int id,userlist users);
void numdigit(int n,int d[]);
void xaxb(int g,int a,int AB[]);
bool islegal(int n);
int Login(userlist users);
void input_account(char ac[]);
void input_password(char ac[],char pw[]);
int create(userlist users,char ac[],char pw[],char un[]);
void MainScreen(int select,int id,userlist users);
int MainUI(int select,int id,userlist users);
void reloadusers(userlist users);
void kebukemain(userlist users);
int kMainUI(int select);
void kMainScreen(int select);
int ksmain(userlist users);
int cashmain(userlist users);
int cashMainUI(int select,int num,userlist users);
void cashMainScreen(int select,int num,userlist users);

int sweat,ice;
char big,bub,fan;
guest guests[13];
int Orderlist[100],sweats[100],ices[100];
char bigs[100],bubs[100],fans[100];
int orderno=0;

int main()
{
	sndPlaySound("M.wav", SND_ASYNC | SND_NODEFAULT|SND_LOOP);	
	userlist users;
	int id;	
	int i;
	users = LoadUsers();
	orderno = LoadOrders();
	id = Login(users);
	if(id==-1)
	{
		id=create(users,users.member[users.user_num].account,users.member[users.user_num].passwd,users.member[users.user_num].username);
		users.user_num++;
	}
	users.member[id].login_num++;
	reloadusers(users);
	LoadUsers();
	if(id==0)
	{
		kebukemain(users);
		return 0;
	}
	int select=1;
	do{
		select=MainUI(select,id,users);
		switch(select){
			case 1:
				users.member[id].money-=ordermain(id,users);
				break;
			case 2:
				searchmain(id,users);
				break;
			case 3:
				editmain(id,users,users.member[id].passwd);
				reloadusers(users);
				break;
			case 4:
				chatmain(id,users); 
				break;
			case 5:
				sudokumain(id,users);
				break;
			case 6:
				guessmain(id,users);
				break;
			case 0:
				reloadusers(users);
				break;
		}
	}while(select!=0);
	return 0; 
} 


void MainScreen(int select,int id,userlist users)
{
	system("cls");
	logo();
	cout<<"\t"<<users.member[id].username<<"�z�n�A�w��Y�{�i���i�A�z�w�n�J��"<<users.member[id].login_num<<"���A�x�Ȫ���"<<users.member[id].money<<"��"<<endl;
	cout<<endl<<"---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;  
	int i;
	char L[7],R[7];
	for(i=0;i<7;i++){
		L[i]=' ';
		R[i]=' ';
	} 
	L[select]='[';
	R[select]=']';
	cout<< L[1]<<"1"<<R[1]<<"Order"<<endl;
	cout<< L[2]<<"2"<<R[2]<<"�d�q��"<<endl;
	cout<< L[3]<<"3"<<R[3]<<"�ק�|���K�X"<<endl;
	cout<< L[4]<<"4"<<R[4]<<"�I���ѫ�"<<endl;
	cout<< L[5]<<"5"<<R[5]<<"Sudoku"<<endl;
	cout<< L[6]<<"6"<<R[6]<<"�q�Ʀr"<<endl;
	cout<< L[0]<<"0"<<R[0]<<"Exit"<<endl;
}

int MainUI(int select,int id,userlist users)
{
	char x,x1;
	do{
		MainScreen(select,id,users);
		x=getch(); 
		if(x==-32){
			x1=getch();
			if(x1==72)
				select=(select+6)%7;
			if(x1==80)
				select=(select+1)%7;
			if(x1==77)
				return select;
		}
		if(x>='0'&& x<='6')
			select = x-'0';
	}while(x!=13);
	return select;
	
}


void logo()
{
		cout<<"---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
		cout<<endl;
		cout<<"\t\t\t\t .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------. "<<endl;
		cout<<"\t\t\t\t| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |"<<endl;
		cout<<"\t\t\t\t| |  ___  ____   | || |  _________   | || |   ______     | || | _____  _____ | || |  ___  ____   | || |  _________   | |"<<endl; 
		cout<<"\t\t\t\t| | |_  ||_  _|  | || | |_   ___  |  | || |  |_   _ \\    | || ||_   _||_   _|| || | |_  ||_  _|  | || | |_   ___  |  | |"<<endl; 
		cout<<"\t\t\t\t| |   | |_/ /    | || |   | |_  \\_|  | || |    | |_) |   | || |  | |    | |  | || |   | |_/ /    | || |   | |_  \\_|  | |"<<endl; 
		cout<<"\t\t\t\t| |   |  __'.    | || |   |  _|  _   | || |    |  __'.   | || |  | '    ' |  | || |   |  __'.    | || |   |  _|  _   | |"<<endl; 
		cout<<"\t\t\t\t| |  _| |  \\ \\_  | || |  _| |___/ |  | || |   _| |__) |  | || |   \\ `--' /   | || |  _| |  \\ \\_  | || |  _| |___/ |  | |"<<endl; 
		cout<<"\t\t\t\t| | |____||____| | || | |_________|  | || |  |_______/   | || |    `.__.'    | || | |____||____| | || | |_________|  | |"<<endl;
		cout<<"\t\t\t\t| |              | || |              | || |              | || |              | || |              | || |              | |"<<endl;
		cout<<"\t\t\t\t| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |"<<endl;
		cout<<"\t\t\t\t '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------' "<<endl; 
		cout<<endl;
		cout<<endl;
		cout<<"---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;  
}
int ordermain(int id,userlist users)
{
	ifstream fin;
	ofstream fout;
	int select=1,cost=0,i=0,t=0;
	char x;
	int tOrderlist[100],tsweats[100],tices[100];
	char tbigs[100],tbubs[100],tfans[100];
	do{
		select=orderMainUI(select,id,users,cost);
		if(select>=1 && select<=5)
		{
			cost+=drinkcos(select);
			tOrderlist[t]=select;
			tbigs[t]=big;
			tbubs[t]=bub;
			tfans[t]=fan;
			tsweats[t]=sweat;
			tices[t]=ice;
			t++;
		}
		else if(select==6)
		{
			int addmoney;
			if(users.member[id].money < cost)
			{
				system("cls");
				logo();
				cout<<"�l�B���� �п�ܥR�Ȥ覡(1)�״�/(2)�ƿW/(3)�q�Ʀr:"<<endl;
				do{
					x=getch();
					if(x=='1')
						addmoney=1;
					else if(x=='2')
						addmoney=2;
					else if(x=='3')
						addmoney=3;
					}while(x!='0' && x!= '1' && x!='2' && x!='3');
				cin>>addmoney;
				if(addmoney == 1)
				{
					cout<<"�ж״ڦܰ��013 069500145684"<<endl; 
					x=getch();
				}
				else if(addmoney == 2)
					sudokumain(id,users);
				else if(addmoney == 3)
				 	guessmain(id,users);
			}
			else
			{
				users.member[id].money-=cost;
				reloadusers(users);
				for(i=0;i<t;i++)
				{
					Orderlist[orderno+i] = tOrderlist[i];
					bigs[orderno+i] = tbigs[i];
					sweats[orderno+i] = tsweats[i];
					ices[orderno+i] = tices[i];
					bubs[orderno+i] = tbubs[i];
					fans[orderno+i] = tfans[i];
				}
				orderno+=t;
				order(id,users,orderno);
				orderno = LoadOrders();
				return cost;
			}
		}
	}while(select!=0);
	if(select==0)
		cost=0;
}

int orderMainUI(int select,int id,userlist users,int cost)
{
	char x,x1;
	do{
		orderMainScreen(select,id,users,cost);
		x=getch(); 
		if(x==-32){
			x1=getch();
			if(x1==72)
				select=(select+6)%7;
			if(x1==80)
				select=(select+1)%7;
			if(x1==77)
				return select;
		}
		if(x>='0'&& x<='6')
			select = x-'0';
	}while(x!=13);
	return select;
}

void orderMainScreen(int select,int id,userlist users,int cost)
{
	system("cls");
	logo();
	cout<<"\t"<<users.member[id].username<<"�z�n�A�w��ϥΥi���iOrder�t�ΡA�z�Ѿl���x�Ȫ���"<<users.member[id].money<<"���A�z�ثe���q�欰"<<cost<<"��"<<endl;
	cout<<endl<<"---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;  
	int i;
	char L[7],R[7];
	for(i=0;i<7;i++){
		L[i]=' ';
		R[i]=' ';
	} 
	L[select]='[';
	R[select]=']';
	cout<< L[1]<<"1"<<R[1]<<"��������($25)"<<endl;
	cout<< L[2]<<"2"<<R[2]<<"�Ӧm����($30)"<<endl;
	cout<< L[3]<<"3"<<R[3]<<"�����N�S($25)"<<endl;
	cout<< L[4]<<"4"<<R[4]<<"�N�S����($40)"<<endl;
	cout<< L[5]<<"5"<<R[5]<<"�եɼ���($50)"<<endl;
	cout<< L[6]<<"6"<<R[6]<<"�U��"<<endl;
	cout<< L[0]<<"0"<<R[0]<<"Exit"<<endl;
}

int drinkcos(int select)
{
	int cost=0;
	char x;
	switch(select)
	{
		case 1:
			cost=25;
			break;
		case 2:
			cost=30;
			break;
		case 3:
			cost=25;
			break;
		case 4:
			cost=40;
			break;
		case 5:
			cost=50;
			break;
	}
	system("cls");
	logo();
	cout<<"�O�_�ɯŤj�M(+$10)(y/n):";
	do{
		x=getch();
		big=x;
	}while(x!='y' && x!= 'Y' && x!='n' && x!='N');
	cout<<big;
	cout<<endl<<"����(0=�L�} 1=�ֿ} 2=�b�} 3=���}):";
	do{
		x=getch();
		if(x=='0')
			sweat=0;
		else if(x=='1')
			sweat=1;
		else if(x=='2')
			sweat=2;
		else if(x=='3')
			sweat=3;
	}while(x!='0' && x!= '1' && x!='2' && x!='3');
	cout<<sweat;
	cout<<endl<< "�B��(0=�h�B 1=�֦B 2=���`�B):";
	do{
		x=getch();
		if(x=='0')
			ice=0;
		else if(x=='1')
			ice=1;
		else if(x=='2')
			ice=2;
	}while(x!='0' && x!= '1' && x!='2');
	cout<<ice;
	cout<<endl<< "�O�_�[�ï](+$10)(y/n):";
	do{
		x=getch();
		bub=x;
	}while(x!='y' && x!= 'Y' && x!='n' && x!='N');
	cout<<bub;
	cout<<endl<< "�O�_�[����(+$5)(y/n):";
	do{
		x=getch();
		fan=x;
	}while(x!='y' && x!= 'Y' && x!='n' && x!='N');
	cout<<fan;
	if(big=='y'|| big=='Y')
		cost+=10;
	if(bub=='y'|| bub=='Y')
		cost+=10;
	if(fan=='y'|| fan=='Y')
		cost+=5;
	return cost;	 
}

void reloaddrinks(int id,userlist users)
{
	int i;
	ofstream fout;
	fout.open("memberlist.txt"); 
	fout << users.user_num << endl;
	for(i=0;i<users.user_num;i++)
	{
		fout << users.member[i].account << endl;
		fout << users.member[i].passwd << endl;
		fout << users.member[i].username << endl;
		fout << users.member[i].login_num << endl;
		fout << users.member[i].money << endl;
		fout << users.member[i].sudoku_win << endl;
		fout << users.member[i].sudoku_lose << endl;
		fout << users.member[i].guess_win << endl;
		fout << users.member[i].guess_lose << endl;
	}
	fout.close();
}

int searchmain(int id,userlist users)
{
	char c;
	int cost=0;
	int t=0;
	system("cls");
	logo();
	cout<<"\t"<<users.member[id].username<<"�z�n�A�����z�ثe�|���������q��C��A��E�H���}"<<endl;
	cout<<endl<<"---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;  
	int i;
	do{ 
		system("cls");
		logo();
		t=0;
		cout<<"\t"<<users.member[id].username<<"�z�n�A�����z�ثe�|���������q��C��A��E�H���}"<<endl;
		cout<<endl<<"---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;  
		if(orderno==0)
		{
			cout<<"\t�ثe�S���q��A�w���~��[�I!!!"<<endl;
		}	
		else
		{
			for(i=0;i<orderno;i++)
			{
				t++;
				cost=0;
				if(strcmp(guests[i].account,users.member[id].account) == 0)
				{
					cout<<"----------------------------------------------------"<<endl;
					cout<<t;
					switch(Orderlist[i])
					{
						case 1:
							cout<<"\t��������"<<endl;
							cost+=25;
							break;
						case 2:
							cout<<"\t�Ӧm����"<<endl;
							cost+=30;
							break;
						case 3:
							cout<<"\t�����N�S"<<endl;
							cost+=25;
							break;
						case 4:
							cout<<"\t�N�S����"<<endl;
							cost+=40;
							break;
						case 5:
							cout<<"\t�եɼ���"<<endl;
							cost+=50;
							break;
					}
					cout<<"----------------------------------------------------"<<endl;
					switch(bigs[i])
					{
						case 'y': 
							cout<<"\t�j�M"<<endl;
							cost+=10;
							break;
					}
					switch(sweats[i])
					{
						case 0:
							cout<<"\t�L�}"<<endl;
							break;
						case 1:
							cout<<"\t�ֿ}"<<endl;
							break;
						case 2:	
							cout<<"\t�b�}"<<endl;
							break;
						case 3:
							cout<<"\t���}"<<endl;
							break;
					
					}
					switch(ices[i])
					{
						case 0:
							cout<<"\t�h�B"<<endl;
							break;
						case 1:
							cout<<"\t�֦B"<<endl;
							break; 
						case 2:
							cout<<"\t���`�B"<<endl;
							break;
					}
					switch(bubs[i])
					{
						case 'y': 
							cout<<"\t�[�ï]"<<endl;
							cost+=10;
							break;
					}
					switch(fans[i])
					{
						case 'y': 
							cout<<"\t�[����"<<endl;
							cost+=5;
							break;
					}
					cout<<"----------------------------"<<endl;
					cout << "��O: $" << cost << endl; 
					cout<<"----------------------------"<<endl;
				}
				if(t==0)
				{
					system("cls");
					logo();
					cout<<"\t"<<users.member[id].username<<"�z�n�A�����z�ثe�|���������q��C��A��E�H���}"<<endl;
					cout<<endl<<"---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;  
					cout<<"\t�ثe�S���q��A�w���~��[�I!!!"<<endl;
				}
				else
					cout<<"----------------------------------------------------"<<endl;
			}
			
		}
		c=getch();
	}while(c!='E'&& c!='e');
}

int LoadOrders()
{
	int i;
	ifstream fin;
	fin.open("orderlist.txt");
	fin >> orderno;
	for(i=0;i<orderno;i++)
	{
		fin >> guests[i].account;
		fin >> Orderlist[i];
		fin >> bigs[i];
		fin >> sweats[i];
		fin >> ices[i];
		fin >> bubs[i];
		fin >> fans[i];
	}
	fin.close();
	return orderno;
}

void order(int id,userlist users,int num)
{
	int i;
	ofstream fout;
	fout.open("orderlist.txt");
	fout << num << endl;
	for(i=0;i<num;i++)
	{
		fout << users.member[id].account << endl;
		fout << Orderlist[i] << endl;
		fout << bigs[i] << endl;
		fout << sweats[i] << endl;
		fout << ices[i] << endl;
		fout << bubs[i] << endl;
		fout << fans[i] << endl;
	}
}


int editmain(int id,userlist users,char pw[])
{
	char rpw[13],npw[13];
	char c1,c2;
	int n=0,i;
	ofstream fout;
	do
	{
		system("cls");
		logo();
		cout << "�п�J�z�{�b���K�X: ";
		for(i=0;i<n;i++)
			cout << '*';
		c1 = getch();
		if(c1==-32||c1==0)
			c2 = getch();
		if((c1>='a'&&c1<='z')||(c1>='A'&&c1<='Z')||(c1>='0'&&c1<='9')||c1=='_')
		{
			if(n==12)
			{
				rpw[11] = c1;
			}
			else
			{
				rpw[n] = c1;
				n++;
			}
		}
		if(c1==8&&n>0)
			n--;
		if(c1==13)
		{
			if(strcmp(rpw,pw) != 0)
			{
				cout<<endl<<"�K�X���~ �Э��s��J"<<endl;
				cout<<endl<<"�Ы����N���~��......"<<endl;
				for(i=0;i<13;i++)
					rpw[i]='\0';
				c2=getch();
				n=0;
				
			}
		}
	}while(strcmp(rpw,pw) != 0 || c1!=13 || n<4);
	n=0;
	do
	{
		system("cls");
		logo();
		cout << "�п�J�z�{�b���K�X: ";
		for(i=0;i<strlen(rpw);i++)
			cout << '*';
		cout<<endl;
		cout << "�п�J�z���s���K�X: ";
		for(i=0;i<n;i++)
			cout << '*';
		c1 = getch();
		if(c1==-32||c1==0)
			c2 = getch();
		if((c1>='a'&&c1<='z')||(c1>='A'&&c1<='Z')||(c1>='0'&&c1<='9')||c1=='_')
		{
			if(n==12)
			{
				npw[11] = c1;
			}
			else
			{
				npw[n] = c1;
				n++;
			}
		}
		if(c1==8&&n>0)
			n--;
		if(c1==13)
		{
			if(strcmp(npw,pw) == 0)
			{
				cout<<endl<<"�P��K�X�ۦP �ЦA���@��"<<endl;
				cout<<endl<<"�Ы����N���~��......"<<endl;
				for(i=0;i<13;i++)
					npw[i]='\0';
				c2=getch();
				n=0;
				
			}	
		}
	}while(strcmp(npw,pw) == 0||c1!=13||n<4);
	strcpy(pw,npw);
	reloadusers(users);
} 

int chatmain(int id,userlist users)
{
	char talk[100];
	ifstream fin;
	ofstream fout;
	do{
		system("cls");
		logo();
		cout<<endl<<"\t�w��i�J�I���ѫ� ��J\"\\EXIT\"�Y�i���}"<<endl; 
		cout<<endl<<"---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;  
		fin.open("msg.txt");
		while(!fin.eof())
		{
			fin.getline(talk,99);
			cout<<talk<<endl;
		}
		fin.close();
		cout<<"---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;  
		cout<<users.member[id].username<< ": ";
		cin.getline(talk,99);
		if(strcmp(talk,"\\EXIT")==0)
			break;
		if(strlen(talk)>0)
		{
			fout.open("msg.txt",std::ofstream::app);
			fout<<users.member[id].username<<": "<<talk<<endl;
			fout.close(); 
		}
	}while(true);
}

int sudokumain(int id,userlist users)
{
	int r,c,n,modified = 1,flag = 0,chance=3;
	int Q[9][9];
	int A[9][9],A2[9][9];
	int pool[9][9][10];
	char x;
	sudokuinit(pool);
	sudokuRead(1,Q,pool);
	for(r=0;r<9;r++)
		for(c=0;c<9;c++)
		{
			A[r][c] = Q[r][c];
			A2[r][c] = Q[r][c];
		}
	while(flag==0)
	{
		cout << endl;
		sudokuMainUI(Q,A2,chance);
		while(modified==1)
		{
			modified = 0;
			for(r=0;r<9;r++)
			{
				for(c=0;c<9;c++)
				{
					if(A[r][c]==0)
					{
						n = sudokuCheck(pool,r,c); //0-9
						if(n>0)
						{
							A[r][c] = n;
							sudokuupdate(pool,r,c,n);
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
		{
			chance--;
			if(chance>0)
				cout<<"���D���~ �z�ٳѤU"<<chance<<"�����| �ЦA���A�F�I"<<endl; 
			if(chance==0)
			{
				cout<<"�Q����p �z�w�κɩҦ����| �D�ԥ���"<<endl;
				users.member[id].sudoku_lose ++;
				reloadusers(users);
				break;
			}
			cout<<endl<<"�Ы����N���~��......"<<endl;
			x=getch();
		}
	}
	if(flag==1)
	{
		cout<<"���D���T ���߱zĹ�o20��!!!"<<endl;
		cout<<endl<<"�Ы����N���~��......"<<endl;
		x=getch();
		users.member[id].money += 20;
		users.member[id].sudoku_win ++;
		reloadusers(users);
	 } 
}

void sudokuinit(int p[][9][10])
{
	int r,c,n;
	for(r=0;r<9;r++)
		for(c=0;c<9;c++)
			for(n=1;n<=9;n++)
				p[r][c][n] = 1;
}

void sudokuupdate(int p[][9][10],int R,int C,int N)
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

void sudokuRead(int Qno, int Q[][9], int p[][9][10])
{
	int r,c,n,x;
	ifstream fin;
	srand(time(NULL));
	x=rand()%2;
	if(x==0)
		fin.open("Q1.txt");
	else
		fin.open("Q2.txt");
	for(r=0;r<9;r++)
	{
		for(c=0;c<9;c++)
		{
			fin >> n;
			Q[r][c] = n;
			if(n>0)
				sudokuupdate(p,r,c,n);
		}
	}
	fin.close();
}

void sudokuPrint(int Q[][9],int A[][9],int R,int C,int chance)
{
	//HW:finish
	int r,c;
	system("cls");
	logo();
	cout<<endl<<"\t�w��D�ԼƿW �z�֦�"<<chance<<"�����|�D�� �Y���D���T�h�R��$20�x�Ȫ� (���G�N�O��)"<<endl;
	cout<<endl<<"---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;  
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

int sudokuCheck(int p[][9][10],int R,int C)
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

void sudokuMainUI(int Q[][9],int A[][9],int chance)
{
		int r=0,c=0;
	char c1,c2;
	do
	{
		sudokuPrint(Q,A,r,c,chance);
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

int guessmain(int id,userlist users)
{
	int pool[10000],userAB[2],comAB[2],tmpAB[2],count=0;
	int i,u,c,ansU,ansC;	
	srand(time(NULL));
	do{
		ansC = rand()%10000;
	}while(islegal(ansC)==false);
	do{
		system("cls");
		logo();
		cout<<endl<<"\t�w��D�Բq�Ʀr �z�N�P�q�����ۥX�D�i����� �Y��q�����q���X�ӫh�R��$20�x�Ȫ� (���G�N�O��)"<<endl;
		cout<<endl<<"---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;  
		cout<<"�п�J�z�����q���q�����Ʀr:";
		cin>>ansU;
	}while(islegal(ansU)==false);
	for(i=0;i<10000;i++){
		if(islegal(i))
			pool[i]=1;	
		else
			pool[i]=0;	
	}	
	do{
		cout<<"�п�J�z�q�����Ʀr:";
		cin>>u;
		xaxb(u,ansC,userAB);
		count++;
		if(u<10)
			cout<<"You:("<<count<<")000"<<u<<"		"<<userAB[0]<<"A"<<userAB[1]<<"B"<<endl;
		else if(u<100)
			cout<<"You:("<<count<<")00"<<u<<"		"<<userAB[0]<<"A"<<userAB[1]<<"B"<<endl;
		else if(u<1000)
			cout<<"You:("<<count<<")0"<<u<<"		"<<userAB[0]<<"A"<<userAB[1]<<"B"<<endl;
		else
			cout<<"You:("<<count<<")"<<u<<"		"<<userAB[0]<<"A"<<userAB[1]<<"B"<<endl;
		for(i=0;i<10000;i++)
			if(pool[i]==1)
				break;
		c = i;
		xaxb(c,ansU,comAB);
		
		if(c<10)
			cout<<"PC :("<<count<<")000"<<c<<"		"<<comAB[0]<<"A"<<comAB[1]<<"B"<<endl;
		else if(c<100)
			cout<<"PC :("<<count<<")00"<<c<<"		"<<comAB[0]<<"A"<<comAB[1]<<"B"<<endl;
		else if(c<1000)
			cout<<"PC :("<<count<<")0"<<c<<"		"<<comAB[0]<<"A"<<comAB[1]<<"B"<<endl;
		else
			cout<<"PC :("<<count<<")"<<c<<"		"<<comAB[0]<<"A"<<comAB[1]<<"B"<<endl;
		for(i=0;i<10000;i++){
			if(pool[i]==1){
				xaxb(c,i,tmpAB);					
			if(tmpAB[0]!=comAB[0] || tmpAB[1]!=comAB[1])
				pool[i]=0;
				}
			}
	}while(comAB[0]!=4 && userAB[0]!=4);
	if(userAB[0]==4)
	{
		cout<<endl<<"�z���ӧQ ���߱zĹ�o20��!!!"<<endl;
		users.member[id].guess_win ++;
		users.member[id].money+=20;
		reloadusers(users);
		getch();
	 } 
	else
	{
		cout<<endl<<"�q���ӧQ �U���Х[�o"<<endl;
		users.member[id].guess_lose ++;
		reloadusers(users);
		getch();
	}


}

void numdigit(int n,int d[]){
	d[0]=n/1000;
	d[1]=n%1000/100;
	d[2]=n%100/10;
	d[3]=n%10;
}

bool islegal(int n){
	int d[4],i,j;
	numdigit(n,d);
	for(i=0;i<3;i++){
		for(j=i+1;j<4;j++){
			if(d[i]==d[j])
				return false;
		}
	}
	return true;	
}

void xaxb(int g,int a,int AB[]){
	AB[0]=0;
	AB[1]=0;
	int GD[4];
	int AD[4];
	int i,j;
	numdigit(g,GD);
	numdigit(a,AD);
	for(i=0;i<4;i++){
		if (GD[i]==AD[i])
			AB[0]++;
			}
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++){
			if (GD[i]==AD[j])
				AB[1]++;
		}
	}	
	AB[1]-=AB[0];
}

userlist LoadUsers()
{
	int i;
	userlist users;
	ifstream fin;
	fin.open("memberlist.txt");
	fin >> users.user_num;
	for(i=0;i<users.user_num;i++)
	{
		fin >> users.member[i].account;
		fin >> users.member[i].passwd;
		fin >> users.member[i].username;
		fin >> users.member[i].login_num;
		fin >> users.member[i].money;
		fin >> users.member[i].sudoku_win;
		fin >> users.member[i].sudoku_lose;
		fin >> users.member[i].guess_win;
		fin >> users.member[i].guess_tie;
		fin >> users.member[i].guess_lose;
	}
	fin.close();
	return users;
}

int Login(userlist users)
{
	char account[13];
	char password[13];
	int i;
	do{
		input_account(account);
		input_password(account,password);
		for(i=0;i<users.user_num;i++)
		{
			if(strcmp(account,users.member[i].account) == 0)
			{
				if(strcmp(password,users.member[i].passwd) == 0)
					return i;
				else
				{
					cout<<endl<<endl<<"�K�X���~ �Э��s��J�b�K"<<endl;
					cout<<"�Ы����N���~��......"<<endl;
					getch();
					break;
				}
			}
		}
		if(i==users.user_num)
			return -1;
	}while(true);
	
}

void input_account(char ac[])
{
	char c1,c2;
	int n=0,i;
	do
	{
		system("cls");
		logo();
		cout << "Account: ";
		for(i=0;i<n;i++)
			cout << ac[i];
		c1 = getch();
		if(c1==-32||c1==0)
			c2 = getch();
		if((c1>='a'&&c1<='z')||(c1>='A'&&c1<='Z')||(c1>='0'&&c1<='9')||c1=='_')
		{
			if(n==12)
			{
				ac[11] = c1;
			}
			else
			{
				ac[n] = c1;
				n++;
			}
		}
		if(c1==8&&n>0)
			n--;
	}while(c1!=13||n<4);
	ac[n] = '\0';
} 

void input_password(char ac[],char pw[])
{
	char c1,c2;
	int n=0,i;
	do
	{
		system("cls");
		logo();
		cout << "Account: ";
		cout << ac << endl;
		cout << "Password: ";
		for(i=0;i<n;i++)
			cout << '*';
		c1 = getch();
		if(c1==-32||c1==0)
			c2 = getch();
		if((c1>='a'&&c1<='z')||(c1>='A'&&c1<='Z')||(c1>='0'&&c1<='9')||c1=='_')
		{
			if(n==12)
			{
				pw[11] = c1;
			}
			else
			{
				pw[n] = c1;
				n++;
			}
		}
		if(c1==8&&n>0)
			n--;
	}while(c1!=13||n<4);
	pw[n] = '\0';
} 

int create(userlist users,char ac[13],char pw[13],char un[13])
{
	int i,s=0;
	ifstream fin;
	ofstream fout;
	cout<<endl<<endl<<"��Ʈw�S�����|����� �N�۰ʾɤJ���U�{��......"<<endl;
	cout << "*�`�N:�ȥi��J�j�p�g�^��r���μƦr�M���u*"<<endl;
	cout<<"�Ы����N���~��......"<<endl;
	getch();
	do{
		input_account(ac);
		input_password(ac,pw);
		s=1;
		for(i=0;i<users.user_num;i++)
		{
			if(strcmp(ac,users.member[i].account) == 0)
			{
					cout<<endl<<endl<<"�ӱb���w�Q���U �Э��s��J"<<endl;
					cout<<"�Ы����N���~��......"<<endl;
					getch();
					s=0;
					break;
				}
			}
	}while(s==0);
	cout<<endl<<"Username: ";
	cin>>un;
	users.member[users.user_num].login_num = 1;
	users.member[users.user_num].money = 0;
	users.member[users.user_num].sudoku_win = 0;
	users.member[users.user_num].sudoku_lose = 0;
	users.member[users.user_num].guess_win = 0;
	users.member[users.user_num].guess_tie = 0;
	users.member[users.user_num].guess_lose = 0;
	reloadusers(users);
	return users.user_num;
}

void reloadusers(userlist users)
{
	int i;
	ofstream fout;
	fout.open("memberlist.txt");
	fout << users.user_num << endl;
	for(i=0;i<users.user_num;i++)
	{
			fout << users.member[i].account << endl;
			fout << users.member[i].passwd << endl;
			fout << users.member[i].username << endl;
			fout << users.member[i].login_num << endl;
			fout << users.member[i].money << endl;
			fout << users.member[i].sudoku_win << endl;
			fout << users.member[i].sudoku_lose << endl;
			fout << users.member[i].guess_win << endl;
			fout << users.member[i].guess_tie << endl;
			fout << users.member[i].guess_lose << endl;
	}
	fout.close();
	LoadUsers();
}

void kebukemain(userlist users)
{
	int select=1;
	do{
		select=kMainUI(select);
		switch(select){
			case 1:
				ksmain(users);
				break;
			case 2:
				cashmain(users);
				break;
			case 0:
				break;
		}
	}while(select!=0); 
	
}

int kMainUI(int select)
{
	char x,x1;
	do{
		kMainScreen(select);
		x=getch(); 
		if(x==-32){
			x1=getch();
			if(x1==72)
				select=(select+2)%3;
			if(x1==80)
				select=(select+1)%3;
			if(x1==77)
				return select;
		}
		if(x>='0'&& x<='6')
			select = x-'0';
	}while(x!=13);
	return select;
}

void kMainScreen(int select)
{
	system("cls");
	logo();
	int i;
	char L[3],R[3];
	for(i=0;i<3;i++){
		L[i]=' ';
		R[i]=' ';
	} 
	L[select]='[';
	R[select]=']';
	cout<< L[1] << "1" << R[1] << "�d�߭q��" << endl;
	cout<< L[2] << "2" << R[2] << "�x��" << endl;
	cout<< L[0] << "0" << R[0] << "Exit" << endl;
}

int ksmain(userlist users)
{
	int c1,c2;
	int cost=0;
	int t=0;
	
	int i;
	do{ 
		system("cls");
		logo();
		cout<<"\t�q��C��A��E�H���}"<<endl;
		cout<<endl<<"---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;  
		if(orderno==0)
			cout<<"\t�ثe�S���q��"<<endl;
		else
		{
			cost=0;
			cout<<"----------------------------------------------------"<<endl;
			switch(Orderlist[orderno-1])
			{
					case 1:
						cout<<"\t��������"<<endl;
						cost+=25;
						break;
					case 2:
						cout<<"\t�Ӧm����"<<endl;
						cost+=30;
						break;
					case 3:
						cout<<"\t�����N�S"<<endl;
						cost+=25;
						break;
					case 4:
						cout<<"\t�N�S����"<<endl;
						cost+=40;
						break;
					case 5:
						cout<<"\t�եɼ���"<<endl;
						cost+=50;
						break;
				}
				cout<<"----------------------------------------------------"<<endl;
				switch(bigs[orderno-1])
				{
					case 'y': 
						cout<<"\t�j�M"<<endl;
						cost+=10;
						break;
				}
				switch(sweats[orderno-1])
				{
					case 0:
						cout<<"\t�L�}"<<endl;
						break;
					case 1:
						cout<<"\t�ֿ}"<<endl;
						break;
					case 2:	
						cout<<"\t�b�}"<<endl;
						break;
					case 3:
						cout<<"\t���}"<<endl;
						break;	
				}
				switch(ices[orderno-1])
				{
					case 0:
						cout<<"\t�h�B"<<endl;
						break;
					case 1:
						cout<<"\t�֦B"<<endl;
						break; 
					case 2:
						cout<<"\t���`�B"<<endl;
						break;
				}
				switch(bubs[orderno-1])
				{
					case 'y': 
						cout<<"\t�[�ï]"<<endl;
						cost+=10;
						break;
				}
				switch(fans[orderno-1])
				{
					case 'y': 
						cout<<"\t�[����"<<endl;
						cost+=5;
						break;
				}
				cout<<"----------------------------"<<endl;
				cout << "��O: $" << cost << endl; 
				cout<<"----------------------------"<<endl;
			}
		c1=getch();
		if(c1==0)
		{
			c2=getch();
			if(c2==81)
			{
				orderno-=1;
				ofstream fout;
				fout.open("orderlist.txt");
				if(orderno<0)
					orderno=0;
				fout << orderno << endl;
				for(int i=0;i<orderno;i++)
				{
					fout << guests[i].account << endl;
					fout << Orderlist[i] << endl;
					fout << bigs[i] << endl;
					fout << sweats[i] << endl;
					fout << ices[i] << endl;
					fout << bubs[i] << endl;
					fout << fans[i] << endl;
				}
				continue;
			}			
				
		}
	}while(c1!=69 && c1!=101);
	
}

int cashmain(userlist users)
{
	int i,money,id;
	int select=1;
	char x;
	while(true)
	{
		select=cashMainUI(select,users.user_num,users);
		if(select==-1)
			break;
		system("cls");
		logo();
		cout<<"\t�x�Ȫ��B:";
		cin>>money;
		switch(select){
			case 0:
				id = users.user_num-1;
			default:
				id = select;
		}
		users.member[id].money+=money;
		reloaddrinks(id,users);
		cout<<endl<<endl<<"�w�x��"<<money<<"��\n�Ы����N���~��......";
		x=getch();
	}
	
}

int cashMainUI(int select,int num,userlist users)
{
	char x,x1;
	do{
		cashMainScreen(select,num,users);
		x=getch(); 
		if(x==-32){
			x1=getch();
			if(x1==72)
				select=(select+num-1)%num;
			if(x1==80)
				select=(select+1)%num;
			if(x1==77)
				return select;
		}
	}while(x!=13 && x!='e' &&  x!='E');
	if(x=='e' ||  x=='E')
		return -1;
	return select;
}

void cashMainScreen(int select,int num,userlist users)
{
	system("cls");
	logo();
	cout<<"\t�Τ��x�Ȥ����A��E�H���}"<<endl;
	cout<<endl<<"---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;  
	int i;
	char L[100],R[100];
	for(i=0;i<num;i++){
		L[i]=' ';
		R[i]=' ';
	} 
	L[select]='[';
	R[select]=']';
	for(i=1;i<num;i++)
		cout<< L[i]<<i<<R[i]<<users.member[i].username<<endl;
}


