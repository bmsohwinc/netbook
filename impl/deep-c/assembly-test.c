long int simple_l(long int *xp, long int y) {  long int t = *xp + y; *xp = t; return t; }

int main() {
	long int x = 1l
	simple_l(&x, x);
	return 0;
}
