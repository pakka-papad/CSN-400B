#include "algo.cpp"
#include "point.cpp"
#include "line.cpp"
#include <iostream>
#include <vector>
using namespace std;

void print(const pair<Point2d,Point2d> &l){
	cout << "[" << "{" << l.first.x << "," << l.first.y << "} {" << l.second.x << "," << l.second.y << "}] ";
}

void print(const vector<pair<Point2d,Point2d>> &v){
	for(auto &x: v) print(x);
	cout << "\n\n";
}

void print(const tuple<Point2d,Point2d,Point2d> &l){
	cout << "[{" << get<0>(l).x << "," << get<0>(l).y << "} {" << get<1>(l).x << "," << get<1>(l).y << "} {" << get<2>(l).x << "," << get<2>(l).y << "}] ";
}

void print(const vector<tuple<Point2d,Point2d,Point2d>> &v){
	for(auto &x: v) print(x);
	cout << "\n\n";
}

void print(const tuple<Point3d,Point3d,Point3d> &l){
	cout << "[{" << get<0>(l).x << "," << get<0>(l).y << "," << get<0>(l).z << "} {" << get<1>(l).x << "," << get<1>(l).y << "," << get<1>(l).z << "} {" << get<2>(l).x << "," << get<2>(l).y << "," << get<2>(l).z << "}] ";
}

void print(const vector<tuple<Point3d,Point3d,Point3d>> &v){
	for(auto &x: v) print(x);
	cout << "\n\n";
}

void print(const tuple<Point2d,Point2d,Point2d, Point2d> &l){
	cout << "[{" << get<0>(l).x << "," << get<0>(l).y << "} {" << get<1>(l).x << "," << get<1>(l).y << "} {" << get<2>(l).x << "," << get<2>(l).y << "} {" << get<3>(l).x << "," << get<3>(l).y << "}] ";
}

void print(const vector<tuple<Point2d,Point2d,Point2d,Point2d>> &v){
	for(auto &x: v) print(x);
	cout << "\n\n";
}

void print(const tuple<Point3d,Point3d,Point3d, Point3d> &l){
	cout << "[{" << get<0>(l).x << "," << get<0>(l).y << "," << get<0>(l).z << "} {" << get<1>(l).x << "," << get<1>(l).y << "," << get<1>(l).z << "} {" << get<2>(l).x << "," << get<2>(l).y << "," << get<2>(l).z << "} {" << get<3>(l).x << "," << get<3>(l).y << "," << get<3>(l).z << "}] ";
}

void print(const vector<tuple<Point3d,Point3d,Point3d,Point3d>> &v){
	for(auto &x: v) print(x);
	cout << "\n\n";
}

void print(const pair<Point3d,Point3d> &l){
	cout << "[" << "{" << l.first.x << "," << l.first.y << "," << l.first.z << "} {" << l.second.x << "," << l.second.y << "," << l.second.z << "}] ";
}

void print(const vector<pair<Point3d,Point3d>> &v){
	for(auto &x: v) print(x);
	cout << "\n\n";
}

int main() {
    // int n, m;
    // cin >> n >> m;
    // auto res = generatePairs(n, m);
    // print(res);

    int a, b, c;
    cin >> a >> b >> c;
    auto res = generate4Tuples(a,b,c);
    print(res);
    return 0;
}