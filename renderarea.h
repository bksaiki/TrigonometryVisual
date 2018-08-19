/*
    Trigonometry Visual
    Brett Saiki <bksaiki@gmail.com>
    August 2018

    Graphically displays all six trignometric functions (sin, cos, tan, csc, sec, cot)
    on a unit circle.
*/
/*
    File: renderarea.h

    Defins a widget that
 */

#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <math.h>
#include <QPainter>
#include <QWidget>

/* Restricts a value within a certain range */
template <typename T>
const T& clamp(const T& value, const T& low, const T& high)
{
    return (value < low) ? low : (value > high) ? high : value;
}

/* Implements a QWidget that draws the unit circle and lines corresponding
   to the trigonometric functions */
class RenderArea : public QWidget
{
public:
    /* Default constructor. Initializes widgets */
    explicit RenderArea(QWidget* parent = nullptr);

    /* Explicit overridden destructor */
    ~RenderArea() override {}

    /* Returns the angle of the line on the unit circle */
    inline double getAngle() { return mAngle; }

    /* Sets the angle of the line on the unit circle */
    inline void setAngle(double angle)
    {
        mAngle = angle;
        update();
    }

protected:
    /* Draws */
    void paintEvent(QPaintEvent* event) override;

private:
    double mAngle;
};

#endif // RENDERAREA_H
