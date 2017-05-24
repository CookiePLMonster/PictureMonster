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

    void applyEffect(Effect effect, QImage& image);

    void setPosterizationProperties(int numThresholds);

    EffectApplicator();

private:
    int m_posterizationThresholds;
};

#endif // EFFECTAPPLICATOR_H
