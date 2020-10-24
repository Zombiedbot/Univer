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
    bool all_sum = false;
    for (int i = 0; i < n; ++i) {
        all_sum = bool_sum(all_sum, v[i]);
    }
    while(n > st) {
        bool sum = false;
        for (int i = 0; i < n; ++i) {
            if(st & i) sum = bool_sum(sum, v[i]);
        }
        v.push_back(sum);
        st *= 2;
    }
    v.push_back(all_sum);
    cout << "size of encoded\n";
    cout << v.size() << '\n';
    cout << "encoded message\n";
    for (int i = 0; i < v.size(); ++i)
        if (v[i]) cout << 1 << ' '; else cout << 0 << ' ';
    cout << '\n';
    srand (time(NULL));
    int rnd = rand() % v.size();
    cout << "Random mistake in " << rnd << " bit\n";
    v[rnd] = !v[rnd];
    for (int i = 0; i < v.size(); ++i)
        if (v[i]) cout << 1 << ' '; else cout << 0 << ' ';
    cout << "\n";
}

void decode() {
    int sz = 1;
    int suf = 2;
    while(sz * 2 + suf + 1 < n) {
        suf += 1;
        sz *= 2;
    }
    sz = n - suf;
    int ind = sz;
    //cout << sz << ' ';
    bool all_sum = v[v.size() - 1];
    int step = 1;
    bool cur_sum = false;
    for (int i = 0; i < sz; ++i) cur_sum = bool_sum(cur_sum, v[i]);
    if (cur_sum == all_sum) {
        cout << "No mistake detected\n";
        return;
    } 
    int res = 0;
    while(step < sz) {
        bool sum = false;
        for (int i = 0 ; i < sz; ++i) {
            if(i & step) sum = bool_sum(sum, v[i]);
        }
        if (sum != v[ind]) {
            res = res | step;
        }
        step *= 2;
        ind++;
    }
    cout << "Mistake was in bit " << res << '\n';
    v[res] = !v[res];
    cout << "Resulting message\n";
    for (int i = 0; i < sz; ++i) {
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