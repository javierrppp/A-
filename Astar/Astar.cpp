 //A_star.cpp : 定义控制台应用程序的入口点。


#include "stdafx.h"
#include "Astar.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include<string>

using namespace std;

//bool node::operator==(node n)
//{
//	if (n.x == this->x && n.y == this->y)
//		return true;
//	return false;
//}

class min_fun
{
public:
	node* minNode;
	void operator() (node* n)
	{
		if (minNode == 0) minNode = n;
		else if (n->f < minNode->f) {
			minNode = n;
		}
	}
	operator node*()
	{
		return minNode;
	}
};

A_star::A_star(node*** map)
{
	this->map = map;
	initial();
	this->start_x = 0;
	this->start_y = 0;
	this->end_x = 0;
	this->end_y = 0;
}

void A_star::initial()
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			_G[i][j] = 0;
			_H[i][j] = 0;
			_F[i][j] = 0;
		}
	}
}

void A_star::initial2()
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			_H[i][j] = abs(end_x - i) + abs(end_y - j);
			_F[i][j] = _H[i][j] + _G[i][j];
		}
	}
}

void A_star::printG()
{
	cout << "————G————" << endl;
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			cout << _G[i][j] << " ";
		}
		cout << endl;
	}
}

void A_star::printH()
{
	cout << "————H————" << endl;
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			cout << _H[i][j] << " ";
		}
		cout << endl;
	}
}

void A_star::printF()
{
	cout << "————F————" << endl;
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			cout << _F[i][j] << " ";
		}
		cout << endl;
	}
}

void A_star::setStart(int start_x, int start_y)
{
	this->start_x = start_x;
	this->start_y = start_y;
}

void A_star::setEnd(int end_x, int end_y)
{
	this->end_x = end_x;
	this->end_y = end_y;
}

void A_star::printResult()
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			if ((*(*(map + i) + j))->value == 1)
				result[i][j] = "■";
			else
				result[i][j] = "  ";
		}
	}
	node* target = *(*(map + end_x) + end_y);
	result[target->x][target->y] = "o ";
	node* p = target;
	while (p->next != 0)
	{
		p = p->next;
		result[p->x][p->y] = "o ";
	}
	cout << "————result————" << endl;
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			cout << result[i][j];
		}
		cout << endl;
	}
}

