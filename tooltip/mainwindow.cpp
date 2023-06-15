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
    //    m_pTooltip->setContent("测试内容信息测试内容信息测试内容信息测试内容信息测试内容信息测试内容信息测fqrfeqrf试内容信息rafkrnigrleigutgowalunrovniltgouv");
    m_pTooltip->setContent("像素蛋糕文件名像素蛋糕文件名像素蛋糕文件名文件名文件名IMG_5610PixCake-IMG_5610PixCake-IMG_5610.JPG");

    //m_pTooltip->resize(300,300);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked(bool checked)
{
    //    TsToolTip *tooltip = new TsToolTip(this);
    //    tooltip->setContent("测试tooltip内容超长。。。");
    //    tooltip->show();

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"zhy mouse move event "<<event<<event->pos();

//    m_pTooltip->setTriangleInfo(10, 6);
   m_pTooltip->placeTip(mapToGlobal(event->pos()));
    //m_pTooltip->move(mapToGlobal(event->pos()));

}
