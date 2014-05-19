#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle
{
private:
    float x;
    float y;
    float width;
    float height;
public:
    Rectangle(float x, float y, float height, float width);
    void vSetX(float _x) {x = _x;}
    void vSetY(float _y) {y = _y;}
    void vSetHeight(float _height) {height = _height;}
    void vSetWidth(float _width) {width = _width;}
    bool contains(float x, float y);
};

#endif // RECTANGLE_H
