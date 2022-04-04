//
// DD1388 - Lab 2: The matrix
//

#pragma once

#include <initializer_list>
#include <iostream>
#include <stdexcept>

template <typename T>
class Matrix {
    static_assert(std::is_move_constructible<T>::value, "T must be move constructible");
    static_assert(std::is_move_assignable<T>::value, "T must be move-assignable");

public:
    // constructors and assignment operators
    explicit Matrix();
    explicit Matrix(size_t dim);
    explicit Matrix(size_t rows, size_t cols);
    explicit Matrix(const std::initializer_list<T>& list);
    Matrix(Matrix<T>& other);
    Matrix(Matrix<T>&& other) noexcept;

    Matrix<T>& operator=(const Matrix<T>& other);
    Matrix<T>& operator=(Matrix<T>&& other) noexcept;

    ~Matrix();

    // accessors
    size_t rows() const;
    size_t cols() const;

    T& operator()(size_t row, size_t col);
    const T& operator()(size_t row, size_t col) const;

    // operators
    Matrix<T> operator*(const Matrix<T>& other) const;
    Matrix<T> operator+(const Matrix<T>& other) const;
    Matrix<T> operator-(const Matrix<T>& other) const;

    void operator*=(const Matrix<T>& other);
    void operator+=(const Matrix<T>& other);
    void operator-=(const Matrix<T>& other);

    // methods
    void reset();

    void insert_row(size_t row);
    void append_row(size_t row);
    void remove_row(size_t row);
    void insert_column(size_t col);
    void append_column(size_t col);
    void remove_column(size_t col);

    // iterators
    typedef T* iterator;

    iterator begin();
    iterator end();

private:
    size_t m_rows;
    size_t m_cols;
    size_t m_capacity;
    T* m_vec;
};

// input/output operators
template<typename T>
std::istream& operator>>(std::istream& is, Matrix<T>& m);

template<typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& m);

// functions
template<typename T>
Matrix<T> identity(size_t dim);


//
// Implementations
//

template<typename T>
Matrix<T>::Matrix()
{   //initializes all the values for an object without arguments

    m_rows = 0;
    m_cols = 0;
    m_capacity = 0;
    m_vec = new T[0];
}

template<typename T>
Matrix<T>::Matrix(size_t dim)
{   //Initializes values for a square matrix with dimensions dim*dim
    m_rows = dim;
    m_cols = dim;
    m_capacity = m_rows * m_cols;
    m_vec = new T[m_capacity];
    for (int i = 0; i < m_capacity; i++) {
        m_vec[i] = 0;
    }
}

template<typename T>
Matrix<T>::Matrix(size_t rows, size_t cols)
{   //initializes values for a matrix with dimensions rows*cols
    m_rows = rows;
    m_cols = cols;
    m_capacity = m_rows * m_cols;
    m_vec = new T[m_capacity];
    for (int i = 0; i < m_capacity; i++) {
        m_vec[i] = 0;
    }
}

template<typename T>
Matrix<T>::Matrix(const std::initializer_list<T>& list)
{   //initializes values for a square matrix with items specified in list
    try {
        if (int(sqrt(list.size())) != sqrt(list.size())) { //checks if even square root
            throw std::out_of_range("list size must be an even square root");
        }
    }
    catch (const std::out_of_range& oor) {
        std::cerr << "Out of Range error: " << oor.what() << '\n';
    }
    int x = sqrt(list.size());
    m_rows = x;
    m_cols = x;
    m_capacity = m_rows * m_cols;
    m_vec = new T[m_capacity];
    int i = 0;
    int j = 0;
    for (auto k : list) { //adds all the items from the list to the matrix vector
        m_vec[j * m_rows + i] = k;//j is column index and i is row index
        j += 1; //iterate through columns
        if (j == x) { //when a column has been iterated set column index to zero and go to next row
            j = 0;
            i += 1;
        }
    }
}

template<typename T>
Matrix<T>::Matrix(Matrix<T>& other)
{ //Copy constructor
    m_rows = other.m_rows;
    m_cols = other.m_cols;
    m_capacity = other.m_capacity;
    m_vec = new T[other.m_capacity]; //deep copy for the vector so the objects doesn't share pointers
    for (int i = 0; i < other.m_rows; i++) {
        for (int j = 0; j < other.m_cols; j++) {
            m_vec[j * m_rows + i] = other.m_vec[j * m_rows + i];
        }
    }
}

