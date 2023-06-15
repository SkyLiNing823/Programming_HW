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
		cout<<"漩渦鳴人 & 日向雛田"<<endl;
	}
	if(total==2||total==3)
	{
		cout<<"比企谷八幡 & 雪之下雪乃"<<endl;
	}
	if(total==4||total==5)
	{
		cout<<"桐人 & 亞斯娜"<<endl;
	}
	if(total==6||total==7)
	{
		cout<<"神田空太 & 椎名真白"<<endl;
	}
	if(total==8||total==9)
	{
		cout<<"鷹原羽依里 & 鳴瀨白羽"<<endl;
	}	
	
	return 0;

	} 
