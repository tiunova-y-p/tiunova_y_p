#include <iostream>
#include <stdexcept>
#include <sstream>

using namespace std;

class Rational
{
public:
    Rational() noexcept
        : Rational{ 0, 1 }
    {
    }

    Rational(const int num) noexcept
        : Rational{ num, 1 }
    {
    }

    Rational(const int num, const int den)
        : num_{ num }, den_{ den }
    {
        if (0 == den_)
        {
            throw domain_error("zero denominator in Rational");
        }
        normalize();
    }

    Rational(const Rational& rhs) noexcept = default;

    Rational& operator=(const Rational& rhs) = default;

    Rational& operator=(Rational&& rhs) = default;

    int num() const
    {
        return num_;
    }

    int den() const
    {
        return den_;
    }

    Rational operator-() const
    {
        return Rational{ -num_, den_ };
    }

    Rational& operator+=(const Rational& rhs)
    {
        num_ = num_ * rhs.den_ + den_ * rhs.num_;
        den_ *= rhs.den_;
        normalize();
        return *this;
    }

    Rational& operator-=(const Rational& rhs)
    {
        num_ = num_ * rhs.den_ - den_ * rhs.num_;
        den_ *= rhs.den_;
        normalize();
        return *this;
    }
// a/b;  c/d = c/d * a/b; <==> c/d *= a/b;
    Rational& operator*=(const Rational& rhs)
    {
        num_ *= rhs.num_;
        den_ *= rhs.den_;
        normalize();
        return *this;
    }

    Rational& operator/=(const Rational& rhs)
    {
        num_ *= rhs.den_;
        den_ *= rhs.num_;
        normalize();
        return *this;
    }

    bool operator==(const Rational& rhs) const
    {
        return (num_ == rhs.num_) && (den_ == rhs.den_);
    }

    bool operator!=(const Rational& rhs) const
    {
        return !operator==(rhs);
    }

    bool operator<(const Rational& rhs) const
    {
        return (num_ * rhs.den_) < (rhs.num_ * den_);
    }

    bool operator<=(const Rational& rhs) const
    {
        return (num_ * rhs.den_) <= (rhs.num_ * den_);
    }

    bool operator>(const Rational& rhs) const
    {
        return !operator<=(rhs);
    }

    bool operator>=(const Rational& rhs) const
    {
        return !operator<(rhs);
    }

    ostream& writeToTxt(std::ostream& ostrm) const
    {
        ostrm << num_ << '/' << den_;
        return ostrm;
    }

    istream& readFromTxt(std::istream& istrm)  
    {
        int num{ 0 };
        istrm >> num;

        char sep{ 0 };
        istrm >> sep;
        if ('/' != sep)
            istrm.setstate(ios_base::failbit);

        int den{ 0 };
        istrm >> den;

        if (istrm)
        {
            num_ = num;
            den_ = den;
            normalize();
        }
        return istrm;
    }

private:
    // Алгоритм Евклида для НОД
    int ENOD(int n, int d) {
        int an = abs(n);
        int ad = abs(d);

        while (an != ad) {
            if (an > ad) an -= ad;
            else         ad -= an;
        }
        return an;
    }

    void normalize()
    {
        if (0 == num_)
        {
            den_ = 1;
        }
        else 
        {
            if (den_ < 0) 
            {
                num_ *= -1;
                den_ *= -1;
            }
            // DONE: упрощение до несократимой дроби 
            int nod = ENOD(num_, den_);
            if (nod > 1)
            {
                num_ /= nod;
                den_ /= nod;
            }
        }
    }

private:
    int num_; //< числитель, целое 
    int den_; //< знаменатель, натуральное 
};

Rational operator+(const Rational& lhs, const Rational& rhs)
{
    Rational summ{ lhs };
    summ += rhs;
    return summ;
}

Rational operator-(const Rational& lhs, const Rational& rhs)
{
    Rational summ{ lhs };
    summ -= rhs;
    return summ;
}

Rational operator*(const Rational& lhs, const Rational& rhs)
{
    Rational summ{ lhs };
    summ *= rhs;
    return summ;
}

Rational operator/(const Rational& lhs, const Rational& rhs)
{
    Rational summ{ lhs };
    summ /= rhs;
    return summ;
}

std::ostream& operator<<(std::ostream& ostrm, const Rational& r)
{
    return r.writeToTxt(ostrm);
}

std::istream& operator>>(std::istream& istrm, Rational& r)
{
    return r.readFromTxt(istrm);
}

void testRationalConstructor(const int num, const int den)
{
    cout << "Rational{" << num << ',' << den << "} -> " << flush;
    cout << Rational{ num, den } << endl;
}

void testRationalOpPlus(const Rational& lhs, const Rational& rhs)
{
    cout << lhs << " + " << rhs << " -> " << (lhs + rhs) << endl;
}

