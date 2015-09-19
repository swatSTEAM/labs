//Qt'шный темплайт для интерфейса
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "classes/binarytree.h"
#include "classes/bankrecord.h"
#include "classes/bankrecord_ext.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    binaryTree<bankRecord_ext> *tree;             //Дерево для расширенных рекордов
    binaryTree<bankRecord> *tree_usual;           //Дерево для стандартных рекордов
    bool change = false;                          //Статус кнопки
    bool ext = true;                              //Использовать расширенный тип рекорда
    void updateTreeCtrl();                        //Обновление контрола дерева
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_lineEdit_3_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
