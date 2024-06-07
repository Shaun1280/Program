#include <iostream>
#include <iomanip> 
using namespace std;
//http://www.cplusplus.com/reference/library/manipulators/
int main() {
	int T; cin >> T;
	cout << setiosflags(ios::uppercase);
	cout<< setw(0xf) << internal;
	while(T--) {
		double A; cin >> A;
		double B; cin >> B;
		double C; cin >> C;

		// LINE 1 
        cout << hex << left << showbase << nouppercase; // formatting
        cout << (long long) A << endl; // actual printed part

        // LINE 2
        cout << dec << right << setw(15) << setfill('_') << showpos << fixed << setprecision(2); // formatting
        cout << B << endl; // actual printed part

        // LINE 3
        cout << scientific << uppercase << noshowpos << setprecision(9); // formatting
        cout << C << endl; // actual printed part
        /*
		        BEGIN: unlocked 
          // Sample solution:
            cout << left << hex << showbase << nouppercase;
            cout << (long long) A << endl;

            // One decimal place, right aligned, show sign, and fill left with underscores
            cout.precision(2);
            cout << showpos << fixed << setfill('_') << setw(15) << right;
            cout << B << endl;

            // Scientific notation with 9 decimal places
            cout.precision(9);
            cout << noshowpos << uppercase << scientific;
            cout << C << endl;
        */
	}
	return 0;

}
