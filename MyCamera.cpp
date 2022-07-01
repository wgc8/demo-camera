#include "MyCamera.h"

MyCamera::MyCamera(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	Init();
}

MyCamera::~MyCamera()
{
	delete mCamera;
	delete mCamImgCap, mCamViewFind, mDisplayLabel;
	delete mImageNamesList;
}

void MyCamera::Init() {

	gDir = QCoreApplication::applicationDirPath() + QString::fromLocal8Bit("/Phtots");
	CreateFileDir();

	ui.widgetOpeartions->setVisible(false);

	this->setWindowTitle(QString::fromLocal8Bit("MyCamera"));

	mDisplayLabel = new MyLabel(this);
	mImageNamesList = new QStringList();
	mDisplayLabel->setAlignment(Qt::AlignCenter);
	mDisplayLabel->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));	//很关键
	mCamerasList = QCameraInfo::availableCameras();
	if (mCamerasList.empty()) {
		QMessageBox MesBox(this);
		QString tmpstr;
		if (curLanguage == Chiness) tmpstr = QString::fromLocal8Bit("无可用摄像头");
		if (curLanguage == English) tmpstr = QString::fromLocal8Bit("No camera available");
		MesBox.setText(tmpstr);
		MesBox.exec();
		return;
	}

	for (int i = 0; i < mCamerasList.size(); i++) {
		ui.cBoxCameras->addItem(mCamerasList[i].deviceName());
	}

	int curCameraIdx = ui.cBoxCameras->currentIndex();
	mCamera = new QCamera(mCamerasList[curCameraIdx]);
	mCamViewFind = new QCameraViewfinder();
	mCamImgCap = new QCameraImageCapture(mCamera);

	mCamImgCap->setCaptureDestination(QCameraImageCapture::CaptureToFile);
	ui.DisplayLayout->addWidget(mCamViewFind);	//加入取景框
	ui.DisplayLayout->addWidget(mDisplayLabel);	//加入照片渲染窗口

	mCamera->setCaptureMode(QCamera::CaptureStillImage);

	mCamera->setViewfinder(mCamViewFind);
	mCamera->start();
	if (curLanguage == Chiness) ui.label->setText(QString::fromLocal8Bit("拍摄中"));
	if (curLanguage == English) ui.label->setText(QString::fromLocal8Bit("Taking photos..."));

	mTimer = new QTimer(this);
	mTimer->setInterval(1000);	//	设置倒计时计时器间隔为1s;

	//链接信号槽
	InitConnections();

}

void MyCamera::InitConnections(){
	connect(ui.btnCapture, &QPushButton::clicked, this, &MyCamera::btnCaptureResponsed);
	connect(mCamImgCap, &QCameraImageCapture::imageCaptured, this, &MyCamera::ImageCaptured);

	connect(ui.btnPrevious, &QPushButton::clicked, this, &MyCamera::btnPreviousResponsed);
	connect(ui.btnNext, &QPushButton::clicked, this, &MyCamera::btnNextResponsed);
	connect(ui.btnCut, &QPushButton::clicked, this, &MyCamera::btnCutResponsed);
	connect(ui.btnDelete, &QPushButton::clicked, this, &MyCamera::btnDeleteResponsed);
	connect(ui.btnPhotos, &QPushButton::clicked, this, &MyCamera::btnPhotosResponsed);
	connect(ui.btnSaveImage, &QPushButton::clicked, this, &MyCamera::btnSaveImageResponsed);
	connect(ui.btnSettings, &QPushButton::clicked, this, &MyCamera::btnSettingsResponsed);
	connect(ui.btnTurnLeft, &QPushButton::clicked, this, &MyCamera::btnTurnLeftResponsed);
	connect(ui.btnTurnRight, &QPushButton::clicked, this, &MyCamera::btnTurnRightResponsed);

	connect(mTimer, &QTimer::timeout, this, &MyCamera::CountTime);
}

