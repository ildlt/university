#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    const int maxn = 10000000;
    int n;
    long long result = 0;
    vector<int> a(2*maxn);

    cin >> n;

    for (int i = 0; i < sqrt(maxn); i++) {
        for (int j = 0; j < sqrt(maxn); j++) {
            a[pow(i, 2) + pow(j, 2)] += 1;
        }
    }

    for (int i = 0; i <= n; i++) {
        result += (long long) a[i] * a[n - i];
    }

    cout << result << "\n";
}