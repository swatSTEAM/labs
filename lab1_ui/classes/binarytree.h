#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include "bankrecord.h"
#include <QListWidget>
#include <QMutex>

using namespace std;

template<typename Type>
struct comparator {                                                         //Определяет по какому свойству рекорды добавляются в дерево
    bool operator() (const Type* lhs, const Type* rhs) const {              //true в правую ветку, false в левую
        return (*lhs).getSum()<(*rhs).getSum();                             //Добавляем по сумме.
    }
};

template<typename Type>
class binaryTree {
    multiset<Type*,comparator<Type>> content;                               //multiset контейнер-дерево.
    mutable uint count_u = 0;
    mutable uint count_e = 0;
public:
    binaryTree() {}
    binaryTree(const binaryTree&);
    void insert(Type* record);                                              //Вставление элемента
    Type& findByID(const int ID) const;                                     //Поиск элемента по ID
    void removeByID(const int ID);                                          //Удаления элемента по ID
    string toString() const;
    Type& operator[](const int num) const;                                  //Получение элемента по n'му итератору
    ulong operator()(const int num) const;
    multiset<Type*,comparator<Type>>& getContent();                         //Получение multiset-контейнера
    bool pop();
    QMutex dataMutex;
    bool Work = false;
    bool Consume = true;
    ~binaryTree();
};

template<typename Type>
binaryTree<Type>::~binaryTree() {
    for (auto curr:content) {
            delete curr;
    }
}

//Methods
template<typename Type>
Type& binaryTree<Type>::findByID(const int ID) const {
    for (auto curr:content) {
        if ((*curr).getID() == ID)                             //Итерируем по дерево
            return curr;                                       //Пока не найдём рекорд с нужным айди
    }
    throw invalid_argument("Can't find record with ID: " + to_string(ID));
}

template<typename Type>
bool binaryTree<Type>::pop() {
    if (content.size()==0) {
        return false;
    } else {
        auto curr = *content.begin();
        content.erase(content.begin());
        delete curr;
        return true;
    }
}


template<typename Type>
void binaryTree<Type>::insert(Type* record) {
    record->isExtended() ? count_e+=1: count_u+=1;
    this->content.insert(record);
}

template<typename Type>
void binaryTree<Type>::removeByID(const int ID) {
    typename multiset<Type*,comparator<Type>>::iterator it;
    for (it=content.begin(); it!=content.end(); ++it) {     //Аналогичено с find, но с итератором
        Type* curr = *it;
        if ((*curr).getID() == ID) {
            content.erase(it);                              //set требует итератор для удаления
            delete curr;
            return;
        }
    }
    throw invalid_argument("Can't find record with ID: " + to_string(ID));
}

template<typename Type>
string binaryTree<Type>::toString() const {
    ostringstream strStream;
    for (auto curr:content) {
        strStream << (*curr).toString() << endl;               //Собираем все объекты-члены в строку
    }
    return strStream.str();
}

template<typename Type>
Type& binaryTree<Type>::operator[](const int num) const {
    return **(std::next(content.begin(),num));               //Возвращаем значение итератора, находящемся на num месте от начала.
}

template<typename Type>
ulong binaryTree<Type>::operator()(const int num) const {
    return (*(std::next(content.begin(),num)))->getSum();
}

template<typename Type>
multiset<Type*,comparator<Type>>& binaryTree<Type>::getContent() {
    return content;
}

typedef binaryTree<bankRecord> treeRecs;
#endif // BINARYTREE_H
