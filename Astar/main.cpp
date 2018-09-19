#include "stdafx.h"
#include "Astar.h"
#include <iostream>

using namespace std;
void init(node*** map)
{
	for (int i = 0; i < MAP_SIZE; i++)
		*(map + i) = new node*[MAP_SIZE];
	for (int i = 1; i < MAP_SIZE - 1; i++)
	{
		for (int j = 1; j < MAP_SIZE - 1; j++)
		{
			*(*(map + i) + j) = new node{ 0, i, j, 0, 0 };
		}
	}
	for (int i = 0; i < MAP_SIZE; i++)
	{
		*(*(map + i)) = new node{ 1, i, 0, 0, 0 };
		*(*(map + i) + MAP_SIZE - 1) = new node{ 1, i, MAP_SIZE - 1, 0, 0 };
		//避免重复分配内存空间
		if (i != 0 && i != MAP_SIZE - 1)
		{
			*(*map + i) = new node{ 1, 0, i, 0, 0 };
			*(*(map + MAP_SIZE - 1) + i) = new node{ 1, MAP_SIZE - 1, i, 0, 0 };
		}
	}
	//在几个节点处设置墙壁
	(*(*(map + 2) + 3))->value = 1;
	(*(*(map + 3) + 3))->value = 1;
	(*(*(map + 3) + 6))->value = 1;
	(*(*(map + 4) + 3))->value = 1;
	(*(*(map + 4) + 4))->value = 1;
	(*(*(map + 5) + 4))->value = 1;
	(*(*(map + 6) + 2))->value = 1;
}
void del(node*** map)
{
	for (int i = 0; i < MAP_SIZE; i++)
		delete *(map + i);
	delete map;
}
void print(node*** map)
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			int value = (*(*(map + i) + j))->value;
			cout << value << " ";
		}
		cout << endl;
	}
}
int main()
{

	node*** map = new node**[MAP_SIZE];
	init(map);
	cout << "the map:" << endl;
	print(map);
	A_star a(map);
	a.setStart(1, 1);
	a.setEnd(6, 6);
	a.findWay();
	a.printG();
	a.printH();
	a.printF();
	a.printResult();
	del(map);
	system("pause");
	return 0;
}