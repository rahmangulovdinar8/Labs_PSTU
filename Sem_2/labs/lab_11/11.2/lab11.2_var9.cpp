#include <iostream>
#include <fstream>
using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;
};

struct List {
    Node* head = nullptr;
    int size = 0;
};

List* createList(int n) {
    List* list = new List;
    if (n <= 0) return list;
    
    Node* tail = nullptr;
    for (int i = 1; i <= n; i++) {
        Node* newNode = new Node;
        cout << "Введите элемент " << i << ": ";
        cin >> newNode->data;
        newNode->next = nullptr;
        newNode->prev = tail;
        
        if (tail == nullptr) {
            list->head = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
        list->size++;
    }
    return list;
}

void printList(List* list) {
    if (list->head == nullptr) {
        cout << "Список пуст!" << endl;
        return;
    }
    Node* p = list->head;
    while (p != nullptr) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

void addToEnd(List* list, int k) {
    if (k <= 0) return;
    
    Node* tail = list->head;
    if (tail != nullptr) {
        while (tail->next != nullptr) {
            tail = tail->next;
        }
    }
    
    for (int i = 1; i <= k; i++) {
        Node* newNode = new Node;
        cout << "Введите новый элемент " << i << ": ";
        cin >> newNode->data;
        newNode->next = nullptr;
        newNode->prev = tail;
        
        if (tail == nullptr) {
            list->head = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
        list->size++;
    }
}

void deleteBeforePosition(List* list, int pos, int k) {
    if (list->head == nullptr || pos <= 1 || k <= 0) return;
    if (pos > list->size) {
        cout << "Позиция " << pos << " не найдена!" << endl;
        return;
    }
    
    Node* p = list->head;
    for (int i = 1; i < pos && p != nullptr; i++) {
        p = p->next;
    }
    if (p == nullptr) return;
    
    Node* before = p->prev;
    for (int i = 0; i < k && before != nullptr; i++) {
        Node* toDelete = before;
        before = before->prev;
        
        if (toDelete->prev != nullptr) {
            toDelete->prev->next = toDelete->next;
        } else {
            list->head = toDelete->next;
        }
        
        if (toDelete->next != nullptr) {
            toDelete->next->prev = toDelete->prev;
        }
        
        delete toDelete;
        list->size--;
    }
}

void saveToFile(List* list, const char* filename) {
    ofstream fout(filename);
    Node* p = list->head;
    while (p != nullptr) {
        fout << p->data << " ";
        p = p->next;
    }
    fout.close();
}

List* loadFromFile(const char* filename) {
    ifstream fin(filename);
    if (!fin) return nullptr;
    
    List* list = new List;
    int val;
    Node* tail = nullptr;
    while (fin >> val) {
        Node* newNode = new Node;
        newNode->data = val;
        newNode->next = nullptr;
        newNode->prev = tail;
        
        if (tail == nullptr) {
            list->head = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
        list->size++;
    }
    return list;
}

void deleteList(List* list) {
    Node* p = list->head;
    while (p != nullptr) {
        Node* next = p->next;
        delete p;
        p = next;
    }
    delete list;
}

int main() {
    List* list = createList(5);
    cout << "Список: ";
    printList(list);
    
    addToEnd(list, 2);
    cout << "После добавления 2 элементов в конец: ";
    printList(list);
    
    deleteBeforePosition(list, 4, 2);
    cout << "После удаления 2 элементов перед позицией 4: ";
    printList(list);
    
    saveToFile(list, "doubly_list.txt");
    deleteList(list);
    
    list = loadFromFile("doubly_list.txt");
    cout << "После восстановления из файла: ";
    printList(list);
    
    deleteList(list);
    return 0;
}