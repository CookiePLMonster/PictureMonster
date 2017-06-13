#ifndef POSTERIZEDIALOG_H
#define POSTERIZEDIALOG_H

#include <QDialog>

#include "previewdialog.h"

namespace Ui {
class PosterizeDialog;
}

class PosterizeDialog : public PreviewDialog
{
    Q_OBJECT

public:
    explicit PosterizeDialog(QWidget *parent = 0);
    ~PosterizeDialog();

private slots:
    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::PosterizeDialog *ui;

};

#endif // POSTERIZEDIALOG_H
