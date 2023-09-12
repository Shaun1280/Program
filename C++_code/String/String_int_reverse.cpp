/* #include<bits/stdc++.h>
using namespace std;
int main(){
	std::ios::sync_with_stdio(false);
	int i,j,modd,tot(0);
	cin>>i>>j>>modd;
	for(int num=i;num<=j;num++){
		stringstream ss;
		string s;
		s=to_string(num);
		ss.clear();
		reverse(s.begin(),s.end());
		ss.str(s);
		int reverse_int;
		ss>>reverse_int;
		if(abs(num-reverse_int)%modd==0) tot++;
	}
	cout<<tot<<endl;
	return 0;
}

!! stoi(s,nullptr,10)
*/
#include<bits/stdc++.h>
using namespace std;
int main(){
	std::ios::sync_with_stdio(false);
	int i,j,modd,tot(0);
	cin>>i>>j>>modd;
	for(int num=i;num<=j;num++){
		stringstream ss;
		string s;
		ss<<num;
		ss>>s;
		reverse(s.begin(),s.end());
		ss.clear();
		ss<<s;
		int reverse_int;
		ss>>reverse_int;
		cout<<reverse_int<<endl;
		if(abs(num-reverse_int)%modd==0) tot++;
	}
	cout<<tot<<endl;
	return 0;
}