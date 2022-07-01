#include "MyLabel.h"

MyLabel::MyLabel(QWidget * parent)
	: QLabel(parent)
	, mScaleValue(1.0)
	, mMousePoint(0, 0)
	, mDrawPoint(0, 0)
	, mRectPixmap(0, 0, 0, 0)
	, misMousePress(0)
	, mImageName("")
	, mScaledPixmap(new QPixmap())
{
}

MyLabel::~MyLabel()
{

}

void MyLabel::TurnImage(QMatrix & matrix, Qt::TransformationMode mode)
{
	this->setPixmap(this->pixmap()->transformed(matrix, mode));
	Reset();
}

void MyLabel::Reset()
{
	if (this->pixmap() == nullptr) return;
	*mScaledPixmap = this->pixmap()->scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation); // 按比例缩放
	qDebug() << mScaledPixmap->size();
	mScaleValue = 1.0;
	double width = mScaledPixmap->width();
	double height = mScaledPixmap->height();
	mDrawPoint.setX((this->width() - width) / 2);
	mDrawPoint.setY((this->height() - height) / 2);
}

void MyLabel::paintEvent(QPaintEvent *)
{
	if (this->pixmap() == nullptr) return;
	QPainter painter(this);
	double width = mScaledPixmap->width() * mScaleValue;
	double height = mScaledPixmap->height() * mScaleValue;
	//mScaledPixmap = this->pixmap()->scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation); // 按比例缩放
	//mDrawPoint.setX((this->width() - width) / 2);
	//mDrawPoint.setY((this->height() - height) / 2);
	mRectPixmap = QRect(mDrawPoint.x(), mDrawPoint.y(), width, height);  // 图片区域
	//qDebug() << this->pixmap()->size();
	painter.drawPixmap(mRectPixmap, *mScaledPixmap);
}

void MyLabel::mouseMoveEvent(QMouseEvent * event)
{
	if (misMousePress) {
		int dx = event->pos().x() - mMousePoint.x();
		int dy = event->pos().y() - mMousePoint.y();
		mMousePoint = event->pos();
		mDrawPoint.setX(mDrawPoint.x() + dx);
		mDrawPoint.setY(mDrawPoint.y() + dy);

		update();
	}
}

void MyLabel::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton && mRectPixmap.contains(event->pos()))
	{
		setCursor(Qt::ClosedHandCursor);
		misMousePress = true;
		mMousePoint = event->pos();
	}
}

void MyLabel::mouseReleaseEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton) misMousePress = false;
	setCursor(Qt::ArrowCursor);
	if (event->button() == Qt::RightButton)
	{
		Reset();
		update();
	}
}

void MyLabel::wheelEvent(QWheelEvent * event)
{
	double oldScaleValue = mScaleValue;
	if (event->delta() > 0) mScaleValue *= ZOOM_VALUE;
	if (event->delta() < 0) mScaleValue /= ZOOM_VALUE;

	if (mScaleValue > SCALE_MAX_VALUE) {
		mScaleValue = SCALE_MAX_VALUE;
	}
	if (mScaleValue < SCALE_MIN_VALUE) {
		mScaleValue = SCALE_MIN_VALUE;
	}

	int X = event->pos().x(), Y = event->pos().y();
	int x = mDrawPoint.x(), y = mDrawPoint.y();
	double radio = mScaleValue / oldScaleValue;
	mDrawPoint.setX(x - (X - x) * (radio - 1));
	mDrawPoint.setY(y - (Y - y) * (radio - 1));
	//qDebug() << "x:" << x << " y:" << y;

	update();
}

void MyLabel::resizeEvent(QResizeEvent * event)
{
	Reset();
}

