#include <iostream>
#include <algorithm> 
#include <assert.h>

class Matrix {
	int n;
	int *data;
public:
	int Size() {
		return n;
	}

	Matrix(const int n) : n(n) {
		data = new int[n * n];
		std::fill_n(data, n * n, 0);
	}

	~Matrix() {
		delete[] data;
	}

	int Get(int column, int row) {
		assert(column > 0 && column <= n);
		assert(row > 0 && row <= n);

		return data[(row - 1) * n + (column - 1)];
	}

	void Set(int column, int row, int value) {
		int oldValue = this->Get(column, row);
		assert(oldValue == 0);
		assert(value != 0);

		//std::cout << "Set " << row << " : " << column << " to " << value << "\n";
		data[(row - 1) * n + column - 1] = value;
	}
};

int main() {
	int n;
	std::cin >> n;
	int left = 1;
	int right = n;
	int value = 1;
	Matrix matrix(n);
	while (left < right) {

		for (int i = left; i < right; i++)
			matrix.Set(i, left, value++);

		for (int i = left; i < right; i++)
			matrix.Set(right, i, value++);

		for (int i = right; i > left; i--)
			matrix.Set(i, right, value++);

		for (int i = right; i > left; i--)
			matrix.Set(left, i, value++);


		left++;
		right--;
	}

	if (n % 2)
		matrix.Set((n + 1) / 2, (n + 1 )/ 2, value++);
	assert(n * n == --value);
	std::cout << n * n;
	return 0;
}