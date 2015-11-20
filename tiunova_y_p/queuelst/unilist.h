#ifndef UNILIST_H_20151023
#define UNILIST_H_20151023 

#include <iostream>
#include <initializer_list>
#include <memory> 

class UniList{

    using ValueType = int32_t;
    using IndexType = ptrdiff_t;

        class Node
        {
        public:
            ValueType val_{0};      //������
            Node* next_{nullptr};   //��������� �� ��������� ����

            Node() = default;
            Node(ValueType v, Node* nxt) : val_{ v }, next_{ nxt }
            {}
        };

    public:
        UniList() = default;                            //����������� �� ���������
        UniList(int len);                               //����������� "�������" ������ �������� �����    
        UniList(std::initializer_list<ValueType> vals); //����������� ������ �� ������� �������� ��������
        ~UniList();                                     //����������

        bool operator==(const UniList&);                //���������� �������� "==" - �������� �� �����������
        bool operator!=(const UniList&);                //���������� �������� "!=" - �������� �� �����������
        UniList& operator=(const UniList&);             //���������� �������� ������������
        ValueType& operator[](const IndexType index);   //���������� �������� [] -������ � �������� � �������� �������

        bool isEmpty() const;                           //�������� ������� ������
        void add(ValueType v);                          //���������� �������� � ����� ������
        void del();                                     //�������� �������� � ����� ������
        void deltop();                                  //�������� �������� � ������ ������
        void print();                                   //������� ������ ������ �� �����
        UniList* reverse();                             //��������� ������
        int length();                                   //����� ������
        void clear();                                   //������� ������

private:
        Node* head_{ nullptr };     //��������� �� ��������� ...
};

#endif	// UNILIST_H_20151023