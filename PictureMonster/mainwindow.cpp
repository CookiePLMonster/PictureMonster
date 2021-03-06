#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "posterizedialog.h"

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

    addUndo();

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
        file->write(getCurrentImage());
        file->close();

        m_history.erase(m_historyCursor, m_history.end());
        m_history.append(QSharedPointer<QTemporaryFile>(file));
        m_historyCursor = m_history.end();

        ui->actionUndo->setEnabled(m_history.size() > 1);
        ui->actionRedo->setEnabled(false);
    }
}

QByteArray MainWindow::getCurrentImage()
{
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::ReadWrite);
    m_currentImage.save(&buffer, "PNG");
    return ba;
}

void MainWindow::on_actionNegative_triggered()
{
    m_applicator.applyEffect( EffectApplicator::EFFECT_NEGATIVE, m_currentImage );
    submitToScene();

    addUndo();
}

void MainWindow::on_actionSepia_triggered()
{
    m_applicator.applyEffect( EffectApplicator::EFFECT_SEPIA, m_currentImage );
    submitToScene();

    addUndo();
}

void MainWindow::on_actionPosterize_triggered()
{
    PosterizeDialog dialog;
    dialog.setPixmap(m_currentImage);

    int result = dialog.exec();
    if ( result == QDialog::Accepted )
    {
        m_currentImage = dialog.getImage();
        submitToScene();

        addUndo();

    }
}

void MainWindow::on_actionMax_RGB_triggered()
{
    m_applicator.applyEffect( EffectApplicator::EFFECT_MAXRGB, m_currentImage );
    submitToScene();

    addUndo();
}

void MainWindow::on_actionUndo_triggered()
{
    --m_historyCursor;
    auto& file = (*(m_historyCursor-1));
    if ( file->open() )
    {
        m_currentImage.loadFromData(file->readAll());
        file->close();

        submitToScene();
    }
    if ( (m_historyCursor-1) == m_history.begin() )
    {
        ui->actionUndo->setEnabled(false);
    }
    ui->actionRedo->setEnabled(true);
}

void MainWindow::on_actionRedo_triggered()
{
    auto& file = (*(m_historyCursor++));
    if ( file->open() )
    {
        m_currentImage.loadFromData(file->readAll());
        file->close();

        submitToScene();
    }
    if ( m_historyCursor == m_history.end() )
    {
        ui->actionRedo->setEnabled(false);
    }
    ui->actionUndo->setEnabled(true);
}

void MainWindow::on_actionSave_triggered()
{
    if ( m_currentImage.isNull() ) return;

    QString fileName = QFileDialog::getSaveFileName( this, tr("Save file"), QString(), tr("Images (*.png *.xpm *.jpg)") );
    m_currentImage.save(fileName);
}

void MainWindow::on_actionAverage_triggered()
{
    onActionDesaturate(EffectApplicator::DESATURATE_AVG);
}

void MainWindow::on_actionLuma_triggered()
{
    onActionDesaturate(EffectApplicator::DESATURATE_LUMA);
}

void MainWindow::on_actionDesaturate_2_triggered()
{
    onActionDesaturate(EffectApplicator::DESATURATE_DES);
}

void MainWindow::onActionDesaturate(EffectApplicator::Desaturate technique)
{
    m_applicator.setDesaturationTechnique(technique);
    m_applicator.applyEffect( EffectApplicator::EFFECT_DESATURATE, m_currentImage );
    submitToScene();

    addUndo();
}

void MainWindow::on_actionMax_Decomposition_triggered()
{
    onActionDesaturate(EffectApplicator::DESATURATE_DECOMPMAX);
}

void MainWindow::on_actionMin_Decomposition_triggered()
{
    onActionDesaturate(EffectApplicator::DESATURATE_DECOMPMIN);
}

void MainWindow::on_actionMin_RGB_triggered()
{
    m_applicator.applyEffect( EffectApplicator::EFFECT_MINRGB, m_currentImage );
    submitToScene();

    addUndo();
}

void MainWindow::on_actionBox_Blur_triggered()
{
    m_applicator.applyEffect( EffectApplicator::EFFECT_BOXBLUR, m_currentImage );
    submitToScene();

    addUndo();
}
