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

#include <math.h>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent)
{
    mRenderArea = new RenderArea(this);
    mRenderArea->setAngle(M_PI / 4);

    mAngleTableLayout = new QGridLayout;
    mAngleTableLayout->setHorizontalSpacing(40);
    mAngleTableLayout->setVerticalSpacing(40);

    mValueTableLayout = new QGridLayout;
    mValueTableLayout->setHorizontalSpacing(40);
    mValueTableLayout->setVerticalSpacing(40);

    mEquivalentTableLayout = new QGridLayout;
    mEquivalentTableLayout->setHorizontalSpacing(40);
    mEquivalentTableLayout->setVerticalSpacing(40);

    for(int i = 0; i < 2; ++i)
    {
        mLabels[i] = new QLabel;
        mAngleTableLayout->addWidget(mLabels[i], i, 0, 1, 1);
    }

    for(int i = 2; i < 6; ++i)
    {
        mLabels[i] = new QLabel;
        mEquivalentTableLayout->addWidget(mLabels[i], i - 2, 0, 1, 1);
    }

    for(int i = 6; i < 12; ++i)
    {
        mLabels[i] = new QLabel;
        mValueTableLayout->addWidget(mLabels[i], i - 2, 0, 1, 1);
    }

    mLabels[0]->setText("Angle Type:");
    mLabels[1]->setText("Angle:");
    mLabels[2]->setText("Degrees:");
    mLabels[3]->setText("Radians:");
    mLabels[4]->setText("Radians (terms of pi):");
    mLabels[5]->setText("Gradians:");
    mLabels[6]->setText("Sine:");
    mLabels[7]->setText("Cosine:");
    mLabels[8]->setText("Tangent:");
    mLabels[9]->setText("Cosecant:");
    mLabels[10]->setText("Secant:");
    mLabels[11]->setText("Cotangent:");

    for(int i = 0; i < 4; ++i)
    {
        mValues[i] = new QLabel;
        mEquivalentTableLayout->addWidget(mValues[i], i, 1, 1, 1);
    }

    for(int i = 4; i < 10; ++i)
    {
        mValues[i] = new QLabel;
        mValueTableLayout->addWidget(mValues[i], i, 1, 1, 1);
    }

    mAngleTypeComboBox = new QComboBox;
    mAngleTypeComboBox->addItem("Degrees");
    mAngleTypeComboBox->addItem("Radians");
    mAngleTypeComboBox->addItem("Radians (multiples of pi)");
    mAngleTypeComboBox->addItem("Gradians");
    mAngleTableLayout->addWidget(mAngleTypeComboBox, 0, 1, 1, 1);
    mAngleType = DEGREES;

    mInputAngleLineEdit = new QLineEdit;
    mInputAngleLineEdit->setFixedWidth(75);
    mInputAngleLineEdit->setValidator(new QDoubleValidator(mInputAngleLineEdit));
    mInputAngleLineEdit->setText("45.0");
    mAngleTableLayout->addWidget(mInputAngleLineEdit, 1, 1, 1, 1);

    double angle = M_PI / 4;
    double sinValue = sin(angle);
    double cosValue = cos(angle);
    double tanValue = tan(angle);

    mValues[0]->setText(QString::number(angle * 180.0 / M_PI, 'f', 6));
    mValues[1]->setText(QString::number(angle, 'f', 6));
    mValues[2]->setText(QString::number(angle / M_PI, 'f', 6));
    mValues[3]->setText(QString::number(angle * 200.0 / M_PI, 'f', 6));
    mValues[4]->setText(QString::number(sinValue, 'f', 6));
    mValues[5]->setText(QString::number(cosValue, 'f', 6));
    mValues[6]->setText(QString::number(tanValue, 'f', 6));
    mValues[7]->setText(QString::number(1.0 / sinValue, 'f', 6));
    mValues[8]->setText(QString::number(1.0 / cosValue, 'f', 6));
    mValues[9]->setText(QString::number(1.0 / tanValue, 'f', 6));

    mAngleGroup = new QGroupBox;
    mAngleGroup->setLayout(mAngleTableLayout);

    mEquivalentGroup = new QGroupBox;
    mEquivalentGroup->setLayout(mEquivalentTableLayout);

    mValueGroup = new QGroupBox;
    mValueGroup->setLayout(mValueTableLayout);

    mVerticalLayout = new QVBoxLayout;
    mVerticalLayout->setSpacing(20);
    mVerticalLayout->addWidget(mAngleGroup, 1);
    mVerticalLayout->addWidget(mEquivalentGroup, 1);
    mVerticalLayout->addWidget(mValueGroup, 1);

    mMainLayout = new QGridLayout;
    mMainLayout->setContentsMargins(20, 20, 20, 20);
    mMainLayout->addWidget(mRenderArea, 0, 0, 1, 1);
    mMainLayout->addLayout(mVerticalLayout, 0, 1, 1, 1);

    mCentralWidget = new QWidget;
    mCentralWidget->setLayout(mMainLayout);

    connect(mInputAngleLineEdit, SIGNAL(textEdited(const QString&)), this, SLOT(inputAngleChanged()));
    connect(mAngleTypeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(angleTypeChanged()));

    setCentralWidget(mCentralWidget);
    setWindowTitle("Trigonometry Visual " + mVersionIdentifier);
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

    double radians = toRadians(value, mAngleType);
    mValues[0]->setText(QString::number(radians * 180.0 / M_PI, 'f', 6));
    mValues[1]->setText(QString::number(radians, 'f', 6));
    mValues[2]->setText(QString::number(radians / M_PI, 'f', 6));
    mValues[3]->setText(QString::number(radians * 200.0 / M_PI, 'f', 6));

    double adjustedAngle = toRadians(fmod(value, 360.0), mAngleType);
    double sinValue = sin(adjustedAngle);
    double cosValue = cos(adjustedAngle);
    double tanValue = tan(adjustedAngle);
    mRenderArea->setAngle(adjustedAngle);

    mValues[4]->setText(QString::number(sinValue, 'f', 6));
    mValues[5]->setText(QString::number(cosValue, 'f', 6));
    mValues[6]->setText(QString::number(tanValue, 'f', 6));
    mValues[7]->setText(QString::number(1.0 / sinValue, 'f', 6));
    mValues[8]->setText(QString::number(1.0 / cosValue, 'f', 6));
    mValues[9]->setText(QString::number(1.0 / tanValue, 'f', 6));

    if(value == 0.0 || value == 180.0)
    {
        mValues[7]->setText("undef");
        mValues[9]->setText("undef");
    }

    if(value == 90.0 || value == 270.0)
    {
        mValues[6]->setText("undef");
        mValues[8]->setText("undef");
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
