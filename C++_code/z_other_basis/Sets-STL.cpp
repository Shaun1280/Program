#include<bits/stdc++.h>
using namespace std;
/*
set<int>s; //Creates a set of integers.
Size:

int length=s.size(); //Gives the size of the set.
Insert:

s.insert(x); //Inserts an integer x into the set s.
Erasing an element:

s.erase(val); //Erases an integer val from the set s.
Finding an element:

set<int>::iterator itr=s.find(val); //Gives the iterator to the element val if it is found otherwise returns s.end() .
Ex: set<int>::iterator itr=s.find(100); //If 100 is not present then it==s.end().
begin()     ���� ,����set������һ��Ԫ�صĵ�����

end() �������� ,����һ��ָ��ǰsetĩβԪ�ص���һλ�õĵ�����.

clear()   ����     ,ɾ��set�����е����е�Ԫ��

empty() ������,�ж�set�����Ƿ�Ϊ��

max_size() �� ,����set�������ܰ�����Ԫ��������

size() �������� ,���ص�ǰset�����е�Ԫ�ظ���

rbegin() same as end

rend() same as begin
*/
set<int>s;
int n,type,num;
inline int read() {
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') f=(ch=='-')?-1:1, ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-48,ch=getchar();
	return x*f;
}
int main() {
	n=read();
	for(int i=1; i<=n; i++) {
		type=read(),num=read();
		if(type==1) {
			s.insert(num);
		}
		if(type==2) {
			s.erase(num);
		}
		if(type==3) {
			set<int>::iterator itr=s.find(num);
			if(itr!=s.end()) cout<<"Yes"<<endl;
			else cout<<"No"<<endl;
		}
	}
	return 0;
}
