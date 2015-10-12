#include <iostream>
#include <sstream>

using namespace std;

class Complex
{
public:
    Complex()
        : Complex(0.0, 0.0)
    {
    }

    Complex(const double re)
        : Complex(re, 0.0)
    {
    }

    Complex(const double re, const double im)
        : re_{ re }   
        , im_{ im }
    {
    }

    Complex(const Complex&) = default;

    //получение вещественной части
    double re() const
    {
        return re_;
    }
    // получение мнимой части
    double im() const
    {
        return im_;
    }

    Complex& operator= (const Complex&) = default;

    ostream& print(ostream& ostrm) const
    {
        cout << '(' << re_ << ',' << im_ << ')';
        return ostrm;
    }

    istream& readFromTxt(std::istream& istrm)
    {
        double re{ 0 };    // "123.9,34.6"
        istrm >> re;

        if (istrm) re_ = re;
        else       re_ = 0.0;

        char sep{ 0 };
        istrm >> sep;
        if (',' != sep)
            istrm.setstate(ios_base::failbit);

        double im{ 0 };
        istrm >> im;

        if (istrm) im_ = im;
        else       im_ = 0.0;

        return istrm;
    }
    
    // оператор отрицания
    Complex operator-() const
    {
        return Complex{ -re_, -im_ };
    }
    // получение сопряженного числа
    Complex Conj() const
    {
        return Complex{ re_, -im_ };
    }

    Complex& operator+=(const Complex& rhs)
    {
        re_ += rhs.re_;
        im_ += rhs.im_;
        return *this;
    }
    // оператор *=
    Complex& operator*=(const Complex& rhs)
    { 
        double tmp;
        tmp = (re_*rhs.re_ - im_*rhs.im_);   //  (a; b) * (c; d) = (ac - bd; ad + bc)
        im_ = (re_*rhs.im_ + im_*rhs.re_);   //  (re_;im_)*(rhs.re_;rhs.im_) = 
        re_ = tmp;
        return *this;
    }

    //(a; b) : (c; d) = ((ac + bd) / (c2 + d2); (bc - ad) / (c2 + d2))
    // оператор /=
    Complex& operator/=(const Complex& rhs)
    {
        double tmp;
        tmp = (re_*rhs.re_ + im_*rhs.im_) / (rhs.re_*rhs.re_ + rhs.im_*rhs.im_);
        im_ = (im_*rhs.re_ - re_*rhs.im_) / (rhs.re_*rhs.re_ + rhs.im_*rhs.im_);
        re_ = tmp;
        return *this;
    }

    // оператор -=
    Complex& operator-=(const Complex& rhs)
    {
        re_ -= rhs.re_;
        im_ -= rhs.im_;
        return *this;
    }
    // оператор равенства
    bool operator==(const Complex& rhs) const
    {
        return (re_ == rhs.re_) && (im_ == rhs.im_);
    }
    // неравенство
    bool operator!=(const Complex& rhs) const
    {
        return !operator==(rhs);
    }

private:
    double re_ = 0.0;
    double im_ = 0.0;
};


ostream& operator<<(ostream& ostrm, const Complex& z)
{
    z.print(ostrm);
    return ostrm;
}

std::istream& operator>>(std::istream& istrm, Complex& z)
{
    return z.readFromTxt(istrm);
}

Complex operator+(const Complex& lhs, const Complex& rhs)
{
    Complex sum{ lhs };
    sum += rhs;
    return sum;
}
// операция вычитания
Complex operator-(const Complex& lhs, const Complex& rhs)
{
    Complex diff{ lhs };
    diff -= rhs;
    return diff;
}
// операция произведения комплексных чисел
Complex operator*(const Complex& lhs, const Complex& rhs)
{
    Complex mult{ lhs };
    mult *= rhs;
    return mult;
}

// операция деления комплексных чисел
Complex operator/(const Complex& lhs, const Complex& rhs)
{
    Complex div{ lhs };
    div /= rhs;
    return div;
}


Complex operator+(const Complex& lhs, const double rhs)
{
    Complex sum{ lhs };
    sum += Complex{ rhs };
    return sum;
}
// операция разности
Complex operator-(const Complex& lhs, const double rhs)
{
    Complex diff{ lhs };
    diff -= Complex{ rhs };
    return diff;
}

// операция произведения комплексного числа на вещественное
Complex operator*(const Complex& lhs, const double rhs)
{
    Complex mult{ lhs };
    mult *= Complex{ rhs };
    return mult;
}

void testReadFromStream(const string& s)
{
    istringstream istrm(s);
    Complex z;
    istrm >> z;
    cout << "Read from text \"" << s << "\" -> " << z << ", stream state is " << boolalpha << !!istrm << endl;
}

int main()
{
    Complex z1;
    z1.print(cout);
    cout << endl;

    Complex z2{ 2.5 };
    Complex z3{ 3.5, -8.0 };

    cout << "z2=" << z2 << endl;
    cout << "z3=" << z3 << endl << endl;
    z2 += z3;
    cout << "z2 += z3 => z2 =" << z2 << endl << endl;
    cout << "z2 + z3  =" << (z2 + z3) << endl << endl;
    cout << "z2 + 0.3 =" << (z2 + 0.3) << endl << endl;

    //DONE
    cout << "z3 - 0.5 =" << (z3 - 0.5) << endl << endl;
    cout << "z3 * 0.8 =" << (z3 * 0.8) << endl << endl;

    Complex z4{ z3 };
    Complex z5{ z2.im(), z4.re() };

    cout << "-z3=" << -z3 << endl;
    cout << "conj_z3=" << z3.Conj() << endl << endl;

    cout << z3 << " == " << z4 << " -> " << boolalpha << (z3 == z4) << endl;
    cout << z3 << " == " << z5 << " -> " << boolalpha << (z3 == z5) << endl;

    cout << z3 << " != " << z5 << " -> " << boolalpha << (z3 != z5) << endl << endl;

    cout << "z4=" << z4 << endl;
    cout << "z5=" << z5 << endl << endl;
    cout << "z2 += z3 => z2 =" << z2 << endl << endl;

    z4 -= z5;
    cout << "z4 -= z5 => z4 =" << z4 << endl << endl;
    cout << "z4 - z5  =" << (z4 - z5) << endl;
    cout << "z4 - 0.9 =" << (z4 - 0.9) << endl << endl;

    // (1; 2) * (4; 9) = (1*4 - 2*9; 1*9 + 2*4) = (-14; 17) 
    Complex z6{ 1.0, 2.0 };
    Complex z7{ 4.0, 9.0 };
    cout << "z6=" << z6 << endl;
    cout << "z7=" << z7 << endl << endl;
    cout << "z6 * z7 =" << (z6 * z7) << endl << endl;
    Complex z8{ z6 };
    z6 *= z7;
    cout << "z6 *= z7 => z6 =" << z6 << endl << endl;

   // (1; 2) : (4; 9) = ((1 * 4 + 2 * 9) / (42 + 92); (2 * 4 - 1 * 9) / (42 + 92)) = (0.23; -0.01)
    cout << "z8 / z7 =" << (z8 / z7) << endl << endl;
    z8 /= z7;
    cout << "z8 /= z7 => z8 =" << z8 << endl << endl;

    cout << "\nTest Complex read from stream" << endl;
    testReadFromStream("");
    testReadFromStream("1.5");
    testReadFromStream("15,");
    testReadFromStream(",1.5");
    testReadFromStream("1.3,2.4");
    testReadFromStream("-4/5");
    testReadFromStream("-4a;5");

    return 0;
}