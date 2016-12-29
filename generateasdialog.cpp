#include "generateasdialog.h"
#include "ui_generateasdialog.h"
#include <QPainter>
#include <QImage>

GenerateAsDialog::GenerateAsDialog(QGraphicsScene* scene_, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GenerateAsDialog),
    scene(scene_)
{
    ui->setupUi(this);

    ui->generateButton->setDisabled(true);
    connect(ui->generateButton, SIGNAL(released()), this, SLOT(onGenerateClicked()));
    connect(ui->fileName, SIGNAL(textChanged(QString)), this, SLOT(onEditCleared()));
    connect(ui->fileName, SIGNAL(returnPressed()), this, SLOT(onReturnPressed()));
}

void GenerateAsDialog::onReturnPressed()
{
    onGenerateClicked();
}

void GenerateAsDialog::onEditCleared()
{
    //text() returns by value, so not const reference
    QString currentText = ui->fileName->text();

    if (currentText.isEmpty())
    {
        ui->statusMessage->setText("File name cannot be empty");
        ui->generateButton->setDisabled(true);
        return;
    }
    ui->statusMessage->clear();
    ui->generateButton->setDisabled(false);
}

void GenerateAsDialog::onGenerateClicked()
{
    QString fileName = ui->fileName->text() + ui->fileExtension->currentText();
    if (tryGenerateFile(fileName))
    {
        ui->statusMessage->setText("Map generated successfully");
    }
    else
    {
        ui->statusMessage->setText("Error occured during generation");

    }
}

bool GenerateAsDialog::tryGenerateFile(const QString &fileName)
{
    scene->clearSelection();
    QImage image(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    QPainter painter(&image);
    scene->render(&painter);
    return image.save(fileName);
}


GenerateAsDialog::~GenerateAsDialog()
{
    delete ui;
}
