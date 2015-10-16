#include "znvectord.h" 

#include <iostream>
using namespace std;

class stack
{
public:
    stack()
        : size_{ 0}, data(size_) 
    {
    }

    ~stack()
    {
    }

    void push(const double v)
    {
        if (itop == size_)
        {
            if (size_ == 0) size_ = 1;
            else size_ *= 2;
            data.resize(size_);
        }
        data[itop] = v; //добавление в стек элемента массива
        itop++;
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

    int stacksize() { return itop; };

    void print()
    {
        cout << "[" << stacksize() << "] <bottom: ";
        for (int ix = 0; ix < itop; ++ix)
        {
            cout << data[ix] << " ";
        }
        cout << " :top >" << endl;
    }

private:
    IndexType size_{ 0 }; //размер
    ZnVectorD data; // указатель на кусок памяти, где будет хранится содержимое самого стека
    IndexType itop{ 0 };// индекс
};

int main()
{
    stack s;
    cout << "Proverim pustotu steka (1 mean true): " << s.isempty() << endl;
    s.print();
    cout << " push 4 6 5 " << endl;
    s.push(4);
    s.push(6);
    s.push(5);
    cout << "Proverim pustotu steka (1 mean true): " << s.isempty() << endl;
    s.print();
    cout << " pop " << endl;
    s.pop();
    cout << "Proverim pustotu steka (1 mean true): " << s.isempty() << endl;
    s.print();

    return 0;
}
