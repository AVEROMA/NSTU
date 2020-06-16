#ifndef TRAINWINDOW_H
#define TRAINWINDOW_H

#include <QScrollArea>
#include <QLabel>
#include <QHBoxLayout>
#include <QFile>
#include <QTableWidget>
#include <QDateTime>
#include <QDialog>
#include <QVector>

#include "qdynamicbutton.h"
#include "paywindow.h"

namespace Ui {
class TrainWindow;
}

class TrainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TrainWindow(QWidget *parent = nullptr);
    ~TrainWindow();

public slots:
    void receiveData(int, QString, QString, QDate, QTime, QDate, QTime);

signals:
    void sendData(QString, QStringList, int, int, int);

private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);
    void slotGetNumber();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::TrainWindow *ui;
    int train_number;
    QFile *inputFile;
    Paywindow *paywindow;
    void setWagonsInfo(int, QString, QString, QDate, QTime, QDate, QTime);
    void setTicketTableWidget();
};

#endif // TRAINWINDOW_H
