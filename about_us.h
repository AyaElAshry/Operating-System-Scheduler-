#ifndef ABOUT_US_H
#define ABOUT_US_H

#include <QDialog>

namespace Ui {
class about_us;
}

class about_us : public QDialog
{
    Q_OBJECT

public:
    explicit about_us(QWidget *parent = nullptr);
    ~about_us();

private:
    Ui::about_us *ui;
};

#endif // ABOUT_US_H
