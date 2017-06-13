#ifndef EFFECTAPPLICATOR_H
#define EFFECTAPPLICATOR_H

#include <QImage>

class EffectApplicator
{
public:
    enum Effect
    {
        EFFECT_NEGATIVE,
        EFFECT_SEPIA,
        EFFECT_POSTERIZE,
        EFFECT_MAXRGB,
        EFFECT_MINRGB,
        EFFECT_DESATURATE,

        EFFECT_BOXBLUR
    };

    enum Desaturate
    {
        DESATURATE_AVG,
        DESATURATE_LUMA,
        DESATURATE_DES,
        DESATURATE_DECOMPMAX,
        DESATURATE_DECOMPMIN
    };

    void applyEffect(Effect effect, QImage& image);

    void setPosterizationProperties(int numThresholds);
    void setDesaturationTechnique(Desaturate technique) { m_desaturateTechnique = technique; }

    EffectApplicator();

private:
    uint desaturatePixel(uchar* pixel) const;

    int m_posterizationThresholds;

    Desaturate m_desaturateTechnique = DESATURATE_AVG;
};

#endif // EFFECTAPPLICATOR_H