void MyCamera::UpdateLanguage()
{
	// 改变标签
	if (curLanguage == Chiness) {

		if (curMode == Album) ui.btnPhotos->setText(QString::fromLocal8Bit("拍照"));
		else ui.btnPhotos->setText(QString::fromLocal8Bit("相冊"));
		ui.btnCapture->setText(QString::fromLocal8Bit("拍摄"));
		ui.btnPrevious->setText(QString::fromLocal8Bit("上一张"));
		ui.btnNext->setText(QString::fromLocal8Bit("下一张"));
		ui.btnCut->setText(QString::fromLocal8Bit("剪裁"));
		ui.btnSaveImage->setText(QString::fromLocal8Bit("保存"));
		ui.btnDelete->setText(QString::fromLocal8Bit("删除"));
		ui.btnSettings->setText(QString::fromLocal8Bit("设置"));
		ui.btnTurnLeft->setText(QString::fromLocal8Bit("左转"));
		ui.btnTurnRight->setText(QString::fromLocal8Bit("右转"));
		ui.label_2->setText(QString::fromLocal8Bit("选择摄像头"));

		if (curMode == Taking_photos) ui.label->setText(QString::fromLocal8Bit("拍摄中"));
		else ui.label->setText(QString::fromLocal8Bit("查看相冊中"));
	}

	if (curLanguage == English) {

		if (curMode == Album) ui.btnPhotos->setText(QString::fromLocal8Bit("Taking Photos"));
		else ui.btnPhotos->setText(QString::fromLocal8Bit("Album"));
		ui.btnPrevious->setText(QString::fromLocal8Bit("Previous"));
		ui.btnNext->setText(QString::fromLocal8Bit("Next"));
		ui.btnCapture->setText(QString::fromLocal8Bit("Capture"));
		ui.btnCut->setText(QString::fromLocal8Bit("Cut"));
		ui.btnSaveImage->setText(QString::fromLocal8Bit("Save"));
		ui.btnDelete->setText(QString::fromLocal8Bit("Delete"));
		ui.btnSettings->setText(QString::fromLocal8Bit("Settings"));
		ui.btnTurnLeft->setText(QString::fromLocal8Bit("Turn Left"));
		ui.btnTurnRight->setText(QString::fromLocal8Bit("Turn Right"));
		ui.label_2->setText(QString::fromLocal8Bit("Select the Camera"));

		if (curMode == Taking_photos) ui.label->setText(QString::fromLocal8Bit("Taking photos..."));
		else ui.label->setText(QString::fromLocal8Bit("Browsing album"));
	}
}

void MyCamera::CreateFileDir()
{
	QDir dir(gDir);
	if (!dir.exists())
	{
		dir.mkdir(gDir);
		qDebug() << "文件夹创建成功";
	}
}

void MyCamera::ImageCaptured(int id, QImage image)
{
	QString savepath = QFileDialog::getSaveFileName(this, "Save Capture", gDir+"/Untitled", "Image png(*.png);;Image jpg(*.jpg);;Image bmp(*.bmp)");
	if (!savepath.isEmpty()) {
		image.save(savepath);
	}

	ui.btnCapture->setEnabled(true);
	ui.btnPhotos->setEnabled(true);
	if (curLanguage == Chiness) ui.label->setText(QString::fromLocal8Bit("拍摄中"));
	if (curLanguage == English) ui.label->setText(QString::fromLocal8Bit("Taking photos..."));
}

void MyCamera::GetCurPathImagesList()
{
	mImageNamesList->clear();
	QDir dir(gDir);//当前程序工作路径 作为目录路径 
	if (!dir.exists())
	{
		return;
	}
	dir.setFilter(QDir::Files | QDir::NoSymLinks);
	QStringList filters;
	filters << "*.bmp" << "*.jpg" << "*.png" << "*.jpeg";
	dir.setNameFilters(filters);
	*mImageNamesList = dir.entryList();
}

void MyCamera::RenderImage()
{
	QString imageName = gDir + "/" + mImageNamesList->at(mIntCurImageIdx);
	//QPixmap pixmap = QPixmap(imageName);
	//QPixmap tmp = pixmap.scaled(mDisplayLabel->size(), Qt::KeepAspectRatio);
	////mDisplayLabel->setScaledContents(true);
	//mDisplayLabel->setPixmap(tmp);
	mDisplayLabel->setPixmap(imageName);
	mDisplayLabel->Reset();
	mDisplayLabel->update();
}

void MyCamera::btnCaptureResponsed()
{
	ui.btnCapture->setDisabled(true);
	ui.btnPhotos->setDisabled(true);
	mIntRestTime = gWaitTime;
	int time = gWaitTime;
	QTimer::singleShot(1000 * gWaitTime, this, [this] {int id = mCamImgCap->capture(); });
	mTimer->start();
}

void MyCamera::btnCutResponsed()
{
	if (mDisplayLabel->isCornerBtnsVisible()) mDisplayLabel->SetCornerBtnsVisible(false);
	else mDisplayLabel->SetCornerBtnsVisible(true);
	mDisplayLabel->update();
}

