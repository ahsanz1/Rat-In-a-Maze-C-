#include<iostream>
using namespace std;

template <class T>
class Array
{
	template <class T> friend ostream& operator<<(ostream&, const Array<T>&);
private:
	T* arrPtr;
	int row;
	int col;      //pointer to array of total dimensions entered by user
	int maxSize;               //size of linear array obtained after multiplying all dimensions

public:
	Array();
	Array(int, int);
	Array(const Array<T>&);
	int CalculateOffset(int, int);
	void insert(int, char);
	void extend();
	void shrink();
	void deleteElement(T&);
	int GetCols();
	int GetRows();
	T* GetArray();
	int GetMaxSize();
	int getRowNo(int);
	int getColNo(int);
	T& operator=(const Array<T>&);
	T retrieve();
	~Array();
};

template <class T>
Array<T>::Array()                                      //default array size=10
{
	row = 4;
	col = 4;
	maxSize = 16;
	arrPtr = new T[maxSize];
}

template <class T>
Array<T>::~Array()
{
	delete[] arrPtr;
}

template <class T>
int Array<T>::GetCols()
{
	return col;
}

template <class T>
int Array<T>::GetRows()
{
	return row;
}

template <class T>
T* Array<T>::GetArray()
{
	return arrPtr;
}

template <class T>
int Array<T>::GetMaxSize()
{
	return maxSize;
}

template <class T>
Array<T>::Array(int x = 4, int y = 4)
{
	row = x + 1;                 //to generate an n*n playing field, arguments are incremented
	col = y + 1;
	maxSize = row * col;

	arrPtr = new T[maxSize];
}

template <class T>
Array<T>::Array(const Array<T>& obj)
{
	row = obj.row;
	col = obj.col;
	delete[] arrPtr;

	maxSize = obj.maxSize;
	arrPtr = new T[maxSize];

	for (int i = 0; i < maxSize; i++)
	{
		arrPtr[i] = obj.arrPtr[i];
	}
}

template <class T>
int Array<T>::CalculateOffset(int x, int y)
{
	int offset = 0;
	offset = x*col + y;

	if (offset < 0)
		offset = offset* -1;
	return offset;
}

template <class T>
int Array<T>::getRowNo(int offset)
{
	return offset / col;
}

template <class T>
int Array<T>::getColNo(int offset)
{
	int x = offset / col;
	return offset - (x*col);
}

template <class T>
void Array<T>::insert(int offset, char value)
{
	/*int r, c;
	r = this->getRowNo(offset);
	c = this->getColNo(offset);
*/
	arrPtr[offset] = value;
}

template <class T>
T& Array<T>::operator=(const Array<T>& obj)
{
	if (this != &obj)
	{
		delete[] arrPtr;
		row = obj.row;
		col = obj.col;
		maxSize = obj.maxSize;
		arrPtr = new T[maxSize];

		for (int i = 0; i < maxSize; i++)
		{
			arrPtr[i] = obj.arrPtr[i];
		}
	}

	return *this;
}

template <class T>
void Array<T>::deleteElement(T& element)
{
	for (int i = 0; i < maxSize; i++)         //to make sure operation stays in O(1), replace current element with next
	{
		if (arrPtr[i] == element)
			arrPtr[i] = arrPtr[i + 1];
	}
}

template <class T>
T Array<T>::retrieve()
{
	int row, col;
	int offset = 0;
	cout << "Enter Indexes You Want to Retrieve Element From: " << endl;
	cin >> row >> col;

	offset = CalculateOffset(row, col);

	if (offset >= maxSize)
		cout << "Index Out of Bounds!" << endl;
	else
		return arrPtr[offset];
}


template <class T>
void Array<T>::extend()
{
	T* tempArr = new T[maxSize];
	int tempSize = maxSize;

	for (int i = 0; i < maxSize; i++)
	{
		tempArr[i] = arrPtr[i];
	}

	delete[] arrPtr;

	row = row * 2;
	col = col * 2;
	maxSize = row*col;            //to extend array, original dimensions are doubled and maxSize calculated afterwards
	                             
	arrPtr = new T[maxSize];

	for (int i = 0; i < tempSize; i++)
	{
		arrPtr[i] = tempArr[i];
	}
	delete[] tempArr;
}

template <class T>
void Array<T>::shrink()
{
	T* tempArr = new T[maxSize];

	for (int i = 0; i < maxSize; i++)
	{
		tempArr[i] = arrPtr[i];
	}

	delete[] arrPtr;
	arrPtr = new T[maxSize / 2];
	maxSize = maxSize / 2;

	for (int i = 0; i < maxSize; i++)
	{
		arrPtr[i] = tempArr[i];
	}

	delete[] tempArr;
}

template <class T>
ostream& operator<<(ostream& obj, const Array<T>& arrObj)
{
	int rowCheck = 0;
	for (int i = 0; i < arrObj.maxSize; i += arrObj.col)
	{
		for (int j = i; rowCheck < arrObj.col; rowCheck++, j++)
		{
			cout << arrObj.arrPtr[j] << " ";
		}
		cout << endl;
		rowCheck = 0;
	}

	return obj;
}

void menu()
{
	cout << "Press 1 to Insert an Element." << endl;
	cout << "Press 2 to Delete an Element." << endl;
	cout << "Press 3 to Extend Array." << endl;
	cout << "Press 4 to Shrink Array." << endl;
	cout << "Press 5 to Retrieve an Element." << endl;
	cout << "Press 6 to Print All Elements." << endl;
	cout << "Press e to EXIT." << endl;
}

