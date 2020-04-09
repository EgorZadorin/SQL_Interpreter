#include <iostream>
#include <cstdio>

using namespace std;

enum state_t {H, A, B, C, D, E, OK, ERR};

int main(){
	state_t state = H;
	int c;
	while ((state != OK) && (state!= ERR)){
		
		c = getchar();

		switch(state){
			case H:
				if (c == '1'){
					state = A;
					cout << "goes to A" << endl;
				}
				else{
					state = ERR;
					cout << "goes to ERR!!!" << endl;
				}
				break;
			case A:
				if (c == '1'){
					state = B;
					cout << "goes to B" << endl;
				}
				else 
					if (c == '0'){
						state = C;
						cout << "goes to C" << endl;
					}
					else{ 
						state = ERR;
						cout << "goes to ERR!!!" << endl;
					}
				break;
			case B:
				if (c == '1'){
					state = B;
					cout << "goes to B" << endl;
				}
				else 
					if (c == '0'){
						state = E;
						cout << "goes to E" << endl;
					}
					else{ 
						state = ERR;
						cout << "goes to ERR!!!" << endl;
					}
				break;
			case C:
				if (c == '1'){
					state = B;
					cout << "goes to B" << endl;
				}
				else
				       	if (c == '0'){
						state = D;
						cout << "goes to D" << endl;
					}
					else{
						state = ERR;
						cout << "goes to ERR!!!" << endl;	
					}
				break;
			case D:
				if (c == '0'){
					state = B;
					cout << "goes to C" << endl;
				}
				else
				       	if (c == '\n'){
						state = OK;
						cout << "goes to OK!" << endl;
					}
					else{ 
						state = ERR;
						cout << "goes to ERR!!!" << endl;
					}
				break;
			case E:
				if (c == '1'){
					state = B;
					cout << "goes to B" << endl;
				}
				else 	
					if (c == '0'){
						state = D;
						cout << "goes to D" << endl;
					}
					else
				       		if (c == '\n'){
							state = OK;
							cout << "goes to OK!" << endl;
						}
						else{ 
							state = ERR;
							cout << "goes to ERR!!!" << endl;
						}
				break;
		}
	}

	if (state == OK)
		cout << "YES" << endl;
	else 
		cout << "NO" << endl;

	return 0;
}

