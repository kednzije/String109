int getPow(int a, int b) {
	if(b == 0) {
		return 1;
	}
	else if(b < 0) {
		return 0;
	}
	else {
		return a * getPow(a, b - 1);
	}
}
double getPow(double a, int b) {
	if(b == 0) {
		return 1;
	}
	else if(b < 0) {
		return getPow(a, b + 1) / a;
	}
	else {
		return a * getPow(a, b - 1);
	}
}