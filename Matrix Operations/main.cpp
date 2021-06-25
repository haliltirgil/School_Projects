#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>
#include <sstream>

using namespace std;

template <class Type>
class Matrix
{
public:
	//kurucu ve yýkýcý fonksiyonlar istege göre ayarlandý------------------------//
	Matrix();
	Matrix(int rows, int cols, Type inValue);
	~Matrix();
	//-----------------getter ve setter yapýsý kuruldu---------------------------//
	void setRows(int rows);
	void setCols(int cols);
	void setinValue(Type inValue);
	int getRows();
	int getCols();
	Type getinValue();
	Type** getMatrix();
	//--------------------matris islemlerini barindiran fonksiyonlar--------------//
	Type** generateMatrix(int rows, int cols, Type inValue);
	void print(string txtname);
	virtual void print();
	void inverseMatrix();
	void getCofactor(Type** mat, Type** temp, int p, int q, int n);
	int determinantMatrix(Type** mat, int size);
	void transpozeMatrix(int rows, int cols);
	void resize(int newRows, int newCols);
	//----------overloadlar yapýldý----------//
	Matrix operator +(Matrix& obj);
	Matrix operator -(Matrix& obj);
	Matrix operator *(Matrix& obj);
	void emul(Matrix& obj);
	//----------skaler overloadlar yapýldý------------//
	Matrix operator +(Type value);
	Matrix operator -(Type value);
	Matrix operator *(Type value);
	Matrix operator /(Type value);
	Matrix operator %(Type value);
	Matrix operator ^(Type value);

protected:
	int rows;
	int cols;
	Type** mat;
	Type inValue;
};

template<class Type>
class Table :public Matrix<Type>
{
public:

	Table();
	Table(int rows, int cols, Type inValue);
	void print();
	Type itemAt(int numberofRows, int numberofCols);
	Type itemAt(string index);
	Type itemAt(string rowName, string colName);
	void setrowNames(string rNames[], int n);
	void setcolNames(string cNames[], int n);
protected:
	string colsName[50] = { " ","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S"
		,"T","U","V","W","X","Y","Z","AA","AB","AC","AD","AE","AF","AG","AH","AI" };
	string rowsName[50] = { "1","2","3","4","5", "6","7","8","9","10", "11","12","13","14","15", "16","17","18","19"
		,"20", "21","22","23","24","25", "26","27","28","29","30","31","32","33","34","35" };

};

template <class Type>
Matrix<Type>::Matrix()
{
	this->rows = 10;
	this->cols = 10;
	this->inValue = 0;

	this->mat = generateMatrix(getRows(), getCols(), getinValue());
}

template <class Type>
Matrix<Type>::Matrix(int rows, int cols, Type inValue)
{
	this->rows = rows;
	this->cols = cols;
	this->inValue = inValue;

	this->mat = generateMatrix(getRows(), getCols(), getinValue());
}

template <class Type>
Matrix<Type>::~Matrix()
{

}

template <class Type>
void Matrix<Type>::setRows(int rows)
{
	this->rows = rows;
}

template <class Type>
void Matrix<Type>::setCols(int cols)
{
	this->cols = cols;
}

template <class Type>
void Matrix<Type>::setinValue(Type inValue)
{
	this->inValue = inValue;
}

template <class Type>
int Matrix<Type>::getRows()
{
	return rows;
}

template <class Type>
int Matrix<Type>::getCols()
{
	return cols;
}

template <class Type>
Type Matrix<Type>::getinValue()
{
	return inValue;
}

template <class Type>
Type** Matrix<Type>::getMatrix()
{
	return mat;
}

template<class Type>
Matrix<Type> Matrix<Type>::operator +(Matrix<Type>& obj)
{
	Matrix<Type> result(getRows(), getCols(), 0);

	if (this->rows == obj.rows && this->cols == obj.cols)
	{
		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < this->cols; j++)
			{
				result.mat[i][j] = this->mat[i][j] + obj.mat[i][j];
			}
		}
	}

	else
	{
		cout << "Bu iki matris toplama kurallarini saglamaz." << endl;

		exit(0);
	}

	return result;
}

template<class Type>
Matrix<Type> Matrix<Type>::operator -(Matrix<Type>& obj)
{

	Matrix<Type> result(getRows(), getCols(), 0);

	if (this->rows == obj.rows && this->cols == obj.cols)
	{
		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < this->cols; j++)
			{
				result.mat[i][j] = this->mat[i][j] - obj.mat[i][j];
			}
		}
	}

	else
	{
		cout << "Bu iki matris cikarma kurallarini saglamaz." << endl;

		exit(0);
	}

	return result;
}