void A_star::findWay()
{
	initial2();
	node* endNode = *(*(map + end_x) + end_y);
	node* curNode = *(*(map + start_x) + start_y);
	while (curNode != endNode)
	{
		close_list.push_back(curNode);
		int cur_x = curNode->x;
		int cur_y = curNode->y;
		//以右下左上的顺序遍历邻节点
		if (cur_x < MAP_SIZE - 1)
		{
			node* rightNode = *(*(map + cur_x + 1) + cur_y);
			//如果右边不是墙壁且不在close_list当中，则判断：
			if (rightNode->value == 0 && find(close_list.begin(), close_list.end(), rightNode) == close_list.end())
			{
				//如果它不在open_list当中，则加入open_list并且指定当前节点为父节点，否则判断是否更换open_list的父节点
				if (find(open_list.begin(), open_list.end(), rightNode) == open_list.end())
				{
					open_list.push_back(rightNode);
					rightNode->next = curNode;
					_G[cur_x + 1][cur_y] = _G[cur_x][cur_y] + 1;
					_F[cur_x + 1][cur_y] = _G[cur_x + 1][cur_y] + _H[cur_x + 1][cur_y];
					rightNode->f = _F[cur_x + 1][cur_y];
				}
				else
				{
					node* fatherNode = rightNode->next;
					if (_F[fatherNode->x][fatherNode->y] > _F[cur_x][cur_y])
					{
						rightNode->next = curNode;
						_G[cur_x + 1][cur_y] = _G[cur_x][cur_y] + 1;
						_F[cur_x + 1][cur_y] = _G[cur_x + 1][cur_y] + _H[cur_x + 1][cur_y];
						rightNode->f = _F[cur_x + 1][cur_y];
					}
				}
			}
			if (rightNode == endNode) break;
		}
		if (cur_y < MAP_SIZE - 1)
		{
			node* downNode = *(*(map + cur_x) + cur_y + 1);
			if (downNode->value == 0 && find(close_list.begin(), close_list.end(), downNode) == close_list.end())
			{
				if (find(open_list.begin(), open_list.end(), downNode) == open_list.end())
				{
					open_list.push_back(downNode);
					downNode->next = curNode;
					_G[cur_x][cur_y + 1] = _G[cur_x][cur_y] + 1;
					_F[cur_x][cur_y + 1] = _G[cur_x][cur_y + 1] + _H[cur_x][cur_y + 1];
					downNode->f = _F[cur_x][cur_y + 1];
				}
				else
				{
					node* fatherNode = downNode->next;
					if (_F[fatherNode->x][fatherNode->y] > _F[cur_x][cur_y])
					{
						downNode->next = curNode;
						_G[cur_x][cur_y + 1] = _G[cur_x][cur_y] + 1;
						_F[cur_x][cur_y + 1] = _G[cur_x][cur_y + 1] + _H[cur_x][cur_y + 1];
						downNode->f = _F[cur_x][cur_y + 1];
					}
				}
			}
			if (downNode == endNode) break;
		}
		if (cur_x > 0)
		{
			node* leftNode = *(*(map + cur_x - 1) + cur_y);
			if (leftNode->value == 0 && find(close_list.begin(), close_list.end(), leftNode) == close_list.end())
			{
				if (find(open_list.begin(), open_list.end(), leftNode) == open_list.end())
				{
					open_list.push_back(leftNode);
					leftNode->next = curNode;
					_G[cur_x - 1][cur_y] = _G[cur_x][cur_y] + 1;
					_F[cur_x - 1][cur_y] = _G[cur_x - 1][cur_y] + _H[cur_x - 1][cur_y];
					leftNode->f = _F[cur_x - 1][cur_y];
				}
				else
				{
					node* fatherNode = leftNode->next;
					if (_F[fatherNode->x][fatherNode->y] > _F[cur_x][cur_y])
					{
						leftNode->next = curNode;
						_G[cur_x - 1][cur_y] = _G[cur_x][cur_y] + 1;
						_F[cur_x - 1][cur_y] = _G[cur_x - 1][cur_y] + _H[cur_x - 1][cur_y];
						leftNode->f = _F[cur_x - 1][cur_y];
					}
				}
			}
			if (leftNode == endNode) break;
		}
		if (cur_y > 0)
		{
			node* upNode = *(*(map + cur_x) + cur_y - 1);
			if (upNode->value == 0 && find(close_list.begin(), close_list.end(), upNode) == close_list.end())
			{
				if (find(open_list.begin(), open_list.end(), upNode) == open_list.end())
				{
					open_list.push_back(upNode);
					upNode->next = curNode;
					_G[cur_x][cur_y - 1] = _G[cur_x][cur_y] + 1;
					_F[cur_x][cur_y - 1] = _G[cur_x][cur_y - 1] + _H[cur_x][cur_y - 1];
					upNode->f = _F[cur_x][cur_y - 1];
				}
				else
				{
					node* fatherNode = upNode->next;
					if (_F[fatherNode->x][fatherNode->y] > _F[cur_x][cur_y])
					{
						upNode->next = curNode;
						_G[cur_x][cur_y - 1] = _G[cur_x][cur_y] + 1;
						_F[cur_x][cur_y - 1] = _G[cur_x][cur_y - 1] + _H[cur_x][cur_y - 1];
						upNode->f = _F[cur_x][cur_y - 1];
					}
				}
			}
			if (upNode == endNode) break;
		}
		curNode = for_each(open_list.begin(), open_list.end(), min_fun());
		remove(open_list.begin(), open_list.end(), curNode);
		//cout << "open_list:" << open_list.size() << endl;
	}
}
