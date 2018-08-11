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
    mRenderArea = new RenderArea(this);
    mRenderArea->setAngle(M_PI / 4);

    mTableLayout = new QGridLayout;
    mTableLayout->setHorizontalSpacing(40);
    mTableLayout->setVerticalSpacing(40);
    mTableLayout->setContentsMargins(0, 200, 0, 200);

    for(int i = 0; i < mLabelCount; ++i)
    {
        mLabels[i] = new QLabel;
        mTableLayout->addWidget(mLabels[i], i, 0, 1, 1);
    }

    mLabels[0]->setText("Angle Type:");
    mLabels[1]->setText("Angle:");
    mLabels[2]->setText("Sine:");
    mLabels[3]->setText("Cosine:");
    mLabels[4]->setText("Tangent:");
    mLabels[5]->setText("Cosecant:");
    mLabels[6]->setText("Secant:");
    mLabels[7]->setText("Cotangent:");

    for(int i = 0; i < mValueCount; ++i)
    {
        mValues[i] = new QLabel;
        mTableLayout->addWidget(mValues[i], i + 2, 1, 1, 1);
    }

    mAngleTypeComboBox = new QComboBox;
    mAngleTypeComboBox->addItem("Degrees");
    mAngleTypeComboBox->addItem("Radians");
    mAngleTypeComboBox->addItem("Radians (multiples of pi)");
    mAngleTypeComboBox->addItem("Gradians");
    mTableLayout->addWidget(mAngleTypeComboBox, 0, 1, 1, 1);
    mAngleType = DEGREES;

    mInputAngleLineEdit = new QLineEdit;
    mInputAngleLineEdit->setFixedWidth(75);
    mInputAngleLineEdit->setValidator(new QDoubleValidator(mInputAngleLineEdit));
    mInputAngleLineEdit->setText("45.0");
    mTableLayout->addWidget(mInputAngleLineEdit, 1, 1, 1, 1);

    double sinValue = sin(M_PI / 4);
    double cosValue = cos(M_PI / 4);
    double tanValue = tan(M_PI / 4);

    mValues[0]->setText(QString::number(sinValue, 'f', 6));
    mValues[1]->setText(QString::number(cosValue, 'f', 6));
    mValues[2]->setText(QString::number(tanValue, 'f', 6));
    mValues[3]->setText(QString::number(1.0 / sinValue, 'f', 6));
    mValues[4]->setText(QString::number(1.0 / cosValue, 'f', 6));
    mValues[5]->setText(QString::number(1.0 / tanValue, 'f', 6));

    mMainLayout = new QGridLayout;
    mMainLayout->setHorizontalSpacing(40);
    mMainLayout->addWidget(mRenderArea, 0, 0, 1, 1);
    mMainLayout->addLayout(mTableLayout, 0, 1, 1, 1);

    mCentralWidget = new QWidget;
    mCentralWidget->setLayout(mMainLayout);

    connect(mInputAngleLineEdit, SIGNAL(textEdited(const QString&)), this, SLOT(inputAngleChanged()));
    connect(mAngleTypeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(angleTypeChanged()));

    setCentralWidget(mCentralWidget);
    setWindowTitle("Trigonometry Visual v" + mVersionIdentifier);
    layout()->setSizeConstraint(QLayout::SetFixedSize);
}

MainWindow::~MainWindow()
{
    delete mCentralWidget;
}

void MainWindow::centerWindow(QApplication* app)
{
    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(), app->desktop()->availableGeometry(mCentralWidget)));
}

void MainWindow::inputAngleChanged()
{
    bool validInput;
    double value = mInputAngleLineEdit->text().toDouble(&validInput);

    if(!validInput)
        return;

    value = fmod(value, 360.0);
    double sinValue = sin(toRadians(value, mAngleType));
    double cosValue = cos(toRadians(value, mAngleType));
    double tanValue = tan(toRadians(value, mAngleType));
    mRenderArea->setAngle(toRadians(value, mAngleType));

    mValues[0]->setText(QString::number(sinValue, 'f', 6));
    mValues[1]->setText(QString::number(cosValue, 'f', 6));
    mValues[2]->setText(QString::number(tanValue, 'f', 6));
    mValues[3]->setText(QString::number(1.0 / sinValue, 'f', 6));
    mValues[4]->setText(QString::number(1.0 / cosValue, 'f', 6));
    mValues[5]->setText(QString::number(1.0 / tanValue, 'f', 6));

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

void MainWindow::angleTypeChanged()
{
    int requestedType = mAngleTypeComboBox->currentIndex();
    double angle = mInputAngleLineEdit->text().toDouble();

    if(requestedType == 0)
    {
        if(mAngleType == RADIANS) mInputAngleLineEdit->setText(QString::number(angle * 180 / M_PI, 'f', 6));
        else if(mAngleType == RADIANS2) mInputAngleLineEdit->setText(QString::number(angle * 180, 'f', 6));
        else /* mAngleType == GRADIANS */ mInputAngleLineEdit->setText(QString::number(angle * 9 / 10, 'f', 6));
    }
    else if(requestedType == 1)
    {
        if(mAngleType == DEGREES) mInputAngleLineEdit->setText(QString::number(angle * M_PI / 180, 'f', 6));
        else if(mAngleType == RADIANS2) mInputAngleLineEdit->setText(QString::number(angle * M_PI, 'f', 6));
        else /* mAngleType == GRADIANS */ mInputAngleLineEdit->setText(QString::number(angle * M_PI / 200, 'f', 6));
    }
    else if(requestedType == 2)
    {
        if(mAngleType == DEGREES) mInputAngleLineEdit->setText(QString::number(angle / 180, 'f', 6));
        else if(mAngleType == RADIANS) mInputAngleLineEdit->setText(QString::number(angle / M_PI, 'f', 6));
        else /* mAngleType == GRADIANS */ mInputAngleLineEdit->setText(QString::number(angle / 200, 'f', 6));
    }
    else /* requestedType == 3 */
    {
        if(mAngleType == DEGREES) mInputAngleLineEdit->setText(QString::number(angle * 10 / 9, 'f', 6));
        else if(mAngleType == RADIANS) mInputAngleLineEdit->setText(QString::number(angle * 200 / M_PI, 'f', 6));
        else /* mAngleType == RADIANS2 */ mInputAngleLineEdit->setText(QString::number(angle * 200, 'f', 6));
    }

    mAngleType = static_cast<AngleType>(requestedType);
}

double MainWindow::toRadians(double value, AngleType currentAngleType)
{
    if(currentAngleType == DEGREES)         return value * M_PI / 180.0;
    else if(currentAngleType == RADIANS)    return value;
    else if(currentAngleType == RADIANS2)   return value * M_PI;
    else /* currentAngleType == GRADIANS */ return value * M_PI / 200.0;
}
