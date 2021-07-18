#include "MazeRouter.h"
// constants 
// empty cell = -1
// Obsticle = 999
// Points of pins = 0
// Any positive value from 1 is weight
void MazeRouter::readFile() {
	ifstream in("data.txt");

	in >> row;
	in >> col;
	
	a = new int*[row];
	for (int i = 0; i < row; i++)
	{
		a[i] = new int[col];
	}

	int numOBS,numNet,numPin,x,y;
	
	in >> numOBS;
	for (int i = 0; i < numOBS; i++)
	{
		Point p;
		in >> p.x >> p.y;
		obs.push_back(p);
	}

	in >> numNet;
	for (int i = 0; i < numNet; i++)
	{
		Net net;
		in >> net.name;

		in >> numPin;
		for (int j = 0; j < numPin; j++)
		{
			NetInfo netInfo;

			in >> netInfo.level;
			in >> netInfo.location.x;
			in >> netInfo.location.y;

			net.netInfo.push_back(netInfo);
		}
		nets.push_back(net);
	}
	in.close();
}

void MazeRouter::init2DArray(int netIndex,int p1,int p2) {
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			a[i][j] = -1;
		}
	}
	for (int i = 0; i < obs.size(); i++)
	{
		a[obs[i].x][obs[i].y] = OBS_VALUE;
	}

	a[nets[netIndex].netInfo[p1].location.x][nets[netIndex].netInfo[p1].location.y] = 0; // put zero at source
	a[nets[netIndex].netInfo[p2].location.x][nets[netIndex].netInfo[p2].location.y] = 0; // put zero at destination
}

void MazeRouter::applyLee(int netIndex,int p1,int p2) {
	init2DArray(netIndex,p1,p2);
	// up, right, down, left
	int dx [] = {-1,0,1,0};
	int dy [] = {0,1,0,-1};

	Point start = nets[netIndex].netInfo[p1].location;

	vector<Point> points;
	points.push_back(start);

	while (!points.empty())
	{
		Point p = points.front();
		points.erase(points.begin());

		for (int i = 0; i < 4; i++)
		{
			int newx = p.x + dx[i];
			int newy = p.y + dy[i];
			
			if(newx >= 0 && newy >= 0 && newx < row && newy < col) {
				if(a[newx][newy] == -1) {
					a[newx][newy] = a[p.x][p.y] + 1;
					Point q;
					q.x = newx;
					q.y = newy;
					points.push_back(q);
				}
			}
		}
	}
	
	display();
	// start preparing the results
	Point end = nets[netIndex].netInfo[p2].location;

	Point cur = end;
	points.push_back(cur);
	int min = INT_MAX;

	while (cur != start)
	{	
		int x,y;
		for (int i = 0; i < 4; i++)
		{
			int newx = cur.x + dx[i];
			int newy = cur.y + dy[i];
			// check for boundries
			if(newx >= 0 && newy >= 0 && newx < row && newy < col) {
				// get the new minimum value
				if(a[newx][newy] < min && !(newx == end.x && newy == end.y)) {
					min = a[newx][newy];
					x = newx;
					y = newy;
					//break;
				}
			}
		}
		cur.x = x;
		cur.y = y;
		points.push_back(cur);
	}
	ofstream out("results.txt", std::ios_base::app);
	out << nets[netIndex].name << " ,Cost : " << points.size() << endl;
	for (int i = 0; i < points.size(); i++)
	{
		out << "(" << nets[netIndex].netInfo[p1].level << "," << points[i].x << "," << points[i].y << ") ";
	}
	out << endl <<endl;
}

void MazeRouter::getAllMinimumDistances() {
	ofstream out("results.txt");
	out << "<Results>" << endl;
	out.close();

	for (int i = 0; i < nets.size(); i++)
	{
		for (int j = 0; j < nets[i].netInfo.size(); j++)
		{
			applyLee(i,j,(j+1)%nets[i].netInfo.size());
		}
	}
}

// for testing purpose only
void MazeRouter::display() {
	cout << setw(5) << "" ;
	for (int i = 0; i < col; i++)
	{
		cout << setw(5) << i;
	}
	cout << endl;
	for (int i = 0; i < row; i++)
	{
		cout << setw(5) << i;
		for (int j = 0; j < col; j++)
		{
			cout << setw(5) << a[i][j];
		}
		cout << endl;
	}
	cout << endl;
}