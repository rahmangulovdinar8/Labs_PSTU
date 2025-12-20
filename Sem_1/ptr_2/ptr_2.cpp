#include <iostream> 
using namespace std; 
int main(){
    int N, S;
    cout << "first num: "; 
    cin >> N;
    cout << "Second num: "; 
    cin >> S;
    int *ptr1 = &N; 
    int *ptr2 = &S; 
    int tmp = *ptr1; 
    *ptr1 = *ptr2; 
    *ptr2 = tmp;
    cout << N << S << endl;

    return 0;
}