template<typename T>
Matrix<T>::Matrix(Matrix<T>&& other) noexcept
{ //Move constructor
    m_rows = other.m_rows;
    m_cols = other.m_cols;
    m_capacity = other.m_capacity;
    m_vec = other.m_vec;
    other.m_rows = 0;
    other.m_cols = 0;
    other.m_capacity = 0;
    other.m_vec = nullptr;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other)
{   //copy-assignment constructor
    if (this != &other) { //checks so that the objects doesn't have the same address
        m_rows = other.m_rows;
        m_cols = other.m_cols;
        m_capacity = other.m_rows * other.m_cols;
        m_vec = new T[other.m_capacity]; //deep copy for the vector
        for (int i = 0; i < other.m_rows; i++) {
            for (int j = 0; j < other.m_cols; j++) {
                m_vec[j * m_rows + i] = other.m_vec[j * m_rows + i];
            }
        }
    }
    return *this; //returns the object
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& other) noexcept
{ //move assignment constructor
    if (this != &other) {//checks so addresses aren't the same
        m_rows = other.m_rows;
        m_cols = other.m_cols;
        m_capacity = other.m_capacity;
        m_vec = other.m_vec; //no deep copy needed
        other.m_rows = 0;
        other.m_cols = 0;
        other.m_capacity = 0;
        other.m_vec = nullptr;
    }
    return *this;
}


template<typename T>
Matrix<T>::~Matrix() { //Destructor
    delete[] m_vec;
}

template<typename T>
size_t Matrix<T>::rows() const { //returns number of rows
    return m_rows;
}

template<typename T>
size_t Matrix<T>::cols() const { // returns number of columns
    return m_cols;
}

template<typename T>
T& Matrix<T>::operator()(size_t row, size_t col) { //allows to set matrix values by matrix(i,j) = value;
    return m_vec[col * m_rows + row]; //matrix(i,j) corresponds to m_vec[j*m_rows + i]
}

