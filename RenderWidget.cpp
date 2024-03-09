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


RenderWidget::RenderWidget(QWidget* parent) : QWidget(parent){

}

QSize RenderWidget::minimumSizeHint() const{
  return QSize(100, 100);
}

QSize RenderWidget::sizeHint() const{
  return QSize(600, 600);
}

void RenderWidget::paintEvent(QPaintEvent*){

  drawLine(0,0,100,200);
  drawLineFromDerivation(0,0,100,200);
  
}

void RenderWidget::mapPoint(int &x, int &y){
  x = x + 300;
  y = 300 - y;
}

void RenderWidget::drawLine(int x1, int y1, int x2, int y2){
  QPainter painter(this);
  QColor color(0, 0, 0);
  painter.setPen(color);

  int dx = abs(x2 - x1);
  int dy = abs(y2 - y1);

  int xStep = (x1 < x2) ? 1 : -1;
  int yStep = (y1 < y2) ? 1 : -1;

  int pk = dx - dy; //decision parameter

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

void RenderWidget::drawLineFromDerivation(int x1, int y1, int x2, int y2) {

  QPainter painter(this);
  QColor color(0, 0, 0);
  painter.setPen(color);

  painter.drawPoint(x1, y1);

  // Calculate constants outside the loop
  int dx = x2-x1, dy = y2-y1;
  int twoDy = 2*dy, twoDx =2*dx;
  int twoDyMinusDx = twoDy-twoDx;
  int twoDyPlusDx = twoDy+twoDx;
  int twoDxMinusDy = twoDx-twoDy;
  int twoDxPlusDy = twoDx+twoDy;
  int pk;

  if (abs(dx) >= abs(dy)) { // Slope between 0 and 1 (Case 1)
    if (dx >= 0) {
        pk = twoDy - dx;
        while (x1 < x2) {
            x1++;
            if (pk < 0) {
                pk += twoDy;
            } else {
                y1 += (dy >= 0) ? 1 : -1;
                pk += twoDyMinusDx;
            }
            painter.drawPoint(x1, y1);
        }
    }else { // Slope between -1 and 0 (Case 3)
        pk = twoDy + dx;
        while (x1 > x2) {
            x1--;
            if (pk < 0) {
                pk += twoDyPlusDx;
            } else {
                y1 += (dy >= 0) ? 1 : -1;
                pk += twoDyMinusDx;
            }
            painter.drawPoint(x1, y1);
        }
    }
  } else {  // Slope between 1 and infinity (Case 2 )
      if (dy >= 0) {
          pk = twoDx - dy;
          while (y1 < y2) {
              y1++;
              if (pk < 0) {
                  pk += twoDx;
              } else {
                  x1 += (dx >= 0) ? 1 : -1;
                  pk += twoDxMinusDy;
              }
              painter.drawPoint(x1, y1);
          }
      }else { // Slope between -infinity and -1 (Case 4)
          pk = twoDx + dy;
          while (y1 > y2) {
              y1--;
              if (pk < 0) {
                  pk += twoDxPlusDy;
              } else {
                  x1 += (dx >= 0) ? 1 : -1;
                  pk += twoDxMinusDy;
              }
              painter.drawPoint(x1, y1);
          }
      }
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
  else     // i.e., m > 1
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
