#include "trainwindow.h"
#include "ui_trainwindow.h"

TrainWindow::TrainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrainWindow)
{
    ui->setupUi(this);
    setTicketTableWidget();
}

TrainWindow::~TrainWindow()
{
    delete ui;
}

void TrainWindow::setWagonsInfo(int train_num,
                                QString dep_point, QString arr_point,
                                QDate dep_date, QTime dep_time,
                                QDate arr_date, QTime arr_time)
{
    train_number = train_num;
    inputFile = new QFile;
    QString str;
    int i = 0;

    ui->lineEdit_3->setText("Поезд № " + QString::number(train_number) + ". Маршрут " + dep_point + "-" + arr_point);
    ui->lineEdit_4->setText(dep_date.toString("d.M.yyyy") + ", " + dep_time.toString("h.mm"));
    ui->lineEdit_5->setText(arr_date.toString("d.M.yyyy") + ", " + arr_time.toString("h.mm"));

    inputFile->setFileName("C:/Users/ROMAN/Documents/ARM_ZHD_V2/train" + QString::number(train_number) + ".txt");
    inputFile->open((QIODevice::ReadOnly | QIODevice::Text));

    while(!inputFile->atEnd())
    {
        str = inputFile->readLine();
        i++;
    }

    inputFile->close();

    for (int j = 1; j <= i/2; j++)
        ui->comboBox->addItem("Вагон № " + QString::number(j));

    inputFile->close();
}

void TrainWindow::setTicketTableWidget()
{
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels({"Вагон", "Место", "Цена, руб."});
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void TrainWindow::receiveData(int train_num,
                              QString dep_point, QString arr_point,
                              QDate dep_date, QTime dep_time,
                              QDate arr_date, QTime arr_time)
{
    setWagonsInfo(train_num, dep_point, arr_point, dep_date, dep_time, arr_date, arr_time);
}

void TrainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    int i = 0;
    QString str;
    QStringList lst;
    int int_wagon_type_row_counter;

    QString wagon_num = arg1.split(" ").at(2);

    inputFile->open((QIODevice::ReadOnly | QIODevice::Text));
    while(!inputFile->atEnd())
    {
        str = inputFile->readLine();
        if ((i % 2 == 0) && (str.split(" ").at(0) == wagon_num))
            break;
        i++;
    }

    if (str.split(" ").at(1) == "PLAC")
    {
        ui->lineEdit->setText("Плацкарт");
        int_wagon_type_row_counter = 3;
    }
    else
    {
        ui->lineEdit->setText("Купе");
        int_wagon_type_row_counter = 2;
    }
    ui->lineEdit_2->setText(str.split(" ").at(2));

    while(ui->horizontalLayout_4->count() != 0)
    {
        QdynamicButton *button = qobject_cast<QdynamicButton*>(ui->horizontalLayout_4->itemAt(0)->widget());

        button->hide();
        delete button;
    }
    while(ui->horizontalLayout_5->count() != 0)
    {
        QdynamicButton *button = qobject_cast<QdynamicButton*>(ui->horizontalLayout_5->itemAt(0)->widget());

        button->hide();
        delete button;
    }
    while(ui->horizontalLayout_6->count() != 0)
    {
        QdynamicButton *button = qobject_cast<QdynamicButton*>(ui->horizontalLayout_6->itemAt(0)->widget());

        button->hide();
        delete button;
    }

    str = inputFile->readLine();
    lst = str.split(" ");

    for (i = 0; i < lst.length() / int_wagon_type_row_counter; i++)
    {
        QdynamicButton *button = new QdynamicButton(this);
        button->setText("Место\n №" + lst.at(i * 2));
        button->setID(lst.at(i * 2).toInt());
        button->setMinimumSize(0, 70);
        connect(button, SIGNAL(clicked()), this, SLOT(slotGetNumber()));
        if (lst.at(i * 2 + 1).toInt() != 0)
            button->setEnabled(false);
        if (i < lst.length() / (int_wagon_type_row_counter))
        {
            if (button->getID() % 2 != 0)
                ui->horizontalLayout_4->addWidget(button);
            else
                ui->horizontalLayout_5->addWidget(button);
        }
    }
    if (int_wagon_type_row_counter == 3)
        for ( i = lst.length() / 2 - 1; i > lst.length() / int_wagon_type_row_counter - 1; i--)
        {
            QdynamicButton *button = new QdynamicButton(this);
            button->setText("Место\n №" + lst.at(i * 2));
            button->setID(lst.at(i * 2).toInt());
            button->setMinimumSize(0, 70);
            connect(button, SIGNAL(clicked()), this, SLOT(slotGetNumber()));
            if (lst.at(i * 2 + 1).toInt() != 0)
                button->setEnabled(false);
            ui->horizontalLayout_6->addWidget(button);
        }

    inputFile->close();

}

void TrainWindow::slotGetNumber()
{
    QdynamicButton *button = (QdynamicButton*) sender(); // Определение кнопки, вызвавшей сигнал
    bool addFlag = true;

    if (ui->tableWidget->rowCount() == 0)
        addFlag = true;
    else
    {
        for (int i = 0; i < ui->tableWidget->rowCount(); i++)
        {
            if ((((ui->comboBox->itemText(ui->comboBox->currentIndex())).split(" ").at(2)) == (ui->tableWidget->item(i, 0)->text()))
                    && QString::number(button->getID()) == (ui->tableWidget->item(i, 1)->text()))
            {
                addFlag = false;
                break;
            }
        }
    }

    if (addFlag)
    {
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
        ui->tableWidget->setItem((ui->tableWidget->rowCount() - 1), 0,
                                 new QTableWidgetItem((ui->comboBox->itemText(ui->comboBox->currentIndex())).split(" ").at(2)));
        ui->tableWidget->setItem((ui->tableWidget->rowCount() - 1), 1,
                                 new QTableWidgetItem(QString::number(button->getID())));
        ui->tableWidget->setItem((ui->tableWidget->rowCount() - 1), 2,
                                 new QTableWidgetItem((ui->lineEdit_2->text())));
        ui->lineEdit_6->setText(QString::number((ui->lineEdit_6->text()).toInt() + (ui->lineEdit_2->text()).toInt() ));
    }
}

void TrainWindow::on_pushButton_clicked()
{
    QVector<int> selectedRows;
        foreach (QModelIndex index, ui->tableWidget->selectionModel()->selectedRows())
        {
            selectedRows.append(index.row());
        }
        for(int i = selectedRows.length() - 1; i != -1; i--)
        {
            ui->lineEdit_6->setText(QString::number((ui->lineEdit_6->text()).toInt() - (ui->tableWidget->item(selectedRows[i], 2)->text()).toInt() ));
            ui->tableWidget->removeRow(selectedRows[i]);
        }
}

void TrainWindow::on_pushButton_2_clicked()
{
    QStringList tablelist;

    QString sum = ui->lineEdit_6->text();

    int rows = ui->tableWidget->rowCount();
    if (rows > 0)
    {
        paywindow = new Paywindow;
        paywindow->setModal(true);
        paywindow->show();

        int columns = ui->tableWidget->columnCount();
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                tablelist.push_back(ui->tableWidget->item(i, j)->text());

        QObject::connect(paywindow, SIGNAL(accepted()), this, SLOT(close()));

        connect(this, SIGNAL(sendData(QString, QStringList, int, int, int)), paywindow, SLOT(receiveData(QString, QStringList, int, int, int)));
        sendData(sum, tablelist, rows, columns, train_number);
    }
    else
        QMessageBox::warning(this, "Неудача", "Повторите попытку!");
}
