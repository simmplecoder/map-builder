#include "callablegraphicscircleitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEllipseItem>
#include <mainwindow.h>

CallableGraphicsCircleItem::CallableGraphicsCircleItem(
        int xPos, int yPos, int r,
        const QString& rectName, MainWindow* p):
    QGraphicsEllipseItem(xPos, yPos, r, r),
    name_(rectName),
    ptr(p),
    isPressed(false)
{}

//void CallableGraphicsCircleItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
//{
//    if (!isPressed)
//    {
//        ptr->updateEdits(this);
//        isPressed = true;
//    }
//    QGraphicsEllipseItem::mousePressEvent(event);
//}

//void CallableGraphicsCircleItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
//{
//    auto pressedButton = event->button();

//    if (pressedButton == Qt::MouseButton::RightButton)
//    {
//        ptr->deleteItem(this);
//        return;
//    }

//    QGraphicsEllipseItem::mouseReleaseEvent(event);
//    ptr->updateEdits(this);
//    isPressed = false;
//}

QVariant CallableGraphicsCircleItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionHasChanged)
    {
        ptr->updateEdits(this);
    }

    return QGraphicsItem::itemChange(change, value);
}


QString CallableGraphicsCircleItem::name() const
{
    return name_;
}
