#pragma once
#include <QObject>
#include <QLabel>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPainter>
#include <QDebug>

class MyLabel :public QLabel
{
public:
	MyLabel(QWidget *parent = nullptr);
	~MyLabel();
	void TurnImage(QMatrix& matrix, Qt::TransformationMode mode = Qt::SmoothTransformation);
	void Reset();
	void loadImage(QString& imagename) { mImageName = imagename; };

protected:
	virtual void paintEvent(QPaintEvent *) override;
	virtual void mouseMoveEvent(QMouseEvent *ev) override;
	virtual void mousePressEvent(QMouseEvent *ev) override;
	virtual void mouseReleaseEvent(QMouseEvent *ev) override;
	virtual void wheelEvent(QWheelEvent *event) override;
	virtual void resizeEvent(QResizeEvent *event) override;
	void changeWheelValue(QPoint event, int value);
private:
	double mScaleValue;			// 图片缩放倍数
	QPointF mDrawPoint;			// 绘图起点
	QPointF mMousePoint;			// 鼠标当前位置点
	QRect mRectPixmap;			// 被绘图片的矩形范围
	QPixmap mScaledPixmap;		// 调整后的图片Pixmap
	QString mImageName;			// 被绘图片的文件名
	bool misMousePress;			// 鼠标是否按下

	const double ZOOM_VALUE = 1.1;
	const double SCALE_MAX_VALUE = 5.0;//最大放大到原来的10倍
	const double SCALE_MIN_VALUE = 0.5;//最小缩小到原来的0.5倍

};
