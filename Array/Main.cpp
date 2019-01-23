
#include "cpparray.hpp"

#include <cassert>
#include <iostream>
using namespace std;

#if ACTIVATE_THIS_FOR_SEEING_THE_CORRECT_RESULT
#include <vector>
#define Array vector
#endif

template<typename T>
using Matrix = Array<Array<T>>;

// Matrix multiplication. The arrays are stored by columns. Passing in a
// non-rectangular array of arrays causes undefined behavior.
template<typename T>
Matrix<T> matrix_mult(const Matrix<T>& a, const Matrix<T>& b)
{
	if (a.empty() || b.empty()) return Matrix<T>();
	assert(a.size() == b.front().size());
	size_t h = a.front().size(), w = b.size(), d = a.size();

	Matrix<T> res;
	res.resize(w);
	for (size_t i = 0; i < w; ++i)
		res[i].resize(h); // resize should run default constructors,
						   // i.e. assign zero elements to the matrix

	for (size_t i = 0; i < w; ++i)
		for (size_t j = 0; j < h; ++j)
			for (size_t k = 0; k < d; ++k)
				res[i][j] += a[k][j] * b[i][k];

	return res;
}

static constexpr size_t S = 10;

int main()
{
	Matrix<float> a, b, c;
	// first, generate some data
	a.reserve(S);
	b.reserve(S);
	for (size_t i = 0; i < S; ++i) {
		Array<float> col;
		col.reserve(S);
		for (size_t j = 0; j < S; ++j)
			col.push_back(0.3 * i + 0.5 * j);
		a.push_back(col);
		col.pop_back();
		col.push_back(10 * i);
		b.push_back(col);
	}
	
	// permutations!
	a[5].swap(b[2]);
	b[3].swap(a[0]);
	
	// run the multiplication
	c = matrix_mult(a, b);
	
	// empty the matrices in various weird ways
	while (!a.empty()) a.pop_back();
	b.clear();

	// print out the content of 'c'
	/*for (size_t i = 0; i < S; ++i) {
		for (size_t j = 0; j < S; ++j) std::cout << c[i][j] << '\t';
		std::cout << std::endl;
	}*/

//#if YOU_HAVE_IMPLEMENTED_ITERATORS
	for (auto &&i : c) {
		for (auto&&j : i) cout << j << '\t';
		cout << endl;
	}
//#endif

	return 0;
}