template<class Type>
Matrix<Type> Matrix<Type>::operator *(Matrix<Type>& obj)
{

	Matrix<Type> result(getRows(), obj.cols, 0);

	if (this->cols == obj.rows)
	{
		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < obj.cols; j++)
			{
				for (int k = 0; k < obj.cols; k++)
				{
					result.mat[i][j] = result.mat[i][j] + (this->mat[i][k] * obj.mat[k][j]);
				}

			}
		}
	}

	else
	{
		cout << "Bu iki matris carpma kurallarini saglamaz." << endl;

		exit(0);
	}

	return result;
}

template<class Type>
void Matrix<Type>::emul(Matrix<Type>& obj)
{

	Matrix<Type> result(getRows(), getCols(), 1);

	if (this->rows == obj.rows && this->cols == obj.cols)
	{
		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < this->cols; j++)
			{
				this->mat[i][j] = this->mat[i][j] * obj.mat[i][j];
			}
		}
	}

	else
	{
		cout << "Bu iki matris carpma kurallarini saglamaz." << endl;

		exit(0);
	}

}

template<class Type>
Matrix<Type> Matrix<Type>::operator +(Type value)
{
	Matrix<Type> result(getRows(), getCols(), 0);


	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			result.mat[i][j] = this->mat[i][j] + value;
		}
	}

	return result;
}

template<class Type>
Matrix<Type> Matrix<Type>::operator -(Type value)
{
	Matrix<Type> result(getRows(), getCols(), 0);


	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			result.mat[i][j] = this->mat[i][j] - value;
		}
	}

	return result;
}

template<class Type>
Matrix<Type> Matrix<Type>::operator *(Type value)
{
	Matrix<Type> result(getRows(), getCols(), 0);


	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			result.mat[i][j] = this->mat[i][j] * value;
		}
	}

	return result;
}

template<class Type>
Matrix<Type> Matrix<Type>::operator /(Type value)
{
	Matrix<Type> result(getRows(), getCols(), 0);


	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			result.mat[i][j] = this->mat[i][j] / value;
		}
	}

	return result;
}

template<class Type>
Matrix<Type> Matrix<Type>::operator	%(Type value)
{
	Matrix<Type> result(getRows(), getCols(), 0);


	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			result.mat[i][j] = this->mat[i][j] % value;
		}
	}

	return result;
}

template<class Type>
Matrix<Type> Matrix<Type>::operator ^(Type value)
{
	Matrix<Type> result(getRows(), getCols(), 0);


	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			result.mat[i][j] = pow(this->mat[i][j], value);
		}
	}

	return result;
}

template <class Type>
Type** Matrix<Type>::generateMatrix(int rows, int cols, Type inValue)
{
	srand(time(NULL));

	Type** tempMatrix = new Type * [rows];

	for (int i = 0; i < rows; i++)
	{
		tempMatrix[i] = new Type[cols];
	}


	if (inValue == 'r' || inValue == 'R')
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				tempMatrix[i][j] = (Type)(rand() % 256);
			}
		}
	}

	else if (inValue == 'e' || inValue == 'E')
	{
		if (rows != cols)
		{
			cout << "Satir ve sutun sayisi esit olmayan bir matris birim matrise donusturulemez." << endl;

			exit(0);
		}
		else
		{
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
				{
					if (i == j) tempMatrix[i][j] = (Type)1;

					else tempMatrix[i][j] = (Type)0;
				}
			}
		}


	}

	else
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				tempMatrix[i][j] = inValue;
			}
		}
	}

	return tempMatrix;
}

template<class Type>
void Matrix<Type>::transpozeMatrix(int rows, int cols)
{
	this->cols = rows;
	this->rows = cols;

	Type** tempMatrix = new Type * [cols];

	for (int i = 0; i < cols; i++)
	{
		tempMatrix[i] = new Type[rows];
	}

	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			tempMatrix[i][j] = this->mat[j][i];
		}
	}

	for (int i = 0; i < rows; i++)
	{
		delete[] mat[i];
	}

	delete[] mat;

	this->mat = tempMatrix;

}

template <class Type>
void Matrix<Type>::inverseMatrix()
{
	Type** temp = new Type * [rows];

	for (int i = 0; i < this->rows; i++)
	{
		temp[i] = new Type[cols];
	}

	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			if (i == j) temp[i][j] = 1;

			else temp[i][j] = 0;
		}
	}

	float d, k;

	for (int i = 0; i < this->rows; i++)
	{
		d = this->mat[i][i];

		for (int j = 0; j < this->cols; j++)
		{
			this->mat[i][j] = this->mat[i][j] / d;
			temp[i][j] = temp[i][j] / d;
		}
		for (int x = 0; x < this->rows; x++)
		{
			if (x != i)
			{
				k = this->mat[x][i];

				for (int j = 0; j < this->cols; j++)
				{
					this->mat[x][j] = this->mat[x][j] - (this->mat[i][j] * k);
					temp[x][j] = temp[x][j] - (temp[i][j] * k);
				}
			}
		}

	}

	this->mat = temp;
}

