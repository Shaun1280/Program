#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	int a[n][n];
	for(int i=1;i<=n;i++) a[i][1]=a[i][i]=1;
	for(int i=3;i<=n;i++)
		for(int j=2;j<i;j++){
			a[i][j]=a[i-1][j-1]+a[i-1][j];
		}
	for(int i=1;i<=n;i++){
		cout<<setw(3*n-3*i)<<" "; //setw ÉèÖÃ¼ä¸ô eg. 1 6<=setw(2); 
		for(int j=1;j<=i;j++)
			cout<<setw(6)<<a[i][j];
		cout<<endl;
	}
		
	return 0;
}
