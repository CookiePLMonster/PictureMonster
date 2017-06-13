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
        EFFECT_DESATURATE
    };

    enum Desaturate
    {
        DESATURATE_AVG

    };

    void applyEffect(Effect effect, QImage& image);

    void setPosterizationProperties(int numThresholds);
    void setDesaturationTechnique(Desaturate technique) { m_desaturateTechnique = technique; }

    EffectApplicator();

private:
    int m_posterizationThresholds;

    Desaturate m_desaturateTechnique = DESATURATE_AVG;
};

#endif // EFFECTAPPLICATOR_H
