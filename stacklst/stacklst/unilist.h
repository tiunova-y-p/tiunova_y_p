#ifndef UNILIST_H_20151023
#define UNILIST_H_20151023 

#include <cstdint> 
#include <iostream>

using ValueType = int32_t; 
using IndexType = ptrdiff_t; 

using namespace std;

class node //Класс node содержит данные элемента/узла списка
{
private:
    ValueType val_; 	//Данные элемента/узла списка
    node* next_; 	//Указатель на следующий элемент в списке

public:
    node() : next_{ nullptr }
    {}
    ~node()
    {}

    ValueType val() const { return val_; }
    void setval(ValueType v) { val_ = v; }
    node* next() const { return next_; }
    void setnext(node* n) { next_ = n; }

    std::ostream& print(std::ostream& ostrm) const
    {
        cout << val();
        return ostrm;
    }
};

class UniList
{
public:

private:
	node* head_{ nullptr }; //Указатель на начало списка узлов/элементов
	int count_; //Количество элементов в списке

public:
    UniList();
	~UniList();

	int GetCount() const; //Возвращает количество элементов в списке
    void SetCount(int c);
    int IncCount();
	node* GetHead() const; //Возвращает Указатель на начало списка
	int Add(ValueType v) const;//Добавление элемента в конец списка. Возвращает количество элементов в списке
	int Del() const; //Удаление элемента из списка. Возвращает количество элементов в списке. 
	void Clearlist() const; //Очистка списка
	ValueType Last() const; //Возвращает данные последнего элемента списка
	std::ostream& Print(std::ostream& ostrm) const;
};

#endif	// UNILIST_H_20151023