//
// copyright 2018 Palestine Polytechnic Univeristy
//
// This software can be used and/or modified for academich use as long as
// this commented part is listed
//
// Last modified by: Zein Salah, on 24.04.2020
//

#pragma once

#include <QWidget>

class RenderWidget : public QWidget{
  Q_OBJECT

public:
  RenderWidget(QWidget *parent = 0);

  QSize minimumSizeHint() const override;
  QSize sizeHint() const override;

  void myDrawLine(float x1, float y1, float x2, float y2);
  void drawTicks(float xc, float yc, float r);
  void mapPoint(float &x, float &y);
  void drawLine(float x1, float y1, float x2, float y2);
  void drawLineMyDerivation(float x1, float y1, float x2, float y2);
  void drawCircle(float xc, float yc, float r);
  void drawArc(float xc, float yc, float t1, float t2, float r);
  void drawEllipse(float xc, float yc, float a, float b);
  void drawTableLamp();
  void drawCar();
  void CohenSutherland(float point1X, float point1Y, float point2X, float point2Y, float wLeft, float wRight, float wTop, float wBottom);
  void convexPolygonFilling(std::pair<float, float> polygonVertices[], int verticesNumber, float xMax, float xMin, float yMax, float yMin);

protected:
  void paintEvent(QPaintEvent *event) override;
};
