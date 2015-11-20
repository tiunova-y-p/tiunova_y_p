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

        bool isEmpty() const;                           //Проверка пустоты списка
        void add(ValueType v);                          //Добавление элемента в конец списка
        void del();                                     //Удаление элемента в конце списка
        void deltop();                                  //Удаление элемента в начале списка
        void print();                                   //Функция вывода списка на экран
        UniList* reverse();                             //Обращение списка
        int length();                                   //Длина списка
        void clear();                                   //Очистка списка

private:
        Node* head_{ nullptr };     //Указатели на начальный ...
};

#endif	// UNILIST_H_20151023