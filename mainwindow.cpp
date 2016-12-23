#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QListWidgetItem>
#include <QIcon>
#include <QRect>
#include <QGraphicsScene>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "callbackgraphicsrectitem.h"
#include "callablegraphicscircleitem.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dist(0, 255),
    currentWidth(1024),
    currentHeight(768)
{
    ui->setupUi(this);

    connect(ui->ShapesList, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(onSelectedShapeChanged(QListWidgetItem*,QListWidgetItem*)));
    connect(ui->createShapeButton, SIGNAL(released()), this, SLOT(onCreateClicked()));
    connect(ui->resizeMapButton, SIGNAL(released()), this, SLOT(onMapResizeClicked()));
    connect(ui->generateButton, SIGNAL(released()), this, SLOT(onGenerateClicked()));
    connect(ui->updateShapeButton, SIGNAL(released()), this, SLOT(onUpdateShapeClicked()));

    QIcon rectangleIcon(":/images/assets/rectangle-128.ico");
    QIcon circleIcon(":/images/assets/circle-128.ico");

    QListWidgetItem* item = new QListWidgetItem(rectangleIcon, "Rectangle", nullptr, Shapes::Rectangle);
    ui->ShapesList->addItem(item);

    item = new QListWidgetItem(circleIcon, "Circle", nullptr, Shapes::Circle);
    ui->ShapesList->addItem(item);

    scene = new QGraphicsScene(ui->mapBg);
    auto mapSize = ui->mapBg->size();

    scene->setSceneRect(0, 0, mapSize.width() - 20, mapSize.height() - 20);
    ui->graphicsView->setScene(scene);

    ui->updateShapeButton->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSelectedShapeChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    (void)previous;
    if (current->type() == Shapes::Circle)
    {
        ui->leftX->setText("X");
        ui->upperY->setText("Y");
        ui->width->setText("Radius");
        ui->height->setText("Unused");
        ui->heightEdit->setDisabled(true);
//        ui->height->hide();
//        ui->heightEdit->hide();
    }
    else
    {
        ui->leftX->setText("Left X");
        ui->upperY->setText("Upper Y");
        ui->width->setText("Width");
        ui->heightEdit->setDisabled(false);
//        ui->height->show();
//        ui->heightEdit->show();
        ui->height->setText("Height");
    }
}

void MainWindow::onCreateClicked()
{
    int x = ui->leftXEdit->text().toInt();
    int y = ui->upperYEdit->text().toInt();
    QString name = ui->shapeNameEdit->text();
    if (ui->ShapesList->currentItem()->type() == Rectangle)
    {
        int w = ui->widthEdit->text().toInt();
        int h = ui->heightEdit->text().toInt();
        createRectangle(x, y, w, h, name);
    }
    else
    {
        int radius = ui->widthEdit->text().toInt();
        createCircle(x, y, radius, name);
    }

    currentShapeIndex = items.size() - 1;
    ui->updateShapeButton->setDisabled(false);
}

void MainWindow::onGenerateClicked()
{
    QFile file("Shapes.txt");
    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "shapes.txt opening failed, aborting\n";
        return;
    }

    QTextStream stream(&file);

    for (int i = 0; i < items.size(); ++i)
    {
        auto pos = items[i].shape->pos();
        stream << items[i].x + pos.x() << ' ' << items[i].y + pos.y() << ' ';
        auto rect = items[i].shape->boundingRect();
        if (items[i].isRect)
        {
//            stream << rect.width() << ' ' << rect.height() << ' ';
            stream << items[i].width << ' ' << items[i].height << ' ';
        }
        else
        {
            stream << rect.width() << ' ';
        }
        stream << items[i].name << '\n';
    }
}

void MainWindow::createRectangle(int x, int y, int w, int h, const QString& str)
{
    int red = dist(twister);
    int green = dist(twister);
    int blue = dist(twister);

    auto callableRect = new CallableGraphicsRectItem(x, y, w, h, str, this);

    callableRect->setBrush(QBrush(QColor(red, green, blue)));
    //callableRect->setPen(QPen(Qt::black));
    callableRect->setFlag(QGraphicsItem::ItemIsMovable);
    callableRect->setFlag(QGraphicsItem::ItemSendsGeometryChanges);

    scene->addItem(callableRect);

    const ShapeData shapeData(callableRect, str, true, x, y, w, h);
    items.push_back(shapeData);
}

void MainWindow::createCircle(int x, int y, int radius, const QString& str)
{
    int red = dist(twister);
    int green = dist(twister);
    int blue = dist(twister);

    auto callableCircle = new CallableGraphicsCircleItem(x, y, radius, str, this);

    callableCircle->setBrush(QBrush(QColor(red, green, blue)));
    //callableCircle->setPen(QPen(Qt::black));
    callableCircle->setFlag(QGraphicsItem::ItemIsMovable);
    callableCircle->setFlag(QGraphicsItem::ItemSendsGeometryChanges);

    scene->addItem(callableCircle);

    const ShapeData shapeData(callableCircle, str, false, x, y, radius, radius);
    items.push_back(shapeData);
}

void MainWindow::resetEdits()
{
    ui->upperYEdit->clear();
    ui->leftXEdit->clear();
    ui->widthEdit->clear();
    ui->heightEdit->clear();
    ui->shapeNameEdit->clear();
}

void MainWindow::updateEdits(QAbstractGraphicsShapeItem* item)
{
    for (int i =0; i < items.size(); ++i)
    {
        if (items[i].shape == item)
        {
            currentShapeIndex = i;
            ui->updateShapeButton->setDisabled(false);
            break;
        }
    }

    ui->shapeNameEdit->setText(items[currentShapeIndex].name);

    auto posReal = item->scenePos();
    auto pos = posReal.toPoint();

    QString coordinate;
    coordinate.setNum(items[currentShapeIndex].x + (int)pos.x());
    ui->leftXEdit->setText(coordinate);
    coordinate.setNum(items[currentShapeIndex].y + (int)pos.y());
    ui->upperYEdit->setText(coordinate);


//    auto boundingRectReal = item->sceneBoundingRect();
//    auto boundingRect = boundingRectReal.toRect();
//    ui->widthEdit->setText(QString::number(boundingRect.width()));
    ui->widthEdit->setText(QString::number(items[currentShapeIndex].width));
    if (!items[currentShapeIndex].isRect)
    {
        ui->heightEdit->setDisabled(true);
    }
    else
    {
        ui->heightEdit->setDisabled(false);
//        ui->heightEdit->setText(QString::number(boundingRect.height()));
        ui->heightEdit->setText(QString::number(items[currentShapeIndex].height));
    }
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

void MainWindow::onMapResizeClicked()
{
    int newWidth = ui->mapWidthEdit->text().toInt();
    int newHeight = ui->mapHeightEdit->text().toInt();
    scene->setSceneRect(0, 0, newWidth, newHeight);
    currentWidth = newWidth;
    currentHeight = newHeight;

    for (int i = 0; i < items.size(); ++i)
    {
        auto pos = items[i].shape->pos();
        if (pos.x() > currentWidth || pos.y() > currentHeight)
        {
            scene->removeItem(items[i].shape);
            delete items[i].shape;
            items.remove(i);
        }
    }
}
