#include <iostream>
#include <string>

using namespace std;

string code;
string obr = "100000111";

string divide(string code, string obr) {
    code += "00000000";
    for (int i = 0; i < code.length() - obr.length() + 1; ++i) {
        if (code[i] == obr[0]) {
            for (int j = 0; j < obr.length(); ++j) {
                if (code[i + j] == obr[j]) {
                    code[i + j] = '0';
                } else {
                    code[i + j] = '1';
                }
            }
        }
    }
    return code.substr(code.length() - obr.length() + 1);
}

void encode() {
    cout << "Input your message\n";
    cin >> code;
    string rest = divide(code, obr);
    cout << "Your encoded messace by CRC-8-CCIT\n";
    cout << code + rest << '\n';
}

void decode() {
    cout << "Input your encoded message\n";
    cin >> code;
    string rest = divide(code, obr);
    if (rest == "00000000") {
        cout << "Message: " << code.substr(0, code.length() - 8) << '\n';
        cout << "Code is clear. reminder: " << rest << '\n';
    } else {
        cout << "Mistake was detected. reminder: " << rest << '\n';
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Wrong number of arguments\n";
        return 0;
    }
    if (string(argv[1]) == "-e") {
        encode();
    } else if (string(argv[1]) == "-d") {
        decode();
    }
}