void MyCamera::btnDeleteResponsed()
{
	QString imageName = gDir + "/" + mImageNamesList->at(mIntCurImageIdx);
	if (!QDir().exists(imageName))
		return;
	QFileInfo fileInfo(imageName);

	if (fileInfo.isFile())
		QFile::remove(imageName);
	GetCurPathImagesList();
	mIntCurImageIdx = mIntCurImageIdx % mImageNamesList->size();
	RenderImage();
}

void MyCamera::btnPhotosResponsed()
{
	if (curMode == Album) {	//	当前为相册模式，要切換到拍照模式
		curMode = Taking_photos;
		ui.widgetOpeartions->setVisible(false);
		ui.widget_4->setVisible(true);
		ui.btnCapture->show();

		if (curLanguage == Chiness) {
			ui.btnPhotos->setText(QString::fromLocal8Bit("相册"));
			ui.label->setText(QString::fromLocal8Bit("拍照中"));
		}
		if (curLanguage == English) {
			ui.btnPhotos->setText(QString::fromLocal8Bit("Album"));
			ui.label->setText(QString::fromLocal8Bit("Taking photos..."));
		}
		mCamera->start();
		mDisplayLabel->hide();
		mCamViewFind->show();

	}
	else {					//	当前为拍照模式，要切換到相冊模式
		curMode = Album;
		mCamViewFind->hide();
		mCamera->stop();
		mDisplayLabel->show();

		ui.widgetOpeartions->setVisible(true);
		ui.widget_4->setVisible(false);
		ui.btnCapture->hide();

		if (curLanguage == Chiness) {
			ui.btnPhotos->setText(QString::fromLocal8Bit("拍照"));
			ui.label->setText(QString::fromLocal8Bit("浏览相册中"));
		}
		if (curLanguage == English) {
			ui.btnPhotos->setText(QString::fromLocal8Bit("Taking Photos"));
			ui.label->setText(QString::fromLocal8Bit("Browsing album"));
		}


		mDisplayLabel->setStyleSheet("QLabel{background-color:rgb(255, 255, 255);}");//设置样式表，底色为白色

		GetCurPathImagesList();
		mIntCurImageIdx = 0;
		if (mImageNamesList->empty()) {
			QMessageBox::warning(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("当前路径无照片"));
			return;
		}
		qDebug() << "MyCamera::btnPhotosResponsed():" << mDisplayLabel->size();

		RenderImage();	//渲染图片
	}
}

void MyCamera::btnSaveImageResponsed()
{
	QString savepath = QFileDialog::getSaveFileName(this, "Save Capture", gDir + "/Untitled", "Image png(*.png);;Image jpg(*.jpg);;Image bmp(*.bmp);;Image jpeg(*.jpeg)");
	const QPixmap *current_img = mDisplayLabel->pixmap();
	if (!savepath.isEmpty()) {
		current_img->save(savepath);
	}
	GetCurPathImagesList();
	//mIntCurImageIdx = mIntCurImageIdx % mImageNamesList->size();
	RenderImage();
}

void MyCamera::btnSettingsResponsed()
{
	DialogSettings dialog(this);
	dialog.exec();
	UpdateLanguage();
}

void MyCamera::btnTurnLeftResponsed()
{
	QMatrix matrix;
	matrix.rotate(-90);
	mDisplayLabel->TurnImage(matrix);
}

void MyCamera::btnTurnRightResponsed()
{
	QMatrix matrix;
	matrix.rotate(90);
	mDisplayLabel->TurnImage(matrix);
}

void MyCamera::btnPreviousResponsed()
{
	if (mIntCurImageIdx <= 0) {
		QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("已是第一张照片"));
		return;
	}

	mIntCurImageIdx--;
	RenderImage();
}

void MyCamera::btnNextResponsed()
{
	if (mIntCurImageIdx >= mImageNamesList->size() - 1) {
		QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("已是最后一张照片"));
		return;
	}

	mIntCurImageIdx++;
	RenderImage();
}

void MyCamera::CountTime()
{
	if (mIntRestTime >= 0)
	{
		mIntRestTime--;
		if (curLanguage == Chiness) ui.label->setText(QString::fromLocal8Bit("拍摄倒计时：") + QString::number(mIntRestTime) + QString::fromLocal8Bit("秒"));
		if (curLanguage == English) ui.label->setText(QString::fromLocal8Bit("Shooting countdown: ") + QString::number(mIntRestTime) + QString::fromLocal8Bit("s"));
	}
	else
	{
		mTimer->stop();
	}
}
