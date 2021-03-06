#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QGraphicsScene>
#include <QTemporaryFile>

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

    void on_actionPosterize_triggered();

    void on_actionMax_RGB_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionSave_triggered();

    void on_actionAverage_triggered();

    void on_actionLuma_triggered();

    void on_actionDesaturate_2_triggered();

    void on_actionMax_Decomposition_triggered();

    void on_actionMin_Decomposition_triggered();

    void on_actionMin_RGB_triggered();

    void on_actionBox_Blur_triggered();

private:
    void onActionDesaturate(EffectApplicator::Desaturate technique);

    void submitToScene();
    void addUndo();

    QByteArray getCurrentImage();

private:
    Ui::MainWindow *ui;

    // Monster data
    QImage  m_currentImage;
    QGraphicsScene* m_scene;

    EffectApplicator m_applicator;

    QList<QSharedPointer<QTemporaryFile>> m_history;
    QList<QSharedPointer<QTemporaryFile>>::iterator m_historyCursor;
};

#endif // MAINWINDOW_H
