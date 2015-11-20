#include "unilist.h" 
#include <iostream>
#include <initializer_list>
#include <memory> 

using namespace std;

using ValueType = int32_t;
using IndexType = ptrdiff_t;

UniList::UniList(int len)
{
    UniList* head_ = new UniList;
    for (int ix = 1; ix < len; ++ix)
    {
        head_->add(0);
    }
}

UniList::UniList(std::initializer_list<ValueType> vals)
{
    UniList* head_ = new UniList;
    for (auto ix = vals.begin() + 1; ix < vals.end(); ++ix)
    {
        head_->add((*ix));
    }
}

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

ValueType& UniList::operator[](const IndexType index)
{
    if ((index < 0) || (this->isEmpty()))
    {
        throw out_of_range("index out of range in UniList::operator[]");
    }

    Node* pnode = head_;
    for (IndexType i = 0; i < (this->length() - index - 1); ++i)
    {
        pnode = pnode->next_;
    }
    return pnode->val_;
}

bool UniList::isEmpty()  const
{
    return head_ == nullptr;
}

void UniList::add(ValueType v)
{
    head_ = new Node{ v, head_ };
}

void UniList::del()
{
    if (!isEmpty())
    {
        Node* deleted = head_;
        head_ = head_->next_;
        delete deleted;
    }
}

void UniList::deltop()
{
    if (!isEmpty())
    {
        Node* newtop = head_;
        if (newtop->next_ == NULL) delete newtop;
        else
        {
            Node* deleted = newtop->next_;
            while (deleted->next_ != NULL)
            {
                newtop = newtop->next_;
                deleted = newtop->next_;
            }
            newtop->next_ = nullptr;
            delete deleted;
        }
    }
}

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
