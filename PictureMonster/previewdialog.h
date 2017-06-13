#ifndef PREVIEWDIALOG_H
#define PREVIEWDIALOG_H

#include <QGraphicsScene>
#include <QGraphicsView>

#include "effectapplicator.h"

class PreviewDialog : public QDialog
{
public:
    PreviewDialog(QWidget *parent)
        : QDialog(parent)
    {
        m_scene = new QGraphicsScene(this);
    }

    ~PreviewDialog()
    {
        delete m_scene;
    }

    void setPixmap(const QImage& image)
    {
        m_scratchImage = m_originalImage = image;
        submitToScene();
    }

    QImage& getImage()
    {
        return m_scratchImage;
    }

protected:
    void submitToScene()
    {
        m_scene->clear();
        m_scene->addPixmap(QPixmap::fromImage(m_scratchImage));
        m_view->setScene(m_scene);
    }

    void resetScratch()
    {
        m_scratchImage = m_originalImage;
    }

protected:
    EffectApplicator m_applicator;
    QGraphicsView* m_view;

private:
    QGraphicsScene* m_scene;
    QImage m_scratchImage, m_originalImage;
};

#endif // PREVIEWDIALOG_H
