#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QGraphicsScene>
#include <QVector>
#include <QAbstractGraphicsShapeItem>
#include <random>
#include "shapedata.h"
#include "callablegraphicscircleitem.h"
#include "callbackgraphicsrectitem.h"

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
    void onSelectedShapeChanged(QListWidgetItem* current, QListWidgetItem* previous);
    void onCreateClicked();
    void onMapResizeClicked();
    void onGenerateClicked();
    void onUpdateShapeClicked();

private:
    Ui::MainWindow* ui;
    QGraphicsScene* scene;
    QVector<ShapeData> items;
    std::mt19937 twister;
    std::uniform_int_distribution<> dist;
    int currentWidth;
    int currentHeight;
    int currentShapeIndex;
private:
    enum Shapes : int {Rectangle, Circle};

    void createRectangle(int x, int y, int w, int h, const QString& str);
    void createCircle(int x, int y, int radius, const QString& str);

    void resetEdits();


};

#endif // MAINWINDOW_H
