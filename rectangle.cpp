#include "rectangle.h"

Rectangle::Rectangle(float x, float y, float height, float width)
{
   vSetX(x);
   vSetY(y);
   vSetHeight(height);
   vSetWidth(width);
}

bool Rectangle::contains(float _x, float _y)
{
    float pointX = _x;
    float pointY = _y;
    if (pointX < (x + (.5*width)) && pointX > (x - (.5*width)) && pointY < (y + (.5*height)) && pointY > (y - (.5*height)))
        return true;
    else
        return false;
}
