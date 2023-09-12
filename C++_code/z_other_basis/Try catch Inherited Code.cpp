#include <iostream>
#include <string>
#include <sstream>
#include <exception>
using namespace std;

/* Define the exception here
For anyone else unfamiliar with exceptions, 
an exception consists of a "throw" and a "catch". 
A "throw" is followed by an object or variable. 
When the "throw" is called, the program will jump to the "catch" using said object/variable as an input to the catch. 
In this case, the throw constructs a new object of class "BadLengthException", which is then used as the input to the catch (this is labelled as "e").
 */
class BadLengthException{
	private:
	    int n;
    public:
    	BadLengthException(int errornumber){
    		n=errornumber;
		}
	    int what(){
	    	return n;
		}
	
};
bool checkUsername(string username) {
	bool isValid = true;
	int n = username.length();
	if(n < 5) {
		throw BadLengthException(n);
	}
	for(int i = 0; i < n-1; i++) {
		if(username[i] == 'w' && username[i+1] == 'w') {
			isValid = false;
		}
	}
	return isValid;
}

int main() {
	int T; cin >> T;
	while(T--) {
		string username;
		cin >> username;
		try {
			bool isValid = checkUsername(username); //throw error first
			if(isValid) {
				cout << "Valid" << '\n';
			} else {
				cout << "Invalid" << '\n';
			}
		} catch (BadLengthException e) {
			cout << "Too short: " << e.what() << '\n';
		}
	}
	return 0;
}
