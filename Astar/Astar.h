#pragma once
#define MAP_SIZE 8
#include <iostream>
#include <vector>
#include <string>

struct node
{
	int value;
	int x, y;
	node* next;
	int f;
};

class A_star
{
public:
	A_star(node*** map);
	void printG();
	void printH();
	void printF();
	void findWay();
	void initial();
	void initial2();
	void setStart(int start_x, int start_y);
	void setEnd(int end_x, int end_y);
	void printResult();
private:
	node*** map;
	int _G[MAP_SIZE][MAP_SIZE];
	int _H[MAP_SIZE][MAP_SIZE];
	int _F[MAP_SIZE][MAP_SIZE];
	std::string result[MAP_SIZE][MAP_SIZE];
	int start_x, start_y;
	int end_x, end_y;
	std::vector<node*> close_list;
	std::vector<node*> open_list;
};