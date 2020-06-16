#ifndef QDYNAMICBUTTON_H
#define QDYNAMICBUTTON_H

#include <QPushButton>

class QdynamicButton : public QPushButton
{
    Q_OBJECT
public:
    explicit QdynamicButton(QWidget *parent = 0);
        ~QdynamicButton();
        int getID();
        void setID(int); // Функция для возврата локального номера кнопки


    public slots:

    private:
        int buttonID = 0;   // Локальная переменная, номер кнопки
    };

#endif // QDYNAMICBUTTON_H
