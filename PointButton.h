#pragma once
#include <QPushButton>
#include <QWidget>
#include <QString>
#include <QMouseEvent>


class PointButton : public QPushButton
{
public:
	PointButton(QWidget *parent = nullptr);
	~PointButton();

public:
	 inline bool isPressed() { return misPressed; };	    // 用来判断用户是否正按在拖曳按钮上

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

private:
	void setQss();                                  // 设置拖曳按钮样式

private:
	bool misPressed;
	float mStartX;                                   // 用来移动拖曳按钮
	float mStartY;
};