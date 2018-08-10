/*
	Trigonometry Visual
	Brett Saiki <bksaiki@gmail.com>
	August 2018

	Graphically displays all six trignometric functions (sin, cos, tan, csc, sec, cot)
	on a unit circle.
*/
/**
	File: mainwindow.cpp
	
	Main user interface window
*/

#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent)
{
    renderArea = new RenderArea(this);

    mainLayout = new QGridLayout;
    mainLayout->addWidget(renderArea, 0, 0, 1, 1);

    centralWidget = new QWidget;
    centralWidget->setLayout(mainLayout);

    setCentralWidget(centralWidget);
    setWindowTitle("Trigonometry Visual");
    layout()->setSizeConstraint(QLayout::SetFixedSize);
}

MainWindow::~MainWindow()
{
    delete renderArea;
}
