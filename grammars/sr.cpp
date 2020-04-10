#include <iostream>
using namespace std;

int main(){
    char c;
    cin >> c;
    switch(c){
        case 'S':
            cout << "ab"  << endl;
            cout << "cdf_" << endl;
            break;
        case 'A':
            cout << "bc" << endl;
            cout << "cf" << endl;
            break;
        case 'B':
            cout << "cd" << endl;
            cout << "cdf_" << endl;
            break;
    }

    if (c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'f'){
        cout << c << endl;
        cout << c << endl;
    }

    cout << "YES" << endl;
    return 0;
}