void testRationalOpMinus(const Rational& lhs, const Rational& rhs)
{
    cout << lhs << " - " << rhs << " -> " << (lhs - rhs) << endl;
}

void testRationalOpMult(const Rational& lhs, const Rational& rhs)
{
    cout << lhs << " * " << rhs << " -> " << (lhs * rhs) << endl;
}

void testRationalOpDiv(const Rational& lhs, const Rational& rhs)
{
    cout << lhs << " / " << rhs << " -> " << (lhs / rhs) << endl;
}

void testRationalOpCmpEq(const Rational& lhs, const Rational& rhs)
{
    cout << lhs << " == " << rhs << " -> " << boolalpha << (lhs == rhs) << endl;
}

void testRationalOpCmpNotEq(const Rational& lhs, const Rational& rhs)
{
    cout << lhs << " != " << rhs << " -> " << boolalpha << (lhs != rhs) << endl;
}

void testRationalOpCmpLess(const Rational& lhs, const Rational& rhs)
{
    cout << lhs << " < " << rhs << " -> " << boolalpha << (lhs < rhs) << endl;
}

// DONE: test for operator<= operator> operator>=
// test for operator<=
void testRationalOpCmpLessEq(const Rational& lhs, const Rational& rhs)
{
    cout << lhs << " <= " << rhs << " -> " << boolalpha << (lhs <= rhs) << endl;
}

// test for operator>
void testRationalOpCmpGrt(const Rational& lhs, const Rational& rhs)
{
    cout << lhs << " > " << rhs << " -> " << boolalpha << (lhs > rhs) << endl;
}

// test for operator>=
void testRationalOpCmpGrtEq(const Rational& lhs, const Rational& rhs)
{
    cout << lhs << " >= " << rhs << " -> " << boolalpha << (lhs >= rhs) << endl;
}


void testReadFromStream(const string& s)
{
    istringstream istrm(s);
    Rational r;
    istrm >> r;
    cout << "Read from text \"" << s << "\" -> " << r << ", stream state is " << boolalpha << !!istrm << endl;
}

int main()
{
    cout << "Rational{} -> " << Rational{} << endl;
    Rational r02{ 2 };
    cout << "Rational{} -> " << r02 << endl;
    testRationalConstructor(1, 2);
    testRationalConstructor(-1, 2);
    testRationalConstructor(1, -2);
    testRationalConstructor(-1, -2);
    testRationalConstructor(12, -4);
    try
    {
        testRationalConstructor(5, 0);
    }
    catch (domain_error& e)
    {
        cout << "exception caught (" << e.what() << ')' << endl;
    }
    Rational r03{ -1, 5 };
    Rational r04{ 4, -6 };

    cout << "\nTest Rational operator+" << endl;
    testRationalOpPlus(r03, -r03);
    testRationalOpPlus(r03, r04);

    cout << "\nTest Rational operator-" << endl;
    testRationalOpMinus(r03, r03);
    testRationalOpMinus(r03, r04);

    cout << "\nTest Rational operator*" << endl;
    testRationalOpMult(r03, r03);
    testRationalOpMult(r03, r04);

    cout << "\nTest Rational operator/" << endl;
    testRationalOpDiv(r03, r03);
    testRationalOpDiv(r03, r04);

    cout << "\nTest Rational operator==" << endl;
    testRationalOpCmpEq(r03, r03);
    testRationalOpCmpEq(r03, -r03);
    testRationalOpCmpEq(r03, r04);

    cout << "\nTest Rational operator!=" << endl;
    testRationalOpCmpNotEq(r03, r03);
    testRationalOpCmpNotEq(r03, -r03);
    testRationalOpCmpNotEq(r03, r04);

    cout << "\nTest Rational operator<" << endl;
    testRationalOpCmpLess(r03, r03);
    testRationalOpCmpLess(r03, -r03);
    testRationalOpCmpLess(r03, r04);

    //DONE: test for operator<= operator> operator>=

    cout << "\nTest Rational operator<=" << endl;
    testRationalOpCmpLessEq(r03, r03);
    testRationalOpCmpLessEq(r03, -r03);
    testRationalOpCmpLessEq(r03, r04);

    cout << "\nTest Rational operator>" << endl;
    testRationalOpCmpGrt(r03, r03);
    testRationalOpCmpGrt(r03, -r03);
    testRationalOpCmpGrt(r03, r04);

    cout << "\nTest Rational operator>=" << endl;
    testRationalOpCmpGrtEq(r03, r03);
    testRationalOpCmpGrtEq(r03, -r03);
    testRationalOpCmpGrtEq(r03, r04);

    cout << "\nTest Rational read from stream" << endl;
    testReadFromStream("");
    testReadFromStream("1");
    testReadFromStream("1/2");
    testReadFromStream("-4/5");
    testReadFromStream("3/-5");
    testReadFromStream("-5/-2");
    testReadFromStream("-5.0/-2");

    return 0;
}
