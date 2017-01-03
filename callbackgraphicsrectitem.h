#ifndef CALLBACKGRAPHICSRECTITEM_H
#define CALLBACKGRAPHICSRECTITEM_H

#include <QString>
#include <QGraphicsRectItem>

class MainWindow;

class CallableGraphicsRectItem : public QGraphicsRectItem
{
private:
    MainWindow* ptr;
    bool isPressed;
public:
    CallableGraphicsRectItem(int xPos, int yPos, int rectWidth, int rectHeight,
                             MainWindow* p);

    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    virtual ~CallableGraphicsRectItem() = default;
};

#endif // CALLBACKGRAPHICSRECTITEM_H
