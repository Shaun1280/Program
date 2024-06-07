#include<bits/stdc++.h>
const int maximum=1e1+1; 
using namespace std;
int n;
class Student{
	public:
		int score1,score2,score3,score4,score5,sum;
		inline void input(){
			cin>>score1>>score2>>score3>>score4>>score5;
		}
		inline int calculateTotalScore(){
			return score1+score2+score3+score4+score5;
		}
	
};
int main() {
    int n; // number of students
    cin >> n;
    Student *s = new Student[n]; // an array of n students
    
    for(int i = 0; i < n; i++){
        s[i].input();
    }

    // calculate kristen's score
    int kristen_score = s[0].calculateTotalScore();

    // determine how many students scored higher than kristen
    int count = 0; 
    for(int i = 1; i < n; i++){
        int total = s[i].calculateTotalScore();
        if(total > kristen_score){
            count++;
        }
    }

    // print result
    cout << count;
    
    return 0;
}
