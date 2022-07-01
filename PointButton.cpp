#include "PointButton.h"
#include "MyLabel.h"

PointButton::PointButton(QWidget *parent)
	: QPushButton(parent)
	, misPressed(false)
	, mStartX(0.0)
	, mStartY(0.0)
{
	resize(12, 12);
	setQss();
}

PointButton::~PointButton() {

}

void PointButton::setQss() {
	QString qss = "QPushButton {\n"
		"border-radius: 6px;\n"
		"border: 2px solid black;"
		"background-color: rgb(255, 255, 255);\n"
		"}\n"
		"QPushButton:hover {\n"
		"border-width: 2px;\n"
		"}";

	setStyleSheet(qss);
}

void PointButton::mousePressEvent(QMouseEvent *event) {
	QPushButton::mousePressEvent(event);
	mStartX = event->x();
	mStartY = event->y();
	misPressed = true;
}

void PointButton::mouseMoveEvent(QMouseEvent *event) {
	QPushButton::mouseMoveEvent(event);
	float dx = event->x() - mStartX;
	float dy = event->y() - mStartY;
	move(x() + dx, y() + dy);
	MyLabel *parent = (MyLabel*) this->parent();
	parent->ChangeCutViewfinderSize(x() + dx, y() + dy);
}

void PointButton::mouseReleaseEvent(QMouseEvent *event) {
	QPushButton::mouseReleaseEvent(event);
	misPressed = false;
}