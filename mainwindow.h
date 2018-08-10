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

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QGridLayout*    mainLayout;
    QWidget*        centralWidget;
    RenderArea*     renderArea;

};

#endif // MAINWINDOW_H
