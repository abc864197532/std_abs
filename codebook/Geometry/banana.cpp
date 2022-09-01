int ori(Pt o, Pt a, Pt b) {
    long long k = (o - a) ^ (o - b);
    return (k < 0 ? -1 : (k > 0 ? 1 : 0));
}
bool banana(Pt a, Pt b, Pt c, Pt d) { // segment ab and cd
    if (ori(a, b, c) == 0 && (c - a) * (c - b) <= 0) return true;
    if (ori(a, b, d) == 0 && (d - a) * (d - b) <= 0) return true;
    if (ori(c, d, a) == 0 && (a - c) * (a - d) <= 0) return true;
    if (ori(c, d, b) == 0 && (b - c) * (b - d) <= 0) return true;
    return ori(a, b, c) * ori(a, b, d) == -1 && ori(c, d, a) * ori(c, d, b) == -1;
}
Pt intersect(Pt a, Pt b, Pt c, Pt d) { // segment ab and cd
	double abc = (b - a) ^ (c - a);
	double abd = (b - a) ^ (d - a);
	return (d * abc - c * abd) / (abc - abd);
}