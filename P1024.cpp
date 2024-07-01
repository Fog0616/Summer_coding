#include <bits/stdc++.h>

using namespace std;

const double epsilon = 1e-7;  // Precision for root finding
const double delta = 1.0;     // Minimum difference between roots

// Function to evaluate the polynomial
double f(double a, double b, double c, double d, double x) {
    return ((a * x + b) * x + c) * x + d;
}

// Bisection method to find a root in [low, high]
double bisection(double a, double b, double c, double d, double low, double high) {
    double mid;
    while (high - low > epsilon) {
        mid = (low + high) / 2.0;
        if (f(a, b, c, d, low) * f(a, b, c, d, mid) <= 0)
            high = mid;
        else
            low = mid;
    }
    return (low + high) / 2.0;
}

int main() {
    double a, b, c, d;
    cin >> a >> b >> c >> d;

    double roots[3];
    int root_count = 0;

    for (double x = -100.0; x <= 100.0; x += delta) {
        if (root_count == 3) break;

        double fx1 = f(a, b, c, d, x);
        double fx2 = f(a, b, c, d, x + delta);

        if (fx1 * fx2 <= 0) {
            roots[root_count++] = bisection(a, b, c, d, x, x + delta);
        }
    }

    // Sort roots in ascending order
    sort(roots, roots + 3);

    // Print roots with precision of 2 decimal places
    cout << fixed << setprecision(2) << roots[0] << " " << roots[1] << " " << roots[2] << endl;

    return 0;
}