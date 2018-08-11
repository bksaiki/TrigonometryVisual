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

    const int mLabelCount = 7;
    const int mValueCount = 6;
    const QString mVersionIdentifier = "1.0.0";

public:
    /* Default constructor. Creates all widgets */
    explicit MainWindow(QWidget *parent = nullptr);

    /* Destructor. Destroys all widgets */
    ~MainWindow();

private slots:
    /* Updates the render area */
    void inputAngleChanged();

private:
    QGridLayout*    mMainLayout;
    QLineEdit*      mInputAngle;
    QLabel*         mLabels[7];
    QLabel*         mValues[6];
    QWidget*        mCentralWidget;

    RenderArea*     mRenderArea;
};

#endif // MAINWINDOW_H
