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

#include <QPainter>
#include <QWidget>

/* Implements a QWidget that draws the unit circle and lines corresponding
   to the trigonometric functions */
class RenderArea : public QWidget
{
public:

    /* Default constructor. Initializes widgets */
    explicit RenderArea(QWidget* parent = nullptr);

protected:

    /* Draws */
    void paintEvent(QPaintEvent* event) override;
};

#endif // RENDERAREA_H
