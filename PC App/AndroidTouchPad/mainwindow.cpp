#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->labelIP->setText("IP: ");
    ui->labelPort->setText("Port: ");
}

MainWindow::~MainWindow()
{
    delete ui;
}
