#include "MyLabel.h"

MyLabel::MyLabel(QWidget * parent)
	: QLabel(parent)
	, mScaleValue(1.0)
	, mMousePoint(0, 0)
	, mDrawPoint(0, 0)
	, mRectPixmap(0, 0, 0, 0)
	, misMousePress(0)
	, mTopLeftBtn(new PointButton(this))
	, mTopRightBtn(new PointButton(this))
	, mBottomLeftBtn(new PointButton(this))
	, mBottomRightBtn(new PointButton(this))
	, mScaledPixmap(new QPixmap())
	, mPen(new QPen(Qt::red, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin))
{
	SetCornerBtnsVisible(false);
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
	//qDebug() << mScaledPixmap->size();
	mScaleValue = 1.0;
	double width = mScaledPixmap->width();
	double height = mScaledPixmap->height();
	mDrawPoint.setX((this->width() - width) / 2);
	mDrawPoint.setY((this->height() - height) / 2);
	SetCornerBtns((this->width() - width / 2) / 2, (this->height() - height / 2) / 2, (this->width() + width / 2) / 2, (this->height() + height / 2) / 2);
}

void MyLabel::SetCornerBtnsVisible(bool b)
{
	mTopLeftBtn->setVisible(b);
	mTopRightBtn->setVisible(b);
	mBottomLeftBtn->setVisible(b);
	mBottomRightBtn->setVisible(b);
}

bool MyLabel::isCornerBtnsVisible()
{
	if (mTopLeftBtn->isVisible() && mTopRightBtn->isVisible() && mBottomLeftBtn->isVisible() && mBottomRightBtn->isVisible()) return true;
	return false;
}

void MyLabel::paintEvent(QPaintEvent *)
{
	DrawImage();
	if (isCornerBtnsVisible()) DrawCutViewfinder();
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

	update();
}

void MyLabel::resizeEvent(QResizeEvent * event)
{
	Reset();
}

void MyLabel::DrawImage()
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

inline void MyLabel::DrawCutViewfinder()
{
	QPainter painter(this);
	painter.setPen(*mPen);
	int width = mTopRightBtn->x() - mTopLeftBtn->x();
	int height = mBottomLeftBtn->y() - mTopLeftBtn->y();
	int btnRadius = mTopLeftBtn->width() / 2;
	painter.drawRect(mTopLeftBtn->x() + btnRadius, mTopLeftBtn->y() + btnRadius, width, height);
}

void MyLabel::ChangeCutViewfinderSize(int x, int y)
{
	if (mTopLeftBtn->isPressed()) {
		mTopRightBtn->move(mBottomRightBtn->x(), y);
		mBottomLeftBtn->move(x, mBottomRightBtn->y());
	}
	else if (mTopRightBtn->isPressed()) {
		mTopLeftBtn->move(mBottomLeftBtn->x(), y);
		mBottomRightBtn->move(x, mBottomLeftBtn->y());
	}
	else if (mBottomLeftBtn->isPressed()) {
		mTopLeftBtn->move(x, mTopLeftBtn->y());
		mBottomRightBtn->move(mBottomRightBtn->x(), y);
	}
	else if (mBottomRightBtn->isPressed()) {
		mTopRightBtn->move(x, mTopRightBtn->y());
		mBottomLeftBtn->move(mBottomLeftBtn->x(), y);
	}
	update();
}

void MyLabel::SetCornerBtns(int x1, int y1, int x2, int y2)
{
	mTopLeftBtn->move(x1, y1);
	mBottomLeftBtn->move(x1, y2);
	mTopRightBtn->move(x2, y1);
	mBottomRightBtn->move(x2, y2);
}