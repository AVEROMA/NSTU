#ifndef PAYWINDOW_H
#define PAYWINDOW_H

#include <QDialog>
#include <QStringList>
#include <QFile>
#include <QMessageBox>

namespace Ui {
class Paywindow;
}

class Paywindow : public QDialog
{
    Q_OBJECT

public:
    explicit Paywindow(QWidget *parent = nullptr);
    ~Paywindow();

public slots:
    void receiveData(QString, QStringList, int, int, int);

private slots:
    void on_pushButton_1_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_card_clicked();

    void on_pushButton_pay_clicked();

    void on_lineEdit_2_textChanged(const QString &arg1);

private:
    Ui::Paywindow *ui;
    QString money_sum;
    int train_num;
    void setWindow(QString, QStringList, int, int, int);
    void setTicketTableWidget();
};

#endif // PAYWINDOW_H
