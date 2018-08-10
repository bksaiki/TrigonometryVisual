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
    mRenderArea = new RenderArea(this);
    mRenderArea->setAngle(M_PI / 4);

    mMainLayout = new QGridLayout;
    mMainLayout->addWidget(mRenderArea, 0, 0, 1, 1);

    mCentralWidget = new QWidget;
    mCentralWidget->setLayout(mMainLayout);

    setCentralWidget(mCentralWidget);
    setWindowTitle("Trigonometry Visual");
    layout()->setSizeConstraint(QLayout::SetFixedSize);
}

MainWindow::~MainWindow()
{
    delete mCentralWidget;
}
