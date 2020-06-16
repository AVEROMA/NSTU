#include "paywindow.h"
#include "ui_paywindow.h"

Paywindow::Paywindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Paywindow)
{
    ui->setupUi(this);
    setTicketTableWidget();
}

Paywindow::~Paywindow()
{
    delete ui;
}

void Paywindow::receiveData(QString sum, QStringList tablelist, int rows, int columns, int train_number)
{
    setWindow(sum, tablelist, rows, columns, train_number);
}

void Paywindow::setTicketTableWidget()
{
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels({"Вагон", "Место", "Цена, руб."});
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void Paywindow::setWindow(QString sum, QStringList tablelist, int rows, int columns, int train_number)
{
    money_sum = sum;
    train_num = train_number;
    ui->lineEdit->setText(money_sum);
    if (ui->lineEdit_2->text().toInt() < ui->lineEdit->text().toInt())
        ui->lineEdit_3->setText("Недостаточно средств");
    else
        ui->lineEdit_3->setText(QString::number(ui->lineEdit_2->text().toInt() - ui->lineEdit->text().toInt()));


    int place_counter = 0;
    for (int i = 0; i < rows; i++)
    {
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
        for (int j = 0; j < columns; j++)
        {
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(tablelist.at(place_counter++)));
        }
    }
}

void Paywindow::on_pushButton_1_clicked()
{
    ui->lineEdit_2->setText(QString::number(ui->lineEdit_2->text().toInt() + ui->pushButton_1->text().toInt()));
}

void Paywindow::on_pushButton_2_clicked()
{
    ui->lineEdit_2->setText(QString::number(ui->lineEdit_2->text().toInt() + ui->pushButton_2->text().toInt()));
}
void Paywindow::on_pushButton_3_clicked()
{
    ui->lineEdit_2->setText(QString::number(ui->lineEdit_2->text().toInt() + ui->pushButton_3->text().toInt()));
}

void Paywindow::on_pushButton_4_clicked()
{
    ui->lineEdit_2->setText(QString::number(ui->lineEdit_2->text().toInt() + ui->pushButton_4->text().toInt()));
}

void Paywindow::on_pushButton_5_clicked()
{
    ui->lineEdit_2->setText(QString::number(ui->lineEdit_2->text().toInt() + ui->pushButton_5->text().toInt()));
}

void Paywindow::on_pushButton_6_clicked()
{
    ui->lineEdit_2->setText(QString::number(ui->lineEdit_2->text().toInt() + ui->pushButton_6->text().toInt()));
}

void Paywindow::on_pushButton_7_clicked()
{
    ui->lineEdit_2->setText(QString::number(ui->lineEdit_2->text().toInt() + ui->pushButton_7->text().toInt()));
}

void Paywindow::on_pushButton_8_clicked()
{
    ui->lineEdit_2->setText(QString::number(ui->lineEdit_2->text().toInt() + ui->pushButton_8->text().toInt()));
}

void Paywindow::on_pushButton_9_clicked()
{
    ui->lineEdit_2->setText(QString::number(ui->lineEdit_2->text().toInt() + ui->pushButton_9->text().toInt()));
}

void Paywindow::on_pushButton_10_clicked()
{
    ui->lineEdit_2->setText(QString::number(ui->lineEdit_2->text().toInt() + ui->pushButton_10->text().toInt()));
}

void Paywindow::on_pushButton_card_clicked()
{
    ui->lineEdit_2->setText("Безналичный расчет");

}

void Paywindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    if (ui->lineEdit_2->text() != "Безналичный расчет")
    {
        if (ui->lineEdit_2->text().toInt() < ui->lineEdit->text().toInt())
            ui->lineEdit_3->setText("Недостаточно средств");
        else
            ui->lineEdit_3->setText(QString::number(ui->lineEdit_2->text().toInt() - ui->lineEdit->text().toInt()));
    }
    else
        ui->lineEdit_3->setText("Безналичный расчет");
}

void Paywindow::on_pushButton_pay_clicked()
{
    QStringList fileList;
    QStringList changeStrList;

    QFile inputFile("C:/Users/ROMAN/Documents/ARM_ZHD_V2/train" + QString::number(train_num) + ".txt");
    inputFile.open((QIODevice::ReadWrite | QIODevice::Text));
    if ((ui->lineEdit_3->text().toInt() >= 0 || ui->lineEdit_3->text() == "Безналичный расчет") &&
            ui->lineEdit_3->text() != "Недостаточно средств")
    {
        while(!inputFile.atEnd())
        {
            fileList.push_back(inputFile.readLine());
        }
        inputFile.remove();
        inputFile.close();
        inputFile.setFileName("C:/Users/ROMAN/Documents/ARM_ZHD_V2/train" + QString::number(train_num) + ".txt");
        inputFile.open((QIODevice::ReadWrite | QIODevice::Text));
        for (int i = 1; i < fileList.length(); i++)
        {
            for (int j = 0; j < ui->tableWidget->rowCount(); j++)
            {
                if (ui->tableWidget->item(j, 0)->text() == fileList[i - 1].split(" ").at(0) && i % 2 != 0)
                {
                    changeStrList = fileList[i].split(" ");
                    fileList[i].clear();
                    changeStrList[(ui->tableWidget->item(j, 1)->text().toInt() - 1) * 2 + 1].replace(0, 1, "1");
                    for(int k = 0; k < changeStrList.length(); k++)
                    {
                        if (changeStrList[k] != "\n")
                            fileList[i].append(changeStrList[k] + ' ');
                    }
                    fileList[i].append("\n");
                }
            }
        }
        for (int i = 0; i < fileList.length(); i++)
            inputFile.write(fileList[i].toUtf8());
        inputFile.close();

        QMessageBox::information(this, "Успешно", "Билеты оплачены");
        this->accept();
    }
    else
    {
        QMessageBox::warning(this, "Неудача", "Повторите попытку!");
    }
}
