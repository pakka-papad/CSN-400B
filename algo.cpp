#ifndef ALGO_CPP
#define ALGO_CPP

#include "point.cpp"
#include "line.cpp"
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <iostream>
#include <tuple>
#include <algorithm>
using namespace std;

vector<Point2d> generateAllReflections2d(const vector<Line2d> &axes, const Point2d &p) {
    map<Point2d,int> mp;
    mp[p] = 0;
    queue<Point2d> q;
    vector<Point2d> res;
    q.push(p);
    while(!q.empty()) {
        auto pt = q.front();
        q.pop();
        for(auto axis: axes) {
            auto ref = axis.reflect(pt);
            if(ref == nullptr) continue;
            auto refp = *ref;
            if(mp.find(refp) == mp.end()) {
                mp[refp] = mp[pt] + 1;
                if(mp[refp] < 2) {
                    q.push(refp);
                }
                res.push_back(refp);
            }
        }
    }
    return res;
}

vector<Point3d> generateAllReflections3d(const vector<Plane3d> &planes, const Point3d &p) {
    map<Point3d,int> mp;
    mp[p] = 0;
    queue<Point3d> q;
    vector<Point3d> res;
    q.push(p);
    while(!q.empty()) {
        auto pt = q.front();
        q.pop();
        for(auto plane: planes) {
            auto ref = plane.reflect(pt);
            if(ref == nullptr) continue;
            auto refp = *ref;
            if(mp.find(refp) == mp.end()) {
                mp[refp] = mp[pt] + 1;
                if(mp[refp] < 3) {
                    q.push(refp);
                }
                res.push_back(refp);
            }
        }
    }
    return res;
}

vector<pair<Point2d,Point2d>> generatePairs2d(
    const vector<Point2d> &points,
    const vector<Line2d> &axes
) {
    vector<pair<Point2d,Point2d>> result;
    set<Point2d> L1(points.begin(), points.end());
    vector<Line2d> S;
    while(L1.size() > 1) {
        auto const i = *L1.begin();
        L1.erase(i);

        S.clear();
        for(auto axis: axes) {
            if (!axis.containsPoint(i)) {
                continue;
            }
            S.push_back(axis);
        }
        
        auto L2 = L1;

        while(!L2.empty()) {
            auto const j = *L2.begin();
            L2.erase(j);
           
            result.push_back({i,j});
            
            auto jrefs = generateAllReflections2d(S, j);
            for(auto jref: jrefs) {
                L2.erase(jref);
            }
        }
        
        auto irefs = generateAllReflections2d(axes, i);
        for(auto iref: irefs) {
            L1.erase(iref);
        }
    }
    return result;
}

vector<tuple<Point2d,Point2d,Point2d>> generate3Tuple2d(
    const vector<Point2d> &points,
    const vector<Line2d> &axes
){
    vector<tuple<Point2d,Point2d,Point2d>> result;
    set<Point2d> L1(points.begin(), points.end());
    vector<Line2d> S1, S2;
    set<tuple<Point2d,Point2d,Point2d>> blacklist;

    auto isSelfReflection = [](const Line2d &axis, const set<Point2d> &s) -> bool {
        set<Point2d> r;
        for(auto &p: s) {
            auto ref = axis.reflect(p);
            if(ref != NULL) {
                r.insert(*ref);
            }
        }
        return (s == r);
    };

    auto blacklistAllTupleRefs = [&axes, &blacklist](const tuple<Point2d,Point2d,Point2d> &t) {
        blacklist.insert(t);
        map<tuple<Point2d,Point2d,Point2d>,int> mp;
        mp[t] = 0;
        queue<tuple<Point2d,Point2d,Point2d>> q;
        q.push(t);
        while(!q.empty()) {
            auto pt = q.front();
            q.pop();
            for(auto axis: axes) {
                auto ref1 = axis.reflect(get<0>(pt));
                auto ref2 = axis.reflect(get<1>(pt));
                auto ref3 = axis.reflect(get<2>(pt));
                if(ref1 == nullptr) continue;
                if(ref2 == nullptr) continue;
                if(ref3 == nullptr) continue;
                vector<Point2d> refp = {*ref1,*ref2,*ref3};
                sort(refp.begin(), refp.end());
                tuple<Point2d,Point2d,Point2d> tp = {refp[0], refp[1], refp[2]};
                if(mp.find(tp) == mp.end()) {
                    mp[tp] = mp[pt] + 1;
                    if(mp[tp] < 2) {
                        q.push(tp);
                    }
                    blacklist.insert(tp);
                }
            }
        }
    };

    while(!L1.empty()) {
        auto const i = *L1.begin();
        L1.erase(i);
        
        S1.clear();
        for(auto axis: axes) {
            if (!axis.containsPoint(i)) {
                continue;
            }
            S1.push_back(axis);
        }
        
        auto L2 = L1;
        
        while(!L2.empty()) {
            auto const j = *L2.begin();
            L2.erase(j);
        
            S2.clear();
            set<Point2d> x1 = {i,j};
            for(auto axis: axes) {
                if(isSelfReflection(axis, x1)) {
                    S2.push_back(axis);
                }
            }

            auto L3 = L2;

            while(!L3.empty()) {
                auto const k = *L3.begin();
                L3.erase(k);
                if (blacklist.find({i,j,k}) == blacklist.end()) {
                    result.push_back({i,j,k});
                    blacklistAllTupleRefs({i,j,k});
                }
                auto krefs = generateAllReflections2d(S2, k);
                for(auto kref: krefs) {
                    L3.erase(kref);
                    vector<Point2d> y = {i,j,kref};
                    sort(y.begin(), y.end());
                    blacklistAllTupleRefs({y[0], y[1], y[2]});
                }
            }

            auto jrefs = generateAllReflections2d(S1, j);
            for(auto jref: jrefs) {
                L2.erase(jref);
            }
        }

        auto irefs = generateAllReflections2d(axes, i);
        for(auto iref: irefs) {
            L1.erase(iref);
        }
    }

    return result;
}

