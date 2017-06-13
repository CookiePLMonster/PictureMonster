#include "posterizedialog.h"
#include "ui_posterizedialog.h"

PosterizeDialog::PosterizeDialog(QWidget *parent) :
    PreviewDialog(parent),
    ui(new Ui::PosterizeDialog)
{
    ui->setupUi(this);
    m_view = ui->graphicsView;
}

PosterizeDialog::~PosterizeDialog()
{
    delete ui;
}

void PosterizeDialog::on_horizontalSlider_valueChanged(int value)
{
    resetScratch();

    m_applicator.setPosterizationProperties(value);
    m_applicator.applyEffect( EffectApplicator::EFFECT_POSTERIZE, getImage() );
    submitToScene();
}
