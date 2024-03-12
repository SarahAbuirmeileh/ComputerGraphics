//
// copyright 2018 Palestine Polytechnic Univeristy
//
// This software can be used and/or modified for academich use as long as
// this commented part is listed
//
// Last modified by: Zein Salah, on 24.02.2021
//

#include "RenderWidget.h"
#include <QPainter>
#include <cmath>
#include <QtMath>


RenderWidget::RenderWidget(QWidget *parent) : QWidget(parent){
}

QSize RenderWidget::minimumSizeHint() const{
  return QSize(100, 100);
}

QSize RenderWidget::sizeHint() const{
  return QSize(600, 600);
}

void RenderWidget::paintEvent(QPaintEvent *){
   drawTableLamp();
  //drawCar();

}

void RenderWidget::drawTableLamp(){

  drawLine(250,599,0,599);
  drawEllipse(125, 599, 125, 50);

  drawLine(150,549,150,407);
  drawLine(115,548,115,407);

  drawCircle(135,373,38);
  drawCircle(135,373,12);

  drawLine(131,335,190,235);
  drawLine(163,350,220,255);
  drawLine(189,235,235,265);

  drawArc(220,202,50, 230, 45);
  drawLine(249,168,282,191);

  drawArc(345,280,50, 221, 110);
  drawLine(413,195,262,351);
  drawArc(340, 270, 228, 405, 40);

}

void RenderWidget::mapPoint(float &x, float &y){
  x = x + 300;
  y = 300 - y;
}

void RenderWidget::drawLine(float x1, float y1, float x2, float y2){

  QPainter painter(this);
  QColor color(0, 0, 0);
  painter.setPen(color);

  if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0){
    mapPoint(x1, y1);
    mapPoint(x2, y2);
  }

  int dx = abs(x2 - x1);
  int dy = abs(y2 - y1);

  int xStep = (x1 < x2) ? 1 : -1;
  int yStep = (y1 < y2) ? 1 : -1;

  int pk = dx - dy; // decision parameter

  while (true){
    painter.drawPoint(x1, y1);

    if (x1 == x2 && y1 == y2){
      break;
    }

    int pk2 = 2 * pk;
    // If pk2 is positive, the algorithm increments the y-coordinate
    if (pk2 > -dy){
      pk -= dy;
      x1 += xStep;
    }

    if (pk2 < dx){
      pk += dx;
      y1 += yStep;
    }
  }
}

void RenderWidget::drawLineFromDerivation(float x1, float y1, float x2, float y2){

  QPainter painter(this);
  QColor color(0, 0, 0);
  painter.setPen(color);

  if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0){
    mapPoint(x1, y1);
    mapPoint(x2, y2);
  }

  painter.drawPoint(x1, y1);

  // Calculate constants outside the loop
  int dx = x2 - x1, dy = y2 - y1;
  int twoDy = 2 * dy, twoDx = 2 * dx;
  int twoDyMinusDx = twoDy - twoDx;
  int twoDyPlusDx = twoDy + twoDx;
  int twoDxMinusDy = twoDx - twoDy;
  int twoDxPlusDy = twoDx + twoDy;
  int pk;

  if (abs(dx) >= abs(dy)){ // Slope between 0 and 1 (Case 1)
    if (dx >= 0){
      pk = twoDy - dx;
      while (x1 < x2){
        x1++;
        if (pk < 0){
          pk += twoDy;
        }else{
          y1 += (dy >= 0) ? 1 : -1;
          pk += twoDyMinusDx;
        }
        painter.drawPoint(x1, y1);
      }
    }else{ // Slope between -1 and 0 (Case 3)
      pk = twoDy + dx;
      while (x1 > x2){
        x1--;
        if (pk < 0){
          pk += twoDyPlusDx;
        }else{
          y1 += (dy >= 0) ? 1 : -1;
          pk += twoDyMinusDx;
        }
        painter.drawPoint(x1, y1);
      }
    }
  }else{ // Slope between 1 and infinity (Case 2 )
    if (dy >= 0){
      pk = twoDx - dy;
      while (y1 < y2){
        y1++;
        if (pk < 0)
        {
          pk += twoDx;
        }
        else
        {
          x1 += (dx >= 0) ? 1 : -1;
          pk += twoDxMinusDy;
        }
        painter.drawPoint(x1, y1);
      }
    }else{ // Slope between -infinity and -1 (Case 4)
      pk = twoDx + dy;
      while (y1 > y2)
      {
        y1--;
        if (pk < 0)
        {
          pk += twoDxPlusDy;
        }
        else
        {
          x1 += (dx >= 0) ? 1 : -1;
          pk += twoDxMinusDy;
        }
        painter.drawPoint(x1, y1);
      }
    }
  }
}

