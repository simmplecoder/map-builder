#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QListWidgetItem>
#include <QIcon>
#include <iostream>
#include <QPixmap>
#include <QPainter>
#include <QRect>
#include <QPixmap>
#include <QGraphicsScene>
#include <QFile>
#include <QTextStream>
#include <QDebug>

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

    QIcon rectangleIcon("./assets/rectangle.ico");
    QIcon circleIcon("./assets/circle.ico");

    QListWidgetItem* item = new QListWidgetItem(rectangleIcon, "Rectangle", nullptr, Shapes::Rectangle);
    ui->ShapesList->addItem(item);

    item = new QListWidgetItem(circleIcon, "Circle", nullptr, Shapes::Circle);
    ui->ShapesList->addItem(item);

    scene = new QGraphicsScene(ui->mapBg);
    scene->setSceneRect(0, 0, 1024, 768);
    ui->graphicsView->setScene(scene);
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
    }
    else
    {
        ui->leftX->setText("Left X");
        ui->upperY->setText("Upper Y");
        ui->width->setText("Width");
        ui->height->setText("Height");
        ui->heightEdit->setDisabled(false);
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
        stream << pos.x() << ' ' << pos.y() << ' ';
        auto rect = items[i].shape->boundingRect();
        if (items[i].is_rect)
        {
            stream << rect.width() << ' ' << rect.height() << ' ';
            stream << items[i].name << '\n';
        }
        else
        {
            stream << rect.width() << ' ' << items[i].name << '\n';
        }
    }
}

void MainWindow::createRectangle(int x, int y, int w, int h, const QString& str)
{
    int red = dist(twister);
    int green = dist(twister);
    int blue = dist(twister);

    QGraphicsRectItem* rect = scene->addRect(x, y, w, h, QPen(Qt::black), QBrush(QColor(red, green, blue)));
    rect->setFlag(QGraphicsItem::ItemIsMovable);
    items.push_back({rect, true, str});
    shapeTypes.push_back(0);
}

void MainWindow::createCircle(int x, int y, int radius, const QString& str)
{
    int red = dist(twister);
    int green = dist(twister);
    int blue = dist(twister);

    auto circle = scene->addEllipse(x, y, radius, radius, QPen(Qt::black), QBrush(QColor(red, green, blue)));
    circle->setFlag(QGraphicsItem::ItemIsMovable);
    items.push_back({circle, false, str});
    shapeTypes.push_back(1);
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
