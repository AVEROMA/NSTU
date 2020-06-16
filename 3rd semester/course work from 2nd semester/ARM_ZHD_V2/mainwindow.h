#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QLabel>
#include <QHBoxLayout>
#include <QFile>
#include <QTableWidget>
#include <QDateTime>

#include "trainwindow.h"

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

signals:
    void sendData(int, QString, QString, QDate, QTime, QDate, QTime);

private:
    Ui::MainWindow *ui;
    TrainWindow *trainwindow;
    void setTableWidget();
};
#endif // MAINWINDOW_H
