#include<bits/stdc++.h>
using namespace std;
int n,sum1,sum2;
int main(){
	scanf("%d",&n);
	vector<int>vec[n];
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++){
			int num;
			scanf("%d",&num);
			vec[i].push_back(num);
		}
	for(int i=0;i<n;i++){
		sum1+=vec[i][i];
		sum2+=vec[n-1-i][i];
	}
	printf("%d", abs(sum1-sum2));
	return 0;
}