vector<pair<Point3d,Point3d>> generatePairs3d(
    const vector<Point3d> &points,
    const vector<Plane3d> &axes
) {
    vector<pair<Point3d,Point3d>> result;
    set<Point3d> L1(points.begin(), points.end());
    vector<Plane3d> S;
    while(L1.size() > 1) {
        auto const i = *L1.begin();
        L1.erase(i);
        S.clear();
        for(auto axis: axes) {
            if (!axis.containsPoint(i)) {
                continue;
            }
            S.push_back(axis);
        }
        auto L2 = L1;
        while(!L2.empty()) {
            auto const j = *L2.begin();
            L2.erase(j);
            result.push_back({i,j});
            
            auto refs = generateAllReflections3d(S, j);
            for(auto ref: refs) {
                L2.erase(ref);
            }
        }
        auto refs = generateAllReflections3d(axes, i);
        for(auto ref: refs) {
            L1.erase(ref);
        }
    }
    return result;
}

vector<pair<Point2d,Point2d>> generatePairs(int n, int m) {
    vector<Point2d> points;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            points.push_back(Point2d(i,j));
        }
    }
    vector<Line2d> axes;
    axes.push_back(Line2d(2,0,-n+1));
    axes.push_back(Line2d(0,2,-m+1));
    if(n == m) {
        axes.push_back(Line2d(1,-1,0));
        axes.push_back(Line2d(1,1,-n+1));
    }
    return generatePairs2d(points, axes);
}

vector<tuple<Point2d, Point2d, Point2d>> generate3Tuples(int n, int m) {
    vector<Point2d> points;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            points.push_back(Point2d(i,j));
        }
    }
    vector<Line2d> axes;
    axes.push_back(Line2d(2,0,-n+1));
    axes.push_back(Line2d(0,2,-m+1));
    if(n == m) {
        axes.push_back(Line2d(1,-1,0));
        axes.push_back(Line2d(1,1,-n+1));
    }
    return generate3Tuple2d(points, axes);
}

vector<pair<Point3d,Point3d>> generatePairs(int a, int b, int c) {
    vector<Point3d> points;
    for(int i = 0; i < a; i++) {
        for(int j = 0; j < b; j++) {
            for(int k = 0; k < c; k++) {
                points.push_back(Point3d(i,j,k));
            }
        }
    }
    vector<Plane3d> axes;
    axes.push_back(Plane3d(2,0,0,-a+1));
    axes.push_back(Plane3d(0,2,0,-b+1));
    axes.push_back(Plane3d(0,0,2,-c+1));
    if(a == b) {
        axes.push_back(Plane3d(1,-1,0,0));
        axes.push_back(Plane3d(1,1,0,-a+1));
    } 
    if(b == c) {
        axes.push_back(Plane3d(0,1,-1,0));
        axes.push_back(Plane3d(0,1,1,-b+1));
    }
    if(c == a) {
        axes.push_back(Plane3d(1,0,-1,0));
        axes.push_back(Plane3d(1,0,1,-c+1));
    }
    return generatePairs3d(points, axes);
}

#endif