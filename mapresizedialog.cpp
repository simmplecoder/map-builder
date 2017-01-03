#include "mapresizedialog.h"
#include "ui_mapresizedialog.h"
#include "mainwindow.h"
#include <QValidator>
#include <QString>

MapResizeDialog::MapResizeDialog(int currentWidth_, int currentHeight_, const std::function<void(int, int)>& callback_, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapResizeDialog),
    currentWidth(currentWidth_),
    currentHeight(currentHeight_),
    callback(callback_)
{
    ui->setupUi(this);
    QIntValidator* validator = new QIntValidator(40, 999999, this);

    ui->newWidthEdit->setValidator(validator);
    ui->newHeightEdit->setValidator(validator);

    connect(ui->resizeMapButton, SIGNAL(released()), this, SLOT(onResizeMapClicked()));

    setCurrentSizeText();
}

void MapResizeDialog::onResizeMapClicked()
{
    int newWidth = ui->newWidthEdit->text().toInt();
    int newHeight = ui->newHeightEdit->text().toInt();

    callback(newWidth, newHeight);

    currentWidth = newWidth;
    currentHeight = newHeight;

    setCurrentSizeText();
}

void MapResizeDialog::setCurrentSizeText()
{
    static const QString currentWidthText = "Current Width: ";
    static const QString currentHeightText = "Current Height: ";

    ui->currentWidthLabel->setText(currentWidthText + QString::number(currentWidth));
    ui->currentHeightLabel->setText(currentHeightText + QString::number(currentHeight));
}


MapResizeDialog::~MapResizeDialog()
{
    delete ui;
}
