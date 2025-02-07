#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

long long reply;

struct leaf {
	long long sum;
	long long max;
};

void build(vector<leaf>& t, int v, int tl, int tr) {
	if (tl == tr) {
		t[v].sum = 0;
		t[v].max = tl;
		return;
	}
	//else {
		int tm = (tl + tr) / 2;

		build(t, v * 2, tl, tm);
		build(t, v * 2 + 1, tm + 1, tr);

		t[v].sum = t[2 * v].sum + t[2 * v + 1].sum;
		t[v].max = max(t[2 * v].max + t[2 * v + 1].sum, t[2 * v + 1].max);
	//}	
}

void join(vector<leaf>& t, int v, int tl, int tr, int time, int duration) {
	/*if (tl > tr) {
		return;
	}*/

	if (tl == tr) {
		t[v].sum += duration;
		t[v].max += duration;
		return;
	}
	//else {

		int tm = (tl + tr) / 2;

		if (time <= tm) {
			join(t, v * 2, tl, tm, time, duration);
		}
		else {
			join(t, v * 2 + 1, tm + 1, tr, time, duration);
		}

		t[v].sum = t[v * 2].sum + t[v * 2 + 1].sum;
		t[v].max = max(t[v * 2].max + t[v * 2 + 1].sum, t[v * 2 + 1].max);
	//}
}

void query(vector<leaf>& t, int v, int tl, int tr, int time) {
	/*if (tl > tr) {
		return;
	}*/

	if (time >= tr) {
		reply = max(t[v].max, reply + t[v].sum);
		return;
	}
	else {
		int tm = (tl + tr) / 2;

		query(t, v * 2, tl, tm, time);

		if (time > tm) {
			query(t, v * 2 + 1, tm + 1, tr, time);
		}
	}
}

int main()
{
	long long q;
	long long time;
	long long duration;
	const long long t_max = 1000000 + 1;
	//const int t_max = 10;
	const long long q_max = 300000 + 1;
	string action;

	vector<leaf> t(4*t_max);
	vector<pair<long long, long long>> schedule(q_max);

	ifstream in("C:/Users/Alexis/test.txt");

	in >> q;

	build(t, 1, 0, t_max - 1);

	for (long long i = 0; i < q; i++) {
		in >> action;
		reply = 0;

		if (action == "+") {
			in >> time >> duration;
			time--;
			join(t, 1, 0, t_max - 1, time, duration);
			schedule[i + 1] = (make_pair(time, duration));
			//join(t, 1, 0, t_max - 1, time - 1, duration);
			//schedule.push_back(make_pair(time, duration));
		}

		if (action == "-") {
			in >> time;
			join(t, 1, 0, t_max - 1, schedule[time].first, -schedule[time].second);
			//join(t, 1, 0, t_max - 1, schedule[time - 1].first, -schedule[time - 1].second);
		}

		if (action == "?") {
			in >> time;
			time--;
			query(t, 1, 0, t_max - 1, time);
			long long nil = 0;
			cout << max(reply - time, nil) << "\n";
			//query(t, 1, 0, t_max - 1, time - 1);
			//cout << max(reply - time + 1, 0) << "\n";
		}
	}

	/*cin >> q;

	build(t, 1, 0, t_max-1);

	for (int i = 0; i < q; i++) {
		cin >> action;
		reply = 0;

		if (action == "+") {
			cin >> time >> duration;
			time--;
			join(t, 1, 0, t_max - 1, time, duration);
			schedule[i + 1] = (make_pair(time, duration));
			//join(t, 1, 0, t_max - 1, time - 1, duration);
			//schedule.push_back(make_pair(time, duration));
		}

		if (action == "-") {
			cin >> time;
			join(t, 1, 0, t_max - 1, schedule[time].first, -schedule[time].second);
			//join(t, 1, 0, t_max - 1, schedule[time - 1].first, -schedule[time - 1].second);
		}

		if (action == "?") {
			cin >> time;
			time--;
			query(t, 1, 0, t_max - 1, time);
			cout << max(reply - time, 0) << "\n";
			//query(t, 1, 0, t_max - 1, time - 1);
			//cout << max(reply - time + 1, 0) << "\n";
		}
	}*/

	/*long long n;
	int q;
	long long a_i;
	vector<long long> a;

	cin >> n >> q;

	for (long long i = 0; i < n; i++) {
		cin >> a_i;
		a.push_back(a_i);
	}

	build(a, 1, 0, n - 1);

	int action, l, r;

	for (int i = 0; i < q; i++) {
		cin >> action >> l >> r;

		if (action == 1) {
			setValue(1, 0, 0, l, r);
		}

		if (action == 2) {

		}

		if (action == 3) {

		}

		if (action == 4) {

		}
	}*/

}