void RenderWidget::drawCircle(float xc, float yc, float r){

  QPainter painter(this);
  QColor color(0, 0, 0);
  painter.setPen(color);

  if (yc < 0 || xc < 0 ){
    mapPoint(xc, yc);
  }

  float x = r, y = 0; // The first point in the circle
  float theta = 1 / r;
  float sinTheta = sin(theta), cosTheta = cos(theta);

  while (y <= x){ // Using the symmetric property for circle

    // Octant 1
    painter.drawPoint(xc + x, yc - y);
    painter.drawPoint(xc + y, yc - x);

    // Octant 2
    painter.drawPoint(xc - x, yc - y);
    painter.drawPoint(xc - y, yc - x);

    // Octant 3
    painter.drawPoint(xc - x, yc + y);
    painter.drawPoint(xc - y, yc + x);

    // Octant 4
    painter.drawPoint(xc + x, yc + y);
    painter.drawPoint(xc + y, yc + x);

    x = x * cosTheta - y * sinTheta;
    y = x * sinTheta + y * cosTheta;
  }
}

void RenderWidget::drawArc(float xc, float yc, float t1, float t2, float r) {
    // Ensure t1 is less than t2
    if (t1 > t2) {
        std::swap(t1, t2);
    }

    QPainter painter(this);
    QColor color(0, 0, 0);
    painter.setPen(color);

    float theta = 1 / r;
    float sinTheta = sin(theta), cosTheta = cos(theta);

    t1 = t1 * M_PI / 180.0;
    t2 = t2 * M_PI / 180.0;

    float x = r * cos(t1);
    float y = r * sin(t1);

    while (t1 <= t2) {
        // Map the point if needed
        if (yc < 0 || xc < 0) {
            mapPoint(xc, yc);
        }

        painter.drawPoint(xc + x, yc - y);

        t1 += theta;
        x = r * cos(t1);
        y = r * sin(t1);
    }
}


void RenderWidget::drawEllipse(float xc, float yc, float a, float b) {

  QPainter painter(this);
  QColor color(0, 0, 0);
  painter.setPen(color);

  if (yc < 0 || xc < 0 ){
    mapPoint(xc, yc);
  }

  int numPoints = 1000;
  float theta = M_PI / numPoints;  // * 2 if you want the whole ellipse

  for (int i = 0; i <= numPoints; ++i) {

    float currentTheta = theta * i;
    float r = a * b / sqrt(pow(b * cos(currentTheta), 2) + pow(a * sin(currentTheta), 2));

    float xCoordinate = xc + r * cos(currentTheta);
    float yCoordinate = yc - r * sin(currentTheta); 

    painter.drawPoint(xCoordinate, yCoordinate);
  }
}


void RenderWidget::myDrawLine(float x1, float y1, float x2, float y2){
  QPainter painter(this);

  //    painter.setRenderHint(QPainter::Antialiasing, false);
  QColor color(0, 0, 0);
  painter.setPen(color);

  float m = (y2 - y1) / (x2 - x1);
  //  SetPixel(x1, y1, color);   // first point
  painter.drawPoint(x1, y1);

  if (m < 1)
  {
    float y = y1;
    for (int i = x1 + 1; i < x2; ++i)
    {
      y = y + m;
      //      SetPixel(i, round(y), color);
      painter.drawPoint(i, round(y));
    }
  }
  else // i.e., m > 1
  {
    float mm = 1 / m;
    float x = x1;
    for (int i = y1 + 1; i < y2; ++i)
    {
      x = x + mm;
      //      SetPixel(round(x), i, color);
      painter.drawPoint(round(x), i);
    }
  }

  //  SetPixel(x2, y2, color);   // last point
  painter.drawPoint(x2, y2);
}
