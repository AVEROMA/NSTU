#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setTableWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTableWidget()
{
    QString str; //Строка для считывания из файла
    QStringList lst; //Список для разбиения строки на элементы
    int i = 0; // счетчик строк в таблице

    QFile inputFile("C:/Users/ROMAN/Documents/ARM_ZHD_V2/trains.txt");
    inputFile.open(QIODevice::ReadOnly);

    ui->tableWidget->setColumnCount(7);
    QStringList TableHeader;
    TableHeader<<"Номер поезда"<<"Пункт отправления"<<"Пункт прибытия"<<"Дата отправления"<<"Время отправления"<<"Дата прибытия"<<"Время прибытия";
    ui->tableWidget->setHorizontalHeaderLabels(TableHeader);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    while(!inputFile.atEnd())
            {
                ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
                str = inputFile.readLine(); //считать строку
                lst = str.split(" "); //поделить строку и записать в список
                ui->tableWidget->setItem(i, 0, new QTableWidgetItem(lst.at(0)));
                ui->tableWidget->setItem(i, 1, new QTableWidgetItem(lst.at(1)));
                ui->tableWidget->setItem(i, 2, new QTableWidgetItem(lst.at(2)));
                ui->tableWidget->setItem(i, 3, new QTableWidgetItem(lst.at(3)));
                ui->tableWidget->setItem(i, 4, new QTableWidgetItem(lst.at(4)));
                ui->tableWidget->setItem(i, 5, new QTableWidgetItem(lst.at(5)));
                ui->tableWidget->setItem(i, 6, new QTableWidgetItem(lst.at(6)));
                i++;
            }

    inputFile.close();
}

void MainWindow::on_pushButton_clicked()
{
    int row_num = ui->tableWidget->selectionModel()->currentIndex().row();
    int train_num = (ui->tableWidget->item(row_num, 0)->text()).toInt();
    QString departure_point = ui->tableWidget->item(row_num, 1)->text();
    QString arrival_point = ui->tableWidget->item(row_num, 2)->text();
    QDate dep_date = QDate::fromString(ui->tableWidget->item(row_num, 3)->text(),"d.M.yyyy");
    QTime dep_time = QTime::fromString(ui->tableWidget->item(row_num, 4)->text(), "h:mm");
    QDate arr_date = QDate::fromString(ui->tableWidget->item(row_num, 5)->text(),"d.M.yyyy");
    QTime arr_time = QTime::fromString(ui->tableWidget->item(row_num, 6)->text(), "h:mm");

    trainwindow = new TrainWindow;
    trainwindow->setModal(true);
    trainwindow->show();

    connect(this, SIGNAL(sendData(int, QString, QString, QDate, QTime, QDate, QTime)),
            trainwindow, SLOT(receiveData(int, QString, QString, QDate, QTime, QDate, QTime)));
    sendData(train_num, departure_point, arrival_point, dep_date, dep_time, arr_date, arr_time);
}
