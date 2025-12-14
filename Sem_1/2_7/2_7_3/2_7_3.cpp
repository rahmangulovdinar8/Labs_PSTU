#include <iostream> 
using namespace std;
int main(){
    int N; 
    cin >> N; 
    for(int j = 0; j < N; j++){
        cout << "* ";
    }
    cout << endl; 
    for (int i = 0; i < N-2; i++){
        cout << "* ";
        for (int j = 0; j < N-2; j++){
            cout << "  ";
        }
        cout << "* " << endl;
    }
    for(int k = 0; k < N; k++){
        cout << "* ";
    }
    cout << endl;
}