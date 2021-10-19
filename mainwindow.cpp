#include "mainwindow.h"
#include <QMessageBox>
#include <QPushButton>
#include <QPainter>
#include <QInputDialog>
#include <QtGui>
#include "qrx.h"
#include <iostream>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

        ui->setupUi(this);
        connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::boxSelect);
        connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::ButtonClicked);

}

MainWindow::~MainWindow() = default;

void MainWindow::ButtonClicked()
{

    if(ui->lineEdit->text() != 0){
        text = ui->lineEdit->text();
    }
    else{
        if(ui->lineEdit_2->text() != 0 && ui->lineEdit_3->text() !=0){
            text = "WIFI:S:" + ui->lineEdit_2->text() + ";T:WPA2;P:" + ui->lineEdit_3->text() + ";;";
        }
        else{
            QMessageBox::warning(this, "Warning","Input something!"); return;
        }
    }
    paintevent();
}

void MainWindow::boxSelect()
{

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();

}



void MainWindow::paintevent()
{
      if(text.size()!=0) doPainting();

}

void MainWindow::doPainting()
{


      width_ =  qR::qrx(text.toUtf8(), code);
      text.clear();
      QImage image(QSize(width_+10,width_+10),QImage::Format_RGB32);
      image.fill(QColor(50,50,50));
      QPainter painter(&image);
      const QPen black("#000000");
      const QPen white("#FFFFFF");
      painter.setPen(white);
      painter.drawRect(2,2,width_+2,width_+2);
      for (int y = 0; y < width_ ; ++y) {
                      for (int x = 0; x < width_; ++x) {
                          if(code[(y*width_+x)]==1) {
                              painter.setPen(black);
                              painter.drawRect(x+3, y+3, 1,1 );
                             }
                         else{
                              painter.setPen(white);
                              painter.drawRect(x+3, y+3, 1,1 );}
                          }

                  }
      painter.end();
      image.save("Image4QrCode.png");
      const QPixmap pic(QDir::currentPath()+"/Image4QrCode.png");
      QMessageBox mb;
      mb.setIconPixmap(pic);
      mb.show();
      mb.exec();




}
