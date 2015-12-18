#include "matrixarrt.h" 

#include <iostream> 

using namespace std; 

template<typename IndexType, typename ValueType>
MatrixArrT<IndexType, ValueType>::MatrixArrT(const IndexType rows, const IndexType cols)
    : rows_{rows},
      cols_{cols}
{ 
    data_ = new ValueType[rows_*cols_]{0};
} 

template<typename IndexType, typename ValueType>
MatrixArrT<IndexType, ValueType>::MatrixArrT(const IndexType rows, const IndexType cols, std::initializer_list<ValueType> vals)
    : rows_{ rows },
      cols_{ cols },
      data_{new ValueType[rows_*cols_]}
{ 
    std::uninitialized_copy(vals.begin(), vals.end(), data_); 
} 

template<typename IndexType, typename ValueType>
MatrixArrT<IndexType, ValueType>::~MatrixArrT()
{ 
    delete[] data_; 
} 

template<typename IndexType, typename ValueType>
MatrixArrT<IndexType, ValueType>& MatrixArrT<IndexType, ValueType>::transpose()
{
    MatrixArrT<IndexType, ValueType> t( cols_, rows_ );
 
    for (IndexType i{ 0 }; i != rows_; ++i)
    {
        for (IndexType j{ 0 }; j != cols_; ++j)
        {
            t.data_[j*rows_ + i] = data_[i*cols_ + j];
        }
    }
    swap(t);

    return *this;
}

template<typename IndexType, typename ValueType>
std::ostream& MatrixArrT<IndexType, ValueType>::print(std::ostream& ostrm) const
{
    cout << endl;
    if ((rows_ != 0) && (cols_ != 0))
    {
        for (IndexType i{ 0 }; i < rows_; ++i)
        {
            cout << ((0 == i) ? '(' : ' ');
            for (IndexType j{ 0 }; j < cols_- 1; ++j) 
            {
                cout << data_[i*cols_ + j] << ',';
            }
            cout << data_[i*cols_ + cols_ - 1] << ((i == rows_ - 1) ? ')' : ' ') << endl;
        }
    }
    else cout << "( )" << endl;
    return ostrm;
}

template<typename IndexType, typename ValueType>
ValueType& MatrixArrT<IndexType, ValueType>::operator()(const IndexType irow, const IndexType icol)
{
    if ((irow < 0) || (rows_ <= irow) || (icol < 0) || (cols_ <= icol))
    { 
        throw out_of_range("index out of range in MatrixArrT::operator()"); 
    } 
    return data_[irow*cols_ + icol]; 
} 

template<typename IndexType, typename ValueType>
const ValueType& MatrixArrT<IndexType, ValueType>::operator()(const IndexType irow, const IndexType icol) const
{ 
    if ((irow < 0) || (rows_ <= irow) || (icol < 0) || (cols_ <= icol))
    {
        throw out_of_range("index out of range in MatrixArrT::operator()");
    }
    return data_[irow*cols_ + icol];
}

template<typename IndexType, typename ValueType>
void MatrixArrT<IndexType, ValueType>::swap(MatrixArrT<IndexType, ValueType>& m)
{ 
    IndexType rows{m.rows_}; 
    m.rows_ = rows_; 
    rows_ = rows; 

    IndexType cols{ m.cols_ };
    m.cols_ = cols_;
    cols_ = cols;

    ValueType* data{m.data_}; 
    m.data_ = data_; 
    data_ = data; 
} 

template<typename IndexType, typename ValueType>
MatrixArrT<IndexType, ValueType>& MatrixArrT<IndexType, ValueType>::operator+=(const ValueType rhs)
{ 
    for (IndexType i{ 0 }; i != rows_; ++i)
    {
        for (IndexType j{ 0 }; j != cols_; ++j)
        {
            data_[i*cols_ + j] += rhs;
        }
    }
    return *this;
} 

template<typename IndexType, typename ValueType>
MatrixArrT<IndexType, ValueType>& MatrixArrT<IndexType, ValueType>::operator-=(const ValueType rhs)
{ 
    for (IndexType i{ 0 }; i != rows_; ++i)
    {
        for (IndexType j{ 0 }; j != cols_; ++j)
        {
            data_[i*cols_ + j] -= rhs;
        }
    }
    return *this; 
} 

template<typename IndexType, typename ValueType>
MatrixArrT<IndexType, ValueType>& MatrixArrT<IndexType, ValueType>::operator*=(const ValueType rhs)
{ 
    for (IndexType i{ 0 }; i != rows_; ++i)
    {
        for (IndexType j{ 0 }; j != cols_; ++j)
        {
            data_[i*cols_ + j] *= rhs;
        }
    }
    return *this;
} 

