#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QGraphicsScene>

#include "effectapplicator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionNegative_triggered();

    void on_actionSepia_triggered();

private:
    void submitToScene();

private:
    Ui::MainWindow *ui;

    // Monster data
    QImage  m_currentImage;
    QGraphicsScene* m_scene;

    EffectApplicator m_applicator;
};

#endif // MAINWINDOW_H
