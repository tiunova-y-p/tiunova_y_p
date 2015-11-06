#ifndef UNILIST_H_20151023
#define UNILIST_H_20151023 

#include <iostream>
#include <initializer_list>
#include <memory> 

//using namespace std;

class UniList{

    using ValueType = int32_t;
    using IndexType = ptrdiff_t;

        class Node
        {
        public:
            ValueType val_{0};      //Данные
            Node* next_{nullptr};   //Указатель на следующий узел

            Node() = default;
            Node(ValueType v, Node* nxt) : val_{ v }, next_{ nxt }
            {}
        };

    public:
        UniList() = default;                            //Конструктор по умолчанию
        UniList(int len);                               //Конструктор "пустого" списка заданной длины    
        UniList(std::initializer_list<ValueType> vals); //Конструктор списка по перечню заданных значений
        ~UniList();                                     //Деструктор

        bool operator==(const UniList&);                //Перегрузка операции "==" - проверка на неравенство
        bool operator!=(const UniList&);                //Перегрузка операции "!=" - проверка на неравенство
        UniList& operator=(const UniList&);             //Перегрузка операции присваивания
        ValueType& operator[](const IndexType index);   //Перегрузка операции [] -доступ к элементу в заданной позиции

        //bool IsEmpty();                                 //Проверка пустоты списка
        bool isEmpty() const;                                 //Проверка пустоты списка
        //void Add(ValueType v);                          //Добавление элемента в конец списка
        void add(ValueType v);                          //Добавление элемента в конец списка
        //void Del();                                     //Удаление элемента в конце списка
        void del();                                     //Удаление элемента в конце списка
        //void Print();                                   //Функция вывода списка на экран
        void print();                                   //Функция вывода списка на экран
        UniList* reverse();                             //*** Обращение списка
        int length();                                   //*** Длина списка
        void clear();                                   //Очистка списка

private:
        Node* head_{ nullptr };     //Указатели на начальный ...
        //Node* tail_{ nullptr };     //... и конечный узлы списка
};

#endif	// UNILIST_H_20151023