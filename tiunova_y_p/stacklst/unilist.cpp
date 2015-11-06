#include "unilist.h" 
#include <iostream>
//#include <cstddef>
//#include <cstdint> 
#include <initializer_list>
#include <memory> 

using namespace std;

using ValueType = int32_t;
using IndexType = ptrdiff_t;

/*
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
*/

UniList::UniList(int len)
{
    UniList* head_ = new UniList;
    for (int ix = 1; ix < len; ++ix)
    {
        head_->add(0);
    }
}
/*
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
*/

UniList::UniList(std::initializer_list<ValueType> vals)
{
    UniList* head_ = new UniList;
    for (auto ix = vals.begin() + 1; ix < vals.end(); ++ix)
    {
        head_->add((*ix));
    }
}

//ƒеструктор
/*
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
*/

UniList :: ~UniList()
{
    if (head_ != nullptr) head_ = nullptr;
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
/*
UniList& UniList::operator=(const UniList& l)
{
    //this->~UniList();               //”ничтожаем старое содержимое списка
    head_ = nullptr;
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
}
*/

UniList& UniList::operator=(const UniList& rhs)
{
    (*this).clear();
    if (rhs.head_)
    {
        UniList lhs;                //—оздаем пустой список, куда будет копироватьс€ список rhs в обратном пор€дке
        Node* pnode = rhs.head_;
        do 
        {
            lhs.add(pnode->val_);
            pnode = pnode->next_;
        } while (pnode->next_);

        pnode = lhs.head_;
        do
        {
            (*this).add(pnode->val_);
            pnode = pnode->next_;
        } while (pnode->next_);
    }
    return (*this);
}

/*
//ѕерегрузка операции [] -доступ к элементу в заданной позиции
ValueType& UniList::operator[](const IndexType index)
{
    if ((index < 0) || ((*this).isEmpty()))
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
*/

ValueType& UniList::operator[](const IndexType index)
{
    if ((index < 0) || (this->isEmpty()))
    {
        throw out_of_range("index out of range in UniList::operator[]");
    }

    Node* pnode = head_;
    for (IndexType i = 0; i < (this->length() - index); ++i)
    {
        pnode = pnode->next_;
    }
    return pnode->val_;
}

//bool UniList::IsEmpty()
//{
//    return head_ == nullptr;
//}

bool UniList::isEmpty()  const
{
    return head_ == nullptr;
}

/*
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
*/

void UniList::add(ValueType v)
{
    head_ = new Node{ v, head_ };
}
/*
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
*/
void UniList::del()
{
    if (!isEmpty())
    {
        Node* deleted = head_;
        head_ = head_->next_;
        delete deleted;
    }
}

//просмотра всего списка
//void UniList::Print()
//{
//    Node* pnode = head_;
//    cout << endl << "UniList: <";
//    while (pnode)
//    {
//        cout << pnode->val_ << ' ';
//        pnode = pnode->next_;
//    }
//    cout << ">" << endl;
//}

void UniList::print()
{
    Node* pnode = (this->reverse())->head_;
    cout << "UniList [" << this->length() << "]: ";
    while (pnode)
    {
        cout << pnode->val_ << ' ';
        pnode = pnode->next_;
    }
    cout << endl;
}

UniList* UniList::reverse()
{
    if (isEmpty()) return nullptr;
    else
    {
        UniList* rlist = new UniList;
        rlist->add(head_->val_);
        Node* p = head_->next_;
        while (p != nullptr)
        {
            rlist->add(p->val_);
            p = p->next_;
        }
        return rlist;
    }
}

int UniList::length()
{
    int len = 0;
    if (!isEmpty())
    {
        Node* pnode = head_;
        do
        {
            len++;
            pnode = pnode->next_;
        } while (pnode);
    }
    return len;
}

void UniList::clear()
{
    while (!isEmpty())
    {
        this->del();
    }
}
