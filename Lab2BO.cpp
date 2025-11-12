#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <fstream>
#include <string>
using namespace std;

struct InputData {
    double n;
    double step;
    double min;
    double max;
};

double getValidatedInput(const string& prompt) {
    double value;
    cout << prompt;
    cin >> value;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw "Input error: please enter a number!";
    }
    return value;
}

InputData getUserInput() {
    InputData input;

    while (true) {
        try {
            input.n = getValidatedInput("Enter n (> 2): ");
            if (floor(input.n) != input.n)
                throw "n must be an integer!";
            if (input.n <= 2)
                throw "n must be greater than 2!";

            input.step = getValidatedInput("Enter step for x (> 0): ");
            if (input.step <= 0)
                throw "Step must be greater than 0!";

            input.min = getValidatedInput("Enter min x: ");
            input.max = getValidatedInput("Enter max x (>= min): ");
            if (input.max < input.min)
                throw "max must be greater than or equal to min!";

            return input;
        }
        catch (const char* msg) {
            cerr << "[Input Error] " << msg << endl;
            cout << "Please try again.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

string computeFunction(double n, double step, double min, double max) {
    string results;

    while (true) {
        try {
            cout << "\n=== Calculation Results ===\n";
            for (double x = min; x <= max + 1e-9; x += step) {
                double y;
                if (x >= 0) {
                    double mlt1 = 1;
                    for (int i = 0; i < n; i++) {
                        double mlt = 1;
                        for (int j = 1; j < n - 1; j++) {
                            if (i + j == 0)
                                throw "Division by zero detected!";
                            mlt *= (i + (x * x) / (i + j) - 3 * j);
                        }
                        mlt1 *= mlt;
                    }
                    y = mlt1;
                }
                else {
                    double sum = 0;
                    for (int i = 1; i < n; i++)
                        sum += (x + i) * (x + i);
                    y = sum + 5 * x;
                }

                cout << fixed << setprecision(2);
                cout << "x = " << x << " | y = " << y << endl;
                results += "x=" + to_string(x) + ", y=" + to_string(y) + "\n";
            }
            cout << "=============================\n";
            return results;
        }
        catch (const char* msg) {
            cerr << "[Calculation Error] " << msg << endl;
            cout << "Re-enter parameters to continue.\n";
            InputData input = getUserInput();
            n = input.n;
            step = input.step;
            min = input.min;
            max = input.max;
        }
    }
}

void writeHistory(const string& data) {
    ofstream file("history.txt", ios::app);
    if (!file)
        throw "Cannot open file for writing!";
    file << data << "\n";
    file.close();
}

void showHistory() {
    ifstream file("history.txt");
    if (!file)
        throw "No previous calculations found (file missing).";

    string line;
    cout << "\n=== Previous Calculations ===\n";
    while (getline(file, line))
        cout << line << endl;
    cout << "=============================\n";
    file.close();
}

void clearHistory() {
    ofstream file("history.txt", ios::trunc);
    if (!file)
        throw "Failed to clear history file!";
    file.close();
    cout << "History cleared successfully!\n";
}

void historyMenu() {
    while (true) {
        try {
            int choice;
            cout << "\n=== History Menu ===\n";
            cout << "[1] View history\n";
            cout << "[2] Clear history\n";
            cout << "[3] Back to main menu\n";
            cout << "=====================\n";
            cout << "Enter choice: ";
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw "Invalid input! Please enter a number.";
            }

            switch (choice) {
            case 1:
                showHistory();
                break;
            case 2:
                clearHistory();
                break;
            case 3:
                return;
            default:
                throw "Invalid choice! ";
            }
        }
        catch (const char* msg) {
            cerr << "[History Error] " << msg << endl;
            cout << "Please try again.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void aboutAuthor() {
    cout << "\n=== About Author ===\n";
    cout << "Made by Biriukov Oleh\n";
}

void support() {
    cout << "\n==== Support ====\n";
    cout << "will be here soon\n";
    cout << "===================\n";
}

int main() {
    cout << "Hello! I am a program for calculating function.\n";
    cout << "Press ENTER to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();

    while (true) {
        try {
            int choice;
            cout << "\n==============================\n";
            cout << "      FUNCTION CALC TOOL      \n";
            cout << "==============================\n";
            cout << "[1] Start calculation\n";
            cout << "[2] History menu\n";
            cout << "[3] About author\n";
            cout << "[4] Support\n";
            cout << "[5] Exit\n";
            cout << "==============================\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw "Invalid menu input (not a number).";
            }

            switch (choice) {
            case 1: {
                InputData ui = getUserInput();
                string results = computeFunction(ui.n, ui.step, ui.min, ui.max);
                writeHistory("n=" + to_string(ui.n) + ", step=" + to_string(ui.step) +
                    ", min=" + to_string(ui.min) + ", max=" + to_string(ui.max) + "\n" + results);
                break;
            }
            case 2:
                historyMenu();
                break;
            case 3:
                aboutAuthor();
                break;
            case 4:
                support();
                break;
            case 5:
                cout << "Goodbye!\n";
                return 0;
            default:
                throw "Invalid main menu choice ";
            }
        }
        catch (const char* msg) {
            cerr << "[Error] " << msg << endl;
            cout << "Returning to main menu...\n";
        }
        catch (...) {
            cerr << "Unknown error";
        }
    }
}
