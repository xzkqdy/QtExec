#include "tstooltip.h"

#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include <QTextDocument>
#include <QWidget>
#include <QLabel>
#include <qbasictimer.h>
#include <QApplication>
#include <QToolTip>

class TsTipLabel : public QLabel {
Q_OBJECT
public:

    TsTipLabel(const QString &text, const QPoint &pos, QWidget *w, int msecDisplayTime, int offsetX = 0);

    ~TsTipLabel();

    static TsTipLabel *instance;

    void setTriangleInfo(int width, int height);

    void setRectangle(int width, int height);

    void setTipRect(QWidget *w, const QRect &r);

    //内部调用
    void updateSize(const QPoint &pos);

    void placeTip(QPoint pos);

    void hideTipImmediately();

    void restartExpireTimer(int msecDisplayTime);

    void hideTip();

    void reuseTip(const QString &text, int msecDisplayTime, const QPoint &position);

    bool tipChanged(const QPoint &position, const QString &text, QObject *parent);

    bool m_bFadingOut;
protected:
    void paintEvent(QPaintEvent *event) override;

    void timerEvent(QTimerEvent *event) override;

private:
    int getOffsetWidth();

    int m_triangleWidth;
    int m_triangleHeight;

    int m_rectangleWidth;
    int m_rectangleHeight;

    const int TRIANGLE_WIDTH = 10;
    const int TRIANGLE_HEIGHT = 6;

    const int RECTANGLE_WIDTH = 44;
    const int RECTANGLE_HEIGHT = 152;

    const int BORDER_RADIUS = 2;
    const int PARENT_SAFE_BORDER = 8;

    QBasicTimer m_hideTimer;
    QBasicTimer m_expireTimer;

    QRect rect;
    QWidget *widget;
    int m_offset;
};

TsTipLabel *TsTipLabel::instance = nullptr;

TsTipLabel::TsTipLabel(const QString &text, const QPoint &pos, QWidget *w, int msecDisplayTime, int offsetX)
    : QLabel(nullptr, Qt::ToolTip | Qt::BypassGraphicsProxyWidget), widget(nullptr) {
    delete instance;
    instance = this;
    setForegroundRole(QPalette::ToolTipText);
    setBackgroundRole(QPalette::ToolTipBase);
    setPalette(TsToolTip::palette());
    //ensurePolished();
    //setMargin(1 + style()->pixelMetric(QStyle::PM_ToolTipLabelFrameWidth, nullptr, this));
    setFrameStyle(QFrame::NoFrame);
    setAlignment(Qt::AlignLeft);
    //setIndent(1);
    //qApp->installEventFilter(this);
    //setWindowOpacity(style()->styleHint(QStyle::SH_ToolTipLabel_Opacity, nullptr, this) / 255.0);
    //setMouseTracking(true);
    m_bFadingOut = false;
    reuseTip(text, msecDisplayTime, pos);

    m_rectangleHeight = RECTANGLE_WIDTH;
    m_rectangleWidth = RECTANGLE_HEIGHT;
    m_triangleWidth = TRIANGLE_WIDTH;
    m_triangleHeight = TRIANGLE_HEIGHT;
    m_offset = offsetX;

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);

    this->resize(m_rectangleWidth, m_rectangleHeight + m_triangleHeight);
    this->adjustSize();
    this->setMaximumWidth(480);
    this->setWordWrap(true);
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
    this->setStyleSheet(
            "QLabel{ margin: 12px; margin-top: 8px; background-color: transparent; color: rgb(255, 255, 255); font-size: 12px;font-weight: 400; line-height: 20px;}");

    m_bFadingOut = false;
}

TsTipLabel::~TsTipLabel() {
    instance = nullptr;
}

int TsTipLabel::getOffsetWidth() {
    int offsetWidth = 0;
    if (m_rectangleWidth / 2 + PARENT_SAFE_BORDER >= m_offset && m_offset != 0) {
        offsetWidth = m_rectangleWidth / 2 + PARENT_SAFE_BORDER - m_offset;
    }
    if (widget && m_offset != 0) {
        if (m_offset + m_rectangleWidth / 2 + PARENT_SAFE_BORDER > widget->width()) {
            offsetWidth = widget->width() - (m_offset + m_rectangleWidth / 2 + PARENT_SAFE_BORDER);
        }
    }

    return offsetWidth;
}

void TsTipLabel::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0x09090A));

    int offsetWidth = getOffsetWidth();
    // 小三角区域（向下）;
    QPolygon trianglePolygon;
    trianglePolygon << QPoint(m_rectangleWidth / 2 - offsetWidth, (m_triangleHeight + m_rectangleHeight));
    trianglePolygon << QPoint(m_triangleWidth / 2 - offsetWidth + m_rectangleWidth / 2, m_rectangleHeight);
    trianglePolygon << QPoint(m_rectangleWidth / 2 - offsetWidth - m_triangleWidth / 2, m_rectangleHeight);

    QPainterPath drawPath;
    drawPath.addRoundedRect(QRect(0, 0, m_rectangleWidth, m_rectangleHeight), BORDER_RADIUS, BORDER_RADIUS);

    drawPath.addPolygon(trianglePolygon);
    painter.drawPath(drawPath);
    QLabel::paintEvent(event);
}

void TsTipLabel::timerEvent(QTimerEvent *event) {
    if (event->timerId() == m_hideTimer.timerId() || event->timerId() == m_expireTimer.timerId()) {
        m_hideTimer.stop();
        m_expireTimer.stop();
        hideTipImmediately();
    }
}

void TsTipLabel::hideTipImmediately() {
    close();
    deleteLater();
}

