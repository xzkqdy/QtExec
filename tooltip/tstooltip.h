#ifndef TSTOOLTIP_H
#define TSTOOLTIP_H

#include <QObject>
#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QLabel>
class TsToolTip : public QLabel
{
    Q_OBJECT
public:
    enum Derection{
            left,
            right,
            up,
            down
        };

    explicit TsToolTip(QPoint startPoint = QPoint(0,0), QString content="", QWidget *parent = nullptr);

    void setContent(const QString& content);
    void setTriangleInfo(int width, int height);
    void SetStartPosition(QPoint position);
    void setRectangle(int width, int height);

    void placeTip(QPoint pos);
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    QString m_content;
    QGraphicsDropShadowEffect *m_pShadowEffect;
//    QLabel *m_pLabelContent;

    int m_startX;
    int m_triangleWidth;
    int m_triangleHeight;

    int m_rectangleWidth;
    int m_rectangleHeight;

    Derection derect;
    QPoint startPosition;

    const int SHADOW_WIDTH =15;
    const int TRIANGLE_WIDTH =15;
    const int TRIANGLE_HEIGHT =10;
    const int BORDER_RADIUS = 2;
signals:
};

#endif // TSTOOLTIP_H
