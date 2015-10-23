#include "unilist.h" 
#include <iostream> 

using namespace std;

UniList::UniList() :  count_{0}
{
}

UniList::~UniList()
{
    Clearlist(); //Функция освобождает память, используемую для хранения списка
}

int UniList::GetCount() const //Возвращает количество элементов в списке
{
    return count_;
}

int UniList::IncCount() 
{
    return count_ += 1;
}

void SetCount(int c)
{
    count_ = c;
}

node* UniList::GetHead() const
{
	return head_;
}

int UniList::Add(ValueType v)  const //Добавление элемента в конец списка. Возвращает количество элементов в списке
{
	node* to_add = new node;
	(*to_add).setval(v);
    (*to_add).setnext(nullptr);

	node* current = GetHead();
	while ((*current).next() != nullptr)
	{
		current = (*current).next();
	}
    (*current).setnext(to_add);

    (*this).SetCount(1);

	return count_;
}

int UniList::Del() const //Удаление элемента из списка. Возвращает количество элементов в списке. 
{			   //Возвращает -1, если произошла ошибка
	//if (x>count) return -1;
	//node* to_del=head;
	//if (x==1) //Если нужно удалить первый элемент
	//{
	//	head=head.next();
	//	delete to_del;
	//}
	//else
	//{
	//	node* current=head;
	//	for(int i=1;i<x-1;i++)
	//		current=current.next();
	//	to_del=current.next();
	//	current.next()=current.next().next();
	//	delete to_del;
	//}
	//count--;
	//return count;
}
	
void UniList::Clearlist() const//Очистка списка
{
	//node* current = head;
	//node* to_del = head;
	//while(to_del!=nullptr)
	//{
	//	current=current.next();
	//	delete to_del;
	//	to_del=current;
	//}
	//head=nullptr;
	//count=0;
}
	
ValueType UniList::Last() const //Возвращает данные из списка.
{
	//node* current;
	//for(current=head;x>1;x--)
	//	current=current.next();
	//return current.val();
}

std::ostream& Print(std::ostream& ostrm) const
{
    return ostrm;
}