void TsTipLabel::hideTip() {
    if (!m_hideTimer.isActive()) {
        m_hideTimer.start(300, this);
    }
}

void TsTipLabel::restartExpireTimer(int msecDisplayTime) {
    int time = 10000 + 40 * qMax(0, text().length() - 100);
    if (msecDisplayTime > 0)
        time = msecDisplayTime;
    m_expireTimer.start(time, this);
    m_hideTimer.stop();
}


void TsTipLabel::reuseTip(const QString &text, int msecDisplayTime, const QPoint &pos) {
    setText(text);
    updateSize(pos);
    restartExpireTimer(msecDisplayTime);
}

bool TsTipLabel::tipChanged(const QPoint &position, const QString &text, QObject *parent) {
    if (TsTipLabel::instance->text() != text)
        return true;

    if (parent != widget)
        return true;

    if (!rect.isNull())
        return !rect.contains(position);
    else
        return false;
}

void TsTipLabel::setTriangleInfo(int width, int height) {
    m_triangleWidth = width;
    m_triangleHeight = height;
    this->resize(m_rectangleWidth, m_rectangleHeight + m_triangleHeight);
    this->update();
}

void TsTipLabel::setRectangle(int width, int height) {
    m_rectangleWidth = width;
    m_rectangleHeight = height;
    this->resize(m_rectangleWidth, m_rectangleHeight + m_triangleHeight);
    this->update();
}

void TsTipLabel::setTipRect(QWidget *parent, const QRect &r) {
    if (Q_UNLIKELY(!r.isNull() && !parent)) {
        qWarning("QToolTip::setTipRect: Cannot pass null widget if rect is set");
        return;
    }
    widget = parent;
    rect = r;
}

//对内调用接口
void TsTipLabel::placeTip(QPoint position) {
    updateSize(position);
    int offsetWidth = getOffsetWidth();
    QPoint movePoint = QPoint(position.x() - m_rectangleWidth / 2 + offsetWidth,
                              position.y() - m_rectangleHeight - m_triangleHeight);
    this->move(movePoint);
}

void TsTipLabel::updateSize(const QPoint &pos) {
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

    setRectangle(sh.width(), sh.height());
}


void TsToolTip::showText(const QPoint &pos, const QString &text, QWidget *w) {
    TsToolTip::showText(pos, text, w, QRect());
}

void TsToolTip::showText(const QPoint &pos, const QString &text, QWidget *w, const QRect &rect) {
    TsToolTip::showText(pos, text, w, rect, 0);
}

void TsToolTip::showText(const QPoint &pos, const QString &text, QWidget *parentWidget, const QRect &rect, int msecDisplayTime, int offsetx) {
    if (TsTipLabel::instance && TsTipLabel::instance->isVisible()) { // a tip does already exist
        if (text.isEmpty()) { // empty text means hide current tip
            TsTipLabel::instance->hideTip();
            return;
        } else if (!TsTipLabel::instance->m_bFadingOut) {
            // If the tip has changed, reuse the one
            // that is showing (removes flickering)
            QPoint localPos = pos;
            if (parentWidget) {
                localPos = parentWidget->mapFromGlobal(pos);
            }

            if (TsTipLabel::instance->tipChanged(localPos, text, parentWidget)) {
                TsTipLabel::instance->reuseTip(text, msecDisplayTime, pos);
                TsTipLabel::instance->setTipRect(parentWidget, rect);
                TsTipLabel::instance->placeTip(pos);
            }
            return;
        }
    }

    if (!text.isEmpty()) { // no tip can be reused, create new tip:
#ifdef Q_OS_WIN32
        // On windows, we can't use the widget as parent otherwise the window will be
        // raised when the tooltip will be shown
        QT_WARNING_PUSH
        QT_WARNING_DISABLE_DEPRECATED
        new QTipLabel(text, pos, QApplication::desktop()->screen(QTipLabel::getTipScreen(pos, w)), msecDisplayTime, offsetX);
        QT_WARNING_POP
#else
        new TsTipLabel(text, pos, parentWidget, msecDisplayTime, offsetx); // sets QTipLabel::instance to itself
#endif
        TsTipLabel::instance->setTipRect(parentWidget, rect);
        TsTipLabel::instance->placeTip(pos);
        TsTipLabel::instance->setObjectName(QLatin1String("qtooltip_label"));

        //#if QT_CONFIG(effects)
        //        if (QApplication::isEffectEnabled(Qt::UI_FadeTooltip))
        //            qFadeEffect(QTipLabel::instance);
        //        else if (QApplication::isEffectEnabled(Qt::UI_AnimateTooltip))
        //            qScrollEffect(QTipLabel::instance);
        //        else
        //            QTipLabel::instance->showNormal();
        //#else
        TsTipLabel::instance->showNormal();

    }
}

bool TsToolTip::isVisible() {
    return (TsTipLabel::instance != nullptr && TsTipLabel::instance->isVisible());
}

QString TsToolTip::text() {
    if (TsTipLabel::instance) {
        return TsTipLabel::instance->text();
    }
    return QString("");
}

Q_GLOBAL_STATIC(QPalette, tooltip_palette)

QPalette TsToolTip::palette() {
    return *tooltip_palette();
}


void TsToolTip::setPalette(const QPalette &palette) {
    *tooltip_palette() = palette;
    if (TsTipLabel::instance)
        TsTipLabel::instance->setPalette(palette);
}

void TsToolTip::setFont(const QFont &font) {
    QApplication::setFont(font, "TsTipLabel");
}

QFont TsToolTip::font() {
    return QApplication::font("TsTipLabel");;
}

#include "tstooltip.moc"
