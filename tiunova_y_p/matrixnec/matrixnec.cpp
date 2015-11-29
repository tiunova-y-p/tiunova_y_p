#include "matrixnec.h" 

#include <cassert>
#include <iostream>

using namespace std;

using ValueType = int32_t;
using IndexType = ptrdiff_t;

MatrixNec::MatrixNec(const IndexType rows, const IndexType cols)
    : rows_{ rows },
    cols_{ cols },
    data_{ new  ValueType*[rows_] }
{
    for (int i = 0; i < rows; i++)
        data_[i] = new  ValueType[cols_]{ 0 };
}

MatrixNec::MatrixNec(const IndexType rows, const IndexType cols, std::initializer_list<ValueType> vals)
    : rows_{ rows },
    cols_{ cols },
    data_{ new  ValueType*[rows_] }
{
    for (int i = 0; i < rows_; i++)
    {
        data_[i] = new  ValueType[cols_];
        for (int j = 0; j < cols; j++)
            data_[i][j] = *(vals.begin() + i*cols_ + j);
    }
}

MatrixNec::MatrixNec(const MatrixNec& m)
    : rows_{ m.rows_ },
    cols_{ m.cols_ },
    data_{ new  ValueType*[rows_] }
{
    for (int i = 0; i < rows_; i++)
    {
        data_[i] = new  ValueType[cols_];
        for (int j = 0; j < cols_; j++)
            data_[i][j] = m.data_[i][j];
    }
}

MatrixNec::MatrixNec(MatrixNec&& m)
    : rows_{ m.rows_ },
    cols_{ m.cols_ },
    data_{ new  ValueType*[rows_] }
{
    for (int i = 0; i < rows_; i++)
    {
        data_[i] = new  ValueType[cols_];
        for (int j = 0; j < cols_; j++)
            data_[i][j] = m.data_[i][j];
    }
}

MatrixNec::~MatrixNec()
{
    for (int i = 0; i < rows_; i++)
    {
        delete[] data_[i];
    }
    delete[] data_;
}

MatrixNec& MatrixNec::operator=(const MatrixNec& m)
{
    if (this != &m)
    {
        swap(MatrixNec(m));
    }
    return *this;
}

MatrixNec& MatrixNec::operator=(MatrixNec&& m)
{
    if (this != &m)
    {
        swap(MatrixNec(m));
    }
    return *this;
}

MatrixNec& MatrixNec::transpose()
{
    MatrixNec t(cols_, rows_);

    for (IndexType i{ 0 }; i != rows_; ++i)
    {
        for (IndexType j{ 0 }; j != cols_; ++j)
        {
            t.data_[j][i] = data_[i][j];
        }
    }
    swap(t);

    return *this;
}

std::ostream& MatrixNec::print(std::ostream& ostrm) const
{
    cout << endl;
    if ((rows_ != 0) && (cols_ != 0))
    {
        for (IndexType i{ 0 }; i < rows_; ++i)
        {
            cout << ((0 == i) ? '(' : ' ');
            for (IndexType j{ 0 }; j < cols_ - 1; ++j)
            {
                cout << data_[i][j] << ',';
            }
            cout << data_[i][cols_ - 1] << ((i == rows_ - 1) ? ')' : ' ') << endl;
        }
    }
    else cout << "( )" << endl;
    return ostrm;
}

ValueType& MatrixNec::operator()(const IndexType irow, const IndexType icol)
{
        if ((irow < 0) || (rows_ <= irow) || (icol < 0) || (cols_ <= icol))
        { 
            throw out_of_range("index out of range in MatrixNec::operator()"); 
        } 
        return data_[irow][icol]; 
}

const ValueType& MatrixNec::operator()(const IndexType irow, const IndexType icol) const
{
        if ((irow < 0) || (rows_ <= irow) || (icol < 0) || (cols_ <= icol))
        {
            throw out_of_range("index out of range in MatrixNec::operator()");
        }
        return data_[irow][icol];
}

void MatrixNec::swap(MatrixNec& m)
{
    IndexType rows{ m.rows_ };
    m.rows_ = rows_;
    rows_ = rows;

    IndexType cols{ m.cols_ };
    m.cols_ = cols_;
    cols_ = cols;

    ValueType** data{ m.data_ };
    m.data_ = data_;
    data_ = data;
}

MatrixNec& MatrixNec::operator-()
{
    MatrixNec res(rows_, cols_);
    for (IndexType i{ 0 }; i < rows_; i += 1)
    {
        for (IndexType j{ 0 }; j < cols_; j += 1)
        {
            res.data_[i][j] = -data_[i][j];
        }
    }
    swap(res);

    return *this;
}

