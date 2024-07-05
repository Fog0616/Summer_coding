#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> winning_numbers(7);
    for (int i = 0; i < 7; ++i) {
        cin >> winning_numbers[i];
    }

    vector<vector<int>> tickets(n, vector<int>(7));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 7; ++j) {
            cin >> tickets[i][j];
        }
    }

    vector<int> prize_count(7, 0);

    for (const auto& ticket : tickets) {
        int match_count = 0;
        for (int number : ticket) {
            if (find(winning_numbers.begin(), winning_numbers.end(), number) != winning_numbers.end()) {
                ++match_count;
            }
        }
        if (match_count > 0 && match_count <= 7) {
            ++prize_count[7 - match_count];
        }
    }

    for (int count : prize_count) {
        cout << count << ' ';
    }
    cout << endl;

    return 0;
}