#ifndef MAPRESIZEDIALOG_H
#define MAPRESIZEDIALOG_H

#include <QDialog>
#include <functional>

namespace Ui {
class MapResizeDialog;
}

class MapResizeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MapResizeDialog(int currentWidth_, int currentHeight_,
                             const std::function<void(int, int)>& callback_, QWidget *parent = 0);
    ~MapResizeDialog();

public slots:
    void onResizeMapClicked();

private:
    Ui::MapResizeDialog *ui;
    int currentWidth;
    int currentHeight;
    std::function<void(int, int)> callback;

private:
    void setCurrentSizeText();
};

#endif // MAPRESIZEDIALOG_H