template<class Type>
void Matrix<Type>::getCofactor(Type * *mat, Type * *temp, int p, int q, int n)
{
	int i = 0, j = 0;

	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
		{
			if (row != p && col != q)
			{
				temp[i][j++] = mat[row][col];

				if (j == n - 1)
				{
					j = 0;
					i++;
				}
			}
		}
	}
}

template<class Type>
int Matrix<Type>::determinantMatrix(Type * *mat, int size)
{
	int det = 0;


	if (size == 1) return mat[0][0];

	Type * *temp = new Type * [size];

	for (int counter = 0; counter < size; counter++)
	{
		temp[counter] = new Type[size];
	}

	int sign = 1;

	for (int h = 0; h < size; h++)
	{

		getCofactor(mat, temp, 0, h, size);

		det += sign * mat[0][h] * determinantMatrix(temp, size - 1);

		sign = -sign;
	}

	return det;
}

template <class Type>
void Matrix<Type>::print(string txtname)
{
	const int n = 10;

	fstream file;

	file.open(txtname, ios::out | ios::in | ios::app);

	file << "Matrisiniz asagidaki gibi olusturulmustur!" << endl;
	file << "------------------------------------------" << endl;


	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			file.setf(ios::left);
			file << setw(n) << this->mat[i][j] << setw(n);
		}
		file << setw(n) << endl << setw(n);
	}
	file << "------------------------------------------" << endl;
	file << endl;

	file.close();

}


template <class Type>
void Matrix<Type>::print()
{
	const int n = 3;

	cout << "Matrisiniz asagidaki gibi olusturulmustur!" << endl;
	cout << "------------------------------------------" << endl;
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{

			cout << setw(n) << this->mat[i][j] << setw(n) << " " << setw(n);
		}
		cout << setw(n) << endl << setw(n);
	}
	cout << "------------------------------------------" << endl << endl;


}

template<class Type>
void Matrix<Type>::resize(int newRows, int newCols)
{
	int oldRows = this->rows;
	int oldCols = this->cols;
	this->rows = newRows;
	this->cols = newCols;


	if (newRows <= 0 || newCols <= 0)
	{
		cout << "Matrisi yok edemezsiniz!" << endl;
		exit(0);
	}


	if (newRows > oldRows && newCols > oldCols)
	{
		Type** newMat = new Type * [newRows];

		for (int i = 0; i < newRows; i++)
		{
			newMat[i] = new Type[newCols];
		}

		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < this->cols; j++)
			{
				newMat[i][j] = 0;
			}
		}

		for (int i = 0; i < oldRows; i++)
		{
			for (int j = 0; j < oldCols; j++)
			{
				newMat[i][j] = this->mat[i][j];
			}
		}

		for (int i = 0; i < oldRows; i++)
		{
			delete[] mat[i];
		}

		delete[] mat;

		this->mat = newMat;
	}

	else if (newRows > oldRows && newCols < oldCols)
	{
		Type** newMat = new Type * [newRows];

		for (int i = 0; i < newRows; i++)
		{
			newMat[i] = new Type[newCols];
		}

		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < this->cols; j++)
			{
				newMat[i][j] = 0;
			}
		}

		for (int i = 0; i < oldRows; i++)
		{
			for (int j = 0; j < newCols; j++)
			{
				newMat[i][j] = this->mat[i][j];
			}
		}

		for (int i = 0; i < oldRows; i++)
		{
			delete[] mat[i];
		}

		delete[] mat;

		this->mat = newMat;
	}

	if (newRows < oldRows && newCols > oldCols)
	{
		Type** newMat = new Type * [newRows];

		for (int i = 0; i < newRows; i++)
		{
			newMat[i] = new Type[newCols];
		}

		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < this->cols; j++)
			{
				newMat[i][j] = 0;
			}
		}

		for (int i = 0; i < newRows; i++)
		{
			for (int j = 0; j < oldCols; j++)
			{
				newMat[i][j] = this->mat[i][j];
			}
		}

		for (int i = 0; i < oldRows; i++)
		{
			delete[] mat[i];
		}

		delete[] mat;

		this->mat = newMat;
	}

	if (newRows < oldRows && newCols < oldCols)
	{
		Type** newMat = new Type * [newRows];

		for (int i = 0; i < newRows; i++)
		{
			newMat[i] = new Type[newCols];
		}

		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < this->cols; j++)
			{
				newMat[i][j] = 0;
			}
		}

		for (int i = 0; i < newRows; i++)
		{
			for (int j = 0; j < newCols; j++)
			{
				newMat[i][j] = this->mat[i][j];
			}
		}

		for (int i = 0; i < oldRows; i++)
		{
			delete[] mat[i];
		}

		delete[] mat;

		this->mat = newMat;
	}



}

