#ifndef UNILIST_H_20151023
#define UNILIST_H_20151023 

#include <cstdint> 
#include <iostream>

using ValueType = int32_t; 
using IndexType = ptrdiff_t; 

using namespace std;

class node //����� node �������� ������ ��������/���� ������
{
private:
    ValueType val_; 	//������ ��������/���� ������
    node* next_; 	//��������� �� ��������� ������� � ������

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
	node* head_{ nullptr }; //��������� �� ������ ������ �����/���������
	int count_; //���������� ��������� � ������

public:
    UniList();
	~UniList();

	int GetCount() const; //���������� ���������� ��������� � ������
    void SetCount(int c);
    int IncCount();
	node* GetHead() const; //���������� ��������� �� ������ ������
	int Add(ValueType v) const;//���������� �������� � ����� ������. ���������� ���������� ��������� � ������
	int Del() const; //�������� �������� �� ������. ���������� ���������� ��������� � ������. 
	void Clearlist() const; //������� ������
	ValueType Last() const; //���������� ������ ���������� �������� ������
	std::ostream& Print(std::ostream& ostrm) const;
};

#endif	// UNILIST_H_20151023