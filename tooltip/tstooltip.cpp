#include "tstooltip.h"

#include <QHBoxLayout>
#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include <QTextDocument>

TsToolTip::TsToolTip(QPoint startPoint, QString content, QWidget *parent)
    : QLabel{parent}, m_startX(50), startPosition(startPoint)
{
    m_triangleWidth = TRIANGLE_WIDTH;
    m_triangleHeight = TRIANGLE_HEIGHT;
    m_rectangleHeight = 44;
    m_rectangleWidth = 152;
    m_triangleWidth = 10;
    m_triangleHeight = 6;
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    this->resize(m_rectangleWidth,m_rectangleHeight + m_triangleHeight);

    m_pShadowEffect = new QGraphicsDropShadowEffect(this);
    m_pShadowEffect->setOffset(0, 0);
    m_pShadowEffect->setColor(0x09090A);
    m_pShadowEffect->setBlurRadius(SHADOW_WIDTH);
    this->setGraphicsEffect(m_pShadowEffect);
    this->topLevelWidget();
    //    m_pLabelContent = new QLabel();
    //    QHBoxLayout* hMainLayout = new QHBoxLayout(this);
    //    hMainLayout->addWidget(m_pLabelContent);
    //    hMainLayout->setSpacing(0);
    //    hMainLayout->setContentsMargins(SHADOW_WIDTH, SHADOW_WIDTH + TRIANGLE_HEIGHT, SHADOW_WIDTH, SHADOW_WIDTH);

    derect = Derection::down;

    this->setMaximumWidth(480);
    this->setWordWrap(true);
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
    this->setStyleSheet("QLabel{ margin: 12px; background-color: transparent; color: rgb(255, 255, 255); font-size: 12px;font-weight: 400; line-height: 20px;}");
}

void TsToolTip::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0x09090A));
    // 小三角区域;
    QPainterPath drawPath;
    QPolygon trianglePolygon;

    trianglePolygon << QPoint(m_rectangleWidth/2, (m_triangleHeight + m_rectangleHeight));
    trianglePolygon << QPoint(m_triangleWidth/2 + m_rectangleWidth/2,  m_rectangleHeight);

    drawPath.addRoundedRect(QRect(0,  0,m_rectangleWidth,m_rectangleHeight), BORDER_RADIUS, BORDER_RADIUS);

    trianglePolygon << QPoint(m_rectangleWidth/2 - m_triangleWidth /2,  m_rectangleHeight);
    //qDebug()<<"position "<<trianglePolygon;
    drawPath.addPolygon(trianglePolygon);
    painter.drawPath(drawPath);
    QLabel::paintEvent(event);
}

void TsToolTip::setContent(const QString& content)
{
    m_content = content;
    this->setText(content);
}

void TsToolTip::setTriangleInfo(int width, int height)
{
    m_triangleWidth = width;
    m_triangleHeight = height;
    this->resize(m_rectangleWidth,m_rectangleHeight + m_triangleHeight);
    this->update();
}

void TsToolTip::setRectangle(int width, int height)
{
    m_rectangleWidth = width;
    m_rectangleHeight = height;
    this->resize(m_rectangleWidth,m_rectangleHeight + m_triangleHeight);
    this->update();
}

void TsToolTip::SetStartPosition(QPoint point)
{
    startPosition = point;
}

//对内调用接口
void TsToolTip::placeTip(QPoint pos)
{
    QPoint movePoint = QPoint(pos.x()-m_rectangleWidth/2,pos.y()-m_rectangleHeight-m_triangleHeight);
    updateSize(movePoint);
    this->move(movePoint);
    this->show();
}

void TsToolTip::updateSize(const QPoint &pos)
{
    QFontMetrics fm(font());
    QSize extra(1, 0);
    // Make it look good with the default ToolTip font on Mac, which has a small descent.
    if (fm.descent() == 2 && fm.ascent() >= 11)
        ++extra.rheight();
    //setWordWrap(Qt::mightBeRichText(text()));
    QSize sh = sizeHint();
//    // ### When the above WinRT code is fixed, windowhandle should be used to find the screen.
//    QScreen *screen = QGuiApplication::screenAt(pos);
//    if (!screen)
//        screen = QGuiApplication::primaryScreen();
//    if (screen) {
//        const qreal screenWidth = screen->geometry().width();
//        if (!wordWrap() && sh.width() > screenWidth) {
//            setWordWrap(true);
//            sh = sizeHint();
//        }
//    }
    qDebug()<<"zhy this size is: "<<sh<<extra;
    setRectangle(sh.width(),sh.height());
}
