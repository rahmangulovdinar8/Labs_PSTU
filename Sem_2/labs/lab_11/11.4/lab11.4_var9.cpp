#include <iostream>
#include <fstream>
#include <clocale>
using namespace std;

struct Queue {
    int* data;
    int front;
    int rear;
    int capacity;
    int count;

    void init(int cap = 100) {
        data = new int[cap];
        front = 0;
        rear = -1;
        capacity = cap;
        count = 0;
    }

    void push(int val) {
        if (count < capacity) {
            rear = (rear + 1) % capacity;
            data[rear] = val;
            count++;
        }
    }

    int pop() {
        if (count > 0) {
            int val = data[front];
            front = (front + 1) % capacity;
            count--;
            return val;
        }
        return -1;
    }

    int size() {
        return count;
    }

    bool empty() {
        return count == 0;
    }

    void clear() {
        delete[] data;
    }
};

Queue* createQueue(int n) {
    Queue* q = new Queue;
    q->init(100);
    for (int i = 1; i <= n; i++) {
        int val;
        cout << "Введите элемент " << i << ": ";
        cin >> val;
        q->push(val);
    }
    return q;
}

void printQueue(Queue* q) {
    if (q->empty()) {
        cout << "Очередь пуста!" << endl;
        return;
    }
    Queue temp;
    temp.init(100);
    while (!q->empty()) {
        int val = q->pop();
        cout << val << " ";
        temp.push(val);
    }
    while (!temp.empty()) {
        q->push(temp.pop());
    }
    cout << endl;
    temp.clear();
}

void addToEnd(Queue* q, int k) {
    if (k <= 0) return;
    for (int i = 1; i <= k; i++) {
        int val;
        cout << "Введите новый элемент " << i << ": ";
        cin >> val;
        q->push(val);
    }
}

void deleteBeforePosition(Queue* q, int pos, int k) {
    if (q->empty() || pos <= 1 || k <= 0) return;
    if (pos > q->size()) {
        cout << "Позиция " << pos << " не найдена!" << endl;
        return;
    }

    Queue temp;
    temp.init(100);

    for (int i = 1; i < pos - k; i++) {
        temp.push(q->pop());
    }

    for (int i = 0; i < k; i++) {
        q->pop();
    }

    int pivot = q->pop();
    temp.push(pivot);

    while (!q->empty()) {
        temp.push(q->pop());
    }

    while (!temp.empty()) {
        q->push(temp.pop());
    }

    temp.clear();
}

void saveToFile(Queue* q, const char* filename) {
    ofstream fout(filename);
    Queue temp;
    temp.init(100);
    while (!q->empty()) {
        int val = q->pop();
        fout << val << " ";
        temp.push(val);
    }
    while (!temp.empty()) {
        q->push(temp.pop());
    }
    fout.close();
    temp.clear();
}

Queue* loadFromFile(const char* filename) {
    ifstream fin(filename);
    if (!fin) return nullptr;

    Queue* q = new Queue;
    q->init(100);
    int val;
    while (fin >> val) {
        q->push(val);
    }
    return q;
}

void deleteQueue(Queue* q) {
    q->clear();
    delete q;
}

int main() {
    setlocale(LC_ALL, "Russian");

    Queue* q = createQueue(5);
    cout << "Очередь: ";
    printQueue(q);

    int k, pos;

    cout << "\nСколько элементов добавить в конец? ";
    cin >> k;
    addToEnd(q, k);
    cout << "После добавления: ";
    printQueue(q);

    cout << "\nВведите позицию: ";
    cin >> pos;
    cout << "Сколько элементов удалить перед ней? ";
    cin >> k;
    deleteBeforePosition(q, pos, k);
    cout << "После удаления: ";
    printQueue(q);

    saveToFile(q, "queue.txt");
    deleteQueue(q);

    q = loadFromFile("queue.txt");
    cout << "\nПосле восстановления: ";
    printQueue(q);

    deleteQueue(q);
    return 0;
}