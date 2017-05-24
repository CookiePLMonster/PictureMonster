#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qfiledialog.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_scene = new QGraphicsScene(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_scene;
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName( this, tr("Open file"), QString(), tr("Images (*.png *.xpm *.jpg)") );
    m_currentImage.load( fileName );

    submitToScene();
}

void MainWindow::submitToScene()
{
    m_scene->addPixmap(QPixmap::fromImage(m_currentImage));
    ui->graphicsView->setScene(m_scene);
}
