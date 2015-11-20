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

MatrixArr& MatrixArr::transpose()
{
    MatrixArr t( cols_, rows_ );
 
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
    //assert(irow >= 0 && irow < rows_ && icol >= 0 && icol < cols_);
    if ((irow < 0) || (rows_ <= irow) || (icol < 0) || (cols_ <= icol))
    { 
        throw out_of_range("index out of range in MatrixArr::operator()"); 
    } 
    return data_[irow*cols_ + icol]; 
} 

const ValueType& MatrixArr::operator()(const IndexType irow, const IndexType icol) const
{ 
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

// оператор сложения матриц
MatrixArr& operator+(MatrixArr& lhs, MatrixArr& rhs)
{
    IndexType  r = rhs.nRows();
    IndexType  c = rhs.nCols();

    MatrixArr summ( r, c );

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
        //return lhs;
    }
    try {
        throw std::runtime_error("Error: ");
    }
    catch (const std::runtime_error & e) {
        cout << "Mismatch MatrixArr dimensions: ";
    }
    return lhs;
}

// оператор вычитания матриц
MatrixArr& operator-(MatrixArr& lhs, MatrixArr& rhs)
{
    IndexType  r = rhs.nRows();
    IndexType  c = rhs.nCols();

    MatrixArr subt(r, c);

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
        cout << "Mismatch MatrixArr dimensions: ";
    }
    return lhs;
}

// оператор умножения матриц
MatrixArr& operator*(MatrixArr& lhs, MatrixArr& rhs)
{
    IndexType  r = lhs.nRows();
    IndexType  c = rhs.nCols();

    MatrixArr mult(r, c);

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
bool operator!=(MatrixArr& lhs, MatrixArr& rhs)
{
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& ostrm, const MatrixArr& m)
{
    return m.print(ostrm);
}

