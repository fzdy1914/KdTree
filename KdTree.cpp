#include<math.h>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<iostream>
#include<fstream>
#include"KdTree.h"

using namespace std;


void KdTree::print() {
    for (int i = 0; i < 100; i++) {
        this->P[i].print();
    }
}
 
int KdTree::makeKDTree(int l, int r, int depth) {
    if (!(l < r)) return NIL;

    int mid = (l + r) / 2;
    int t = this->np++;
    if (depth % 3 == 0) {
        sort(this->P + l, this->P + r, lessX);
    } else if (depth % 3 == 1) {
        sort(this->P + l, this->P + r, lessY);
    } else {
        sort(this->P + l, this->P + r, lessZ);
    }

    this->T[t].location = mid;
    this->T[t].l = this->makeKDTree(l, mid, depth + 1);
    this->T[t].r = this->makeKDTree(mid + 1, r, depth + 1);
    
    return t;
}


void KdTree::region_find(int v, int sx, int tx, int sy, int ty, int sz, int tz, int depth, vector<Point>& ans) {
    int x = this->P[this->T[v].location].x;
    int y = this->P[this->T[v].location].y;
    int z = this->P[this->T[v].location].z;

    if (sx <= x && x <= tx && sy <= y && y <= ty && sz <= z && z <= tz) {
        ans.push_back(this->P[this->T[v].location]);
    }

    if (depth % 3 == 0) {
        if (this->T[v].l != NIL) {
            if (sx <= x) {
                this->region_find(this->T[v].l, sx, tx, sy, ty, sz, tz, depth + 1, ans);
            }
        }
        if (this->T[v].r != NIL) {
            if (x <= tx) {
                this->region_find(this->T[v].r, sx, tx, sy, ty, sz, tz, depth + 1, ans);
            }
        }
    } else if (depth % 3 == 1) {
        if (this->T[v].l != NIL) {
            if (sy <= y) {
                this->region_find(this->T[v].l, sx, tx, sy, ty, sz, tz, depth + 1, ans);
            }
        }
        if (this->T[v].r != NIL) {
            if (y <= ty) {
                this->region_find(this->T[v].r, sx, tx, sy, ty, sz, tz, depth + 1, ans);
            }
        }
    } else {
        if (this->T[v].l != NIL) {
            if (sz <= z) {
                this->region_find(this->T[v].l, sx, tx, sy, ty, sz, tz, depth + 1, ans);
            }
        }
        if (this->T[v].r != NIL) {
            if(z <= tz) {
                this->region_find(this->T[v].r, sx, tx, sy, ty, sz, tz, depth + 1, ans);
            }
        }
    }
}

void KdTree::nearst_find(int v, double x1, double y1, double z1, double& r, int depth, Point &ans) {
    double sx = x1 - r;
    double tx = x1 + r;
    double sy = y1 - r;
    double ty = y1 + r;
    double sz = z1 - r;
    double tz = z1 + r;

    double x = this->P[this->T[v].location].x;
    double y = this->P[this->T[v].location].y;
    double z = this->P[this->T[v].location].z;
    
    if(sx <= x && x <= tx && sy <= y && y <= ty && sz <= z && z <= tz){
        double r1 = sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1) + (z - z1) * (z - z1));
        if (r1 < r) {
            ans = this->P[this->T[v].location];
        }
        r = r1;
    }
    
    if(depth % 3 == 0) {
        if(this->T[v].l != NIL) {
            if(sx <= x) this->nearst_find(this->T[v].l, x1, y1, z1, r, depth + 1, ans);
        }
        if(this->T[v].r != NIL) {
            if(x <= tx) this->nearst_find(this->T[v].r, x1, y1, z1, r, depth + 1, ans);
        }
    } else if(depth % 3 == 1) {
        if(this->T[v].l != NIL) {
            if(sy <= y) this->nearst_find(this->T[v].l, x1, y1, z1, r, depth + 1, ans);
        }
        if(this->T[v].r != NIL) {
            if(y <= ty) this->nearst_find(this->T[v].r, x1, y1, z1, r, depth + 1, ans);
        }
    } else {
        if(this->T[v].l != NIL) {
            if(sz <= z) this->nearst_find(this->T[v].l, x1, y1, z1, r, depth + 1, ans);
        }
        if(this->T[v].r != NIL) {
            if(z <= tz) this->nearst_find(this->T[v].r, x1, y1, z1, r, depth + 1, ans);
        }
    }
}

bool lessX(const Point &p1, const Point &p2) { return p1.x < p2.x; }
bool lessY(const Point &p1, const Point &p2) { return p1.y < p2.y; }
bool lessZ(const Point &p1, const Point &p2) { return p1.z < p2.z; }