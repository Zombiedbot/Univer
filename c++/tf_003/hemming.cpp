#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<bool> v;
int n;

bool bool_sum(bool a, bool b) {
    if (a && b) return false;
    return a || b; 
}

void encode() {
    long long st = 1;
    while (st <= v.size()) {
        v.insert(v.begin() + st - 1, 0);
        st *= 2;
    }
    st = 1;
    while (st <= v.size()) {
        bool res = false;
        for (int i = 0; i < v.size(); ++i) {
            if ((i + 1) & st) res ^= v[i];
        }
        if (res) v[st - 1] = 1;
        st *= 2;
    }
    cout << "size of encoded\n";
    cout << v.size() << '\n';
    cout << "encoded message\n";
    for (int i = 0; i < v.size(); ++i)
        if (v[i]) cout << 1 << ' '; else cout << 0 << ' ';
    cout << '\n';
    srand (time(NULL));
    int rnd = rand() % v.size();
    cout << "Random mistake in " << rnd + 1 << " bit\n";
    v[rnd] = !v[rnd];
    for (int i = 0; i < v.size(); ++i)
        if (v[i]) cout << 1 << ' '; else cout << 0 << ' ';
    cout << "\n";
}

void decode() {
    long long sz = 1;
    long long res = 0;
    while (sz <= v.size()) {
        bool val = false;
        for (int i = sz; i < v.size(); ++i) {
            if ((i + 1) & sz) val ^= v[i];
        }
        if (val != v[sz - 1]) {
            res |= sz;
        }
        sz *= 2;
    }
    sz /= 2;
    if (!res) {
        cout << "Mistake was not found\n";
        return;
    }
    cout << "Mistake was in bit " << res << '\n';
    v[res - 1] = !v[res - 1];
    /*
    while(sz > 0) {
        v.erase(v.begin() + sz - 1);
        sz /= 2;
    }
    */
    cout << "Resulting message\n";
    for (int i = 0; i < v.size(); ++i) {
        if (v[i]) cout << 1 << ' '; else cout << 0 << ' ';
    }
    cout << '\n';
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Wrong number of arguments\n";
        return 0;
    }
    if (string(argv[1]) == "-e") {
        cout << "input number of bits\n";
        cin >> n;
        cout << "input message\n";
        int buf;
        for (int i = 0 ; i < n; ++i) {
            cin >> buf;
            if (buf) v.push_back(true); else v.push_back(false);
        }
        encode();
    } else if (string(argv[1]) == "-d") {
        cout << "input number of bits\n";
        cin >> n;
        cout << "input message\n";
        int buf;
        for (int i = 0 ; i < n; ++i) {
            cin >> buf;
            if (buf) v.push_back(true); else v.push_back(false);
        }
        decode();
    }
}