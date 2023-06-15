#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "tstooltip.h"
#include <QDebug>
#include <QPushButton>
#include <QMouseEvent>
#include <QTimer>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pTooltip = new TsToolTip();
    m_pTooltip->setContent("像素蛋糕文件名像素蛋糕文件名像素蛋糕文件名文件名文件名IMG_5610PixCake-IMG_5610PixCake-IMG_5610.JPG");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
   m_pTooltip->placeTip(mapToGlobal(event->pos()));
}

void MainWindow::on_textEdit_textChanged()
{
    m_pTooltip->setContent(ui->textEdit->toPlainText());
}

