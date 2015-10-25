#include "unilist.h" 
#include <iostream>
#include <cstddef>
#include <cstdint> 
#include <initializer_list>
#include <memory> 

using namespace std;

UniList::UniList(int len)
{
    Node* pfirst = new Node;
    pfirst->val_ = { 0 };
    head_ = tail_ = pfirst;
    for (int ix = 1; ix < len; ++ix)
    {
        Node* pnode = new Node;
        pnode->val_ = { 0 };
        tail_->next_ = pnode;
        tail_ = pnode;
    }
}

UniList::UniList (std::initializer_list<ValueType> vals)
{
    Node* pfirst = new Node;
    pfirst->val_ = (*vals.begin());
    head_ = tail_ = pfirst;
    for (auto ix = vals.begin() + 1; ix < vals.end(); ++ix)
    {
        Node* pnode = new Node;
        pnode->val_ = (*ix);
        tail_->next_ = pnode;
        tail_ = pnode;
    }
}

//ƒеструктор
UniList :: ~UniList ()
{
    if (head_ != nullptr)
    {
        Node* pnode = head_;
        while (pnode)
        {
            pnode = pnode->next_;
            delete head_;
            head_ = pnode;
        }
    }
}
//ѕроверка списков на равенство
bool UniList::operator==(const UniList& l)
{
    Node* pnode = head_;
    Node* plnode = l.head_;
    while ((pnode) && (plnode))
    {
        if (pnode->val_ != plnode->val_) return false;
        pnode = pnode->next_;
        plnode = plnode->next_;
    }
    return true;
}

//ѕроверка списков на неравенство
bool UniList::operator!=(const UniList& l)
{
    Node* pnode = head_;
    Node* plnode = l.head_;
    while ((pnode) && (plnode))
    {
        if (pnode->val_ == plnode->val_) return false;
        pnode = pnode->next_;
        plnode = plnode->next_;
    }
    return true;
}

//ѕерегрузка операции присваивани€
UniList& UniList::operator=(const UniList& l)
{
    this->~UniList();               //”ничтожаем старое содержимое списка
    Node* pfirst = new Node;        //—оздаем первый узел списка, куда будет копироватьс€ список l
    pfirst->val_ = l.head_->val_;   // опируем значение данных из первого узла
    head_ = tail_ = pfirst;         //”казатели головы и хвоста устанавливаем на первый узел
    Node* plnode = l.head_->next_;  //
    while (plnode)
    { 
        Node* pnode = new Node;
        pnode->val_ = plnode->val_;
        tail_->next_ = pnode;
        tail_ = pnode;
        plnode = plnode->next_;
    };
    return (*this);
};

//ѕерегрузка операции [] -доступ к элементу в заданной позиции
ValueType& UniList::operator[](const IndexType index)
{
    if ((index < 0) || ((*this).IsEmpty()))


    {
        throw out_of_range("index out of range in UniList::operator[]");
    }

    Node* pnode = head_;
    for (IndexType i = 0; i < index; ++i)
    {
        pnode = pnode->next_;
    }
    return pnode->val_;
}

bool UniList::IsEmpty()
{
    return head_ == nullptr;
}

void UniList::Add(ValueType v)
{
    Node* pnode = new Node;
    pnode->val_ = v;
    if (this->IsEmpty())
    {
        head_ = tail_ = pnode;
    }
    else
    {
        tail_->next_ = pnode;
        tail_ = pnode;
    }
}

void UniList::Del()
{
    if (head_ != nullptr)
    {
        Node* pnode = head_;
        while ((pnode->next_ != tail_) && (pnode->next_ != nullptr))
        {
            pnode = pnode->next_;
        }
        if (head_->next_ != nullptr)
        {
            delete tail_;
            tail_ = pnode;
            pnode->next_ = nullptr;
        }
        else
        {
            head_ = nullptr;
            delete tail_;
            tail_ = head_;
        }
    }
}

//просмотра всего списка
void UniList::Print()
{
    Node* pnode = head_;
    cout << endl << "UniList: <";
    while (pnode)
    {
        cout << pnode->val_ << ' ';
        pnode = pnode->next_;
    }
    cout << ">" << endl;
}

