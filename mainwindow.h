#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QGraphicsScene>
#include <QVector>
#include <QAbstractGraphicsShapeItem>
#include <random>
#include "shapedata.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onSelectedShapeChanged(QListWidgetItem* current, QListWidgetItem* previous);
    void onCreateClicked();
    void onMapResizeClicked();
    void onGenerateClicked();
private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    QVector<ShapeData> items;
    QVector<int> shapeTypes;
    std::mt19937 twister;
    std::uniform_int_distribution<> dist;
    int currentWidth;
    int currentHeight;
private:
    enum Shapes : int {Rectangle, Circle};

    void createRectangle(int x, int y, int w, int h, const QString& str);
    void createCircle(int x, int y, int radius, const QString& str);

};

#endif // MAINWINDOW_H
