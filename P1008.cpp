#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Function to convert a number to the required format
string powerRepresentation(int n);

int main() {
    int n;
    cin >> n;
    cout << powerRepresentation(n) << endl;
    return 0;
}

// Helper function to convert a number to the required power representation format
string powerRepresentation(int n) {
    if (n == 0) return "0";
    if (n == 1) return "2(0)";
    if (n == 2) return "2";
    
    string result;
    vector<int> powers;
    
    // Decompose the number into sum of powers of 2
    for (int i = 0; n > 0; ++i) {
        if (n & 1) {
            powers.push_back(i);
        }
        n >>= 1;
    }
    
    // Construct the result string
    reverse(powers.begin(), powers.end());
    for (size_t i = 0; i < powers.size(); ++i) {
        if (i > 0) {
            result += "+";
        }
        int power = powers[i];
        if (power == 0) {
            result += "2(0)";
        } else if (power == 1) {
            result += "2";
        } else {
            result += "2(" + powerRepresentation(power) + ")";
        }
    }
    
    return result;
}