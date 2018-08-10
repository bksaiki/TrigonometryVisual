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
#include <iostream>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent)
{
    mMainLayout = new QGridLayout;
    mMainLayout->setSpacing(15);

    mRenderArea = new RenderArea(this);
    mRenderArea->setAngle(M_PI / 4);
    mMainLayout->addWidget(mRenderArea, 0, 0, 13, 1);

    mInputAngle = new QLineEdit;
    mInputAngle->setValidator(new QDoubleValidator(mInputAngle));
    mInputAngle->setText("45.0");
    mMainLayout->addWidget(mInputAngle, 3, 2, 1, 1);

    for(int i = 0; i < mLabelCount; ++i)
    {
        mLabels[i] = new QLabel;
        mMainLayout->addWidget(mLabels[i], i + 3, 1, 1, 1);
    }

    mLabels[0]->setText("Angle:");
    mLabels[1]->setText("Sine:");
    mLabels[2]->setText("Cosine:");
    mLabels[3]->setText("Tangent:");
    mLabels[4]->setText("Cosecant:");
    mLabels[5]->setText("Secant:");
    mLabels[6]->setText("Cotangent:");

    for(int i = 0; i < mValueCount; ++i)
    {
        mValues[i] = new QLabel;
        mMainLayout->addWidget(mValues[i], i + 4, 2, 1, 1);
    }

    double sinValue = sin(M_PI / 4);
    double cosValue = cos(M_PI / 4);
    double tanValue = tan(M_PI / 4);

    mValues[0]->setText(QString::number(sinValue, 'f', 3));
    mValues[1]->setText(QString::number(cosValue, 'f', 3));
    mValues[2]->setText(QString::number(tanValue, 'f', 3));
    mValues[3]->setText(QString::number(1.0 / sinValue, 'f', 3));
    mValues[4]->setText(QString::number(1.0 / cosValue, 'f', 3));
    mValues[5]->setText(QString::number(1.0 / tanValue, 'f', 3));

    mCentralWidget = new QWidget;
    mCentralWidget->setLayout(mMainLayout);

    connect(mInputAngle, SIGNAL(textEdited(const QString&)), this, SLOT(inputAngleChanged()));

    setCentralWidget(mCentralWidget);
    setWindowTitle("Trigonometry Visual");
    layout()->setSizeConstraint(QLayout::SetFixedSize);
}

MainWindow::~MainWindow()
{
    delete mCentralWidget;
}

void MainWindow::inputAngleChanged()
{
    bool validInput;
    double value = mInputAngle->text().toDouble(&validInput);

    if(!validInput)
        return;

    value = fmod(value, 360.0);
    mRenderArea->setAngle(value * M_PI / 180.0);

    double sinValue = sin(value * M_PI / 180.0);
    double cosValue = cos(value * M_PI / 180.0);
    double tanValue = tan(value * M_PI / 180.0);

    mValues[0]->setText(QString::number(sinValue, 'f', 3));
    mValues[1]->setText(QString::number(cosValue, 'f', 3));
    mValues[2]->setText(QString::number(tanValue, 'f', 3));
    mValues[3]->setText(QString::number(1.0 / sinValue, 'f', 3));
    mValues[4]->setText(QString::number(1.0 / cosValue, 'f', 3));
    mValues[5]->setText(QString::number(1.0 / tanValue, 'f', 3));

    if(value == 0.0 || value == 180.0)
    {
        mValues[3]->setText("undef");
        mValues[5]->setText("undef");
    }

    if(value == 90.0 || value == 270.0)
    {
        mValues[2]->setText("undef");
        mValues[4]->setText("undef");
    }
}
