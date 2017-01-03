#include "callbackgraphicsrectitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include "mainwindow.h"

CallableGraphicsRectItem::CallableGraphicsRectItem(
        int xPos, int yPos,
        int rectWidth, int rectHeight,
        MainWindow* p):
    QGraphicsRectItem(xPos, yPos, rectWidth, rectHeight),
    ptr(p)
{}

void CallableGraphicsRectItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (!isPressed)
    {
        ptr->updateEdits(this);
        isPressed = true;
    }
    QGraphicsRectItem::mousePressEvent(event);
}

void CallableGraphicsRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    auto pressedButton = event->button();
    if (pressedButton == Qt::MouseButton::RightButton)
    {
        ptr->deleteItem(this);
        return;
    }

    isPressed = false;
    QGraphicsRectItem::mouseReleaseEvent(event);
}

QVariant CallableGraphicsRectItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange)
    {
        ptr->updateEdits(this);
    }

    return QGraphicsItem::itemChange(change, value);
}
