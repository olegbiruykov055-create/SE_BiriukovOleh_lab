#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double a, b, c, x1, x2, D;
    cout << "enter a, b, c (ax^2 + bx + c = 0): ";
    cin >> a >> b >> c;

    if (a == 0 && b == 0 && c == 0) {
        cout << "infinite number of roots";
    }
    else if (a == 0 && b == 0) {
        cout << "this equation has no roots";
    }
    else if (a == 0) {
        x1 = -c / b;
        cout << "Equation has one root: x = " << x1;
    }
    else {
        D = b * b - 4 * a * c;
        if (D > 0) {
            x1 = (-b + sqrt(D)) / (2 * a);
            x2 = (-b - sqrt(D)) / (2 * a);
            cout << "two roots: x1 = " << x1 << ", x2 = " << x2;
        }
        else if (D == 0) {
            x1 = -b / (2 * a);
            cout << "one root: x = " << x1;
        }
        else {
            cout << "this equation has no roots";
        }
    }

    return 0;
}
