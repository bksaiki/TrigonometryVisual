/*
	Trigonometry Visual
	Brett Saiki <bksaiki@gmail.com>
	August 2018

	Graphically displays all six trignometric functions (sin, cos, tan, csc, sec, cot)
	on a unit circle.
*/
/**
	File: mainwindow.h
	
	Main user interface window
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "renderarea.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum AngleType
    {
        DEGREES = 0,
        RADIANS,
        RADIANS2,
        GRADIANS
    };

    const QString mVersionIdentifier = "1.0.1";

public:
    /* Default constructor. Creates all widgets */
    explicit MainWindow(QWidget *parent = nullptr);

    /* Destructor. Destroys all widgets */
    ~MainWindow();

    /* Centers this widget */
    void centerWindow(QApplication* app);

private slots:
    /* Updates the render area */
    void inputAngleChanged();

    /* Changes degree type */
    void angleTypeChanged();

private:
    /* Helper function */
    double toRadians(double value, MainWindow::AngleType currentAngleType);

private:
    QComboBox*      mAngleTypeComboBox;
    QGridLayout*    mMainLayout;
    QGridLayout*    mAngleTableLayout;
    QGridLayout*    mEquivalentTableLayout;
    QGridLayout*    mValueTableLayout;
    QGroupBox*      mAngleGroup;
    QGroupBox*      mEquivalentGroup;
    QGroupBox*      mValueGroup;
    QLineEdit*      mInputAngleLineEdit;
    QLabel*         mLabels[12];
    QLabel*         mValues[10];
    QVBoxLayout*    mVerticalLayout;
    QWidget*        mCentralWidget;

    AngleType       mAngleType;
    RenderArea*     mRenderArea;
};

#endif // MAINWINDOW_H
