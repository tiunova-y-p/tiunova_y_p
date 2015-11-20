#include "unilist.h" 
#include <iostream>

using namespace std;

class QueueLst
{
    using ValueType = int32_t;
    using IndexType = ptrdiff_t;

public:
    QueueLst::QueueLst()
        : itail_{ 0 }, data_{} 
    {
    }

    QueueLst::~QueueLst()
    {
    }

    void QueueLst::push(const ValueType v)
    {
        if (itail_ == MAX_QUEUE_SIZE) 
        {
            throw domain_error("Queue overflow!");
        }
        else 
        {
            data_.add(v); //добавление в очередь элемента массива
            itail_++;
        }
    }

    bool QueueLst::isempty() const
    {
        return 0 == itail_;
    }

    ValueType QueueLst::pop()
    {
        if (!isempty())
        {
            ValueType v = getTop();
            data_.deltop();
            --itail_;

            return v;
        }
        else
        {
            throw domain_error("Empty queue!");
            return 0;
        }
    }

    ValueType QueueLst::getTop()
    {
        if (!isempty())
        {
            return data_[0];
        }
        else
        {
            throw domain_error("Empty top!");
            return 0;
        }
    }

    ValueType QueueLst::getTail()
    {
        if (!isempty())
        {
            return data_[itail_];
        }
        else
        {
            throw domain_error("Empty tail!");
            return 0;
        }
    }

    void QueueLst::print()
    {
        if (itail_ != 0) data_.print();
        else cout << "Queue isEmpty" << endl;
    }

    void QueueLst::clear()
    {
        if (!isempty())
        {
            data_.clear();
            itail_ = 0;
        }
        cout << "Clear Queue" << endl;
    }

private:
    const IndexType MAX_QUEUE_SIZE = 8;
    UniList data_;          // указатель на кусок памяти, где будет хранится содержимое очереди
    IndexType itail_{ 0 };  // индекс
};

//===============================================================================

int main()
{
    QueueLst q;
    q.print();
    cout << endl;

    cout << " push 4 6 " << endl;
    q.push(4);
    q.push(6);
    q.print();
    cout << endl;

    cout << " push 5 " << endl;
    q.push(5);
    q.print();
    cout << "Top: " << q.getTop() << endl;
    cout << "Tail: " << q.getTail() << endl;
    cout << endl;

    cout << " pop() ==> " << q.pop() << endl;
    q.print();
    cout << "Top: " << q.getTop() << endl;
    cout << "Tail: " << q.getTail() << endl;
    cout << endl;

    q.clear();
    q.print();
    cout << endl;

    try 
    {
        cout << "Push 0 ... 8" << endl;
        for (int j = 0; j < 9; j++)
        {
            q.push(j);
            q.print();
        }
    }
    catch (domain_error& e)
    {
        cout << "Exception caught (" << e.what() << ')' << endl;
    };
    cout << "Top: " << q.getTop() << endl;
    cout << "Tail: " << q.getTail() << endl;
    cout << endl;

    cout << "Pop 10 times" << endl;
    q.print();

    try
    {
        for (int j = 0; j < 10; j++)
        {
            q.pop();
            q.print();
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
        cout << q.getTop() << endl;
    }
    catch (domain_error& e)
    {
        cout << "Exception caught (" << e.what() << ')' << endl;
    };

    cout << "Tail: ";
    try
    {
        cout << q.getTail() << endl;
    }
    catch (domain_error& e)
    {
        cout << "Exception caught (" << e.what() << ')' << endl;
    };

    return 0;
}
