#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QListWidgetItem>
#include <QIcon>
#include <QRect>
#include <QGraphicsScene>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QImage>
#include <QPainter>
#include <QResizeEvent>
#include "generateasdialog.h"
#include "mapresizedialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->shapeList, SIGNAL(currentIndexChanged(int)), this,
            SLOT(onSelectedShapeChanged(int)));
    connect(ui->createShapeButton, SIGNAL(released()), this, SLOT(onCreateClicked()));
    connect(ui->updateShapeButton, SIGNAL(released()), this, SLOT(onUpdateShapeClicked()));
    connect(ui->actionGenerate, SIGNAL(triggered(bool)), this, SLOT(onGenerateClicked()));
    connect(ui->actionGenerateAs, SIGNAL(triggered(bool)), this, SLOT(onGenerateAsClicked()));
    connect(ui->actionMap_size, SIGNAL(triggered(bool)), this, SLOT(onResizeMapClicked()));




    QIcon rectangleIcon(":/images/assets/rectangle-128.ico");
    QIcon circleIcon(":/images/assets/circle-128.ico");

    ui->shapeList->setItemIcon(Shapes::Rectangle, rectangleIcon);
    ui->shapeList->setItemIcon(Shapes::Circle, circleIcon);

    auto posValidator = new QIntValidator(0, 999999, this);
    ui->leftXEdit->setValidator(posValidator);
    ui->upperYEdit->setValidator(posValidator);

    auto sizeValidator = new QIntValidator(1, 999999, this);
    ui->widthEdit->setValidator(sizeValidator);
    ui->heightEdit->setValidator(sizeValidator);

    scene = new QGraphicsScene(this);
    auto mapSize = ui->graphicsView->size();

    scene->setSceneRect(0, 0, mapSize.width(), mapSize.height());
    ui->graphicsView->setScene(scene);

    connect(scene, SIGNAL(focusItemChanged(QGraphicsItem*,QGraphicsItem*,Qt::FocusReason)),
            this, SLOT(onAnotherShapeFocused(QGraphicsItem*,QGraphicsItem*,Qt::FocusReason)));

    ui->updateShapeButton->setDisabled(true);

    //disable everything since no shape is selected

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

//    auto newSize = event->size();
//    ui->graphicsView->setGeometry(0, 0, newSize.width(), newSize.height());
}

void MainWindow::onSelectedShapeChanged(int index)
{
    switch (index)
    {
    case Shapes::Circle:
    {
        ui->positionType->setText("Center");
        ui->width->setText("Radius");
        ui->height->setText("Unused");
        ui->heightEdit->setDisabled(true);
        break;
    }

    case Shapes::Rectangle:
    {
        ui->positionType->setText("Upper left corner");
        ui->width->setText("Width");
        ui->heightEdit->setDisabled(false);
        ui->height->setText("Height");
    }
        break;
    default:
    {
        ui->createShapeButton->setDisabled(true);
        return;
    }
    }
    ui->createShapeButton->setDisabled(false);
}

void MainWindow::onCreateClicked()
{
    int x = ui->leftXEdit->text().toInt();
    int y = ui->upperYEdit->text().toInt();

    int index = ui->shapeList->currentIndex();

    if (index == Shapes::Rectangle)
    {
        int w = ui->widthEdit->text().toInt();
        int h = ui->heightEdit->text().toInt();
        createRectangle(x, y, w, h);
    }
    else if (index == Shapes::Circle)
    {
        int radius = ui->widthEdit->text().toInt();
        createCircle(x, y, radius);
    }

    currentShapeIndex = items.size() - 1;
    ui->updateShapeButton->setDisabled(false);
    auto currentShape = items[currentShapeIndex].shape;
    scene->setFocusItem(currentShape);
}

void MainWindow::onGenerateClicked()
{
    auto savedFocusItem = scene->focusItem();
    scene->clearFocus();

    int width = scene->width();
    int height = scene->height();

    QImage generatedMap(width, height, QImage::Format::Format_RGB16);
    generatedMap.fill(Qt::transparent);

    QPainter painter(&generatedMap);
    scene->render(&painter);
    generatedMap.save("Shapes.png");
    scene->setFocusItem(savedFocusItem);
}

