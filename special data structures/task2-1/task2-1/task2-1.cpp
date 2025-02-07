#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct test {
	long long sum_even;
	long long count_even;
	long long sum_odd;
	long long count_odd;
	long long indicator;
};

void build(vector<test>& t, vector<long long>& a, long long v, long long tl, long long tr) {
	if (tl == tr) {
		if (a[tl] % 2 == 0) {
			t[v].sum_even = a[tl];
			t[v].count_even = 1;

			t[v].sum_odd = 0;
			t[v].count_odd = 0;
			t[v].indicator = 0;
		}
		else {
			t[v].sum_even = 0;
			t[v].count_even = 0;

			t[v].sum_odd = a[tl];
			t[v].count_odd = 1;
			t[v].indicator = 0;
		}
	}
	else {
		long long tm = (tl + tr) / 2;
		build(t, a, v * 2, tl, tm);
		build(t, a, v * 2 + 1, tm + 1, tr);

		t[v].sum_even = t[v * 2].sum_even + t[v * 2 + 1].sum_even;
		t[v].count_even = t[v * 2].count_even + t[v * 2 + 1].count_even;
		t[v].sum_odd = t[v * 2].sum_odd + t[v * 2 + 1].sum_odd;
		t[v].count_odd = t[v * 2].count_odd + t[v * 2 + 1].count_odd;
		t[v].indicator = 0;
	}
}

void changeIndicator(vector<test>& t, long long v, long long tl, long long tr) {
	if (t[v].indicator % 2 == 0) {
		// если индикатор четный, оставляем порядок как есть

		t[v].sum_even += (t[v].count_even * t[v].indicator);
		t[v].sum_odd += (t[v].count_odd * t[v].indicator);
	}
	else {
		// если индикатор нечетный, меняем суммы и количество местами

		long long temp_sum = t[v].sum_even;
		long long temp_count = t[v].count_even;
		t[v].sum_even = t[v].sum_odd + t[v].count_odd * t[v].indicator;
		t[v].sum_odd = temp_sum + t[v].count_even * t[v].indicator;
		t[v].count_even = t[v].count_odd;
		t[v].count_odd = temp_count;
	}

	if (tl != tr) {
		t[v * 2].indicator += t[v].indicator;
		t[v * 2 + 1].indicator += t[v].indicator;
	}

	t[v].indicator = 0;
}

void checkIndicator(vector<test>& t, long long v, long long tl, long long tr, long long tm) {
	if (t[v].indicator != 0) {
		changeIndicator(t, v, tl, tr);
	}

	if (t[v * 2].indicator != 0) {
		changeIndicator(t, v * 2, tl, tm);
	}

	if (t[v * 2 + 1].indicator != 0) {
		changeIndicator(t, v * 2 + 1, tm + 1, tr);
	}
}

void setValue(vector<test>& t, long long v, long long tl, long long tr, long long p, long long value) {
	if (tl > tr) {
		return;
	}
	if (tl == tr) {
		if (value % 2 == 0) {
			t[v].sum_even = value;
			t[v].count_even = 1;
			t[v].sum_odd = 0;
			t[v].count_odd = 0;
		}
		else {
			t[v].sum_even = 0;
			t[v].count_even = 0;
			t[v].sum_odd = value;
			t[v].count_odd = 1;
		}

		t[v].indicator = 0;
		return;
	}
	else {
		long long tm = (tl + tr) / 2;

		checkIndicator(t, v, tl, tr, tm);

		if (p <= tm) {
			setValue(t, v * 2, tl, tm, p, value);
		}
		else {
			setValue(t, v * 2 + 1, tm + 1, tr, p, value);
		}
		t[v].sum_even = t[v * 2].sum_even + t[v * 2 + 1].sum_even;
		t[v].count_even = t[v * 2].count_even + t[v * 2 + 1].count_even;
		t[v].sum_odd = t[v * 2].sum_odd + t[v * 2 + 1].sum_odd;
		t[v].count_odd = t[v * 2].count_odd + t[v * 2 + 1].count_odd;
	}
}