template<class Type>
Table<Type>::Table() :Matrix<Type>()
{
}

template<class Type>
Table<Type>::Table(int rows, int cols, Type inValue) : Matrix<Type>(rows, cols, inValue)
{
}

template<class Type>
Type Table<Type>::itemAt(int numberofRows, int numberofCols)
{
	return this->mat[numberofRows - 1][numberofCols - 1];
}

template<class Type>
Type Table<Type>::itemAt(string rowName, string colName)
{
	int rowSize = rowName.size();
	int colSize = colName.size();
	int rowCount;
	int colCount;

	if (rowSize > 1)
	{
		int left = 10 * char(rowName[0] - 48);
		int right = char(rowName[1] - 48);

		rowCount = left + right;

	}
	else
	{
		rowCount = char(rowName[0] - 48);
	}

	if (colSize > 1)
	{
		int left = 26 + char(colName[0] - 65);
		int right = char(colName[1] - 65);

		colCount = left + right;

	}
	else
	{
		colCount = char(colName[0] - 65);
	}

	return this->mat[rowCount - 1][colCount];
}

template<class Type>
Type Table<Type>::itemAt(string index)
{


	int	rowCount = char(index[1] - 48);
	/*int left= 10*char(index[1] - 48);
	int right= char(index[2] - 48);
	int rowCount = left + right;*/
	int	colCount = char(index[0] - 65);
	/*int left= 26+char(index[0] - 65);
	int right= char(index[1] - 65);
	int rowCount = left + right;*/


	return this->mat[rowCount - 1][colCount];

}

template<class Type>
void Table<Type>::print()
{
	const int n = 3;

	for (int i = 0; i < this->cols + 1; i++)
	{
		cout << setw(n) << colsName[i] << setw(n) << " " << setw(n);
	}

	cout << setw(n) << endl << setw(n);

	for (int i = 0; i < this->rows; i++)
	{
		cout << setw(n) << rowsName[i] << setw(n) << " " << setw(n);

		for (int j = 0; j < this->cols; j++)
		{
			cout << setw(n) << this->mat[i][j] << setw(n) << " " << setw(n);
		}
		cout << setw(n) << endl << setw(n);
	}
	cout << endl;
}

template <class Type>
void Table<Type>::setrowNames(string rNames[], int n)
{
	for (int i = 0; i < n; i++)
	{
		rowsName[i] = rNames[i];
	}

}

template <class Type>
void Table<Type>::setcolNames(string cNames[], int n)
{
	for (int i = 0; i < n; i++)
	{
		colsName[i + 1] = cNames[i];
	}

}

int main()
{
	int choose = 1;

	switch (choose)
	{
	case 1:
	{
		Matrix<double> a(2, 3, 1.);
		a.print();
		Matrix<double> b(2, 3, 9.);
		b.print();
		a = a*1. + b;
		a.print("file.txt");
		break;
	}
	case 2:
	{
		Matrix<double> m1(4, 4, 'e');
		Matrix<double> m2(4, 4, 'r');//5x5 matrisle de denenmeli
		m2.print();
		m1 = m1 * m2;
		m1.print();
		break;
	}
	case 3:
	{
		Matrix<double> m3(5, 4, 1);
		m3.print();
		//m3.resize(2,6);
		//m3.resize(10,6);
		m3.resize(10, 3);
		m3.print();
		break;
	}
	case 4:
	{
		Matrix<double> m4(2, 2, 'r');//savunmada soylenecek
		Matrix<double> m5 = m4;
		m5.print();
		cout << endl << endl;
		m4.inverseMatrix();
		m5 = m5 * m4;
		m5.print();//birim matris olmalı

		cout << "===============================" << endl;

		Matrix<double> m6(3, 3, 1);
		cout << m6.determinantMatrix(m6.getMatrix(), m6.getCols()) << endl;
		break;
	}
	case 5:
	{
		Table<int> t1(4, 4, 1);
		t1.print();
		string s[] = { "Sat1","Sat2" };
		t1.setrowNames(s, 2);
		t1.print();
		break;
	}
	case 6:
	{
		Table<int> t2(3, 4, 'r');
		t2.print();
		cout << t2.itemAt(1, 1) << endl;
		cout << t2.itemAt("A2") << endl;
		string s2[] = { "S1","S2","S3" };
		t2.setcolNames(s2, 3);
		t2.print();
		cout << endl << endl << t2.itemAt("1", "S2") << endl;
		break;
	}

	}
	return 0;
}
