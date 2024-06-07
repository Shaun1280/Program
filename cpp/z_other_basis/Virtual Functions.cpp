#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class Person{
    protected:
        string name_;
        int age_;
    public:
        virtual void getdata() = 0; 
        virtual void putdata() = 0;
};

class Professor : public Person {
    int publication_;
    static int cur_id_;    
    public:
        void getdata() { cin>>name_>>age_>>publication_; }
        void putdata() {
            cur_id_+=1;
            cout<<name_<<" "<<age_<<" "<<publication_<<" "<<cur_id_<<endl;
        }    
};

class Student : public Person {
    int marks_[6];
    int sum_marks=0;    
    static int cur_id;

    public:      
      void getdata() {
          cin>>name_>>age_;
          for(int i=0; i<6; ++i)
                cin>>marks_[i];          
      }
      void putdata()
      {
          cur_id+=1;
          cout<<name_<<" "<<age_<<" ";
          for(int i=0; i<6; ++i)
                sum_marks += marks_[i];     
          cout<<sum_marks<<" "<<cur_id<<endl;     
      }
};

int Student::cur_id = 0;
int Professor::cur_id_ = 0;
int main(){

    int n, val;
    cin>>n; //The number of objects that is going to be created.
    Person *per[n];

    for(int i = 0;i < n;i++){

        cin>>val;
        if(val == 1){
            // If val is 1 current object is of type Professor
            per[i] = new Professor;

        }
        else per[i] = new Student; // Else the current object is of type Student

        per[i]->getdata(); // Get the data from the user.

    }

    for(int i=0;i<n;i++)
        per[i]->putdata(); // Print the required output for each object.

    return 0;

}

