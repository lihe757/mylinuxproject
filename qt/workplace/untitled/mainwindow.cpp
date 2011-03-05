#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_4_textEdited(QString )
{
    ui->lineEdit->setText(ui->lineEdit_4->text());

}

void MainWindow::on_checkBox_toggled(bool checked)
{

    QString countStr=ui->lineEdit_3->text();




    ui->lineEdit->setText("proc_"+countStr.sprintf("%s",1));
    ui->lineEdit_2->setText("target_"+ui->lineEdit_3->text());

}
