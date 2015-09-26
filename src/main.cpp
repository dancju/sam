#include<iostream>
#include"sam.cpp"

using namespace std;

int main() {
    SAM sam;
    string s;
    cin >> s;
    for_each(s.begin(), s.end(), [&](char i) { sam.insert(i); });
    cout << sam.to_dot();
    return 0;
}

extern "C" {
    const char* sam(char* s) {
        SAM sam;
        for(char *i = s; *i; i++)
            sam.insert(*i);
        return sam.to_dot().c_str();
    }
}
