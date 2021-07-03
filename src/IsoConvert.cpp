#include "IsoConvert.h"

IsoConvert::IsoConvert()
{
    //ctor
}

IsoConvert::~IsoConvert()
{
    //dtor
}

Point IsoConvert::isoToTwoD(double x, double y)
{
  Point newPoint = Point(0, 0);
  newPoint.x = (2 * y + x) / 2;
  newPoint.y = (2 * y - x) / 2;
  return(newPoint);
}

Point IsoConvert::twoDToIso(double x, double y)
{
  Point newPoint = Point(0, 0);
  newPoint.x = x - y;
  newPoint.y = (x + y) / 2;
  return(newPoint);
}

 void IsoConvert::pointToField(Point *point, Field *field, int offsetX, int offsetY, int tileWidth, int tileHeight)
 {
    int screenXwithOffset = point->x - offsetX;
    int screenYwithOffset = point->y - offsetY;

    Point clickedPoint2D = isoToTwoD(screenXwithOffset, screenYwithOffset);
    clickedPoint2D.x = clickedPoint2D.x - (tileWidth / 2);
    clickedPoint2D.y = clickedPoint2D.y + (tileHeight / 2);

    int column = ceil(clickedPoint2D.x / tileWidth) -1;
    int row = ceil(clickedPoint2D.y / tileHeight) - 1;

    field->x = column;
    field->y = row;
 }
