#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QGraphicsScene>

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

private:
    void submitToScene();

private:
    Ui::MainWindow *ui;

    // Monster data
    QImage  m_currentImage;
    QGraphicsScene* m_scene;
};

#endif // MAINWINDOW_H
