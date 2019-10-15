#include <iostream>

using namespace std;

int sgn(int i, int j)
{
	if (((i + j) % 2) == 1)
	{
		return -1;
	}

	return 1;
}

template<typename T>
class matrix {
	T* values;
	int n, m;

public:
	matrix(int a)
	{
		n = a;
		m = a;
		values = new T[n * m];
	}
	matrix(int a, int b)
	{
		n = a;
		m = b;
		values = new T[n * m];

	}
	~matrix()
	{
		delete values;
	}
	int sizeN()
	{
		return n;
	}
	int sizeM()
	{
		return m;
	}
	T val(int i, int j)
	{
		return values[(i * n) + j];
	}
	matrix<T>* minor(matrix<T>* m, int row, int col)
	{
		matrix<T>* res = new matrix<T>(m->sizeN() - 1);
		int dr = 0;
		int dc = 0;
		for (int i = 0; i < m->sizeN(); i++)
		{
			if (i == row)
			{
				dr = 1;
				continue;
			}
			for (int j = 0; j < m->sizeN(); j++)
			{
				if (j == col)
				{
					dc = 1;
					continue;
				}
				res->insert(m->val(i, j), i - dr, j - dc);
			}
			dc = 0;
		}

		return res;
	}
	T det() {
		T res = 0;
		int i = 0;
		if (this->sizeN() > 2)
		{
			for (int j = 0; j < this->sizeN(); j++)
			{
				res += sgn(i, j) * this->val(i, j) * (minor(this, i, j))->det();
			}
		}
		else if (this->sizeN() == 2)
		{
			return ((this->val(0, 0) * this->val(1, 1)) - (this->val(0, 1) * this->val(1, 0)));
		}
		else if (this->sizeN() == 1)
		{
			return this->val(0, 0);
		}
		else
		{
			cout << "Enter a valid value " << endl;
			return 0;
		}
		return res;
	}
	void insert(T v, int i, int j)
	{
		values[(i * n) + j] = v;
	}
	void scale(T v)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				values[(i * n) + j] *= v;
			}
		}
	}
	void print()
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				cout << this->val(i, j) << " ";
			}
			cout << endl;
		}
	}
	bool operator==(matrix<T>* m)
	{
		if ((this->sizeN() != m->sizeN()) || (this->sizeM() != m->sizeM()))
		{
			return false;
		}
		for (int i = 0; i < this->sizeN(); i++)
		{
			for (int j = 0; j < this->sizeM(); j++)
			{
				if (this->val(i, j) != m->val(i, j))
				{
					return false;
				}
			}
		}
		return true;
	}
	matrix<T>* operator=(matrix<T>* m)
	{
		if (this == m)
		{
			return this;
		}
		delete values;
		this->n = m->sizeN();
		this->m = m->sizeM();
		values = new T[this->n * this->m];
		for (int i = 0; i < m->sizeN(); i++)
		{
			for (int j = 0; j < m->sizeM(); j++)
			{
				this->insert(m->val(i, j), i, j);
			}
		}
		return m;
	}
	matrix<T>* operator+(matrix<T> *m)
	{
		matrix<T>* res = new matrix<T>(this->sizeN(), this->sizeM());
		if ((this->sizeN() == m->sizeN()) && (this->sizeM() == m->sizeM()))
		{
			for (int i = 0; i < this->sizeN(); i++)
			{
				for (int j = 0; j < this->sizeM(); j++)
				{
					int t = this->val(i, j) + m->val(i, j);
					res->insert(t, i, j);
				}
			}
		}
		else
		{
			cout << "Undefined" << endl;
			exit;
		}
		return res;
	}
	matrix<T>* operator-(matrix<T>* m)
	{
		m->scale(-1);
		return *this+m;
	}

	matrix<T>* operator*(matrix<T>* m)
	{
		matrix<T>* res = new matrix<T>(this->sizeN(), m->sizeM());
		if (this->sizeM() == m->sizeN())
		{

			for (int i = 0; i < this->sizeN(); i++)
			{
				for (int j = 0; j < m->sizeN(); j++)
				{
					int temp = 0;
					for (int k = 0; k < m->sizeN(); k++)
					{
						temp += this->val(i, k) * m->val(k, j);
					}
					res->insert(temp, i, j);
				}
			}
		}
		else
		{
			cout << "Undefined" << endl;
			exit;
		}
		return res;
	}

};


template<typename T>
matrix<T>* enterMatrix(int i)
{
	matrix<long double>* m = 0;
	if (i == 0)
	{
		int n;
		cout << "Enter the order of the matrix: ";
		cin >> n;
		m = new matrix<long double>(n);
	}
	else if (i == 1) {
		cout << "Enter the dimensions of the 1st matrix: ";
		int a, b;
		cin >> a >> b;
		m = new matrix<long double>(a, b);
	}
	else if (i == 2) {
		cout << "Enter the dimensions of the 2nd matrix: ";
		int a, b;
		cin >> a >> b;
		m = new matrix<long double>(a, b);
	}
	cout << "Enter the matrix: " << endl;
	for (int i = 0; i < m->sizeN(); i++)
	{
		for (int j = 0; j < m->sizeM(); j++)
		{
			long double t;
			cin >> t;
			m->insert(t, i, j);
		}
	}
	return m;
}

int main()
{
	int operation;
	cout << "Operation: " << endl;
	cout << "1 - determinant" << endl << "2 - matrix addition" << endl
		<< "3 - matrix substraction" << endl << "4 - matrix multiplication" << endl;
	cin >> operation;
	switch (operation)
	{
	case 1:
	{
		matrix<long double>* m = enterMatrix<long double>(0);
		cout << endl;
		cout << "Determinant: " << m->det();
		delete m;
		break;
	}
	case 2:
	{
		matrix<long double>* m1 = enterMatrix<long double>(1);
		matrix<long double>* m2 = enterMatrix<long double>(2);

		cout << endl;
		cout << "Result: " << endl;
		//sum(m1, m2)->print();
		(*m1+m2)->print();
		delete m1, m2;
		break;
	}
	case 3:
	{
		matrix<long double>* m1 = enterMatrix<long double>(1);
		matrix<long double>* m2 = enterMatrix<long double>(2);

		cout << endl;
		cout << "Result: " << endl;
		(*m1-m2)->print();
		delete m1, m2;
		break;
	}
	case 4:
	{
		matrix<long double>* m1 = enterMatrix<long double>(1);
		matrix<long double>* m2 = enterMatrix<long double>(2);

		cout << endl;
		cout << "Result: " << endl;
		((*m1) * (m2))->print();
		delete m1, m2;
		break;
	}
	}

	return 0;
}