MatrixNec& MatrixNec::operator+=(const ValueType rhs) 
{ 
    for (IndexType i{ 0 }; i != rows_; ++i)
    {
        for (IndexType j{ 0 }; j != cols_; ++j)
        {
            data_[i][j] += rhs;
        }
    }
    return *this;
} 

MatrixNec& MatrixNec::operator-=(const ValueType rhs)
{
    for (IndexType i{ 0 }; i != rows_; ++i)
    {
        for (IndexType j{ 0 }; j != cols_; ++j)
        {
            data_[i][j] -= rhs;
        }
    }
    return *this;
}

MatrixNec& MatrixNec::operator*=(const ValueType rhs)
{
    for (IndexType i{ 0 }; i != rows_; ++i)
    {
        for (IndexType j{ 0 }; j != cols_; ++j)
        {
            data_[i][j] *= rhs;
        }
    }
    return *this;
}

// оператор сложения матриц
MatrixNec& operator+(MatrixNec& lhs, MatrixNec& rhs)
{
    IndexType  r = rhs.nRows();
    IndexType  c = rhs.nCols();

    if ((lhs.nRows() == rhs.nRows()) && (lhs.nCols() == rhs.nCols()))
    {
        MatrixNec summ(lhs);
        for (IndexType i{ 0 }; i != r; i++)
        {
            for (IndexType j{ 0 }; j != c; j++)
            {
                (*(*(summ.begin() + i) + j)) += (*(*(rhs.begin() + i) + j));
            }
        }
        summ.print(cout);
        return summ;
    }
    try 
    {
        throw std::runtime_error("Error: ");
    }
    catch (const std::runtime_error & e) 
    {
        cout << "Mismatch MatrixNec dimensions: ";
    }
    return lhs;
}

// оператор умножения матриц
MatrixNec& operator*(MatrixNec& lhs, MatrixNec& rhs)
{
    IndexType  r = lhs.nRows();
    IndexType  c = rhs.nCols();

    if (lhs.nCols() == rhs.nRows())
    {
        MatrixNec mult(r, c);

        for (IndexType i{ 0 }; i != r; ++i)
        {
            for (IndexType k{ 0 }; k != c; ++k)
            {
                for (IndexType j{ 0 }; j != rhs.nRows(); ++j)
                {
                    (*(*(mult.begin() + i) + k)) += (*(*(lhs.begin() + i) + j)) * (*(*(rhs.begin() + j) + k));   
                }
            }
        }
        mult.print(cout);
        return mult;
    }
    try 
    {
        throw std::runtime_error("Error: ");
    }
    catch (const std::runtime_error & e) 
    {
        cout << "No concurrent matrix: ";
    }
    return lhs;
}

MatrixNec operator+(MatrixNec& lhs, const ValueType rhs) { return MatrixNec(lhs) += rhs; }

// оператор разности
MatrixNec& operator-(MatrixNec& lhs, MatrixNec& rhs)
{
    IndexType  r = rhs.nRows();
    IndexType  c = rhs.nCols();

    if ((lhs.nRows() == rhs.nRows()) && (lhs.nCols() == rhs.nCols()))
    {
        MatrixNec subt(lhs);
        for (IndexType i{ 0 }; i != r; i++)
        {
            for (IndexType j{ 0 }; j != c; j++)
            {
                (*(*(subt.begin() + i) + j)) -= (*(*(rhs.begin() + i) + j));
            }
        }
        subt.print(cout);
        return subt;
    }
    try
    {
        throw std::runtime_error("Error: ");
    }
    catch (const std::runtime_error & e)
    {
        cout << "Mismatch MatrixNec dimensions: ";
    }
    return lhs;
}

// оператор равенства
bool operator==(MatrixNec& lhs, MatrixNec& rhs)
{
    IndexType  r = rhs.nRows();
    IndexType  c = rhs.nCols();

    if ((lhs.nRows() == r) && (lhs.nCols() == c))
    {
        for (IndexType i{ 0 }; i != r; ++i)
        {
            for (IndexType j{ 0 }; j != c; ++j)
            {
                if (**(lhs.begin() + i*c + j) != **(rhs.begin() + i*c + j))
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
bool operator!=(MatrixNec& lhs, MatrixNec& rhs)
{
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& ostrm, const MatrixNec& m)
{
    return m.print(ostrm);
}



