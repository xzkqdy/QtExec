#ifndef TSTOOLTIP_H
#define TSTOOLTIP_H

#include <QObject>
#include <QPoint>

QT_BEGIN_NAMESPACE

class TsToolTip
{
    TsToolTip() = delete;
public:
    // ### Qt 6 - merge the three showText functions below
    static void showText(const QPoint &pos, const QString &text, QWidget *w = nullptr);

    static void showText(const QPoint &pos, const QString &text, QWidget *w, const QRect &rect);

    static void showText(const QPoint &pos, const QString &text, QWidget *w, const QRect &rect, int msecShowTime);

    static inline void hideText() { showText(QPoint(), QString()); }

    static bool isVisible();

    static QString text();

    static QPalette palette();

    static void setPalette(const QPalette &);

    static QFont font();
};

#endif // TSTOOLTIP_H
