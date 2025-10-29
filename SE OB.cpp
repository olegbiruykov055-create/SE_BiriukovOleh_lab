#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <fstream> 
#include <string> 
using namespace std;

struct InputData
{
    double n;
    double step;
    double min;
    double max;
};

InputData getUserInput()
{
    InputData input;
    bool nIsOk = false, minIsOk = false, maxIsOk = false, stepIsOk = false;

    while (!nIsOk)
    {
        cout << "Enter n (> 2): ";
        cin >> input.n;
        if (cin.fail()) {
            cout << "Please enter a number!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else if (floor(input.n) != input.n) {
            cout << "Please enter an integer!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else if (input.n <= 2) {
            cout << "n must be greater than 2!\n";
            continue;
        }
        nIsOk = true;
    }

    while (!stepIsOk)
    {
        cout << "Enter step for x (> 0): ";
        cin >> input.step;
        if (cin.fail()) {
            cout << "Please enter a number!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else if (input.step <= 0) {
            cout << "Step must be > 0!\n";
        }
        else stepIsOk = true;
    }

    while (!minIsOk)
    {
        cout << "Enter min x: ";
        cin >> input.min;
        if (cin.fail()) {
            cout << "Please enter a number!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        minIsOk = true;
    }

    while (!maxIsOk)
    {
        cout << "Enter max x: ";
        cin >> input.max;
        if (cin.fail()) {
            cout << "Please enter a number!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else if (input.min > input.max) {
            cout << "max must be >= min!\n";
            continue;
        }
        maxIsOk = true;
    }

    return input;
}

string computeFunction(double n, double step, double min, double max)
{
    string results;
    cout << "\n=== Calculation Results ===\n";
    for (double x = min; x <= max + 1e-9; x += step)
    {
        double y;
        if (x >= 0)
        {
            double mlt1 = 1;
            for (int i = 0; i < n; i++)
            {
                double mlt = 1;
                for (int j = 1; j < n - 1; j++)
                    mlt *= (i + (x * x) / (i + j) - 3 * j);
                mlt1 *= mlt;
            }
            y = mlt1;
        }
        else
        {
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

void writeHistory(const string& data)
{
    ofstream file("history.txt", ios::app);
    file << data << "\n";
    file.close();
}

void showHistory()
{
    ifstream file("history.txt");
    if (!file)
    {
        cout << "No previous calculations found.\n";
        return;
    }

    string line;
    cout << "\n=== Previous Calculations ===\n";
    while (getline(file, line))
        cout << line << endl;
    cout << "=============================\n";
    file.close();
}

void clearHistory()
{
    ofstream file("history.txt", ios::trunc);
    file.close();
    cout << "History cleared successfully!\n";
}

void historyMenu()
{
    int choice;
    while (true)
    {
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
            cout << "[ERROR] Invalid input!\n";
            continue;
        }

        switch (choice)
        {
        case 1:
            showHistory();
            break;
        case 2:
            clearHistory();
            break;
        case 3:
            return;
        default:
            cout << "[ERROR] Invalid choice!\n";
        }
    }
}

void aboutAuthor()
{
    cout << "\n=== About Author ===\n";
    cout << "Made by Biriukov Oleh\n";
}

void support()
{
    cout << "\n==== Support ====\n";
    cout << "\nwill be here soon\n";
    cout << "===================\n";
}

int main()
{
    cout << "Hello! I am a program for calculating function.\n";
    cout << "Press ENTER to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();

    int choice;
    while (true)
    {
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
            cout << "[ERROR] Please enter a valid number!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
        {
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
            cout << "[ERROR] Invalid menu choice!\n";
        }
    }
}
