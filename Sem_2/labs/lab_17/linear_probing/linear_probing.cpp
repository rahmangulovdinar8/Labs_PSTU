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

struct HashTable {
    int size;
    int count;
    Data* table;
    bool* isDeleted;
    bool* isOccupied;

    HashTable(int s) : size(s), count(0) {
        table = new Data[size];
        isDeleted = new bool[size];
        isOccupied = new bool[size];
        for (int i = 0; i < size; i++) {
            isOccupied[i] = false;
            isDeleted[i] = false;
        }
    }

    int hash(string key) {
        int sum = 0;
        for (char c : key) {
            sum += (int)c;
        }
        return sum % size;
    }

    int findPos(string address) {
        int idx = hash(address);
        int start = idx;

        while (isOccupied[idx] && !isDeleted[idx] && table[idx].address != address) {
            idx = (idx + 1) % size;
            if (idx == start) return -1;
        }
        return idx;
    }

    int searchPos(string address) {
        int idx = hash(address);
        int start = idx;

        while (isOccupied[idx]) {
            if (!isDeleted[idx] && table[idx].address == address) {
                return idx;
            }
            idx = (idx + 1) % size;
            if (idx == start) break;
        }
        return -1;
    }

    void insert(Data d) {
        int idx = findPos(d.address);
        if (idx == -1) {
            return;
        }

        if (isOccupied[idx] && table[idx].address == d.address && !isDeleted[idx]) {
            table[idx] = d;
            return;
        }

        table[idx] = d;
        isOccupied[idx] = true;
        isDeleted[idx] = false;
        count++;
    }

    Data* search(string address) {
        int idx = searchPos(address);
        if (idx == -1) return nullptr;
        return &table[idx];
    }

    bool remove(string address) {
        int idx = searchPos(address);
        if (idx == -1) return false;
        isDeleted[idx] = true;
        count--;
        return true;
    }

    int countCollisions() {
        int collisions = 0;
        for (int i = 0; i < size; i++) {
            if (isOccupied[i] && !isDeleted[i]) {
                int originalIdx = hash(table[i].address);
                if (originalIdx != i) collisions++;
            }
        }
        return collisions;
    }


    void clear() {
        for (int i = 0; i < size; i++) {
            isOccupied[i] = false;
            isDeleted[i] = false;
        }
        count = 0;
    }

    void saveToFile(const string& filename) {
        ofstream fout(filename);
        for (int i = 0; i < size; i++) {
            if (isOccupied[i] && !isDeleted[i]) {
                fout << table[i].name << endl;
                fout << table[i].phone << endl;
                fout << table[i].address << endl;
            }
        }
        fout.close();
        cout << "Saved to " << filename << endl;
    }

    void loadFromFile(const string& filename) {
        ifstream fin(filename);
        if (!fin) {
            cout << "File not found" << endl;
            return;
        }

        clear();
        string name, phone, address;
        while (getline(fin, name)) {
            getline(fin, phone);
            getline(fin, address);
            Data d = { name, phone, address };
            insert(d);
        }
        fin.close();
        cout << "Loaded from " << filename << endl;
    }

    ~HashTable() {
        delete[] table;
        delete[] isDeleted;
        delete[] isOccupied;
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

    ht.saveToFile("hash_table_2.txt");

    HashTable ht2(75);
    ht2.loadFromFile("hash_table_2.txt");
    cout << "After load, ht2.count = " << ht2.count << endl;

    return 0;
}