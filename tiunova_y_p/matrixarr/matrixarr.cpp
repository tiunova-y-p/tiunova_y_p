#include "matrixarr.h" 

#include <cassert>
#include <iostream> // ***

using namespace std; 

using ValueType = int32_t;
using IndexType = ptrdiff_t;

MatrixArr::MatrixArr(const IndexType rows, const IndexType cols)
    : rows_{rows},
      cols_{cols}
{ 
    data_ = new ValueType[rows_*cols_]{0};
} 

MatrixArr::MatrixArr(const IndexType rows, const IndexType cols, std::initializer_list<ValueType> vals)
    : rows_{ rows },
      cols_{ cols },
      data_{new ValueType[rows_*cols_]}
{ 
    std::uninitialized_copy(vals.begin(), vals.end(), data_); 
} 

MatrixArr::~MatrixArr() 
{ 
    delete[] data_; 
} 

std::ostream& MatrixArr::print(std::ostream& ostrm) const
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

ValueType& MatrixArr::operator()(const IndexType irow, const IndexType icol)
{
    assert(irow >= 0 && irow < rows_ && icol >= 0 && icol < cols_);
    if ((irow < 0) || (rows_ <= irow) || (icol < 0) || (cols_ <= icol))
    { 
        throw out_of_range("index out of range in MatrixArr::operator()"); 
    } 
    return data_[irow*cols_ + icol]; 
} 

const ValueType& MatrixArr::operator()(const IndexType irow, const IndexType icol) const
{ 
    assert(irow >= 0 && irow < rows_ && icol >= 0 && icol < cols_);
    if ((irow < 0) || (rows_ <= irow) || (icol < 0) || (cols_ <= icol))
    {
        throw out_of_range("index out of range in MatrixArr::operator()");
    }
    return data_[irow*cols_ + icol];
}

void MatrixArr::swap(MatrixArr& m) 
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

MatrixArr& MatrixArr::operator-() 
{ 
    MatrixArr res(rows_, cols_);
    IndexType k;
    for (IndexType i{0}; i < rows_; i += 1) 
    { 
        for (IndexType j{ 0 }; j < cols_; j += 1)
        {
            k = i*cols_ + j;
            res.data_[k] = -data_[k];
        }
    } 
    swap(res);

    return *this; 
} 

//MatrixArr& MatrixArr::operator+=(const MatrixArr& rhs) 
//{ 
//    // TODO 
//    for (IndexType i{ 0 }; i != rows_; ++i)
//    {
//        for (IndexType j{ 0 }; j < cols_; j += 1)
//        {
//            data_[i][j] += rhs.data_[i][j];
//    }
//    return *this; 
//} 

MatrixArr& MatrixArr::operator+=(const ValueType rhs) 
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

//MatrixArr& MatrixArr::operator-=(const MatrixArr& rhs) 
//{ 
//    for (IndexType i{0}; i != dims_; ++i) 
//    { 
//        data_[i] -= rhs.data_[i]; 
//    } 
//    return *this; 
//} 

MatrixArr& MatrixArr::operator-=(const ValueType rhs) 
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

MatrixArr& MatrixArr::operator*=(const ValueType rhs) 
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

// оператор сложения
MatrixArr& operator+(MatrixArr& lhs, MatrixArr& rhs)
{
    IndexType  r = rhs.nRows();
    IndexType  c = rhs.nCols();

    if ((lhs.nRows() == r) && (lhs.nCols() == c))
    {
        for (IndexType i{ 0 }; i != r; ++i)
        {
            for (IndexType j{ 0 }; j != c; ++j)
            {
                (*(lhs.begin() + i*c + j) += *(rhs.begin() + i*c + j));
            }
        }
        return lhs;
    }
    try {
        throw std::runtime_error("Error: ");
    }
    catch (const std::runtime_error & e) {
        cout << "Mismatch MatrixArr dimensions: ";
    }
    return lhs;
};

/*
MatrixArr operator+(MatrixArr& lhs, const ValueType rhs) { return MatrixArr(lhs) += rhs; }

// оператор разности
MatrixArr operator-(MatrixArr& lhs, MatrixArr& rhs)
{

    if (lhs.dim() == rhs.dim()) return MatrixArr(lhs) -= rhs;

    try {
        throw std::runtime_error("Mismatch MatrixArr dimensions");
    }
    catch (const std::runtime_error & e) {
        cout << "Mismatch MatrixArr dimensions: ";
    }
    return lhs;
};

MatrixArr operator-(MatrixArr& lhs, const ValueType rhs) { return MatrixArr(lhs) -= rhs; }
// оператор умножения вектора на число
MatrixArr operator*(MatrixArr& lhs, const ValueType rhs) { return MatrixArr(lhs) *= rhs; }
MatrixArr operator*(const ValueType lhs, MatrixArr& rhs) { return MatrixArr(rhs) *= lhs; }
// оператор деления вектора на число
MatrixArr operator/(MatrixArr& lhs, const ValueType rhs) { return MatrixArr(lhs) /= rhs; }
*/

// оператор равенства
bool operator==(MatrixArr& lhs, MatrixArr& rhs)
{
    IndexType  r = rhs.nRows();
    IndexType  c = rhs.nCols();

    if ((lhs.nRows() == r) && (lhs.nCols() == c))
    {
        for (IndexType i{ 0 }; i != r; ++i)
        {
            for (IndexType j{ 0 }; j != c; ++j)
            {
                if (*(lhs.begin() + i*c + j) != *(rhs.begin() + i*c + j));
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
bool operator!=(MatrixArr& lhs, MatrixArr& rhs)
{
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& ostrm, const MatrixArr& m)
{
    return m.print(ostrm);
}

