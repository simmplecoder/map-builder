#ifndef GENERATEASDIALOG_H
#define GENERATEASDIALOG_H

#include <QDialog>
#include <QGraphicsScene>
#include <QString>

namespace Ui {
class GenerateAsDialog;
}

class GenerateAsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GenerateAsDialog(QGraphicsScene* scene, QWidget *parent = 0);
    ~GenerateAsDialog();

public slots:
    void onGenerateClicked();
    void onEditCleared();
    void onReturnPressed();

private:
    Ui::GenerateAsDialog *ui;
    QGraphicsScene* scene;

private:
    bool tryGenerateFile(const QString& fileName);
};

#endif // GENERATEASDIALOG_H
