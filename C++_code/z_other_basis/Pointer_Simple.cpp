#include<bits/stdc++.h>
using namespace std;
int a,b=100;
inline void testcase1(){
    cout<<"&b:"<<&b<<endl;
    printf("&b:0x%x\n",&b);
    printf("&b:%d\n*******\n",&b);
}
inline void testcase2(){
    a=*&b;
    cout<<dec<<"value  a:"<<a<<endl;
    int *a=&b;
    cout<<dec<<"value *a:"<<*a<<endl;
}
inline void testcase3(){
    int *p=&*&b;
    printf("The value is: %d\n", *p);
}
inline void testcase4(){
    int &r = b;
    cout <<"The value is: "<< r << endl;
}
int main(){
    testcase1();//&
    testcase2();//*
    testcase3();//*p
    testcase4();//引用
    return 0;
}