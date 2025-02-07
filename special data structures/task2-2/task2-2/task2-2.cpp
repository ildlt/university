#include <cassert>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

const int MAXQ = 3e5 + 1;
const int MAXT = 1e6 + 1;

long long ans;

struct vertex {
	long long sum, max;
	int l, r;
};

vertex t[4 * MAXT];
pair<int, int> et[MAXQ];

void build(int v, int tl, int tr) {
	t[v].l = tl;
	t[v].r = tr;

	if (tl == tr) {
		t[v].sum = 0;
		t[v].max = tl;
		return;
	}
	int mid = (tl + tr) / 2;
	build(v * 2, tl, mid);
	build(v * 2 + 1, mid + 1, tr);

	t[v].sum = t[2 * v].sum + t[2 * v + 1].sum;
	t[v].max = max(t[2 * v + 1].max, t[2 * v].max + t[2 * v + 1].sum);
}

void update(int v, int pos, int val) {
	if (t[v].l == t[v].r) {
		t[v].sum += val;
		t[v].max += val;
		return;
	}
	int mid = (t[v].l + t[v].r) / 2;
	if (pos <= mid)
		update(v * 2, pos, val);
	else
		update(v * 2 + 1, pos, val);

	t[v].sum = t[2 * v].sum + t[2 * v + 1].sum;
	t[v].max = max(t[2 * v + 1].max, t[2 * v].max + t[2 * v + 1].sum);
}

void query(int v, int boundary) {
	if (t[v].r <= boundary) {
		ans = max(t[v].max, ans + t[v].sum);
		return;
	}
	int mid = (t[v].l + t[v].r) / 2;
	query(v * 2, boundary);
	if (mid < boundary)
		query(v * 2 + 1, boundary);
}

int main()
{
	int q;

	cin >> q;

	char a;
	int t, d;

	vector<long long> all_ans;

	build(1, 0, MAXT - 1);

	for (int i = 0; i < q; i++) {
		cin >> a;
		ans = 0;
		switch (a) {
		case '+': {
			cin >> t >> d;
			t--;
			update(1, t, d);
			et[i + 1] = make_pair(t, d);
			break;
		}
		case '-': {
			cin >> t;
			update(1, et[t].first, -et[t].second);
			break;
		}
		case '?': {
			cin >> t;
			t--;
			query(1, t);
			all_ans.push_back(max(ans - t, 0ll));
			break;
		}
		}
	}
	for (auto i : all_ans)
		printf("%I64d\n", i);


	return 0;
}