/* ФИО: Вдовкин Василий Алексеевич
 * Группа БИВ-141
 * Задачи:
 * Создать класс банковских операция
 * Хрань его в бинарном дереве
 * Реализация
 * Создан класс банковских операций bankRecord с полями ID, sum, sender, reciever, data
 * От него наследован класс bankRecord_ext с дополнительными полями country, currency
 * Класс-контейнер binaryTree представляет собой обёртку над stl-контейнер multiset с добавлением в дерево по сумме операции (sum)
 * Класс-контейнер шаблонный для возможности создания контейнеров и для bankRecord и для bankRecord_ext
 * Создан итерфейс, использованы виджеты lineEdit, Label, combobox, list, pushButton
 *
*/
//Qt'шный темплейт для интерфейса
#include "mainwindow.h"
#include <QApplication>
#include "classes/binarytree.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

/* Выводы:
*  Создание лабы позволило изучить:
*  Основные принципы ООП
*  Контейнерные классы библитеки stl
*  Написание компараторных функции
*  Работу с интерфейсом Qt
*  0.01% возможностей плюсов
*
*/
