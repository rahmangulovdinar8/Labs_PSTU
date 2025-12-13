#include <iostream>
using namespace std;
int main(){
    int N, tmp;
    bool plusFirst = false; //flag 1 
    bool minusFirst = false; //flag 2

    cout << "Введите количество элементов: ";
    cin >> N; 
    
    for(int i = 1; i <= N; i++){
        cin >> tmp; 
        if (!plusFirst && !minusFirst){
            if(tmp > 0) {plusFirst = true;}
            else if (tmp < 0) {minusFirst = true;}
        }
    }
    if (plusFirst) {cout << "Первое число было положительным" << endl;}
    else if (minusFirst) {cout << "Первое число было отрицательным" << endl;}
    else { cout << "Последовательность состоит из нулей" << endl;}
    cout << endl; 
    return 0;
}