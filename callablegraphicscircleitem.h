#ifndef CALLABLEGRAPHICSCIRCLEITEM_H
#define CALLABLEGRAPHICSCIRCLEITEM_H
#include <QGraphicsRectItem>
#include <QString>

class MainWindow;

class CallableGraphicsCircleItem : public QGraphicsEllipseItem
{
private:
    QString name_; //TODO: remove this from here and rect, remove references
    MainWindow* ptr;
    bool isPressed;
public:

    CallableGraphicsCircleItem(int xPos, int yPos, int r,
            const QString& circleName, MainWindow* p);

    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    QString name() const;

    virtual ~CallableGraphicsCircleItem() = default;
};

#endif // CALLABLEGRAPHICSCIRCLEITEM_H
