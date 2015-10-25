#ifndef UNILIST_H_20151023
#define UNILIST_H_20151023 

#include <cstddef>
#include <cstdint> 
#include <iostream>
#include <initializer_list>
#include <memory> 

using ValueType = int32_t; 
using IndexType = ptrdiff_t; 

using namespace std;

class UniList{
    private:
        struct Node 
        {
            ValueType val_{0};      //������
            Node* next_{nullptr};   //��������� �� ��������� ����
        };

        Node* head_{ nullptr };     //��������� �� ��������� ...
        Node* tail_{ nullptr };     //... � �������� ���� ������

    public:
        UniList() = default;                            //����������� �� ���������
        UniList(int len);                               //����������� "�������" ������ �������� �����    
        UniList(std::initializer_list<ValueType> vals); //����������� ������ �� ������� �������� ��������
        ~UniList();                                     //����������

        bool operator==(const UniList&);                //���������� �������� "==" - �������� �� �����������
        bool operator!=(const UniList&);                //���������� �������� "!=" - �������� �� �����������
        UniList& operator=(const UniList&);             //���������� �������� ������������
        ValueType& operator[](const IndexType index);   //���������� �������� [] -������ � �������� � �������� �������

        bool IsEmpty();                                 //�������� ������� ������
        void Add(ValueType v);                          //���������� �������� � ����� ������
        void Del();                                     //�������� �������� � ����� ������
        void Print();                                   //������� ������ ������ �� �����
    };

#endif	// UNILIST_H_20151023