#include <iostream>
using namespace std;
main(){
    float a, b; 
    cin >> a; 
    if (a < 5){
        b = a * 3;
    }
    
    if ( a > 7){
        b = a + 7; 
    }
    else{
        b = a / 10;
    }
    cout << b << endl; 
}