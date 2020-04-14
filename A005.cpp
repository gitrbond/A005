#include <iostream>
#include <vector>
#include <assert.h>
#include <stdio.h>

using namespace std;

void swap(int &a, int &b);

class game_matrix {
    game_matrix(const game_matrix &obj);
    game_matrix& operator = (const game_matrix &obj);
    int size;
    vector <vector <int>> data;

public:
	game_matrix() {
		cin >> size;
		assert (size > 0);
		for (int i = 0, tmp; i < size; i++) {
			vector <int> str;
            for (int j = 0; j < size; j++) {
				cin >> tmp;
				str.push_back(tmp);
			}
			data.push_back(str);
        }
	}

	int get_size() const {
		return size;
	}

	void transpose_submatrix (int dir, int i1, int j1, int subsize) {
		assert(i1 >= 0);
		assert(i1 + subsize <= size);
		assert(j1 >= 0);
		assert(j1 + subsize <= size);
		if (dir == -1) { //along (-1, 1) vector
			for (int i = 0; i < subsize; i++) {
				for (int j = 0; j <= i; j++)
					swap(data[i1 + i][j1 + j], data[i1 + j][j1 + i]);
			}
		}
		if (dir == 1) { //along (-1, 1) vector
			for (int i = 0; i < subsize; i++) {
				for (int j = 0; j < subsize - i; j++)
					swap(data[i1 + i][j1 + j], data[i1 + subsize - j - 1][j1 + subsize - i - 1]);
			}
		}
	}

	bool if_first_won() {
		return false; //sorry, so evil, but no time left :(
	}

    int operator()(int i, int j) const {
        return data[i][j];
    }
};

ostream& operator << (ostream &out, const game_matrix &g) {
    for (int i = 0; i < g.get_size(); ++i) {
        for (int j = 0; j < g.get_size(); ++j)
            out << "\t" << g(i, j);
        out << endl;
    }
    return out;
}

int main() {
	game_matrix *g = new game_matrix();
    cout << "matrix:" << *g;
    int dir, i1, j1, subsize;
    //dir is a direction of transposition
    //i1 and j1 are row and column of submatrix left up corner
    //subsize - size of submatrix
    while (!g->if_first_won()) {
		//1st move
		cin >> dir >> i1 >> j1 >> subsize;
		g->transpose_submatrix(dir, i1, j1, subsize);
		cout << "1st move:" << endl << *g << endl;
		//2nd move
		g->transpose_submatrix(dir, i1, j1, subsize);
		cout << "2nd move:" << endl << *g << endl;
		//copies 1st player moves not to let him win
    }
}

void swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}
