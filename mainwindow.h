#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <ui_mainwindow.h>
#include <vector>
#include <QScopedPointer>

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QScopedPointer<Ui::MainWindow> ui;
    void paintevent();

private:

    void doPainting();
    std::vector<bool> code ;
    int width_;
    QString text;

public slots:
    void boxSelect();
    void ButtonClicked();



};


#endif // MAINWINDOW_H
