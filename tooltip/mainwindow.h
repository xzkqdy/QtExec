#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <tstooltip.h>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class TipLabel;
class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private slots:

    void on_textEdit_textChanged();

private:
    Ui::MainWindow *ui;
    TsToolTip *m_pTooltip;
    TipLabel *tlabel;
    QLabel *ptestLabel;
};
#endif // MAINWINDOW_H
