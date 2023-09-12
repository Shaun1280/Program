
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <algorithm>
using namespace std;
int map[5][5];
int vis[5][5];
int fx[4] = {1, 0, -1, 0};
int fy[4] = {0, 1, 0, -1};
int sx = 0, sy = 0;

struct node
{
	int x, y;
	int pre;
} q[30];

int valid(int x, int y)
{
	if (x >= 0 && x < 5 && y >= 0 && y < 5)
		return 1;
	else
		return 0;
}

void print(int pos) //递归求路径
{
	if (q[pos].pre != -1)
	{
		print(q[pos].pre);
		printf("(%d, %d)\n", q[pos].x, q[pos].y);
	}
}

void BFS()
{
	int front = 0, rear = 1;
	q[front].x = sx;
	q[front].y = sy;
	q[front].pre = -1;

	while (front < rear)
	{
		for (int i = 0; i < 4; i++)
		{
			int a = q[front].x + fx[i];
			int b = q[front].y + fy[i];

			if (!vis[a][b] && !map[a][b] && valid(a, b))
			{
				vis[a][b] = 1;
				q[rear].x = a;
				q[rear].y = b;
				q[rear].pre = front; //记录前驱
				rear++;
			}
			if (a == 4 && b == 4)
				print(front);
		}
		front++; //头指针+1<=>出队&&保存着当前节点
	}
}

int main()
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
		{
			scanf("%d", &map[i][j]);
			vis[i][j] = 0;
		}
	printf("(0, 0)\n");
	BFS();
	printf("(4, 4)\n");
	return 0;
}