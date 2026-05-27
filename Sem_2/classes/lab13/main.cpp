#include "Money.h"
#include "Vector.h"
#include <iostream>
#include <deque>
#include <set>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

typedef deque<Money>  DequeMoney;
typedef vector<Money> VecMoney;
typedef set<Money>    SetMoney;

Money s_global;

struct Greater_s {
    bool operator()(Money t) { return t > s_global; }
};

struct Less_s {
    bool operator()(Money t) { return t < s_global; }
};

struct Comp_less {
    bool operator()(Money a, Money b) { return a > b; }
};

struct Equal_s {
    bool operator()(Money t) { return t == s_global; }
};

struct Less_money {
    bool operator()(Money a, Money b) { return a < b; }
};

void add_avg(Money& m) { m = m + s_global; }

Money srednee_deque(DequeMoney& d) {
    Money s = d[0];
    for (int i = 1; i < (int)d.size(); i++) s = s + d[i];
    return s / (int)d.size();
}

DequeMoney make_deque(int n) {
    DequeMoney d;
    Money m;
    for (int i = 0; i < n; i++) {
        cout << "Запись " << i+1 << ":\n";
        cin >> m;
        d.push_back(m);
    }
    return d;
}

void print_deque(DequeMoney d) {
    for (int i = 0; i < (int)d.size(); i++) cout << d[i] << "  ";
    cout << endl;
}

void print_vecmoney(VecMoney v) {
    for (int i = 0; i < (int)v.size(); i++) cout << v[i] << "  ";
    cout << endl;
}

void task1() {
    cout << "\n=== Задача 1: deque<Money> + STL алгоритмы ===" << endl;
    int n; cout << "N? "; cin >> n;
    DequeMoney d = make_deque(n);
    cout << "Исходный контейнер:\n"; print_deque(d);

    DequeMoney::iterator it;

    it = max_element(d.begin(), d.end(), Less_money());
    Money maxVal = *it;
    cout << "max = " << maxVal << endl;

    s_global = srednee_deque(d);
    cout << "Среднее = " << s_global << endl;

    replace_if(d.begin(), d.end(), Greater_s(), maxVal);
    cout << "После replace_if (>среднего заменить на max):\n"; print_deque(d);

    cout << "Сортировка по убыванию:\n";
    sort(d.begin(), d.end(), Comp_less());
    print_deque(d);

    cout << "Сортировка по возрастанию:\n";
    sort(d.begin(), d.end(), Less_money());
    print_deque(d);

    cout << "Поиск элемента (введите):\n"; cin >> s_global;
    it = find_if(d.begin(), d.end(), Equal_s());
    if (it != d.end()) cout << "Найден: " << *it << endl;
    else cout << "Не найден" << endl;

    int cnt = count_if(d.begin(), d.end(), Equal_s());
    cout << "Количество таких элементов: " << cnt << endl;

    it = remove_if(d.begin(), d.end(), Equal_s());
    d.erase(it, d.end());
    cout << "После удаления по ключу:\n"; print_deque(d);

    if (!d.empty()) {
        s_global = srednee_deque(d);
        cout << "Среднее для for_each = " << s_global << endl;
        for_each(d.begin(), d.end(), add_avg);
        cout << "После добавления среднего к каждому (for_each):\n"; print_deque(d);
    }

    it = max_element(d.begin(), d.end(), Less_money());
    d.push_back(*it);
    cout << "После добавления max в конец (задание 3):\n"; print_deque(d);
}

void task2() {
    cout << "\n=== Задача 2: параметризированный класс Vector<Money> + STL ===" << endl;
    int n; cout << "N? "; cin >> n;
    Vector<Money> vec(n);
    cout << "Исходный вектор:\n"; vec.Print();

    vec.AddMaxToEnd();
    cout << "После добавления max в конец (задание 3):\n"; vec.Print();

    cout << "Введите ключ для поиска и удаления:\n"; cin >> s_global;
    vec.DeleteByKey(s_global);
    cout << "После удаления по ключу (задание 4):\n"; vec.Print();

    vec.AddAvgToEach();
    cout << "После добавления среднего к каждому (задание 5):\n"; vec.Print();
}

void task3() {
    cout << "\n=== Задача 3: set<Money> + STL алгоритмы ===" << endl;
    int n; cout << "N? "; cin >> n;
    SetMoney s;
    Money m;
    for (int i = 0; i < n; i++) {
        cout << "Запись " << i+1 << ":\n"; cin >> m;
        s.insert(m);
    }

    VecMoney v(s.begin(), s.end());
    cout << "Исходный контейнер (set → vector):\n"; print_vecmoney(v);

    VecMoney::iterator it;
    it = max_element(v.begin(), v.end(), Less_money());
    Money maxVal = *it;
    cout << "max = " << maxVal << endl;

    s_global = v[0];
    for (int i = 1; i < (int)v.size(); i++) s_global = s_global + v[i];
    s_global = s_global / (int)v.size();
    cout << "Среднее = " << s_global << endl;

    replace_if(v.begin(), v.end(), Greater_s(), maxVal);
    cout << "После replace_if:\n"; print_vecmoney(v);

    cout << "Сортировка по убыванию:\n";
    sort(v.begin(), v.end(), Comp_less());
    print_vecmoney(v);

    cout << "Сортировка по возрастанию:\n";
    sort(v.begin(), v.end(), Less_money());
    print_vecmoney(v);

    cout << "Поиск элемента (введите):\n"; cin >> s_global;
    it = find_if(v.begin(), v.end(), Equal_s());
    if (it != v.end()) cout << "Найден: " << *it << endl;
    else cout << "Не найден" << endl;

    int cnt = count_if(v.begin(), v.end(), Equal_s());
    cout << "Количество: " << cnt << endl;

    it = remove_if(v.begin(), v.end(), Equal_s());
    v.erase(it, v.end());
    cout << "После удаления по ключу (задание 4):\n"; print_vecmoney(v);

    if (!v.empty()) {
        s_global = v[0];
        for (int i = 1; i < (int)v.size(); i++) s_global = s_global + v[i];
        s_global = s_global / (int)v.size();
        for_each(v.begin(), v.end(), add_avg);
        cout << "После добавления среднего к каждому (задание 5, for_each):\n"; print_vecmoney(v);
    }

    it = max_element(v.begin(), v.end(), Less_money());
    v.push_back(*it);
    cout << "После добавления max в конец (задание 3):\n"; print_vecmoney(v);
}

int main() {
    task1();
    task2();
    task3();
    return 0;
}
