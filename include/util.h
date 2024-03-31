struct Global{
    static const int TILESIZE = 12;
};

struct Pos{
    int x;
    int y;
    Pos(const Pos& rhs):x(rhs.x), y(rhs.y){}
    Pos(int x, int y):x(x), y(y){}
    Pos operator*(const int mul) const{
        return Pos(x*mul, y*mul);
    }
    bool operator==(const Pos& rhs) const{
        return x==rhs.x && y == rhs.y;
    }
    bool operator<(const Pos& rhs) const{
        return x<rhs.x && y < rhs.y;
    }
    bool operator<=(const Pos& rhs) const{
        return *this < rhs || *this == rhs;
    }
    Pos& operator=(const Pos& rhs){
        x = rhs.x;
        y = rhs.y;
        return *this;
    }
};