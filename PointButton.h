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
	 inline bool isPressed() { return misPressed; };	    // �����ж��û��Ƿ���������ҷ��ť��

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

private:
	void setQss();                                  // ������ҷ��ť��ʽ

private:
	bool misPressed;
	float mStartX;                                   // �����ƶ���ҷ��ť
	float mStartY;
};