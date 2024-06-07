/*hanoi problem 2^n-1
#include <iostream>
using namespace std;

void hanoi(int n, int a, int b, int c)
{
    if(n == 1) { cout << "move " << a << " to " << c << endl; return;}
    hanoi(n-1, a, c, b); //将A上的discs(n-1)个discs通过C移动到B上
    cout << "move " << a << " to " << c << endl; //A上1个移动到C上
    hanoi(n-1, b, a, c);//将B上的discs通过A移动到C上
}
int main()
{
    int n;
    cin >> n;
    hanoi(n, 1, 2, 3);
    return 0;
}
*/

// stack method
#include <iostream>
#include <stack>
using namespace std;

struct hanoiunrec  //结构体，表示汉诺塔的信息
{
    hanoiunrec();
    hanoiunrec(int n, int a, int b, int c)
        : _n(n), _x(a), _y(b), _z(c) {}  //构造函数
    int _n, _x, _y, _z;
};

void hanoi(int n, int x, int y, int z) {
    stack<hanoiunrec>
        s;  //声明一个汉诺塔类型的栈，即其元素都具有汉诺塔结构体信息
    s.push(hanoiunrec(n, x, y, z));  //将一个汉诺塔入栈
    while (!s.empty())               //栈不空则执行
    {
        hanoiunrec q = s.top();  //取栈顶元素为q
        s.pop();                 //把栈顶弹出
        n = q._n;  //分别将当前处理汉诺塔信息赋给函数参数
        x = q._x;
        y = q._y;
        z = q._z;
        if (n == 1)  //如果只剩一个盘了，则移动并输出操作
        {
            cout << "Move " << q._x << " to " << q._z << endl;
        } else  //还剩多个盘，则将新的汉诺塔元素入栈，返回while循环开始操作
        {
            s.push(hanoiunrec(n - 1, y, x, z));
            s.push(hanoiunrec(1, x, y, z));
            s.push(hanoiunrec(n - 1, x, z, y));  //先处理的后入栈
        }
    }
}

int main() {
    hanoi(3, 1, 2, 3);  //以10个盘举个例子
    return 0;
}