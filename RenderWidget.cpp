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

RenderWidget::RenderWidget(QWidget *parent) : QWidget(parent){
}

QSize RenderWidget::minimumSizeHint() const{
  return QSize(100, 100);
}

QSize RenderWidget::sizeHint() const{
  return QSize(600, 600);
}

void RenderWidget::paintEvent(QPaintEvent *){
  //drawTableLamp();
  //drawCar();
  CohenSutherland(0, 0, 500, 500, 200, 400, 200, 400);
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

void RenderWidget::drawCar(){
  drawCircle(200,500,25);
  drawCircle(450,500,25);

  drawCircle(200,500,60);
  drawCircle(450,500,60);

  drawLine(257, 520, 392, 520);
  drawLine(257, 480, 392, 480);

  drawLine(97, 520, 142, 520);
  drawLine(97, 480, 142, 480);

  drawLine(507, 520, 562, 520);
  drawLine(507, 480, 562, 480);

  drawLine(97, 480, 97, 520);
  drawLine(562, 480, 562, 520);

  drawArc(240, 480, 100, 180, 120);
  drawArc(380, 423, -5, 159, 170);
  drawLine(549, 425, 549, 480);

  drawArc(125, 456, 82, 258, 20);
  drawArc(542, 457, 290, 425, 20);

  drawLine(394, 365, 514, 365);
  drawArc(380, 430, 26, 85, 150);
  drawLine(394, 365, 394, 281);

  drawLine(244, 365, 364, 365);
  drawArc(380, 430, 96, 155, 151);
  drawLine(364, 365, 364, 281);

  drawLine(339, 410, 364, 410);
  drawLine(339, 420, 364, 420);
  drawLine(364, 420, 364, 410);
  drawLine(339, 410, 339, 420);
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

void RenderWidget::CohenSutherland(float x1, float y1, float x2, float y2, float wLeft, float wRight, float wTop, float wBottom) {
  
  // Clipping line according to Cohen-Sutherland Algorithm
  // Send the 2 vertices for line that you want to clip, and the dimensions for the window to clip against it 

  QPainter painter(this);
  QColor color(0, 0, 0);
  painter.setPen(color);
  
  // Iterative clipping until the line is completely inside or outside the window
  while (true){
    // Giving regions for the points
    std::string regionPoint1 = "", regionPoint2 = "";

    regionPoint1 += ( y1 < wTop  ) ? "T" : ( y1 >  wBottom) ?  "B" : "";
    regionPoint1 += ( x1 < wLeft ) ? "L" : ( x1 > wRight) ? "R" : "";

    regionPoint2 += ( y2 < wTop  ) ? "T" : ( y2 >  wBottom) ?  "B" : "";
    regionPoint2 += ( x2 < wLeft ) ? "L" : ( x2 > wRight) ? "R" : "";

    // Case 1 : The whole line is in the window (visible) -> draw it 
    if (regionPoint1 == "" && regionPoint2 == ""){
      drawLine(x1, y1, x2, y2);
      return;
    }

    // Case 2 : The whole line is outside the window (invisible) -> do not draw anything
    // if the intersection between the tow points region is {} 
    bool isOutside = false;
    for (char c : regionPoint1) {
        if (regionPoint2.find(c) != std::string::npos) {
            // If there's a common character between the two region strings,
            // it means there's a part of the line inside the window.
            isOutside = true;
            break;
        }
    }

    // If no common character found, the line is completely outside the window.
    if (isOutside) {
        return;
    }

    // Case 3: Otherwise
    // Clip both points
    float m = (y2 - y1) / (x2 - x1);
    float* xArr[] = {&x1, &x2};
    float* yArr[] = {&y1, &y2};
    std::string regionPointArr[] = {regionPoint1, regionPoint2};


    for (int i = 0; i < 2; ++i) {
      // In the first loop we clip the first point against the 4 directions, and in the second loop we do fo the second one
      // I did this to avoid creating new function

      if (regionPointArr[i].find("L") != std::string::npos) {
          *yArr[i] += m * (wLeft - *xArr[i]);
          *xArr[i] = wLeft;
      } else if (regionPointArr[i].find("R") != std::string::npos) {
          *yArr[i] += m * (wRight - *xArr[i]);
          *xArr[i] = wRight;
      }

      if (regionPointArr[i].find("T") != std::string::npos) {
          *xArr[i] += (wTop - *yArr[i]) / m;
          *yArr[i] = wTop;
      } else if (regionPointArr[i].find("B") != std::string::npos) {
          *xArr[i] += (wBottom - *yArr[i]) / m;
          *yArr[i] = wBottom;
      }
    }

    /*
      Other 2 alterative ways for Case 3:

        1. repeat this code for the 2 points

            float m = (y2 - y1) / (x2 - x1);
            if (regionPoint1.find("L") != string::npos ){
              y1 += m * (wLeft - x1);
              x1 = wLeft;
            }else if (regionPoint1.find("R") != string::npos ){
              y1 += m * (wRight - x1 );
              x1 = wRight;
            }

            if (regionPoint1.find("T") != string::npos ){
              x1 += (wTop - y1) / m;
              y1 = wTop;
            }else if (regionPoint1.find("B") != string::npos ){
              x1 += (wBottom - y1) / m;
            }

        2. Write a function to clip a point, and call it twice   
    */
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
