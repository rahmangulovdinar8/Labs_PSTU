#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Data {
    string name;
    string phone;
    string address;
};

struct Node {
    Data data;
    Node* next;
    Node(Data d) : data(d), next(nullptr) {}
};

struct HashTable {
    int size;
    int count;
    Node** table;

    HashTable(int s) : size(s), count(0) {
        table = new Node * [size];
        for (int i = 0; i < size; i++) {
            table[i] = nullptr;
        }
    }

    int hash(string key) {
        int sum = 0;
        for (char c : key) {
            sum += (int)c;
        }
        return sum % size;
    }

    void insert(Data d) {
        int idx = hash(d.address);
        Node* newNode = new Node(d);

        if (table[idx] == nullptr) {
            table[idx] = newNode; 
        }
        else {
            Node* p = table[idx];
            while (p->next != nullptr) {
                if (p->data.address == d.address) {
                    p->data = d;
                    delete newNode;
                    return;
                }
                p = p->next;
            }
            if (p->data.address == d.address) {
                p->data = d;
                delete newNode;
                return;
            }
            p->next = newNode;
        }
        count++;
    }

    Data* search(string address) {
        int idx = hash(address);
        Node* p = table[idx];
        while (p != nullptr) {
            if (p->data.address == address) {
                return &p->data;
            }
            p = p->next;
        }
        return nullptr;
    }

    bool remove(string address) {
        int idx = hash(address);
        Node* p = table[idx];
        Node* prev = nullptr;

        while (p != nullptr) {
            if (p->data.address == address) {
                if (prev == nullptr) {
                    table[idx] = p->next;
                }
                else {
                    prev->next = p->next;
                }
                delete p;
                count--;
                return true;
            }
            prev = p;
            p = p->next;
        }
        return false;
    }

    int countCollisions() {
        int collisions = 0;
        for (int i = 0; i < size; i++) {
            Node* p = table[i];
            int len = 0;
            while (p != nullptr) {
                len++;
                p = p->next;
            }
            if (len > 1) {
                collisions += (len - 1);
            }
        }
        return collisions;
    }

    void saveToFile(string filename) {
        ofstream fout(filename);
        for (int i = 0; i < size; i++) {
            Node* p = table[i];
            while (p != nullptr) {
                fout << p->data.name << endl;
                fout << p->data.phone << endl;
                fout << p->data.address << endl;
                p = p->next;
            }
        }
        fout.close();
    }

    void loadFromFile(string filename) {
        ifstream fin(filename);
        if (!fin) return;

        for (int i = 0; i < size; i++) {
            Node* p = table[i];
            while (p != nullptr) {
                Node* next = p->next;
                delete p;
                p = next;
            }
            table[i] = nullptr;
        }
        count = 0;

        string name, phone, address;
        while (getline(fin, name)) {
            getline(fin, phone);
            getline(fin, address);
            Data d = { name, phone, address };
            insert(d);
        }
        fin.close();
    }

    ~HashTable() {
        for (int i = 0; i < size; i++) {
            Node* p = table[i];
            while (p != nullptr) {
                Node* next = p->next;
                delete p;
                p = next;
            }
        }
        delete[] table;
    }
};

string generateRandomName() {
    string names[] = { "Oleg", "Andrey", "Vladimir", "Valentin", "Georgiy", "Artur", "Maxim", "Marat", "Nikolay", "Mark" };
    string lasts[] = { "Ivanov", "Kuznecov", "Andreev", "Suzev", "Ligalov", "Vasilyev", "Fedorov", "Budeyko" };

    return lasts[rand() % 8] + " " + names[rand() % 10];
}

Data generateRandomData(int i) {
    Data d;
    d.name = generateRandomName();
    d.phone = "8-900-" + to_string(100 + i).substr(0, 3) + "-" + to_string(1000 + i).substr(0, 2);
    string streets[] = { "Lenina", "Pushkina", "Gagarina", "Sovetskaya", "Molodyozhnaya", "Centralnaya", "Komsomolskaya", "Sadovaya", "Lesnaya", "Popova" };

    int house = rand() % 100;

    d.address = streets[rand() % 10] + " " + to_string(house) + "_" + to_string(i);
    return d;
}

int main() {
    srand(time(0));

    const int N = 100;
    Data records[100];
    for (int i = 0; i < N; i++) {
        records[i] = generateRandomData(i);
    }

    int sizes[] = { 40, 75, 90 };
    for (int s = 0; s < 3; s++) {
        HashTable ht(sizes[s]);
        for (int i = 0; i < N; i++) {
            ht.insert(records[i]);
        }
        cout << "Table size: " << sizes[s] << ", Collisions: " << ht.countCollisions() << endl;
    }

    HashTable ht(75);
    for (int i = 0; i < N; i++) {
        ht.insert(records[i]);
    }

    cout << "Loaded elements: " << ht.count << " elements" << endl;

    string testAddress = records[0].address;

    cout << "Searching: " << testAddress << endl;
    Data* found = ht.search(testAddress);
    if (found) {
        cout << "Found: " << found->name << ", " << found->phone << ", " << found->address << endl;
    }

    cout << "Removing: " << testAddress << endl;
    ht.remove(testAddress);

    found = ht.search(testAddress);
    if (found == nullptr) {
        cout << "Successfully removed" << endl;
    }
    ht.saveToFile("hash_table.txt");

    HashTable ht2(75);
    ht2.loadFromFile("hash_table.txt");
    cout << "After load, ht2.count = " << ht2.count << endl;
    return 0;
}