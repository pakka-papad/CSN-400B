#ifndef LINE_CPP
#define LINE_CPP

#include "point.cpp"
#include <stdexcept>
#include <math.h>
#include <iostream>
#include <tuple>

class Line2d {
    public:
    /**
     * Represents line with equation (ax + by + c = 0)
    */
    int a, b, c;
    Line2d(int a, int b, int c): a(a), b(b), c(c) {
        if(a == 0 && b == 0) throw std::invalid_argument("Does not define a line");
    }

    bool operator==(const Line2d &other) const {
        return (((long long)a*other.b == (long long)b*other.a) && ((long long)b*other.c == (long long)c*other.b));
    }

    bool containsPoint(const Point2d &p) {
        return ((long long)a*p.x + (long long)b*p.y + c == 0L);
    }

    Point2d* reflect(const Point2d &p) const {
        std::cerr << "Reflection of point (" << p.x << "," << p.y << ") along ";
        std::cerr << a << "x + " << b << "y + " << c << " = 0 is ";
        long long n = (long long)a*p.x + (long long)b*p.y + c;
        long long d = (long long)a*a + (long long)b*b;
        if (abs(2 * a * n) % abs(d) != 0) {
            std::cerr << "null\n";
            return nullptr;
        }
        if (abs(2 * b * n) % abs(d) != 0) {
            std::cerr << "null\n";
            return nullptr;
        }
        auto res = new Point2d(p.x - (int)((2 * a * n) / d), p.y - (int)((2 * b * n) / d));
        std::cerr << "(" << res->x << "," << res->y << ")\n";
        return res;
    }
};


class Plane3d {
    public:
    /**
     * Represents line with equation (ax + by + cz + d = 0)
    */
    int a, b, c, d;
    Plane3d(int a, int b, int c, int d): a(a), b(b), c(c), d(d) {
        if(a == 0 && b == 0 && c == 0) throw std::invalid_argument("Does not define a plane");
    }

    bool operator==(const Plane3d &other) const {
        return (((long long)a*other.b == (long long)b*other.a) && ((long long)b*other.c == (long long)c*other.b) && ((long long)c*other.d == (long long)d*other.c));
    }

    bool containsPoint(const Point3d &p) {
        return ((long long)a*p.x + (long long)b*p.y + (long long)c*p.z + d == 0L);
    }

    Point3d* reflect(const Point3d &p) const {
        std::cerr << "Reflection of point (" << p.x << "," << p.y << "," << p.z << ") along ";
        std::cerr << a << "x + " << b << "y + " << c  << "z + " << d << " = 0 is ";
        long long n = (long long)a*p.x + (long long)b*p.y + (long long)c*p.z + d;
        long long d = (long long)a*a + (long long)b*b + (long long)c*c;
        if (abs(2 * a * n) % abs(d) != 0) {
            std::cerr << "null\n";
            return nullptr;
        }
        if (abs(2 * b * n) % abs(d) != 0) {
            std::cerr << "null\n";
            return nullptr;
        }
        if (abs(2 * c * n) % abs(d) != 0) {
            std::cerr << "null\n";
            return nullptr;
        }
        auto res = new Point3d(p.x - (int)((2 * a * n) / d), p.y - (int)((2 * b * n) / d), p.z - (int)((2 * c * n) / d));
        std::cerr << "(" << res->x << "," << res->y << "," << res->z << ")\n";
        return res;
    }
};

#endif