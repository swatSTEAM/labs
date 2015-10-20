//Qt'шный темплайт для интерфейса
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "classes/binarytree.h"
#include "classes/bankrecord.h"
#include "classes/bankrecord_ext.h"
#include <QMainWindow>
#include <QTableWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    binaryTree<bankRecord> *tree;                 //Дерево для расширенных рекордов
    bool change = false;                          //Статус кнопки
                                                  //Обновление контрола дерева
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

//    void on_listWidget_itemClicked(QListWidgetItem *item);
    void updateTreeCtrl();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged();

    void on_lineEdit_3_textChanged();

    void on_checkBox_stateChanged();

    void on_tableWidget_itemClicked();

    void on_tableWidget_itemSelectionChanged();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::MainWindow *ui;

    void hideExtCtrl();
    void showExtCtrl();
};

#endif // MAINWINDOW_H
