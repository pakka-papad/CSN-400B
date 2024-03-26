#ifndef Point_CPP
#define Point_CPP

#include <assert.h>

class Point2d {
	public:
	int x, y;
	Point2d(int x, int y): x(x), y(y) {

	}

	bool operator==(const Point2d &other) const {
		return (this->x == other.x && this->y == other.y);
	}

	bool operator<(const Point2d &other) const {
		return (this->x < other.x || (this->x == other.x && this->y < other.y));
	}

};

class Point3d {
	public:
	int x, y, z;
	Point3d(int x, int y, int z): x(x), y(y), z(z) {

	}

	bool operator==(const Point3d &other) const {
		return (this->x == other.x && this->y == other.y && this->z == other.z);
	}

	bool operator<(const Point3d &other) const {
		return (this->x < other.x || (this->x == other.x && this->y < other.y) || (this->x == other.x && this->y == other.y && this->z < other.z));
	}

};

#endif