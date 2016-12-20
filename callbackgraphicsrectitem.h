#ifndef CALLBACKGRAPHICSRECTITEM_H
#define CALLBACKGRAPHICSRECTITEM_H

#include <QGraphicsEllipseItem>
#include <functional>
#include <QString>

class MainWindow;

class CallableGraphicsRectItem : public QGraphicsRectItem
{
public:
    using Action = std::function<void(QAbstractGraphicsShapeItem*)>;
private:
    QString name_;
    MainWindow* ptr;
    bool isPressed;
public:
    CallableGraphicsRectItem(int xPos, int yPos, int rectWidth, int rectHeight,
                             QString rectName,
                             MainWindow* p);

    //virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
//    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    QString name() const;

    virtual ~CallableGraphicsRectItem() = default;
};

#endif // CALLBACKGRAPHICSRECTITEM_H
