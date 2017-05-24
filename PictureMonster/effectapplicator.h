#ifndef EFFECTAPPLICATOR_H
#define EFFECTAPPLICATOR_H

#include <QImage>

class EffectApplicator
{
public:
    enum Effect
    {
        EFFECT_NEGATIVE,
        EFFECT_SEPIA
    };

    void applyEffect(Effect effect, QImage& image);

    EffectApplicator();
};

#endif // EFFECTAPPLICATOR_H
