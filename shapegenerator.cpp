#include "shapegenerator.h"
#include "callablegraphicscircleitem.h"
#include "callbackgraphicsrectitem.h"
#include <QBrush>

QAbstractGraphicsShapeItem* ShapeGenerator::createRectangle(const QPoint& upperLeft,
                                                            int width, int height, MainWindow* p)
{
    CallableGraphicsRectItem* rect = new CallableGraphicsRectItem(upperLeft.x(), upperLeft.y(), width, height, p);
    postprocess(rect);

    return rect;
}

QAbstractGraphicsShapeItem* ShapeGenerator::createCircle(const QPoint &center,
                                                         int radius, MainWindow *p)
{
    CallableGraphicsCircleItem* circle = new CallableGraphicsCircleItem(center.x(), center.y(), radius, p);
    postprocess(circle);

    return circle;

}

void ShapeGenerator::postprocess(QAbstractGraphicsShapeItem *shape)
{
    shape->setBrush(QBrush(gen()));
    shape->setFlag(QGraphicsItem::ItemIsMovable);
    shape->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    shape->setFlag(QGraphicsItem::ItemIsFocusable);
}
