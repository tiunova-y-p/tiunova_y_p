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
            ValueType val_{0};      //Данные
            Node* next_{nullptr};   //Указатель на следующий узел
        };

        Node* head_{ nullptr };     //Указатели на начальный ...
        Node* tail_{ nullptr };     //... и конечный узлы списка

    public:
        UniList() = default;                            //Конструктор по умолчанию
        UniList(int len);                               //Конструктор "пустого" списка заданной длины    
        UniList(std::initializer_list<ValueType> vals); //Конструктор списка по перечню заданных значений
        ~UniList();                                     //Деструктор

        bool operator==(const UniList&);                //Перегрузка операции "==" - проверка на неравенство
        bool operator!=(const UniList&);                //Перегрузка операции "!=" - проверка на неравенство
        UniList& operator=(const UniList&);             //Перегрузка операции присваивания
        ValueType& operator[](const IndexType index);   //Перегрузка операции [] -доступ к элементу в заданной позиции

        bool IsEmpty();                                 //Проверка пустоты списка
        void Add(ValueType v);                          //Добавление элемента в конец списка
        void Del();                                     //Удаление элемента в конце списка
        void Print();                                   //Функция вывода списка на экран
    };

#endif	// UNILIST_H_20151023