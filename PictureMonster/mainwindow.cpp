#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qfiledialog.h>
#include <qbuffer.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_scene = new QGraphicsScene(this);

    m_historyCursor = m_history.end();
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
    m_scene->clear();
    m_scene->addPixmap(QPixmap::fromImage(m_currentImage));
    ui->graphicsView->setScene(m_scene);
}

void MainWindow::addUndo()
{
    QTemporaryFile* file = new QTemporaryFile();
    if ( file->open() )
    {
        QByteArray ba;
        QBuffer buffer(&ba);
        buffer.open(QIODevice::ReadWrite);
        m_currentImage.save(&buffer, "PNG");

        file->write(ba);
        file->close();

        m_history.erase(m_historyCursor, m_history.end());
        m_history.append(QSharedPointer<QTemporaryFile>(file));
        m_historyCursor = m_history.end();

        ui->actionUndo->setEnabled(true);
    }
}

void MainWindow::on_actionNegative_triggered()
{
    addUndo();
    m_applicator.applyEffect( EffectApplicator::EFFECT_NEGATIVE, m_currentImage );
    submitToScene();
}

void MainWindow::on_actionSepia_triggered()
{
    addUndo();
    m_applicator.applyEffect( EffectApplicator::EFFECT_SEPIA, m_currentImage );
    submitToScene();
}

void MainWindow::on_actionPosterize_triggered()
{
    addUndo();
    m_applicator.setPosterizationProperties(2);
    m_applicator.applyEffect( EffectApplicator::EFFECT_POSTERIZE, m_currentImage );
    submitToScene();
}

void MainWindow::on_actionMax_RGB_triggered()
{
    addUndo();
    m_applicator.applyEffect( EffectApplicator::EFFECT_MAXRGB, m_currentImage );
    submitToScene();
}

void MainWindow::on_actionDesaturate_triggered()
{
    addUndo();
    m_applicator.applyEffect( EffectApplicator::EFFECT_DESATURATE, m_currentImage );
    submitToScene();
}

void MainWindow::on_actionUndo_triggered()
{
    --m_historyCursor;
    auto& file = (*m_historyCursor);
    if ( file->open() )
    {
        m_currentImage.loadFromData(file->readAll());
        file->close();

        submitToScene();
    }
    if ( m_historyCursor == m_history.begin() )
    {
        ui->actionUndo->setEnabled(false);
    }
}
