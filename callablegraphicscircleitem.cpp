#include "callablegraphicscircleitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEllipseItem>
#include <mainwindow.h>

CallableGraphicsCircleItem::CallableGraphicsCircleItem(
        int xPos, int yPos, int r,
        MainWindow* p):
    QGraphicsEllipseItem(xPos, yPos, r, r),
    ptr(p),
    isPressed(false)
{}

void CallableGraphicsCircleItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (!isPressed)
    {
        ptr->updateEdits(this);
        isPressed = true;
    }
    QGraphicsEllipseItem::mousePressEvent(event);
}

void CallableGraphicsCircleItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    auto pressedButton = event->button();

    if (pressedButton == Qt::MouseButton::RightButton)
    {
        ptr->deleteItem(this);
        return;
    }

    isPressed = false;
    QGraphicsEllipseItem::mouseReleaseEvent(event);
}

QVariant CallableGraphicsCircleItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionHasChanged)
    {
        ptr->updateEdits(this);
    }

    return QGraphicsItem::itemChange(change, value);
}
