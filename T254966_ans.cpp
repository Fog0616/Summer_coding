#include <iostream>
#include <cstring>
using namespace std;
int main() {
    int n, id;
    string winner = "0", tmp;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> tmp;
        if (tmp.size() >  winner.size()
                || (tmp.size() == winner.size()
                    && tmp >  winner)) {
            winner = tmp;
            id = i;
        }
    }
    cout << id << endl << winner << endl;
    return 0;
}
