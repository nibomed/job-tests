#include <iostream>
#include <vector>
#include <algorithm>

struct point {
	double x, y;
	bool isUsed = false;
	point(double x, double y) : x(x), y(y) {};
};

using namespace std;
int n;
double result, bestResult;
vector<point> points;
vector<pair<point, point>> lines;

double area(point a, point b, point c) {
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool intersect_1(double a, double b, double c, double d) {
	if (a > b)  swap(a, b);
	if (c > d)  swap(c, d);
	return max(a, c) <= min(b, d);
}

bool intersect(point a, point b, point c, point d) {
	return intersect_1(a.x, b.x, c.x, d.x)
		&& intersect_1(a.y, b.y, c.y, d.y)
		&& area(a, b, c) * area(a, b, d) <= 0
		&& area(c, d, a) * area(c, d, b) <= 0;
}

double length(point p1, point p2) {
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

bool isSegmentsIntersects(pair<point, point> line1, pair<point, point> line2) {
	return intersect(line1.first, line1.second, line2.first, line2.second);
}

bool isStillPolygon() {
	if (lines.size() < 2)
		return true;

	pair<point, point> lastLine = lines.back();

	int firstToCheck = 0;
	if (lines.size() == points.size())
		firstToCheck = 1;
	for (int i = firstToCheck; i < lines.size() - 2; i++)
		if (isSegmentsIntersects(lines[i], lastLine))
			return false;
	return true;
}

void addLine(point p1, point p2) {
	lines.push_back(make_pair(p1, p2));
	result += length(p1, p2);
}

void removeLine() {
	pair<point, point> lastLine = lines.back();
	result -= length(lastLine.first, lastLine.second);
	lines.pop_back();
}

void buildPolygon(point vertex) {
	if (isStillPolygon() && result < bestResult) {
		bool isAllPointsUsed = true;;
		for (auto &point : points) {
			if (!point.isUsed) {
				isAllPointsUsed = false;
				point.isUsed = true;
				addLine(vertex, point);

				buildPolygon(point);

				removeLine();
				point.isUsed = false;
			}
		}

		if (isAllPointsUsed) {
			addLine(vertex, points[0]);
			if (isStillPolygon())
				bestResult = min(result, bestResult);
			removeLine();
		}
	}
}

int main() {
	std::cin >> n;
	if (n < 3) return 1;
	while (points.size() < n)
	{
		double x, y;
		std::cin >> x >> y;
		points.push_back(point(x, y));
	}

	bestResult = numeric_limits<double>::max();
	points[0].isUsed = true;
	result = 0;
	buildPolygon(points[0]);

	std::cout << bestResult;
	return 0;
}
