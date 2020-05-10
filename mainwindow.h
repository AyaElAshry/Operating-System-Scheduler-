#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QTableView>
#include <QStandardItemModel>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_comboBox_mode_activated(int index);

    void on_pushButton_delete_clicked();

    void on_actionabout_us_triggered();

    void on_actionabout_AAY_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene * scene;
    QGraphicsRectItem *rectangle;
    QTableWidget *table;
};
#endif // MAINWINDOW_H
