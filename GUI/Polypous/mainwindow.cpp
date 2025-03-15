#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "../../home/Geodesik_/Documents/Programmation/Web_Browser/includes/http.hpp"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    std::string text_test = "j'aime le poulpe c'est vraiment très bon sa mère holalalalalallala";

    ui->setupUi(this);

    textLabel = new QLabel (QString::fromStdString(text_test), this);
    // Optionally set the label's alignment or other properties
    textLabel->setAlignment(Qt::AlignCenter);

    // Set the QLabel's geometry or add it to a layout
    textLabel->setGeometry(10, 10, 1080, 500); // Example geometry

    //QTextLayout(QString::fromStdString(text_test));
}

MainWindow::~MainWindow()
{
    delete ui;
}