// оператор сложения матриц
template<typename IndexType, typename ValueType>
MatrixArrT<IndexType, ValueType>& operator+(MatrixArrT<IndexType, ValueType>& lhs, MatrixArrT<IndexType, ValueType>& rhs)
{
    IndexType  r = rhs.nRows();
    IndexType  c = rhs.nCols();

    MatrixArrT<IndexType, ValueType> summ( r, c );

    if ((lhs.nRows() == r) && (lhs.nCols() == c))
    {
        for (IndexType i{ 0 }; i != r; ++i)
        {
            for (IndexType j{ 0 }; j != c; ++j)
            {
                (*(summ.begin() + i*c + j)) = (*(lhs.begin() + i*c + j)) + (*(rhs.begin() + i*c + j));
            }
        }
        summ.print(cout);
        return summ;
    }
    try {
        throw std::runtime_error("Error: ");
    }
    catch (const std::runtime_error & e) {
        cout << "Mismatch MatrixArrT dimensions: ";
    }
    return lhs;
}

template<typename IndexType, typename ValueType>
MatrixArrT<IndexType, ValueType>& operator-(MatrixArrT<IndexType, ValueType>& v)
{
    for (IndexType i{ 0 }; i < v.nRows(); i += 1)
    {
        for (IndexType j{ 0 }; j < v.nCols(); j += 1)
        {
            *(v.begin() + i*v.nCols() + j) = -(*(v.begin() + i*v.nCols() + j));
        }
    }
    return v;
}

// оператор вычитания матриц
template<typename IndexType, typename ValueType>
MatrixArrT<IndexType, ValueType>& operator-(MatrixArrT<IndexType, ValueType>& lhs, MatrixArrT<IndexType, ValueType>& rhs)
{
    IndexType  r = rhs.nRows();
    IndexType  c = rhs.nCols();

    MatrixArrT<IndexType, ValueType> subt(r, c);

    if ((lhs.nRows() == r) && (lhs.nCols() == c))
    {
        for (IndexType i{ 0 }; i != r; ++i)
        {
            for (IndexType j{ 0 }; j != c; ++j)
            {
                (*(subt.begin() + i*c + j)) = (*(lhs.begin() + i*c + j)) - (*(rhs.begin() + i*c + j));
            }
        }
        subt.print(cout);
        return subt;
    }
    try {
        throw std::runtime_error("Error: ");
    }
    catch (const std::runtime_error & e) {
        cout << "Mismatch MatrixArrT dimensions: ";
    }
    return lhs;
}

// оператор умножения матриц
template<typename IndexType, typename ValueType>
MatrixArrT<IndexType, ValueType>& operator*(MatrixArrT<IndexType, ValueType>& lhs, MatrixArrT<IndexType, ValueType>& rhs)
{
    IndexType  r = lhs.nRows();
    IndexType  c = rhs.nCols();

    MatrixArrT<IndexType, ValueType> mult(r, c);

    if (lhs.nCols() == rhs.nRows())
    {
        for (IndexType i{ 0 }; i != r; ++i)
        {
            for (IndexType k{ 0 }; k != c; ++k)
            {
                for (IndexType j{ 0 }; j != rhs.nRows(); ++j)
                {
                    (*(mult.begin() + i*c + k)) += (*(lhs.begin() + i*lhs.nCols() + j)) * (*(rhs.begin() + j*c + k));
                }
            }
        }
        mult.print(cout);
        return mult;
    }
    try {
        throw std::runtime_error("Error: ");
    }
    catch (const std::runtime_error & e) {
        cout << "No concurrent matrix: ";
    }
    return lhs;
}

// оператор равенства
template<typename IndexType, typename ValueType>
bool operator==(MatrixArrT<IndexType, ValueType>& lhs, MatrixArrT<IndexType, ValueType>& rhs)
{
    IndexType  r = rhs.nRows();
    IndexType  c = rhs.nCols();

    if ((lhs.nRows() == r) && (lhs.nCols() == c))
    {
        for (IndexType i{ 0 }; i != r; ++i)
        {
            for (IndexType j{ 0 }; j != c; ++j)
            {
                if (*(lhs.begin() + i*c + j) != *(rhs.begin() + i*c + j))
                {
                    return false;
                }
            }
        }
        return true;
    }
    else return false;
}

// неравенство
template<typename IndexType, typename ValueType>
bool operator!=(MatrixArrT<IndexType, ValueType>& lhs, MatrixArrT<IndexType, ValueType>& rhs)
{
    return !(lhs == rhs);
}

template<typename IndexType, typename ValueType>
std::ostream& operator<<(std::ostream& ostrm, const MatrixArrT<IndexType, ValueType>& m)
{
    return m.print(ostrm);
}

