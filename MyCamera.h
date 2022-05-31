#pragma once

#include <QtWidgets/QWidget>
#include "ui_MyCamera.h"

class MyCamera : public QWidget
{
	Q_OBJECT

public:
	MyCamera(QWidget *parent = Q_NULLPTR);

private:
	Ui::MyCameraClass ui;
};