void increment(vector<test>& t, long long v, long long tl, long long tr, long long l, long long r) {
	if (l > r) {
		return;
	}
	/*if (tl == tr) {
		int temp_sum, temp_count;
		temp_sum = t[v].sum_even;
		temp_count = t[v].count_even;
		t[v].sum_even = t[v].sum_odd + t[v].count_odd;
		t[v].sum_odd = temp_sum + t[v].count_even;
		t[v].count_even = t[v].count_odd;
		t[v].count_odd = temp_count;
	}*/

	if (l == tl && r == tr) {
		t[v].indicator += 1;
		changeIndicator(t, v, tl, tr);
		return;
	}

	long long tm = (tl + tr) / 2;

	checkIndicator(t, v, tl, tr, tm);

	increment(t, v * 2, tl, tm, l, min(r, tm));
	increment(t, v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
	t[v].sum_even = t[v * 2].sum_even + t[v * 2 + 1].sum_even;
	t[v].count_even = t[v * 2].count_even + t[v * 2 + 1].count_even;
	t[v].sum_odd = t[v * 2].sum_odd + t[v * 2 + 1].sum_odd;
	t[v].count_odd = t[v * 2].count_odd + t[v * 2 + 1].count_odd;
}

long long getSum(vector<test>& t, long long v, long long tl, long long tr, long long l, long long r, int oddity) {
	if (l > r) {
		return 0;
	}

	if (t[v].indicator != 0) {
		changeIndicator(t, v, tl, tr);
	}

	if (l == tl && r == tr) {
		if (oddity == 0) {
			return t[v].sum_even;
		}
		if (oddity == 1) {
			return t[v].sum_odd;
		}
	}

	long long tm = (tl + tr) / 2;

	return getSum(t, v * 2, tl, tm, l, min(r, tm), oddity) + getSum(t, v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, oddity);
}

int main() {
	long long n;
	long long q;
	long long a_i;
	vector<long long> a;

	// --- Начало чтения из файла

	ifstream in("C:/Users/Alexis/test.txt");

	in >> n >> q;

	vector<test> t(4 * n);

	for (long long i = 0; i < n; i++) {
		in >> a_i;
		a.push_back(a_i);
	}

	build(t, a, 1, 0, n - 1);

	long long action, l, r;

	for (long long i = 0; i < q; i++) {
		in >> action >> l >> r;

		if (action == 1) {
			setValue(t, 1, 0, n - 1, l-1, r);
		}

		if (action == 2) {
			increment(t, 1, 0, n - 1, l-1, r-1);
		}

		if (action == 3) {
			cout << getSum(t, 1, 0, n - 1, l-1, r-1, 0) << "\n";
		}

		if (action == 4) {
			cout << getSum(t, 1, 0, n - 1, l-1, r-1, 1) << "\n";
		}
	}
	// --- Конец чтения из файла

	// --- Начало чтения из консоли
	/*cin >> n >> q;

	vector<test> t(4 * n);

	for (long long i = 0; i < n; i++) {
		cin >> a_i;
		a.push_back(a_i);
	}

	build(t, a, 1, 0, n - 1);

	long long action, l, r;

	for (long long i = 0; i < q; i++) {
		cin >> action >> l >> r;

		if (action == 1) {
			setValue(t, 1, 0, n - 1, l-1, r);
		}

		if (action == 2) {
			increment(t, 1, 0, n - 1, l-1, r-1);
		}

		if (action == 3) {
			cout << getSum(t, 1, 0, n - 1, l-1, r-1, 0) << "\n";
		}

		if (action == 4) {
			cout << getSum(t, 1, 0, n - 1, l-1, r-1, 1) << "\n";
		}
	}*/
	// --- Конец чтения из консоли
}