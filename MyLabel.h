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
	bool isCornerBtnsVisible();		// �����ж��Ƿ��ڲü�ģʽ
	void ChangeCutViewfinderSize(int x, int y);	// ͨ�������ĸ�����PointButtoms���ı�ü�ȡ����ߴ���λ��
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
	bool misMousePress;			// ����Ƿ���
	double mScaleValue;			// ͼƬ���ű���
	QPointF mDrawPoint;			// ��ͼ���
	QPointF mMousePoint;		// ��굱ǰλ�õ�
	QRect mRectPixmap;			// ����ͼƬ�ľ��η�Χ
	QRect mRectCutViewfinder;	// �ü���ľ��η�Χ
	QPen *mPen;					// ���ƾ��ο�ı�
	QPixmap *mScaledPixmap;		// �������ͼƬPixmap
	PointButton *mTopLeftBtn;
	PointButton *mTopRightBtn;
	PointButton *mBottomLeftBtn;
	PointButton *mBottomRightBtn;// �ü����ĸ����ǰ�ť

	const double ZOOM_VALUE = 1.1;		// ����ϵ��
	const double SCALE_MAX_VALUE = 5.0;//���Ŵ�ԭ����10��
	const double SCALE_MIN_VALUE = 0.5;//��С��С��ԭ����0.5��

};
