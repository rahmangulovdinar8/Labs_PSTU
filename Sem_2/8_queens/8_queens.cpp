#include <iostream>
using namespace std;

const int N = 8;

void vizualization(int a[N][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << "|";
			if (a[i][j] == 1) cout << "Q";
			else cout << "*";
		}
		cout << "|" << endl;
	}

	for (int j = 0; j < N; j++) {
		cout << "--";
	}
	cout << "-" << endl;
}

bool proverka(int a[N][N], int x, int y) {
	for (int str = 0; str < y; str++) {
		for (int stolb = 0; stolb < N; stolb++) {
			if (a[str][stolb] == 1) {
				if ((x == stolb) || (y == str) || (x - y == stolb - str) || ((N - x) - y == (N - stolb) - str))
					return 0;	
			}
		}
	} 
	return 1;
}

void queens(int a[N][N], int str) {
	static int count = 0;
	for (int stolb = 0; stolb < N; stolb++) {
		if (proverka(a, stolb, str)) {
			if (str == N-1) {
				a[str][stolb] = 1;
				vizualization(a);
				a[str][stolb] = 0;
				count++;
			}
			else {
				a[str][stolb] = 1;
				queens(a, str + 1);
				a[str][stolb] = 0;
			}
		}
	}
	if (str == 0) cout << "total boards: " << count << endl;
}


int main(){
	int a[N][N];

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			a[i][j] = 0;
		}
	}
	queens(a, 0);
}