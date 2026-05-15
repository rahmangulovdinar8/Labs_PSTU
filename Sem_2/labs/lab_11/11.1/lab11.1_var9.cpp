#include <iostream>
#include <fstream>
using namespace std;

struct Node {
    int data;
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
    
    Node* prev = list->head;
    if (prev == p) return;
    
    while (prev->next != p && prev->next != nullptr) {
        prev = prev->next;
    }
    
    for (int i = 0; i < k; i++) {
        if (prev->next == p) {
            Node* toDelete = prev;
            
            Node* prevPrev = list->head;
            if (prevPrev == toDelete) {
                list->head = toDelete->next;
                delete toDelete;
                break;
            }
            while (prevPrev->next != toDelete && prevPrev->next != nullptr) {
                prevPrev = prevPrev->next;
            }
            prevPrev->next = toDelete->next;
            delete toDelete;
            prev = prevPrev;
        }
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
    
    saveToFile(list, "singly_list.txt");
    deleteList(list);
    
    list = loadFromFile("singly_list.txt");
    cout << "После восстановления из файла: ";
    printList(list);
    
    deleteList(list);
    return 0;
}