#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QGraphicsScene>
#include <QVector>
#include <QAbstractGraphicsShapeItem>
#include "shapedata.h"
#include "shapegenerator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void updateEdits(QAbstractGraphicsShapeItem* item);
    void deleteItem(QAbstractGraphicsShapeItem* item);
public slots:
    void onSelectedShapeChanged(int index);
    void onCreateClicked();
    void onGenerateClicked();
    void onGenerateAsClicked();
    void onUpdateShapeClicked();
    void onResizeMapClicked();
    void onAnotherShapeFocused(QGraphicsItem *newFocusItem, QGraphicsItem *oldFocusItem, Qt::FocusReason reason);

private:
    Ui::MainWindow* ui;
    QGraphicsScene* scene;
    QVector<ShapeData> items;
    int currentShapeIndex;
    ShapeGenerator shapeGenerator;

private:
    /*
    Harcode the values starting from 1
    since QCombobx
    has "select item ..." as first element
    */
    enum Shapes : int {
        Circle = 1,
        Rectangle = 2
    };

    void resizeMap(int newWidth, int newHeight);
    void createRectangle(int x, int y, int w, int h);
    void createCircle(int x, int y, int radius);
    void resizeEvent(QResizeEvent *event) override;

    void resetEdits();


};

#endif // MAINWINDOW_H
