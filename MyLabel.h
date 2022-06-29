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
	double mScaleValue;			// ͼƬ���ű���
	QPointF mDrawPoint;			// ��ͼ���
	QPointF mMousePoint;			// ��굱ǰλ�õ�
	QRect mRectPixmap;			// ����ͼƬ�ľ��η�Χ
	QPixmap mScaledPixmap;		// �������ͼƬPixmap
	QString mImageName;			// ����ͼƬ���ļ���
	bool misMousePress;			// ����Ƿ���

	const double ZOOM_VALUE = 1.1;
	const double SCALE_MAX_VALUE = 5.0;//���Ŵ�ԭ����10��
	const double SCALE_MIN_VALUE = 0.5;//��С��С��ԭ����0.5��

};
