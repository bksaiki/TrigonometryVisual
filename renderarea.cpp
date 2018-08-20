/*
 *  2D Graphics Modeler
 *  July 2018
 *
 *  David Epstein <DavidE92@live.com>
 *  Greg Graffius <ggraffius0@saddleback.edu>
 *  Justis Ketcham <justis.ketcham@gmail.com>
 *  Brett Saiki <bsaiki0@saddleback.edu>
 *
 *  Descr:   Final project for CS1C at Saddleback College (Summer 2018)
 *  Teacher: John Kath
 *
 *  Draws shapes using QPainter. Shapes can be loaded from a file, added
 *  to a vector, manipulated and later saved. A login is required to access
 *  the program.
 *
 **/
/*
    File: renderarea.cpp

    Defines a main window
 */

#include "renderarea.h"

/* Helper function */

RenderArea::RenderArea(QWidget* parent)
    : QWidget(parent)
{
    setMinimumSize(750, 750);
    setMaximumSize(750, 750);
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

void RenderArea::paintEvent(QPaintEvent* /* event */)
{
    int fullWidth = width();
    int fullHeight = height();
    int halfWidth = fullWidth / 2;
    int halfHeight = fullHeight / 2;
    int radius = 200;
    int arrowLength = 10;

    int sinVal = static_cast<int>(radius * sin(mAngle));
    int cosVal = static_cast<int>(radius * cos(mAngle));
    int cscVal = static_cast<int>(radius * (1.0 / sin(mAngle)));
    int secVal = static_cast<int>(radius * (1.0 / cos(mAngle)));

    int sinScaled = halfHeight - sinVal;
    int cosScaled = halfWidth + cosVal;
    int cscScaled = halfHeight - cscVal;
    int secScaled = halfWidth + secVal;

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(QColor("black"));

    /* Unit circle */
    painter.drawEllipse(halfWidth - radius, halfHeight - radius, radius * 2, radius * 2);
    painter.drawLine(0, halfHeight, fullWidth, halfHeight);
    painter.drawLine(halfWidth, 0, halfWidth, fullHeight);
    painter.drawLine(halfWidth, halfHeight, cosScaled, sinScaled);

    /* Arrows */
    painter.drawLine(0, halfHeight, arrowLength, halfHeight + arrowLength);
    painter.drawLine(0, halfHeight, arrowLength, halfHeight - arrowLength);
    painter.drawLine(halfWidth, 0, halfWidth + arrowLength, arrowLength);
    painter.drawLine(halfWidth, 0, halfWidth - arrowLength, arrowLength);
    painter.drawLine(fullWidth, halfHeight, fullWidth - arrowLength, halfHeight + arrowLength);
    painter.drawLine(fullWidth, halfHeight, fullWidth - arrowLength, halfHeight - arrowLength);
    painter.drawLine(halfWidth, fullHeight, halfWidth + arrowLength, fullHeight - arrowLength);
    painter.drawLine(halfWidth, fullHeight, halfWidth - arrowLength, fullHeight - arrowLength);

    /* Trigonometric functions */
    painter.setPen(QColor("red"));
    painter.drawLine(cosScaled, halfHeight, cosScaled, sinScaled);
    painter.setPen(QColor("blue"));
    painter.drawLine(halfWidth, sinScaled, cosScaled, sinScaled);
    painter.setPen(QColor(180, 140, 100));
    painter.drawLine(cosScaled, sinScaled, secScaled, halfHeight);
    painter.setPen(QColor("magenta"));
    painter.drawLine(halfWidth, halfHeight, halfWidth, cscScaled);
    painter.setPen(QColor("cyan"));
    painter.drawLine(halfWidth, halfHeight, secScaled, halfHeight);
    painter.setPen(QColor("green"));
    painter.drawLine(halfWidth, cscScaled, cosScaled, sinScaled);

    /* Angle markings */
    int angleLength = 15;
    int sinAngScaled = static_cast<int>(angleLength * sin(mAngle));
    int cosAngScaled = static_cast<int>(angleLength * cos(mAngle));
    int sinSign = signbit(sinAngScaled) ? -1 : 1;
    int cosSign = signbit(cosAngScaled) ? -1 : 1;

    painter.setPen(QColor("black"));
    painter.drawArc(halfWidth - angleLength, halfHeight - angleLength, angleLength * 2, angleLength * 2, 0.0, static_cast<int>(mAngle * 2880 / M_PI));
    painter.drawLine(cosScaled - (cosSign * angleLength), halfHeight, cosScaled - (cosSign * angleLength), halfHeight - (sinSign * angleLength));
    painter.drawLine(cosScaled - (cosSign * angleLength), halfHeight - (sinSign * angleLength), cosScaled, halfHeight - (sinSign * angleLength));
    painter.drawLine(halfWidth, sinScaled + (sinSign * angleLength), halfWidth + (cosSign * angleLength), sinScaled + (sinSign * angleLength));
    painter.drawLine(halfWidth + (cosSign * angleLength), sinScaled + (sinSign * angleLength), halfWidth + (cosSign * angleLength), sinScaled);
    painter.drawLine(cosScaled - cosAngScaled, sinScaled + sinAngScaled,
        cosScaled - cosAngScaled - sinAngScaled, sinScaled + sinAngScaled - cosAngScaled);
    painter.drawLine(cosScaled - cosAngScaled - sinAngScaled, sinScaled + sinAngScaled - cosAngScaled,
        cosScaled - sinAngScaled, sinScaled - cosAngScaled);

    /* Text (sin, cos, sec) */
    painter.setFont(QFont("sans-serif", 10, QFont::Normal, false));
    painter.setPen(QColor("red"));
    painter.drawText(halfWidth + cosVal + (signbit(cosVal) ? -32 : 4), halfHeight - (sinVal / 2) - 7, 30, 14,
        static_cast<int>(Qt::AlignCenter), "sin");
    painter.setPen(QColor("blue"));
    painter.drawText(halfWidth + (cosVal / 2) - 15, sinScaled - (signbit(sinVal) ? -4: 18), 30, 14, static_cast<int>(Qt::AlignCenter), "cos");
    painter.setPen(QColor("cyan"));
    painter.drawText(halfWidth + clamp(secVal, -375, 375) / 2 - 15, halfHeight + (signbit(sinVal) ? -18 : 4),
        30, 14, static_cast<int>(Qt::AlignCenter), "sec");

    /* Text (csc) */
    painter.setPen(QColor("magenta"));
    if(sinVal == 0.0)
    {
        painter.drawText(halfWidth - 32, halfHeight - 190, 30, 14, static_cast<int>(Qt::AlignCenter), "csc");
    }
    else
    {
        painter.drawText(halfWidth + (signbit(cosVal) ? 4 : -32), halfHeight - clamp(cscVal, -375, 375) / 2,
            30, 14, static_cast<int>(Qt::AlignCenter), "csc");
    }

    /* Text (tan) */
    painter.setPen(QColor(180, 140, 100));
    if(cosVal == 0.0)
    {
        painter.drawText(halfWidth - 200, halfHeight - (signbit(sinVal) ? -205 : 218), 30, 14,
            static_cast<int>(Qt::AlignCenter), "tan");
    }
    else if(secVal < -375 || secVal > 375)
    {
        painter.drawText(halfWidth + (signbit(cosVal) ? -210: 190), halfHeight - (sinSign * (abs(cscVal) -
            static_cast<int>(fabs(1.0 / tan(mAngle)) * 188))) - (std::signbit(sinVal) ? -4 : 22), 30, 14,
            static_cast<int>(Qt::AlignCenter), "tan");
    }
    else
    {
        painter.drawText(halfWidth + (clamp(static_cast<int>(secVal - cosVal), -375, 375) / 2) + cosVal +
            (signbit(cosVal) ? -30 : 10), halfHeight - (clamp(sinVal, -375, 375) / 2) - (signbit(sinVal) ? -4 : 10),
            30, 14, static_cast<int>(Qt::AlignCenter), "tan");
    }

    /* Text (cot) */
    painter.setPen(QColor("green"));
    if(sinVal == 0.0)
    {
        painter.drawText(halfWidth + (signbit(cosVal) ? -230 : 200), halfHeight - 190, 30, 14,
            static_cast<int>(Qt::AlignCenter), "cot");
    }
    else if(cscVal < -375 || cscVal > 375)
    {
        painter.drawText(halfWidth + (cosSign * (abs(secVal) - static_cast<int>(fabs(tan(mAngle)) * 188))) +
            (signbit(cosVal) ? -28 : 0), halfHeight - (signbit(sinVal) ? -190 : 210), 30, 14,
            static_cast<int>(Qt::AlignCenter), "cot");
    }
    else
    {
        painter.drawText(halfWidth + (clamp(cosVal, -375, 375) / 2) + (signbit(cosVal) ? -20 : -10), halfHeight -
            (clamp(static_cast<int>(cscVal - sinVal), -375, 375) / 2) - sinVal - (signbit(sinVal) ? -10 : 25),
            30, 14, static_cast<int>(Qt::AlignCenter), "cot");
    }

    /* Background */
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() -1 ));
}
