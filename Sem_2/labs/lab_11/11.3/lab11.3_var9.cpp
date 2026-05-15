#include <iostream>
#include <fstream>
#include <clocale>
using namespace std;

struct Stack {
    int* data;
    int top;
    int capacity;

    void init(int cap = 100) {
        data = new int[cap];
        top = -1;
        capacity = cap;
    }

    void push(int val) {
        if (top < capacity - 1) {
            data[++top] = val;
        }
    }

    int pop() {
        if (top >= 0) {
            return data[top--];
        }
        return -1;
    }

    int size() {
        return top + 1;
    }

    bool empty() {
        return top == -1;
    }

    void clear() {
        delete[] data;
    }
};

Stack* createStack(int n) {
    Stack* s = new Stack;
    s->init(100);
    for (int i = 1; i <= n; i++) {
        int val;
        cout << "Введите элемент " << i << ": ";
        cin >> val;
        s->push(val);
    }
    return s;
}

void printStack(Stack* s) {
    if (s->empty()) {
        cout << "Стек пуст!" << endl;
        return;
    }
    Stack temp;
    temp.init(100);
    while (!s->empty()) {
        temp.push(s->pop());
    }
    while (!temp.empty()) {
        int val = temp.pop();
        cout << val << " ";
        s->push(val);
    }
    cout << endl;
    temp.clear();
}

void addToEnd(Stack* s, int k) {
    if (k <= 0) return;

    Stack temp;
    temp.init(100);

    while (!s->empty()) {
        temp.push(s->pop());
    }

    for (int i = 1; i <= k; i++) {
        int val;
        cout << "Введите новый элемент " << i << ": ";
        cin >> val;
        s->push(val);
    }

    while (!temp.empty()) {
        s->push(temp.pop());
    }
    temp.clear();
}

void deleteBeforePosition(Stack* s, int pos, int k) {
    if (s->empty() || pos <= 1 || k <= 0) return;
    if (pos > s->size()) {
        cout << "Позиция " << pos << " не найдена!" << endl;
        return;
    }

    Stack temp;
    temp.init(100);

    while (!s->empty()) {
        temp.push(s->pop());
    }

    int size = temp.size();
    int* arr = new int[size];

    for (int i = size - 1; i >= 0; i--) {
        arr[i] = temp.pop();
    }

    int newSize = size - k;
    int* newArr = new int[newSize];
    int idx = 0;

    for (int i = 0; i < size; i++) {
        if (i >= pos - k - 1 && i < pos - 1) {
            continue;
        }
        newArr[idx++] = arr[i];
    }

    for (int i = newSize - 1; i >= 0; i--) {
        s->push(newArr[i]);
    }

    delete[] arr;
    delete[] newArr;
    temp.clear();
}

void saveToFile(Stack* s, const char* filename) {
    ofstream fout(filename);
    Stack temp;
    temp.init(100);
    while (!s->empty()) {
        temp.push(s->pop());
    }
    while (!temp.empty()) {
        int val = temp.pop();
        fout << val << " ";
        s->push(val);
    }
    fout.close();
    temp.clear();
}

Stack* loadFromFile(const char* filename) {
    ifstream fin(filename);
    if (!fin) return nullptr;

    Stack* s = new Stack;
    s->init(100);
    int val;
    int arr[100];
    int count = 0;
    while (fin >> val) {
        arr[count++] = val;
    }
    for (int i = count - 1; i >= 0; i--) {
        s->push(arr[i]);
    }
    return s;
}

void deleteStack(Stack* s) {
    s->clear();
    delete s;
}

int main() {
    setlocale(LC_ALL, "Russian");

    Stack* s = createStack(5);
    cout << "Стек: ";
    printStack(s);

    int k, pos;

    cout << "\nСколько элементов добавить в конец? ";
    cin >> k;
    addToEnd(s, k);
    cout << "После добавления: ";
    printStack(s);

    cout << "\nВведите позицию: ";
    cin >> pos;
    cout << "Сколько элементов удалить перед ней? ";
    cin >> k;
    deleteBeforePosition(s, pos, k);
    cout << "После удаления: ";
    printStack(s);

    saveToFile(s, "stack.txt");
    deleteStack(s);

    s = loadFromFile("stack.txt");
    cout << "\nПосле восстановления: ";
    printStack(s);

    deleteStack(s);
    return 0;
}