template<typename T>
const T& Matrix<T>::operator()(size_t row, size_t col) const {//read only access for const declared functions to matrix(i,j) 
    return m_vec[col * m_rows + row];
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const {// Allows matrix multiplication A*B
    Matrix<T> m(m_rows, other.m_cols); //If C = AB then C(i,j) is the sum from k = 1 to B_rows of A(i,k)*B(k,j).
    for (int i = 0; i < m_rows; i++) { //index of row
        for (int j = 0; j < other.m_cols; j++) { //index of column 
            int sum = 0;
            for (int k = 0; k < other.m_rows; k++) { // sumation over k 
                sum += (m_vec[k * m_rows + i] * other.m_vec[j * other.m_rows + k]);
            }
            m(i, j) = sum;
        }
    }
    return m;
}
template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const {//allows matrix addition by matrix1 + matrix2
    Matrix<T> m(m_rows, m_cols);
    for (int i = 0; i < m_capacity; i++) {
        m.m_vec[i] = m_vec[i] + other.m_vec[i]; //adding element by element
    }
    return m;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) const { // allows matrix subtraction by matrix1 - matrix2
    Matrix<T> m(m_rows, m_cols);
    for (int i = 0; i < m_capacity; i++) {
        m.m_vec[i] = m_vec[i] - other.m_vec[i]; //subtracting element by element
    }
    return m;
}

template<typename T>
void Matrix<T>::operator*=(const Matrix<T>& other) {
    Matrix<T> m(m_rows, other.m_cols); //If C = AB then C(i,j) is the sum from k = 1 to B_rows of A(i,k)*B(k,j).
    for (int i = 0; i < m_rows; i++) { //index of row
        for (int j = 0; j < other.m_cols; j++) { //index of column 
            int sum = 0;
            for (int k = 0; k < other.m_rows; k++) { // sumation over k 
                sum += (m_vec[k * m_rows + i] * other.m_vec[j * other.m_rows + k]);
            }
            m(i, j) = sum; //stors result in temporary matrix
        }
    }
    for (int i = 0; i < m.m_capacity; i++) { //copies result from temporary matrix to m_vec
        m_vec[i] = m.m_vec[i];
    }
}

template<typename T>
void Matrix<T>::operator+=(const Matrix<T>& other) {// allows matrix addition by m1 += m2
    for (int i = 0; i < other.m_capacity; i++) {
        this->m_vec[i] += other.m_vec[i]; //adding element by element
    }
}

template<typename T>
void Matrix<T>::operator-=(const Matrix<T>& other) { // allows matrix subtraction by m1 -= m2
    for (int i = 0; i < other.m_capacity; i++) {
        this->m_vec[i] -= other.m_vec[i]; //subtraction element by element
    }
}

template<typename T>
void Matrix<T>::reset() { //sets all elements in matrix to zero
    for (int i = 0; i < m_capacity; i++) {
        m_vec[i] = 0;
    }
}

template<typename T>
void Matrix<T>::insert_row(size_t row) { //inserts a row before row argument
    m_rows += 1; //number of rows is one more
    m_capacity += m_cols; //the capacity is increased by the number of columns
    T* temp_vec = new T[m_capacity];
    for (int i = 0; i < row; i++) { //adds the rows before row argument to a new temporary vector
        for (int j = 0; j < m_cols; j++) {
            temp_vec[j * m_rows + i] = m_vec[(j * (m_rows - 1)) + i];
        }
    }
    for (int i = 0; i < m_cols; i++) { //adds the new row at the row argument
        temp_vec[i * m_rows + row] = 0;
    }
    for (int i = row + 1; i < m_rows; i++) { //adds the rest of the rows after the new row
        for (int j = 0; j < m_cols; j++) {
            temp_vec[j * m_rows + i] = m_vec[(j * (m_rows - 1)) + (i - 1)];
        }
    }
    delete[] m_vec;
    m_vec = new T[m_capacity]; //creates new m_vec with the right size
    for (int i = 0; i < m_capacity; i++) { //copies over the temporary vector to m_vec
        m_vec[i] = temp_vec[i];
    }
    delete[] temp_vec; //the temporary vector can now be deleted
}

template<typename T>
void Matrix<T>::append_row(size_t row) {//adds row after the row argument
    m_rows += 1; //number of rows is one more
    m_capacity += m_cols; //capacity is increased by number of columns
    T* temp_vec = new T[m_capacity];
    for (int i = 0; i < row + 1; i++) { //adds all the rows before the new row to a temporary vector
        for (int j = 0; j < m_cols; j++) {
            temp_vec[j * m_rows + i] = m_vec[(j * (m_rows - 1)) + i];
        }
    }
    for (int i = 0; i < m_cols; i++) { //adds the new row to the temporary vector
        temp_vec[i * m_rows + (row + 1)] = 0;
    }
    for (int i = row + 2; i < m_rows; i++) {//adds all the rows after the new row
        for (int j = 0; j < m_cols; j++) {
            temp_vec[j * m_rows + i] = m_vec[(j * (m_rows - 1)) + (i - 1)];
        }
    }
    delete[] m_vec;
    m_vec = new T[m_capacity];//creates new vector of the right size
    for (int i = 0; i < m_capacity; i++) { // copies temporary vector to new vector
        m_vec[i] = temp_vec[i];
    }
    delete[] temp_vec; // the temporary vector can now be deleted
}

template<typename T>
void Matrix<T>::remove_row(size_t row) { //removes a row at the row argument
    m_rows -= 1; //number of rows is one less
    m_capacity -= m_cols; // capacity decreases by number of columns
    T* temp_vec = new T[m_capacity];
    for (int i = 0; i < row; i++) { //adds all the rows before the removed row to a temporary vector
        for (int j = 0; j < m_cols; j++) {
            temp_vec[j * m_rows + i] = m_vec[(j * (m_rows + 1)) + i];
        }
    }

    for (int i = row; i < m_rows; i++) { //adds all the rows after the removed row
        for (int j = 0; j < m_cols; j++) {
            temp_vec[j * m_rows + i] = m_vec[(j * (m_rows + 1)) + (i + 1)];
        }
    }
    delete[] m_vec;
    m_vec = new T[m_capacity]; //new vector of right size is created
    for (int i = 0; i < m_capacity; i++) {//copies the temporary vector to the new vector
        m_vec[i] = temp_vec[i];
    }
    delete[] temp_vec;// the temporary vector can now be deleted
}

template<typename T>
void Matrix<T>::insert_column(size_t col) {//adds column before the given argument
    m_cols += 1; //same implementation as insert_row but with columns and rows switched
    m_capacity += m_rows;
    T* temp_vec = new T[m_capacity];
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < m_rows; j++) {
            temp_vec[i * m_rows + j] = m_vec[i * m_rows + j];
        }
    }
    for (int i = 0; i < m_rows; i++) {
        temp_vec[col * m_rows + i] = 0;
    }
    for (int i = col + 1; i < m_cols; i++) {
        for (int j = 0; j < m_rows; j++) {
            temp_vec[i * m_rows + j] = m_vec[(i - 1) * m_rows + j];
        }
    }
    delete[] m_vec;
    m_vec = new T[m_capacity];
    for (int i = 0; i < m_capacity; i++) {
        m_vec[i] = temp_vec[i];
    }
    delete[] temp_vec;
}

