#include <iostream>
#include <vector>
//#include <cassert>
//#include <algorithm>
//#include <bitset>
//#include <vector>
//#include <queue>
//#include <cmath>

using namespace std;

const int maxq = 300000 + 1;
const int maxt = 1000000 + 1;
int reply;

struct leaf {
	int l;
	int r;
	long long sum;
	long long max;
};

leaf t[4 * maxt];
pair<int, int> schedule[maxq];

void build(int v, int tl, int tr) {
	t[v].l = tl;
	t[v].r = tr;

	if (tl == tr) {
		t[v].sum = 0;
		t[v].max = tl;
		return;
	}
	
	int tm = (tl + tr) / 2;
	build(v * 2, tl, tm);
	build(v * 2 + 1, tm + 1, tr);

	t[v].sum = t[2 * v].sum + t[2 * v + 1].sum;
	t[v].max = max(t[2 * v + 1].max, t[2 * v].max + t[2 * v + 1].sum);
}

void join(int v, int pos, int value) {
	if (t[v].l == t[v].r) {
		t[v].sum += value;
		t[v].max += value;
		return;
	}

	int tm = (t[v].l + t[v].r) / 2;

	if (pos <= tm) {
		join(v * 2, pos, value);
	} else {
		join(v * 2 + 1, pos, value);
	}

	t[v].sum = t[2 * v].sum + t[2 * v + 1].sum;
	t[v].max = max(t[2 * v + 1].max, t[2 * v].max + t[2 * v + 1].sum);
}

void query(int v, int time) {
	if (t[v].r <= time) {
		//ans = max(t[v].max, ans + t[v].sum);
		reply = max(t[v].max, reply + t[v].sum);
		return;
	}

	int tm = (t[v].l + t[v].r) / 2;
	
	query(v * 2, time);
	
	if (tm < time) {
		query(v * 2 + 1, time);
	}
}

//void query(int v, int boundary) {
//	if (t[v].r <= boundary) {
//		ans = max(t[v].max, ans + t[v].sum);
//		return;
//	}
//	int mid = (t[v].l + t[v].r) / 2;
//	query(v * 2, boundary);
//	if (mid < boundary)
//		query(v * 2 + 1, boundary);
//}

int main()
{
	//ios_base::sync_with_stdio(0);
	//cin.tie(0);
	int q;
	cin >> q;

	string action;

	build(1, 0, maxt - 1);

	for (int i = 0; i < q; i++) {
		//scanf("%d %d %d", action);
		
		cin >> action;
		reply = 0;
		
		if (action == "+") {
			int t, d;
			cin >> t >> d;
			t--;
			join(1, t, d);
			schedule[i] = make_pair(t, d);
			//cout << t << "\n" << d << "\n";
		}

		if (action == "-") {
			int i;
			cin >> i;
			join(1, schedule[i-1].first, -schedule[i-1].second);
		}

		if (action == "?") {
			int t;
			cin >> t;
			t--;
			query(1, t);
			cout << max(reply - t, 0) << "\n";
		}
	}

	//for (auto i : all_ans) {
	//	cout << i << "\n";
	//	// printf("%I64d\n", i);
	//}

	/*string str1;
	string str2;
	vector<int> input(n);

	getline(cin, str1);
	n = stoi(str1.substr(0, 1));
	q = stoi(str1.substr(2, str1.length - 2));
	getline(cin, str2);*/
}
