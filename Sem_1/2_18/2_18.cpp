#include <iostream> 
using namespace std; 
int main(){
    int N, tmp, S; 
    cin >> N; 
    while(N > 0)
    {
        tmp = N%10; 
        S =  (S*10) + tmp;
        N /= 10;
    }
    cout << S << endl;
}