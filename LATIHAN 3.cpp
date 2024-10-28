#include <iostream>
#include <stack>
#include <sstream>
#include <cmath>

using namespace std;

class Stack {
public:
    void push(float value) {
        stk.push(value);
    }

    float pop() {
        if (!stk.empty()) {
            float top = stk.top();
            stk.pop();
            return top;
        }
        return 0;
    }

    bool isEmpty() {
        return stk.empty();
    }

private:
    stack<float> stk;
};

// Fungsi untuk mengevaluasi ekspresi postfix
float evaluasiPostfix(const string& ekspresi);

// Fungsi untuk menampilkan langkah-langkah evaluasi
void tampilkanLangkah(const string& ekspresi);

int main() {
    string ekspresi;
    cout << "Masukkan ekspresi postfix: ";
    getline(cin, ekspresi);

    cout << "\nLangkah-langkah evaluasi:\n";
    tampilkanLangkah(ekspresi);

    float hasil = evaluasiPostfix(ekspresi);
    cout << "Hasil evaluasi ekspresi postfix: " << hasil << endl;

    return 0;
}

float evaluasiPostfix(const string& ekspresi) {
    Stack stack;
    istringstream iss(ekspresi);
    string token;

    while (iss >> token) {
        if (isdigit(token[0])) {
            stack.push(stof(token));
        } else {
            float b = stack.pop();
            float a = stack.pop();
            float hasil;

            if (token == "+") hasil = a + b;
            else if (token == "-") hasil = a - b;
            else if (token == "*") hasil = a * b;
            else if (token == "/") hasil = a / b;
            else if (token == "^") hasil = pow(a, b);
            else {
                cout << "Operator tidak dikenal: " << token << endl;
                return 0;
            }

            stack.push(hasil);
        }
    }

    return stack.pop();
}

void tampilkanLangkah(const string& ekspresi) {
    Stack stack;
    istringstream iss(ekspresi);
    string token;

    while (iss >> token) {
        if (isdigit(token[0])) {
            float nilai = stof(token);
            stack.push(nilai);
            cout << "Push: " << nilai << endl;
        } else {
            float b = stack.pop();
            float a = stack.pop();
            float hasil;

            if (token == "+") hasil = a + b;
            else if (token == "-") hasil = a - b;
            else if (token == "*") hasil = a * b;
            else if (token == "/") hasil = a / b;
            else if (token == "^") hasil = pow(a, b);

            cout << "Operasi: " << a << " " << token << " " << b << " = " << hasil << endl;
            stack.push(hasil);
        }
    }
}
