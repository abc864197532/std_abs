struct Pt {
	int x, y;
	Pt (int _x, int _y) : x(_x), y(_y) {}
	Pt operator + (Pt o) {return Pt(x + o.x, y + o.y);}
	Pt operator - (Pt o) {return Pt(x - o.x, y - o.y);}
	Pt operator * (int k) {return Pt(x * k, y * k);}
	Pt operator / (int k) {return Pt (x / k, y / k);}
	int operator * (Pt o) {return x * o.x + y * o.y;}
	int operator ^ (Pt o) {return x * o.y - y * o.x;}
	double abs() {return hypot(x, y);}
	int pos() {return y == 0 ? x < 0 : y > 0;}
};
bool btw(Pt a, Pt b, Pt c) {
    // c on segment ab?
    return ((a - b) ^ (a - c)) == 0 && ((c - a) * (c - b)) <= 0;
}
int area(Pt a, Pt b, Pt c) {
	return abs((a - b) ^ (a - c));
}