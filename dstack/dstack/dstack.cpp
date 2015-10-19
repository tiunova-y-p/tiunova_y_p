#include "znvectord.h" 
#include <stdexcept>
#include <iostream>

using namespace std;

class stack
{
public:
    stack()
        : itop{ 0}, data(1) 
    {
    }

    ~stack()
    {
    }

    void push(const double v)
    {
        if (itop == MAX_STACK_SIZE) 
        {
            throw domain_error("Stack overflow!");
        }
        else 
        {
            if (itop == data.dim())
            {
                data.resize(2* data.dim());
            }
            *(data.begin() + itop) = v; //добавление в стек элемента массива
            itop++;
        }
    }

    bool isempty()
    {
        return 0 == itop;
    }
    void pop()
    {
        if (!isempty())
        {
            itop--;
        }
    }

    void print()
    {
        cout << "[" << itop << "/" << data.dim() << "] <bottom: ";
        for (int ix = 0; ix < itop; ++ix)
        {
            cout << *(data.begin() + ix) << " ";
        }
        cout << " :top >" << endl;
    }

private:
    const IndexType MAX_STACK_SIZE = 8;
    ZnVectorD data; // указатель на кусок памяти, где будет хранится содержимое самого стека
    IndexType itop{ 0 };// индекс
};

int main()
{
    stack s;
    cout << "Proverim pustotu steka (1 mean true): " << s.isempty() << endl;
    s.print();
    cout << " push 4 6 " << endl;
    s.push(4);
    s.push(6);
    s.print();
    cout << " push 5 " << endl;
    s.push(5);
    s.print();
    cout << "Proverim pustotu steka (1 mean true): " << s.isempty() << endl;
    s.print();
    cout << " pop " << endl;
    s.pop();
    cout << "Proverim pustotu steka (1 mean true): " << s.isempty() << endl;
    s.print();

    try 
    {
        cout << "Push 7 times" << endl;
        for (int j = 0; j < 7; j++)
        {
            s.push(j);
            s.print();
        }
    }
    catch (domain_error& e)
    {
        cout << "Exception caught (" << e.what() << ')' << endl;
    };
    cout << "Pop 10 times" << endl;
    s.print();
    for (int j = 0; j < 10; j++)
    {
        s.pop();
        s.print();
    }

    return 0;
}
