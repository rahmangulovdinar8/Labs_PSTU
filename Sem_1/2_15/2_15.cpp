#include <iostream> 
using namespace std; 
int main(){
    int N, S, pr; 
    bool flag = false;
    cin >> N >> S; 
    while (N > 0){
        pr = N%10;  
        if(pr == S){
            flag = true;
            break;
        }
        N = N/10; 
    }
    if (flag == false){
        cout << "Нет, число S не входит в N" << endl; 
    }
    else{
        cout << "Да, число S входит в N" << endl;
    }
    return 0;
} 