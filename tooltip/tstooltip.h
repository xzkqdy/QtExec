#ifndef TSTOOLTIP_H
#define TSTOOLTIP_H

#include <QObject>
#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QLabel>
class TsToolTip : public QLabel {
Q_OBJECT
public:
    enum Derection {
        left,
        right,
        up,
        down
    };

    explicit TsToolTip(QPoint startPoint = QPoint(0, 0), QString content = "", QWidget *parent = nullptr);

    void setContent(const QString &content);

    void setTriangleInfo(int width, int height);

    void setRectangle(int width, int height);

    //内部调用
    void updateSize(const QPoint &pos);

    void placeTip(QPoint pos);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QGraphicsDropShadowEffect *m_pShadowEffect;

    int m_triangleWidth;
    int m_triangleHeight;

    int m_rectangleWidth;
    int m_rectangleHeight;

    Derection derect;

    const int SHADOW_WIDTH = 15;

    const int TRIANGLE_WIDTH = 10;
    const int TRIANGLE_HEIGHT = 6;

    const int RECTANGLE_WIDTH = 44;
    const int RECTANGLE_HEIGHT = 152;

    const int BORDER_RADIUS = 2;

};

#endif // TSTOOLTIP_H
