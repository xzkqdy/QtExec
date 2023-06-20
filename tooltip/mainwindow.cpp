#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "tstooltip.h"
#include <QDebug>
#include <QPushButton>
#include <QMouseEvent>
#include <QTimer>
#include <QLabel>
#include <QRect>

class TipLabel: public QLabel {
Q_OBJECT
public:
    TipLabel(const QString &content, QWidget *parent = nullptr) : QLabel(content, parent) {
        m_content = content;
        this->setScaledContents(true);
    };

    void setContent(const QString& content){
        m_content = content;
    };
    const QString &getContent() { return m_content; };
    void setText(const QString& string) {
        m_content = string;
        QLabel::setText(string);
    };
signals:

    void onTipLabelHover(const QPoint& pos , const QString &text);

    void onTipLabelLeave();
protected:
    void enterEvent(QEvent *event) override {
        QPoint pos = this->pos();
        pos.setX(pos.x()+this->width()/2);
        emit onTipLabelHover(mapToGlobal(pos), this->m_content);
        return QLabel::enterEvent(event);
    }

    void leaveEvent(QEvent *event) override {
        emit onTipLabelLeave();
        qDebug() << "zhy tip label leave ...";
        return QLabel::leaveEvent(event);
    }
    void mouseMoveEvent(QMouseEvent *event) override {
        qDebug() << "mouse move event position is: " << event->pos();
        QLabel::mouseMoveEvent(event);
    }

private:
    QString m_content;
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    // m_pTooltip = new TsToolTip();
    // m_pTooltip->setContent("像素文件名IMG_5610PixCake-IMG_5610PixCake-IMG_5610.JPG");

    tlabel = new TipLabel("测试。", this);
    tlabel->setScaledContents(true);
    tlabel->setContent("像素蛋糕蛋糕像素祷告辞色测试测试OUXPIXCAKE.jpg®");

    //tlabel->resize(20, 40);
    tlabel->move(10, 10);
    connect(tlabel, &TipLabel::onTipLabelHover, [=](const QPoint &pos, const QString &content) {
        qDebug() << "on label enter..."<<content;
        QPoint pos1 = tlabel->pos();
        QString str = tlabel->text();
        QFontMetrics font_metrics = QFontMetrics(tlabel->font());
        QRect text_rect = font_metrics.boundingRect(tlabel->text());
        QPoint text_center = text_rect.center();
        pos1.setX(pos1.x()+text_center.x());
        TsToolTip::showText(mapToGlobal(pos1),content,NULL, QRect(), 1500);
    });
    connect(tlabel, &TipLabel::onTipLabelLeave, [=]() {
        qDebug() << "on label enter...";
        TsToolTip::hideText();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    TsToolTip::showText(mapToGlobal(event->pos()), "test .....像素文件像素文件像素文件像素文件像素文件像素文件像素文件..jpg", NULL, QRect(), 1500);
//    TsToolTip::showText(mapToGlobal(event->pos()),"");
    //  m_pTooltip->placeTip(mapToGlobal(event->pos()));
}

void MainWindow::on_textEdit_textChanged()
{
    TsToolTip::hideText();
  //  m_pTooltip->setContent(ui->textEdit->toPlainText());
}

#include "mainwindow.moc"