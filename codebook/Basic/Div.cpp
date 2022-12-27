ll divdown(ll a, ll b) {
	return a / b - (a < 0 && a % b);
}
ll divup(ll a, ll b) {
	return a / b + (a > 0 && a % b);
}
a / b <  x -> divdown(a, b) + 1 <= x
a / b <= x -> divup(a, b) <= x
x <  a / b -> x <= divup(a, b) - 1
x <= a / b -> x <= divdown(a, b)