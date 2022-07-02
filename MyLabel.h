#pragma once
#include <QObject>
#include <QLabel>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPainter>
#include <QDebug>
#include "PointButton.h"

class MyLabel :public QLabel
{
public:
	MyLabel(QWidget *parent = nullptr);
	~MyLabel();
	void TurnImage(QMatrix& matrix, Qt::TransformationMode mode = Qt::SmoothTransformation);
	void Reset();
	void SetCornerBtnsVisible(bool);
	bool isCornerBtnsVisible();		// 用于判断是否处于裁剪模式
	void ChangeCutViewfinderSize(int x, int y);	// 通过调节四个顶点PointButtoms来改变裁剪取景框尺寸与位置
	QPixmap GetCutImage();

protected:
	virtual void paintEvent(QPaintEvent *) override;
	virtual void mouseMoveEvent(QMouseEvent *ev) override;
	virtual void mousePressEvent(QMouseEvent *ev) override;
	virtual void mouseReleaseEvent(QMouseEvent *ev) override;
	virtual void wheelEvent(QWheelEvent *event) override;
	virtual void resizeEvent(QResizeEvent *event) override;

private:
	inline void DrawImage();
	inline void DrawCutViewfinder();
	void SetCornerBtns(int x1, int y1, int x2, int y2);

private:
	bool misMousePress;			// 鼠标是否按下
	double mScaleValue;			// 图片缩放倍数
	QPointF mDrawPoint;			// 绘图起点
	QPointF mMousePoint;		// 鼠标当前位置点
	QRect mRectPixmap;			// 被绘图片的矩形范围
	QRect mRectCutViewfinder;	// 裁剪框的矩形范围
	QPen *mPen;					// 绘制矩形框的笔
	QPixmap *mScaledPixmap;		// 调整后的图片Pixmap
	PointButton *mTopLeftBtn;
	PointButton *mTopRightBtn;
	PointButton *mBottomLeftBtn;
	PointButton *mBottomRightBtn;// 裁剪框四个顶角按钮

	const double ZOOM_VALUE = 1.1;		// 缩放系数
	const double SCALE_MAX_VALUE = 5.0;//最大放大到原来的10倍
	const double SCALE_MIN_VALUE = 0.5;//最小缩小到原来的0.5倍

};
