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
	QPixmap scaledPixmap = this->pixmap()->scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation); // 按比例缩放
	// 调整Image初次渲染位置
	mScaleValue = double(scaledPixmap.width()) / this->pixmap()->width();
	//mScaleValue = 1.0;
	double width = scaledPixmap.width();
	double height = scaledPixmap.height();
	mDrawPoint.setX((this->width() - width) / 2);
	mDrawPoint.setY((this->height() - height) / 2);
	
	// 调整CutViewfinder初次渲染位置
	int pointBtnRadius = mTopLeftBtn->width() / 2;
	SetCornerBtns((this->width() - width / 2) / 2 - pointBtnRadius, (this->height() - height / 2) / 2 - pointBtnRadius, 
		(this->width() + width / 2) / 2 - pointBtnRadius, (this->height() + height / 2) / 2 - pointBtnRadius);
	mRectCutViewfinder.setTopLeft(QPoint((this->width() - width / 2) / 2, (this->height() - height / 2) / 2));
	mRectCutViewfinder.setSize(QSize(width / 2, height / 2));
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

inline void MyLabel::DrawImage()
{
	if (this->pixmap() == nullptr) return;
	QPainter painter(this);
	double width = this->pixmap()->width() * mScaleValue;
	double height = this->pixmap()->height() * mScaleValue;
	mRectPixmap = QRect(mDrawPoint.x(), mDrawPoint.y(), width, height);  // 图片区域
	painter.drawPixmap(mRectPixmap, *this->pixmap());
}

inline void MyLabel::DrawCutViewfinder()
{
	QPainter painter(this);
	painter.setPen(*mPen);
	//int width = mTopRightBtn->x() - mTopLeftBtn->x();
	//int height = mBottomLeftBtn->y() - mTopLeftBtn->y();
	int pointBtnRadius = mTopLeftBtn->width() / 2;
	int x1 = std::max(mTopLeftBtn->x() + pointBtnRadius, mRectPixmap.x()), y1 = std::max(mTopLeftBtn->y() + pointBtnRadius, mRectPixmap.y());
	int x2 = std::min(mBottomRightBtn->x() + pointBtnRadius, mRectPixmap.right()), y2 = std::min(mBottomRightBtn->y() + pointBtnRadius, mRectPixmap.bottom());
	mRectCutViewfinder.setTopLeft(QPoint(x1, y1));
	mRectCutViewfinder.setBottomRight(QPoint(x2, y2));
	SetCornerBtns(x1 - pointBtnRadius, y1 - pointBtnRadius, x2 - pointBtnRadius, y2 - pointBtnRadius);
	//mTopLeftBtn->move(x1, y1), mTopRightBtn->move(x2, y1), mBottomLeftBtn->move(x1, y2), mBottomRightBtn->move(x2, y2);
	painter.drawRect(mRectCutViewfinder);
}

void MyLabel::ChangeCutViewfinderSize(int x, int y)
{
	// 越界判断
	int pointBtnRadius = mTopLeftBtn->width() / 2;
	if (x < mRectPixmap.left() - pointBtnRadius) x = mRectPixmap.left() - pointBtnRadius;
	else if (x > mRectPixmap.right() - pointBtnRadius) x = mRectPixmap.right() - pointBtnRadius;
	if (y < mRectPixmap.top() - pointBtnRadius) y = mRectPixmap.top() - pointBtnRadius;
	else if (y > mRectPixmap.bottom() - pointBtnRadius) y = mRectPixmap.bottom() - pointBtnRadius;
	

	// 维持矩形 && CutViewfinder最小尺寸约束
	if (mTopLeftBtn->isPressed()) {
		mTopLeftBtn->move(x, y);
		mTopRightBtn->move(mBottomRightBtn->x(), y);
		mBottomLeftBtn->move(x, mBottomRightBtn->y());
	}
	else if (mTopRightBtn->isPressed()) {
		mTopRightBtn->move(x, y);
		mTopLeftBtn->move(mBottomLeftBtn->x(), y);
		mBottomRightBtn->move(x, mBottomLeftBtn->y());
	}
	else if (mBottomLeftBtn->isPressed()) {
		mBottomLeftBtn->move(x, y);
		mTopLeftBtn->move(x, mTopLeftBtn->y());
		mBottomRightBtn->move(mBottomRightBtn->x(), y);
	}
	else if (mBottomRightBtn->isPressed()) {
		mBottomRightBtn->move(x, y);
		mTopRightBtn->move(x, mTopRightBtn->y());
		mBottomLeftBtn->move(mBottomLeftBtn->x(), y);
	}
	update();
}

QPixmap MyLabel::GetCutImage()
{
	QPixmap cutPixmap;
	if (!this->pixmap()->isNull() && mRectCutViewfinder.isValid())
	{
		// 注意 QPixmap::copy() 传入参数为pixmap的坐标系，所以需进行坐标变换
		cutPixmap = this->pixmap()->copy(mRectCutViewfinder);
	}
	return cutPixmap;
}

void MyLabel::SetCornerBtns(int x1, int y1, int x2, int y2)
{
	mTopLeftBtn->move(x1, y1);
	mBottomLeftBtn->move(x1, y2);
	mTopRightBtn->move(x2, y1);
	mBottomRightBtn->move(x2, y2);
}