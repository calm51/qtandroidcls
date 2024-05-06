#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <qlabel.h>

#include <qtandroidcls/qtandroidcls.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QtAndroidCls *qac = QtAndroidCls::instance("ca/calm/qtandroiddemo/qtandroiddemo");

    connect(qac,&QtAndroidCls::statusbarHeightChanged, this,[=](qint32 i){
        ui->label->setFixedHeight(i);
        ui->label->setText("--------------"+QString::number(i));
    });
    connect(ui->pushButton_2,&QPushButton::clicked, this,[=](){
        qac->vibrate(-1);
    });
    connect(ui->pushButton_3,&QPushButton::clicked, this,[=](){
        qac->vibrate(ui->spinBox->value());
    });
    connect(ui->pushButton_4,&QPushButton::clicked, this,[=](){
        qac->vibrate(0);

    });
    connect(ui->pushButton_5,&QPushButton::clicked, this,[=](){
        qac->notify(ui->lineEdit->text(),ui->lineEdit_2->text());
    });
    connect(ui->pushButton_6,&QPushButton::clicked, this,[=](){
        qac->toast(ui->lineEdit_3->text());
    });
    connect(ui->pushButton_7,&QPushButton::clicked, this,[=](){
        qac->speak(ui->lineEdit_3->text());
    });
    // qac->move_to_background();

    ui->lineEdit_3->setText(ui->lineEdit_3->text()+"   "+QString::number(qac->get_statusbar_qwiget_height()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

