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

RenderArea::RenderArea(QWidget* parent)
    : QWidget(parent)
{
    setMinimumSize(500, 500);
    setMaximumSize(500, 500);
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

void RenderArea::paintEvent(QPaintEvent* /* event */)
{
    QPainter painter(this);

    painter.drawEllipse({ width() / 2, height() / 2 }, 200, 200);

    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() -1 ));
}
