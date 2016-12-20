#ifndef SHAPEDATA_H
#define SHAPEDATA_H

#include <QAbstractGraphicsShapeItem>
#include <QString>

struct ShapeData
{
    ShapeData() = default;
    ShapeData(QAbstractGraphicsShapeItem* shape_, QString shapeName, bool isRect_,
              int x_, int y_, int width_, int height_):
        shape(shape_),
        name(shapeName),
        isRect(isRect_),
        x(x_),
        y(y_),
        width(width_),
        height(height_)
    {}

    QAbstractGraphicsShapeItem* shape;
    QString name;
    bool isRect;
    int x;
    int y;
    int width;
    int height;
};

#endif // SHAPEDATA_H
