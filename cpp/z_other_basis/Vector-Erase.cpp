#include<bits/stdc++.h>
using namespace std;
int N, pos1,pos2;
vector<int>vec;
//Removes the element present at position.  
//Ex: v.erase(v.begin()+4); (erases the fifth element of the vector v)
//Removes the elements in the range from start to end inclusive of the start and exclusive of the end.
//Ex:v.erase(v.begin()+2,v.begin()+5);(erases all the elements from the third element to the fifth element.)
int main(){
	scanf("%d",&N);
	for(int i=1,num;i<=N;i++) scanf("%d",&num), vec.push_back(num);
	scanf("%d",&pos1);
	vec.erase(vec.begin()+pos1-1);
	scanf("%d%d",&pos1,&pos2);
	vec.erase(vec.begin()+pos1-1,vec.begin()+pos2-1);
	int Size=vec.size();
	printf("%d\n",Size);
	for(int i=1;i<=Size;i++){
		printf("%d ", vec[i-1]);
	}
	
	return 0;
} 
