#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

#define OBS_VALUE 999

struct Point
{
	int x;
	int y;

	bool operator!=(Point & p) {
		return (x != p.x || y != p.y);
	}
};

struct NetInfo {
	int level;
	Point location;
};

struct Net
{
	string name;
	vector<NetInfo> netInfo;
};

class MazeRouter
{
public:
	vector<Net> nets;
	vector<Point> obs;
	int ** a;
	int row;
	int col;

	void readFile();
	void init2DArray(int netIndex,int p1,int p2);

	void applyLee(int netIndex,int p1,int p2);
	void getAllMinimumDistances();

	void display();
};

