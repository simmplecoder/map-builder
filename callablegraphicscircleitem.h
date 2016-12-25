#ifndef CALLABLEGRAPHICSCIRCLEITEM_H
#define CALLABLEGRAPHICSCIRCLEITEM_H
#include <QGraphicsRectItem>
#include <QString>

class MainWindow;

class CallableGraphicsCircleItem : public QGraphicsEllipseItem
{
private:
    MainWindow* ptr;
    bool isPressed;
public:

    CallableGraphicsCircleItem(int xPos, int yPos, int r,
            MainWindow* p);

    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    virtual ~CallableGraphicsCircleItem() = default;
};

#endif // CALLABLEGRAPHICSCIRCLEITEM_H
