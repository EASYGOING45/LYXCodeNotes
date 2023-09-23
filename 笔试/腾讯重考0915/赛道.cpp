#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, t;
    cin >> n >> t;

    vector<int> positions(n);
    vector<int> speeds(n);

    for (int i = 0; i < n; i++) {
        cin >> positions[i];
    }

    for (int i = 0; i < n; i++) {
        cin >> speeds[i];
    }

    vector<int> new_positions(n);
    for (int i = 0; i < n; i++) {
        new_positions[i] = positions[i] + speeds[i] * t;
    }

    vector<int> ranks(n);
    for (int i = 0; i < n; i++) {
        ranks[i] = i;
    }

    sort(ranks.begin(), ranks.end(), [&](int a, int b) {
        return new_positions[a] < new_positions[b];
    });

    int count = 0;
    for (int i = 0; i < n; i++) {
        if (ranks[i] < i) {
            count++;
        }
    }

    cout << count << endl;

    return 0;
}
