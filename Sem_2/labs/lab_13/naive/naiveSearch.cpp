#include <iostream>
#include <string>

using namespace std;

int naiveSearch(const string& a, const string& b) {
    int a_size = a.size();
    int b_size = b.size();

    if (a_size < b_size || b_size == 0) {
        return -1;
    }
    for (int i = 0; i <= a_size - b_size; i++) {
        int j = 0;
        
        while (j < b_size && b[j] == a[i + j]) {
            j++;
        }

        if (j == b_size) {
            return i;
        }
    }
    return -1;
}

int main() {
    string text = "vinogradsliviyablokizelenieestxstobanani";
    string pattern = "yablokizelenie";

    int idx = naiveSearch(text, pattern);

    if (idx == -1) {
        cout << "Substring not found" << endl;
    }
    else {
        cout << "Substring found, index: " << idx << endl;
    }

    return 0;
}