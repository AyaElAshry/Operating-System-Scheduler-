#include "about_us.h"
#include "ui_about_us.h"

about_us::about_us(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about_us)
{
    ui->setupUi(this);

    QPixmap pix("C:/Users/Aya El Ashry/Downloads/OS PROJECT/aya/image2.jpeg");
    int w = ui->label_image2->width();
    int h = ui->label_image2->height();
    ui->label_image2->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    ui->label->setText("Copyright 2020 the AAY company all rights reserved");
    ui->label_6->setStyleSheet("QLabel { color : red; }");
    ui->label->adjustSize();
    ui->label_2->adjustSize();
    ui->label_3->adjustSize();
    ui->label_4->adjustSize();
}

about_us::~about_us()
{
    delete ui;
}