void MainWindow::onGenerateAsClicked()
{
    auto generateAsDialog = new GenerateAsDialog(scene, this);
    generateAsDialog->exec();
}

void MainWindow::onResizeMapClicked()
{
    auto callback = std::bind(&MainWindow::resizeMap, this, std::placeholders::_1, std::placeholders::_2);
    auto mapResizeDialog = new MapResizeDialog(scene->width(), scene->height(), callback);

    mapResizeDialog->exec();
}

void MainWindow::createRectangle(int x, int y, int w, int h)
{
    auto callableRect = shapeGenerator.createRectangle(QPoint(x, y), w, h, this);

    scene->addItem(callableRect);

    const ShapeData shapeData(callableRect, true, x, y, w, h);
    items.push_back(shapeData);
}

void MainWindow::createCircle(int x, int y, int radius)
{
    auto callableCircle = shapeGenerator.createCircle(QPoint(x, y), radius, this);

    scene->addItem(callableCircle);

    const ShapeData shapeData(callableCircle, false, x, y, radius, radius);
    items.push_back(shapeData);
}

void MainWindow::resetEdits()
{
    ui->upperYEdit->clear();
    ui->leftXEdit->clear();
    ui->widthEdit->clear();
    ui->heightEdit->clear();
}

void MainWindow::onAnotherShapeFocused(QGraphicsItem *newFocusItem, QGraphicsItem *oldFocusItem, Qt::FocusReason reason)
{
    (void)oldFocusItem; //not needed
    (void)reason; //not needed;

    for (int i =0; i < items.size(); ++i)
    {
        if (items[i].shape == newFocusItem)
        {
            currentShapeIndex = i;
            ui->updateShapeButton->setDisabled(false);
            break;
        }
    }

    ui->shapeList->setCurrentIndex(1 + items[currentShapeIndex].isRect);
    ui->widthEdit->setText(QString::number(items[currentShapeIndex].width));
    if (!items[currentShapeIndex].isRect)
    {
        ui->heightEdit->setDisabled(true);
    }
    else
    {
        ui->heightEdit->setDisabled(false);
        ui->heightEdit->setText(QString::number(items[currentShapeIndex].height));
    }
}

void MainWindow::updateEdits(QAbstractGraphicsShapeItem* item)
{
    auto posReal = item->scenePos();
    auto pos = posReal.toPoint();

    QString coordinate;
    coordinate.setNum(items[currentShapeIndex].x + (int)pos.x());
    ui->leftXEdit->setText(coordinate);
    coordinate.setNum(items[currentShapeIndex].y + (int)pos.y());
    ui->upperYEdit->setText(coordinate);
}

void MainWindow::onUpdateShapeClicked()
{
    scene->removeItem(items[currentShapeIndex].shape);
    delete items[currentShapeIndex].shape;

    items.remove(currentShapeIndex);
    onCreateClicked();
}

void MainWindow::deleteItem(QAbstractGraphicsShapeItem *item)
{
    for (int i = 0; i < items.size(); ++i)
    {
        if (items[i].shape == item)
        {
            scene->removeItem(item);
            delete item;
            items.remove(i);
            break;
        }
    }

    currentShapeIndex = items.size() - 1;
    ui->updateShapeButton->setDisabled(true);
}

void MainWindow::resizeMap(int newWidth, int newHeight)
{
    scene->setSceneRect(0, 0, newWidth, newHeight);

    for (int i = 0; i < items.size(); ++i)
    {
        auto pos = items[i].shape->pos();
        if (pos.x() > newWidth || pos.y() > newHeight)
        {
            scene->removeItem(items[i].shape);
            delete items[i].shape;
            items.remove(i);
        }
    }

    setMaximumWidth(newWidth);
    setMaximumHeight(newHeight);

    ui->graphicsView->setGeometry(0, 0, newWidth, newHeight + 20);
    ui->centralWidget->setGeometry(0, 0, newWidth, newHeight + 20);
}
