#include<bits/stdc++.h> 
using namespace std;
string s1,s2;
int len1,len2;
int getlen(string s){ return s.length(); }
void change(string a,string b){
	 char S1=s1[0], S2=s2[0];
	 s1[0]=S2,s2[0]=S1;
}
int main(){
	cin>>s1;
	cin>>s2;
	printf("%d %d\n",len1=getlen(s1),len2=getlen(s2));
	cout<<s1+s2<<endl;
	change(s1,s2);
	cout<<s1<<" "<<s2;
	return 0;
}
