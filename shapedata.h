#ifndef SHAPEDATA_H
#define SHAPEDATA_H

#include <QAbstractGraphicsShapeItem>
#include <QString>

struct ShapeData
{
    ShapeData(QAbstractGraphicsShapeItem* shape_, bool is_rect_, const QString& name_):
        shape(shape_),
        is_rect(is_rect_),
        name(name_)
    {}

    ShapeData() = default;

    QAbstractGraphicsShapeItem* shape;
    bool is_rect;
    QString name;
};

#endif // SHAPEDATA_H
