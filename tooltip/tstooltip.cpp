#include "tstooltip.h"

#include <QHBoxLayout>
#include <QPainter>
#include <QPainterPath>
#include <QDebug>

TsToolTip::TsToolTip(QPoint startPoint, QString content, QWidget *parent)
    : QWidget{parent}, m_startX(50), startPosition(startPoint)
{
    m_triangleWidth = TRIANGLE_WIDTH;
    m_triangleHeight = TRIANGLE_HEIGHT;
    m_rectangleHeight = 44;
    m_rectangleWidth = 152;
    this->setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    //this->resize(100,30);

    m_pShadowEffect = new QGraphicsDropShadowEffect(this);
    m_pShadowEffect->setOffset(0, 0);
    m_pShadowEffect->setColor(0x09090A);
    m_pShadowEffect->setBlurRadius(SHADOW_WIDTH);
    this->setGraphicsEffect(m_pShadowEffect);

    m_pLabelContent = new QLabel();
    QHBoxLayout* hMainLayout = new QHBoxLayout(this);
    hMainLayout->addWidget(m_pLabelContent);
    hMainLayout->setSpacing(0);
    hMainLayout->setContentsMargins(SHADOW_WIDTH, SHADOW_WIDTH + TRIANGLE_HEIGHT, SHADOW_WIDTH, SHADOW_WIDTH);

    derect = Derection::down;

    //    m_pLabelContent->setFixedWidth(228);
    //    m_pLabelContent->setWordWrap(true);
    //    m_pLabelContent->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
    m_pLabelContent->setStyleSheet("QLabel{ margin: 12px; background-color: transparent; color: rgb(255, 255, 255); font-size: 12px;font-weight: 400; line-height: 20px;}");
}

void TsToolTip::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    // painter.setBrush(QColor(255, 255, 255, 200));
    painter.setBrush(QColor(0x09090A));
    // 小三角区域;
    QPainterPath drawPath;
    QPolygon trianglePolygon;

    //    switch (derect)
    //    {
    //        case up:
    //        trianglePolygon << QPoint(m_startX, m_triangleHeight + SHADOW_WIDTH);
    //        trianglePolygon << QPoint(m_startX + m_triangleWidth / 2, SHADOW_WIDTH);
    //        trianglePolygon << QPoint(m_startX + m_triangleWidth, m_triangleHeight + SHADOW_WIDTH);
    //        drawPath.addRoundedRect(QRect(SHADOW_WIDTH, m_triangleHeight + SHADOW_WIDTH,\
    //                                    width() - SHADOW_WIDTH * 2, height() - SHADOW_WIDTH * 2 - m_triangleHeight),\
    //                                    BORDER_RADIUS, BORDER_RADIUS);
    //        break;
    //        case left:
    //        trianglePolygon << QPoint(3 + m_triangleHeight, 43);
    //        trianglePolygon << QPoint(8, 48 + m_triangleWidth / 2);
    //        trianglePolygon << QPoint(3 + m_triangleHeight, 39 + m_triangleWidth);
    //        drawPath.addRoundedRect(QRect(SHADOW_WIDTH, m_triangleHeight + SHADOW_WIDTH,\
    //                                    width() - SHADOW_WIDTH * 2, height() - SHADOW_WIDTH * 2 - m_triangleHeight),\
    //                                    BORDER_RADIUS, BORDER_RADIUS);
    //        break;
    //        case right:
    //        trianglePolygon << QPoint(115, 40);
    //        trianglePolygon << QPoint(116 + m_triangleHeight, 48 + m_triangleWidth / 2);
    //        trianglePolygon << QPoint(115, 39 + m_triangleWidth);
    //        drawPath.addRoundedRect(QRect(SHADOW_WIDTH, m_triangleHeight + SHADOW_WIDTH,\
    //                                                                    width() - SHADOW_WIDTH * 2, height() - SHADOW_WIDTH * 2 - m_triangleHeight),\
    //                                    BORDER_RADIUS, BORDER_RADIUS);

    //        break;
    //        case down:
#ifdef ZZTEST
    trianglePolygon << QPoint(startPosition.x(), startPosition.y());
    trianglePolygon << QPoint(startPosition.x() + m_triangleWidth / 2, startPosition.y() + m_triangleHeight);
    trianglePolygon << QPoint(startPosition.x() + m_triangleWidth, startPosition.y());
    //    drawPath.addRoundedRect(QRect(SHADOW_WIDTH, m_triangleHeight + SHADOW_WIDTH,\
    //                                  width() - SHADOW_WIDTH * 2, height() - SHADOW_WIDTH * 2 - m_triangleHeight),\
    //                            BORDER_RADIUS, BORDER_RADIUS);
    //        break;
    //    default: break;
    //    }
    drawPath.addPolygon(trianglePolygon);
    painter.drawPath(drawPath);
#endif
    //    int m_triangleWidth = 20;
    //    int m_triangleHeight = 10;

    //    int squareWidth = 50;
    //    int squareHeight = 30;
    trianglePolygon << QPoint(startPosition.x(), startPosition.y());
    trianglePolygon << QPoint(startPosition.x() + m_triangleWidth / 2, startPosition.y() - m_triangleHeight);

    drawPath.addRoundedRect(QRect(startPosition.x() - m_rectangleWidth/2,  startPosition.y() - m_rectangleHeight- m_triangleHeight,m_rectangleWidth,m_rectangleHeight),
                            BORDER_RADIUS, BORDER_RADIUS);

    trianglePolygon << QPoint(startPosition.x() - m_triangleWidth /2, startPosition.y() - m_triangleHeight);
    drawPath.addPolygon(trianglePolygon);
    painter.drawPath(drawPath);
}

void TsToolTip::setContent(const QString& content)
{
    m_content = content;
    m_pLabelContent->setText(content);
}

void TsToolTip::setTriangleInfo(int width, int height)
{
    m_triangleWidth = width;
    m_triangleHeight = height;
}

void TsToolTip::setRectangle(int width, int height)
{
    m_rectangleWidth = width;
    m_rectangleHeight = height;
}

void TsToolTip::SetStartPosition(QPoint point)
{
    startPosition = point;
}
