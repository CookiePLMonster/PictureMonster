#include "effectapplicator.h"

void EffectApplicator::applyEffect(EffectApplicator::Effect effect, QImage &image)
{
    switch ( effect )
    {
    case EFFECT_NEGATIVE:
        {
            uchar* colors = image.bits();
            for ( int i = 0; i < image.byteCount(); i += 4 )
            {
                colors[0] = 255 - colors[0];
                colors[1] = 255 - colors[1];
                colors[2] = 255 - colors[2];

                colors += 4;
            }
            break;
        }
    case EFFECT_SEPIA:
        {
            uchar* colors = image.bits();
            for ( int i = 0; i < image.byteCount(); i += 4 )
            {
                float red = colors[2];
                float green = colors[1];
                float blue = colors[0];

                colors[2] = qMin((.393 * red) + (.769 * green) + (.189 * (blue)), 255.0);
                colors[1] = qMin((.349 * red) + (.686 * green) + (.168 * (blue)), 255.0);
                colors[0] = qMin((.272 * red) + (.534 * green) + (.131 * (blue)), 255.0);

                colors += 4;
            }
            break;
        }
    case EFFECT_POSTERIZE:
        {
            uchar* colors = image.bits();
            float numAreas = 256.0 / m_posterizationThresholds;
            float numValues = 255.0 / (m_posterizationThresholds - 1);
            for ( int i = 0; i < image.byteCount(); i += 4 )
            {
                colors[0] = uint(numValues * uint(colors[0] / numAreas));
                colors[1] = uint(numValues * uint(colors[1] / numAreas));
                colors[2] = uint(numValues * uint(colors[2] / numAreas));

                colors += 4;
            }
            break;
        }
    case EFFECT_MAXRGB:
        {
            uchar* colors = image.bits();
            uchar maxVal = qMax( colors[0], qMax( colors[1], colors[2] ) );
            for ( int i = 0; i < image.byteCount(); i += 4 )
            {
                colors[0] = colors[0] < maxVal ? 0 : colors[0];
                colors[1] = colors[1] < maxVal ? 0 : colors[1];
                colors[2] = colors[2] < maxVal ? 0 : colors[2];

                colors += 4;
            }
            break;
        }
    case EFFECT_DESATURATE:
        {
            uchar* colors = image.bits();
            for ( int i = 0; i < image.byteCount(); i += 4 )
            {
                uint avg = desaturatePixel(colors);
                colors[0] = colors[1] = colors[2] = avg;

                colors += 4;
            }
            break;
        }
    }
}

void EffectApplicator::setPosterizationProperties(int numThresholds)
{
    m_posterizationThresholds = numThresholds;
}

EffectApplicator::EffectApplicator()
    : m_posterizationThresholds( 128 )
{

}

uint EffectApplicator::desaturatePixel(uchar *pixel) const
{
    switch ( m_desaturateTechnique )
    {
    case DESATURATE_AVG:
        return (pixel[0] + pixel[1] + pixel[2]) / 3;
    case DESATURATE_LUMA:
        return (pixel[0] * 0.114 + pixel[1] * 0.587 + pixel[2] * 0.299);
    case DESATURATE_DES:
        return ( qMin(pixel[0], qMin(pixel[1], pixel[2])) + qMax(pixel[0], qMax(pixel[1], pixel[2])) ) / 2;
    case DESATURATE_DECOMPMAX:
        return qMax(pixel[0], qMax(pixel[1], pixel[2]));
    case DESATURATE_DECOMPMIN:
        return qMin(pixel[0], qMin(pixel[1], pixel[2]));
    }
}
