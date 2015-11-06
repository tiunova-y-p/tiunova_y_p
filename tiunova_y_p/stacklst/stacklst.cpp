#include "unilist.h" 
//#include <stdexcept>
#include <iostream>

using namespace std;

class Stacklst
{
    using ValueType = int32_t;
    using IndexType = ptrdiff_t;

public:
    Stacklst::Stacklst()
        : itop{ 0 }, data{}   //*** +
    {
    }

    Stacklst::~Stacklst()
    {
    }

    void Stacklst::push(const ValueType v)
    {
        if (itop == MAX_STACK_SIZE) 
        {
            throw domain_error("Stack overflow!");
        }
        else 
        {
            data.add(v); //добавление в стек элемента массива
            itop++;
        }
    }

    bool Stacklst::isempty() const
    {
        return 0 == itop;
    }

    ValueType Stacklst::pop()
    {
        if (!isempty())
        {
            //--itop;
            ValueType v = data[itop--];
            data.del();
            return v;
        }
        else
        {
            throw domain_error("Empty stack!");
            return 0;
        }
    }

    ValueType Stacklst::getTop()
    {
        if (!isempty())
        {
            return data[itop];
        }
        else
        {
            throw domain_error("Empty top !");
            return 0;
        }
    }

    void Stacklst::print()
    {
        if (itop != 0) data.print();
        else cout << "Stack isEmpty" << endl;
    }

    void Stacklst::clear()
    {
        if (itop != 0)
        {
            data.clear();
            itop = 0;
        }
        cout << "Clear Stack" << endl;
    }

private:
    const IndexType MAX_STACK_SIZE = 8;
    UniList data; // указатель на кусок памяти, где будет хранится содержимое самого стека
    IndexType itop{ 0 };// индекс
};

//===============================================================================

int main()
{
    Stacklst s;
    //cout << "Proverim pustotu steka (1 mean true): " << s.isempty() << endl;
    s.print();
    cout << endl;

    cout << " push 4 6 " << endl;
    s.push(4);
    s.push(6);
    s.print();
    cout << endl;

    cout << " push 5 " << endl;
    s.push(5);
    s.print();
    //cout << "Proverim pustotu steka (1 mean true): " << s.isempty() << endl;
    cout << "Top: " << s.getTop() << endl;
    cout << endl;

    cout << " pop() ==> " << s.pop() << endl;
    //cout << "Proverim pustotu steka (1 mean true): " << s.isempty() << endl;
    s.print();
    cout << "Top: " << s.getTop() << endl;
    cout << endl;

    s.clear();
    s.print();
    cout << endl;

    try 
    {
        cout << "Push 0 ... 8" << endl;
        for (int j = 0; j < 9; j++)
        {
            s.push(j);
            s.print();
        }
    }
    catch (domain_error& e)
    {
        cout << "Exception caught (" << e.what() << ')' << endl;
    };
    cout << "Top: " << s.getTop() << endl;
    cout << endl;

    cout << "Pop 10 times" << endl;
    s.print();

    try
    {
        for (int j = 0; j < 10; j++)
        {
            s.pop();
            s.print();
        }
    }
    catch (domain_error& e)
    {
        cout << "Exception caught (" << e.what() << ')' << endl;
    };
    cout << endl;

    cout << "Top: ";
    try
    {
        cout << s.getTop() << endl;
    }
    catch (domain_error& e)
    {
        cout << "Exception caught (" << e.what() << ')' << endl;
    };

    return 0;
}
