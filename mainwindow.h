#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPen>
#include <vector>
#include <QTime>
#include <QMessageBox>
#include <QDebug>
#include <math.h>
namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  void paintEvent(QPaintEvent *event);
  void drawPointAt(int x,int y,QPainter& painter,QColor color=QColor(225, 0, 0));
private:
  std::vector<QColor> colorList;
  const int gap=6;
  int r;
  int tempRadius;int tempCircleRadius;
  int lineNum=70;//strongly recommend to set this value to an even value
  int boxWidth=gap*(lineNum-1);
  const int startX=30;
  const int startY=30;

  std::vector<int> testCircles;
  std::vector<int> circles;
  bool isTesting;
  int drawAlgorithm;
  bool cmp;
  void drawCircleWithRadius(int r,QPainter &painter,QColor color=QColor(225, 0, 0));
  void drawCircleWithRadiusPolar(int r,QPainter &painter,QColor color=QColor(225, 0, 0));
  void drawCircleWithRadiusInteger(int r,QPainter &painter,QColor color=QColor(225, 0, 0));
  void drawCircleWithRadiusIntegerOptimized(int r,QPainter &painter,QColor color=QColor(225, 0, 0));
public slots:
  void setNewRadius();
  void setNewCircleRadius();
  void addCircle();
  void resetPaintArea();
  void setCmpValue();
  void runPerformanceTest();
private slots:
  void on_original_clicked(bool checked);

  void on_integer_clicked(bool checked);

  void on_optimized_clicked(bool checked);

private:
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
