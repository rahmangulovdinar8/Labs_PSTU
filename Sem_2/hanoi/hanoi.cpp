#include <iostream>
using namespace std;
#include <locale>
void hanoi(int n, int from, int to, int temp) {
    if (n == 1) {
        cout << from << "->" << to << endl;
        return;
    }

    hanoi(n - 1, from, temp, to);
    cout << from << "->" << to << endl;
    hanoi(n - 1, temp, to, from);
}

int main() {
    setlocale(LC_ALL, "RUS");
    int n;
    cout << "Введите количество дисков: ";
    cin >> n;
    if (n <= 0){
        cout << "Ошибка!";
        return 1;
    }
    
    hanoi(n, 1, 3, 2);

    return 0;
}