template<typename T>
void Matrix<T>::append_column(size_t col) { //adds column after the given argument
    m_cols += 1; //same implementation as append_rows but with rows and columns switched
    m_capacity += m_rows;
    T* temp_vec = new T[m_capacity];
    for (int i = 0; i < col + 1; i++) {
        for (int j = 0; j < m_rows; j++) {
            temp_vec[i * m_rows + j] = m_vec[i * m_rows + j];
        }
    }
    for (int i = 0; i < m_rows; i++) {
        temp_vec[(col + 1) * m_rows + i] = 0;
    }
    for (int i = col + 2; i < m_cols; i++) {
        for (int j = 0; j < m_rows; j++) {
            temp_vec[i * m_rows + j] = m_vec[(i - 1) * m_rows + j];
        }
    }
    delete[] m_vec;
    m_vec = new T[m_capacity];
    for (int i = 0; i < m_capacity; i++) {
        m_vec[i] = temp_vec[i];
    }
    delete[] temp_vec;
}

template<typename T>
void Matrix<T>::remove_column(size_t col) { //removes a column at the given argument
    m_cols -= 1; // same implementation as remove_row but with rows and columns switched
    m_capacity -= m_rows;
    T* temp_vec = new T[m_capacity];
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < m_rows; j++) {
            temp_vec[i * m_rows + j] = m_vec[(i * m_rows) + j];
        }
    }

    for (int i = col; i < m_cols; i++) {
        for (int j = 0; j < m_rows; j++) {
            temp_vec[i * m_rows + j] = m_vec[((i + 1) * m_rows) + j];
        }
    }
    delete[] m_vec;
    m_vec = new T[m_capacity];
    for (int i = 0; i < m_capacity; i++) {
        m_vec[i] = temp_vec[i];
    }
    delete[] temp_vec;
}


template<typename T>
typename Matrix<T>::iterator Matrix<T>::begin() { //returns beginning of matrix vector
    return m_vec;
}

template<typename T>
typename Matrix<T>::iterator Matrix<T>::end() { //returns end of matrix vector
    return m_vec + m_capacity;
}

template<typename T>
std::istream& operator>>(std::istream& is, Matrix<T>& m) { //reads a matrix from the console
    for (int i = 0; i < m.rows(); i++) {
        for (int j = 0; j < m.cols(); j++) {
            is >> m(i, j);
        }
    }
    return is;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& m) { //prints a matrix to the console
    for (int i = 0; i < m.rows(); i++) {
        for (int j = 0; j < m.cols(); j++) {
            os << m(i, j) << " ";
        }
        os << std::endl << std::endl;
    }
    return os;
}

template<typename T>
Matrix<T> identity(size_t dim) { //creates an identity matrix with dimension dim
    Matrix<T> m(dim);
    for (int i = 0; i < dim; i++) {
        m(i, i) = 1;
    }
    return m;
}


