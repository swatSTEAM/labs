#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include "bankrecord.h"
#include <QListWidget>

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
public:
    binaryTree() {}
    binaryTree(const binaryTree&);
    void insert(Type* record);                                              //Вставление элемента
    Type& findByID(const int ID);                                           //Поиск элемента по ID
    void removeByID(const int ID);                                          //Удаления элемента по ID
    string toString();

    Type& operator[](const int num);                                        //Получение элемента по n'му итератору
    multiset<Type*,comparator<Type>>& getContent();                          //Получение multiset-контейнера
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
Type& binaryTree<Type>::findByID(const int ID) {
    for (auto curr:content) {
        if ((*curr).getID() == ID)                             //Итерируем по дерево
            return curr;                                       //Пока не найдём рекорд с нужным айди
    }
    throw invalid_argument("Can't find record with ID: " + to_string(ID));
}

template<typename Type>
void binaryTree<Type>::insert(Type* record) {
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
string binaryTree<Type>::toString() {
    ostringstream strStream;
    for (auto curr:content) {
        strStream << (*curr).toString(false) << endl;               //Собираем все объекты-члены в строку
    }
    return strStream.str();
}

template<typename Type>
Type& binaryTree<Type>::operator[](const int num) {
    return **(std::next(content.begin(),num));               //Возвращаем значение итератора, находящемся на num месте от начала.
}

template<typename Type>
multiset<Type*,comparator<Type>>& binaryTree<Type>::getContent() {
    return content;
}


#endif // BINARYTREE_H
