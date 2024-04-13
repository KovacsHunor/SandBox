#ifndef UTIL_H
#define UTIL_H

class Global {
   public:
	static const int TILESIZE = 5;
	static int brush_size;

	static void incBrushSize() { if(brush_size*TILESIZE < 200) brush_size++; }
	static void decBrushSize() { if(brush_size > 1) brush_size--; }
};

struct Vec {
	int x;
	int y;

	Vec(const Vec& rhs) : x(rhs.x), y(rhs.y) {}
	Vec(int x = 0, int y = 0) : x(x), y(y) {}
	Vec operator*(const int mul) const { return Vec(x * mul, y * mul); }
	bool operator==(const Vec& rhs) const { return x == rhs.x && y == rhs.y; }
	bool operator!=(const Vec& rhs) const {
		if (*this == rhs) return false;
		return true;
	}
	bool operator!=(const int k) const { return (x != k || y != k); }
	bool operator>=(const int k) const { return (x >= k && y >= k); }
	void operator+=(const Vec& rhs) {
		x += rhs.x;
		y += rhs.y;
	}
	void operator*=(const int rhs) {
		x *= rhs;
		y *= rhs;
	}
	Vec operator+(const Vec& rhs) const { return Vec(x + rhs.x, y + rhs.y); }
	Vec operator-(const Vec& rhs) const { return Vec(x - rhs.x, y - rhs.y); }
	bool operator<(const Vec& rhs) const { return x < rhs.x && y < rhs.y; }
	bool operator<=(const Vec& rhs) const { return x <= rhs.x && y <= rhs.y; }
	Vec& operator=(const Vec& rhs) {
		x = rhs.x;
		y = rhs.y;
		return *this;
	}
};

#endif