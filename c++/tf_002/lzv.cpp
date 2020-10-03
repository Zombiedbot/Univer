#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <vector>

using namespace std;

string full_file;
string buf;
int MAX_SIZE = 32768;
int atom_size, power[100200], key;
unordered_map<string, long long> dict;
unordered_map<long long, string> dict_reverse;
set<char> unique;
vector<int> res;

void encode(ifstream &fin, ofstream &fout) {
    getline(fin, full_file);
    if (full_file.empty()) return;
    while(!fin.eof()) {
        getline(fin, buf);
        full_file += '\n';
        full_file += buf;
    }
    int cur = 0;
    string atoms = "";
    for (int i = 0; i < full_file.length(); ++i) {
        char c = full_file[i];
        int prev_size = unique.size();
        unique.insert(c);
        if(unique.size() != prev_size) {
            dict[string(1, c)] = cur;
            cur += 1;
            atoms.push_back(c);
        }
    }
    string pref = "";
    for (int i = 0; i < full_file.length(); ++i) {
        string buf = pref;
        buf.push_back(full_file[i]);
        if (dict.count(buf)) {
            pref.push_back(full_file[i]);
        } else {
            res.push_back(dict[pref]);
            if(dict.size() < MAX_SIZE) dict[buf] = dict.size();
            pref = string(1, full_file[i]);
        }
    }

    if (!pref.empty()) {
        res.push_back(dict[pref]);
    }
    fout << unique.size() << '\n';

    fout << atoms << '\n';
}

void compress(ofstream &fout) {
    int bits = 0, dict_size = dict.size();
    while (dict_size)
    {
        bits++;
        dict_size >>= 1;
    }
    fout << bits << '\n';
    fout << res.size() << '\n';
    long long buf = 0;
    int buf_size = 0;
    for (int i = 0; i < res.size(); ++i) {
        buf = (buf << bits) + res[i];
        buf_size += bits;
        while(buf_size >= 8) {
            unsigned char c = buf >> (buf_size - 8);
            fout << c;
            buf = buf % (1 << (buf_size - 8));
            buf_size -= 8;
        }
    }
    while (buf_size > 0 && buf_size < 8) {buf <<= 1; buf_size++;}
    fout << (unsigned char) buf;
}

void decompress(ifstream &fin) {
    int unique_len;
    fin >> unique_len;
    char c;
    fin.get(c);
    for(int i = 0; i < unique_len; ++i) {
        fin.get(c);
        dict_reverse[i] = string(1, c);
    }
    fin.get(c);
    long long res_size, buf = 0, buf_size = 0;
    string s;
    getline(fin, s);
    key = stoi(s);
    int n;
    getline(fin, s);
    n = stoi(s);
    while(n) {
        fin.get(c);
        buf <<= 8;
        buf |= (unsigned char) c;
        buf_size += 8;
        while(buf_size >= key) {
            int suf = buf_size - key;
            res.push_back(buf >> suf);
            buf = buf % (1 << suf);
            buf_size = suf;
            n--;
            if (!n) break;
        }
    }
}

void decode(ofstream &fout) {
    string pref = dict_reverse[res[0]];
    fout << pref;
    for (int i = 1; i < res.size(); ++i) {
        string suf;
        pref = dict_reverse[res[i - 1]];
        if (dict_reverse.count(res[i]) == 0) {
            suf = pref + pref[0];
        } else {
            suf = dict_reverse[res[i]];
        }
        fout << suf;
        dict_reverse[dict_reverse.size()] = pref + suf[0];
        pref = suf;
    }
}

int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(false);
    if (argc != 4) {
        cout << "Wrong number of arguments\n";
        return 0;
    }
    string file_name, mode;
    key = stoi(argv[2]);
    MAX_SIZE = 1 << key;
    file_name = string(argv[3]);
    mode = string(argv[1]);
    if (mode == "-e") {
        ifstream fin(file_name);
        ofstream fout("encoded.txt", ios::binary);
        fin.tie(NULL);
        fout.tie(NULL);
        encode(fin, fout);
        compress(fout);
    } else if (mode == "-d") {
        ifstream fin(file_name, ios::binary);
        ofstream fout("decoded.txt");
        fin.tie(NULL);
        fout.tie(NULL);
        decompress(fin);
        decode(fout);
    } else {
        cout << "Wrong key\n";
    }
}