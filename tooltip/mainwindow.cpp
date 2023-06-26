#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "tstooltip.h"
#include <QDebug>
#include <QPushButton>
#include <QMouseEvent>
#include <QTimer>
#include <QLabel>
#include <QRect>
#include <QFontMetrics>

class TipLabel: public QLabel {
Q_OBJECT
public:
    TipLabel(const QString &content, QWidget *parent = nullptr) : QLabel(content, parent) {
        m_content = content;
        m_postion = QPoint(-1, -1);
        this->setScaledContents(true);
    };

    void setContent(const QString &content) {
        m_content = content;
    };

    const QString &getContent() { return m_content; };

    void setText(const QString &string) {
        m_content = string;
        QLabel::setText(string);
    };
signals:

    void onTipLabelHover(const QPoint &pos, const QString &text);

    void onTipLabelLeave();

protected:
    void enterEvent(QEvent *event) override {
        QPoint pos = this->pos();
        if (pos == m_postion) {
            return;
        }
        m_postion = pos;
        pos.setX(pos.x() + this->width() / 2);
        emit onTipLabelHover(mapToGlobal(pos), this->m_content);
        return QLabel::enterEvent(event);
    }

    void leaveEvent(QEvent *event) override {
        emit onTipLabelLeave();
        qDebug() << "zhy tip label leave ...";
        m_postion = QPoint(-1, -1);
        return QLabel::leaveEvent(event);
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        qDebug() << "mouse move event position is: " << event->pos();
        QLabel::mouseMoveEvent(event);
    }

private:
    QString m_content;
    QPoint m_postion;
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    // m_pTooltip = new TsToolTip();
    // m_pTooltip->setContent("像素文件名IMG_5610PixCake-IMG_5610PixCake-IMG_5610.JPG");

    QString content = "ff40713-6c27-4d41-97ff<br/>40713-6c27-4d41-9a64-33586aa48502a64-33586aff40713-6c27-4d41-97ff40713-6c27-4d41-9a64-33586aa48502a64-33586a.jpg";
    ptestLabel = new QLabel("xifxia西那个就啊纷纷看好iu哈喽哈回府i联合国iu让v了染i", this);

    auto addLineBreaks = [&](const QString &text, int maxPixelWidth, const QFont &font) mutable -> QString {
        QString result;
        QFontMetrics fontMetrics(font);
        int lineWidth = 0;

        for (const QChar &ch : text) {
            lineWidth += fontMetrics.boundingRect(ch).width();
            if (lineWidth > maxPixelWidth) {
                result += '\n';
                lineWidth = fontMetrics.boundingRect(ch).width();
            }
            result += ch;
        }

        return result;
    };
    content = addLineBreaks(content, 100, ptestLabel->font());
    ptestLabel->setText(content);

    //    int index = fontmetrics.elidedText(QFontMetrics::WordWrap, text, targetWidth);
    //    int wid = fontmetrics.width(ptestLabel->text());
    //    qDebug()<<"width is"<<wid;

    ptestLabel->move(200, 200);
    //ptestLabel->setMaximumWidth(200);
    ptestLabel->adjustSize();
    ptestLabel->setWordWrap(true);  // 启用自动换行
    ptestLabel->setFixedWidth(200); // 设置最大行宽
    ptestLabel->setAlignment(Qt::AlignTop); // 文本在标签中顶部对齐
    ptestLabel->setFixedHeight(ptestLabel->height()); //


    tlabel = new TipLabel("测试。", this);
    tlabel->setScaledContents(true);
    tlabel->setContent("像素蛋糕蛋糕像素祷告辞色测试测试OUXPIXCAKE.jpg®");

    QLabel label(this);
    label.setStyleSheet("QLabel { white-space: pre-wrap; }");
    label.setText("This is a long text that will wrap to the next line.");
    label.setFixedSize(200, 100);

    label.show();
    //tlabel->resize(20, 40);
    tlabel->move(10, 10);
    connect(tlabel, &TipLabel::onTipLabelHover, [=](const QPoint &pos, const QString &content) {
        qDebug() << "on label enter..." << content;
        QPoint pos1 = tlabel->pos();
        QFontMetrics font_metrics = QFontMetrics(tlabel->font());
        QRect text_rect = font_metrics.boundingRect(tlabel->text());
        QPoint text_center = text_rect.center();
        pos1.setX(pos1.x() + text_center.x());

        qDebug() << "zhy pos " << pos1;
        TsToolTip::showText(mapToGlobal(pos1), content, NULL, QRect());
    });
    connect(tlabel, &TipLabel::onTipLabelLeave, [=]() {
        qDebug() << "on label enter...";
        TsToolTip::hideText();
    });
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    TsToolTip::hideText();
    int offset = event->pos().x();
    qDebug() << "zhy ----" << offset;
    QStringList content;
    content << "_+_+))())+_)(_)+_)(_(()+_)+_()+_)I()__()(*&^%^^&*()_+.jpg"
            << "32435465765654356756565342345645423243546534231425364"
            << "7ff40713-6c27-4d41-97ff40713-6c27-4d41-9a64-33586aa48502a64-33586aa48502.jpg"
    auto addLineBreaks = [&](const QString &text, int maxPixelWidth, const QFont &font) mutable -> QString {
        QString result;
        QFontMetrics fontMetrics(font);
        int lineWidth = 0;

        for (const QChar &ch : text) {
            lineWidth += fontMetrics.boundingRect(ch).width();
            if (lineWidth > maxPixelWidth) {
                result += '\n';
                lineWidth = 0;//fontMetrics.boundingRect(ch).width();
            }
            result += ch;
        }

        return result;
    };
    QString tooltipContent = addLineBreaks(content[3], 200, TsToolTip::font());
    TsToolTip::showText(mapToGlobal(event->pos()), tooltipContent, this, QRect(), 1500, event->pos().x());
    //    TsToolTip::showText(mapToGlobal(event->pos()),"");
    //  m_pTooltip->placeTip(mapToGlobal(event->pos()));
}

void MainWindow::on_textEdit_textChanged() {
    TsToolTip::hideText();
    //  m_pTooltip->setContent(ui->textEdit->toPlainText());
}

#include "mainwindow.moc"
