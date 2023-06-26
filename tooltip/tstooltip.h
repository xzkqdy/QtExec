#ifndef TSTOOLTIP_H
#define TSTOOLTIP_H

#include <QObject>
#include <QPoint>

QT_BEGIN_NAMESPACE

class TsToolTip {
    TsToolTip() = delete;

public:
    // ### Qt 6  merge the three showText functions below
    static void showText(const QPoint &position, const QString &text, QWidget *parent = nullptr);

    static void showText(const QPoint &position, const QString &text, QWidget *parent, const QRect &rect);

    static void
    showText(const QPoint &position, const QString &text, QWidget *parent, const QRect &rect, int msecShowTime,
             int offsetx = 0);

    static inline void hideText() { showText(QPoint(), QString()); }

    static bool isVisible();

    static QString text();

    static QPalette palette();

    static void setPalette(const QPalette &);

    static void setFont(const QFont &font);

    static QFont font();
};

#endif // TSTOOLTIP_H
