#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;
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

int main(){
	int pool[10000],userAB[2],comAB[2],tmpAB[2],count=0;
	int i,u,c,ansU,ansC;	
	srand(time(NULL));
	do{
		ansC = rand()%10000;
	}while(islegal(ansC)==false);
	do{
		cout<<"Please input your answer:";
		cin>>ansU;
	}while(islegal(ansU)==false);
	for(i=0;i<10000;i++){
		if(islegal(i))
			pool[i]=1;	
		else
			pool[i]=0;	
	}	
	do{
		cout<<"Input your guess:";//user's turn
		cin>>u;
		xaxb(u,ansC,userAB);
		count++;
		cout<<"("<<count<<")"<<u<<"		"<<userAB[0]<<"A"<<userAB[1]<<"B"<<endl;
		for(i=0;i<10000;i++)
			if(pool[i]==1)
				break;
			c = i;
			xaxb(c,ansU,comAB);
			cout<<"("<<count<<")"<<c<<"		"<<comAB[0]<<"A"<<comAB[1]<<"B"<<endl;
			for(i=0;i<10000;i++){
				if(pool[i]==1){
					xaxb(c,i,tmpAB);
					if(tmpAB[0]!=comAB[0] || tmpAB[1]!=comAB[1])
						pool[i]=0;
				}
			}
	}while(comAB[0]!=4 && userAB[0]!=4);
	if(userAB[0]==4 && comAB[0]==4)
		cout<<"Tie!"<<endl;
	else if(userAB[0]==4)
		cout<<"User Win!"<<endl;
	else
		cout<<"Computer Win!"<<endl;
	return 0;
}
