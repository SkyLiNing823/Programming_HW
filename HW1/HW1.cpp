#include <iostream>
using namespace std;
int main(){
	int a,b,total,i=10000000,j=10000000;
	cin>>a>>b;
	while(a>0){
		total+=a/i;
		a=a%i;
		i/=10;							
	}
	while(b>0){
		total+=b/j;
		b=b%j;
		j/=10;							
	}
	while(total>9){
		total=(total/10)+(total%10);	
	}
	if(total==0||total==1)
	{
		cout<<"�x����H & ��V����"<<endl;
	}
	if(total==2||total==3)
	{
		cout<<"������K�n & �����U���D"<<endl;
	}
	if(total==4||total==5)
	{
		cout<<"��H & �ȴ��R"<<endl;
	}
	if(total==6||total==7)
	{
		cout<<"���ЪŤ� & �զW�u��"<<endl;
	}
	if(total==8||total==9)
	{
		cout<<"�N��Ш̨� & ���u�զ�"<<endl;
	}	
	
	return 0;

	} 
