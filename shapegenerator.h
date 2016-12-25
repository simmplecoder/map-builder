#ifndef SHAPEGENERATOR_H
#define SHAPEGENERATOR_H

#include "random_color_generator.h"
#include <QAbstractGraphicsShapeItem>
#include <QPoint>

class MainWindow;

class ShapeGenerator
{
    random_color_generator gen;
public:
    QAbstractGraphicsShapeItem* createRectangle(const QPoint& upperLeft, int width, int height, MainWindow* p);

    QAbstractGraphicsShapeItem* createCircle(const QPoint& center, int radius, MainWindow* p);
private:
    void postprocess(QAbstractGraphicsShapeItem* shape);
};

#endif // SHAPEGENERATOR_H
