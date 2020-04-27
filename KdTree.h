#include<math.h>
#include<algorithm>
#include<vector>
#include <iostream>
#include <fstream>

#define MAX 1000000
#define NIL -1

using namespace std;

class Node{
	public:
		int location;
		int p, l, r;
		Node() {}
}; 
 
class Point{
	public:
		int id;
		double x, y, z;
		Point() {}
		Point(int id, double x, double y, double z): id(id), x(x), y(y), z(z) {}
		
	void print(){
		cout << id << " " << x << " " << y << " " << z << endl;
	}
};

class KdTree{
	public:
		Point P[MAX];
        Node T[MAX];
        int np = 0;

        KdTree() {}

        void print();
        int makeKDTree(int l, int r, int depth);
		void region_find(int v, int sx, int tx, int sy, int ty, int sz, int tz, int depth, vector<Point>&ans);
        void nearst_find(int v, double x1, double y1, double z1, double& r, int depth, Point &ans);
}; 

bool lessX(const Point &p1, const Point &p2);
bool lessY(const Point &p1, const Point &p2);
bool lessZ(const Point &p1, const Point &p2);