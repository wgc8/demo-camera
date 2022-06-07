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
	delete mCamImgCap, mCamViewFind;
}

void MyCamera::Init() {
	this->setWindowTitle(QString::fromLocal8Bit("����ģʽ"));
	mCamerasList = QCameraInfo::availableCameras();
	for (int i = 0; i < mCamerasList.size(); i++) {
		ui.cBoxCameras->addItem(mCamerasList[i].deviceName());
	}

	int curCameraIdx = ui.cBoxCameras->currentIndex();
	mCamera = new QCamera(mCamerasList[curCameraIdx]);
	mCamViewFind = new QCameraViewfinder();
	mCamImgCap = new QCameraImageCapture(mCamera);

	mCamImgCap->setCaptureDestination(QCameraImageCapture::CaptureToFile);
	ui.DisplayLayout->addWidget(mCamViewFind);

	mCamera->setCaptureMode(QCamera::CaptureStillImage);

	mCamera->setViewfinder(mCamViewFind);
	mCamera->start();
	ui.label->setText(QString::fromLocal8Bit("������"));


	//�����źŲ�
	InitConnecting();

}

void MyCamera::InitConnecting(){
	connect(ui.btnCapture, &QPushButton::clicked, this, &MyCamera::btnCaptureResponsed);
	connect(ui.btnCut, &QPushButton::clicked, this, &MyCamera::btnCutResponsed);
	connect(ui.btnDelete, &QPushButton::clicked, this, &MyCamera::btnDeleteResponsed);
	connect(ui.btnPhotos, &QPushButton::clicked, this, &MyCamera::btnPhotosResponsed);
	connect(ui.btnSaveImage, &QPushButton::clicked, this, &MyCamera::btnSaveImageResponsed);
	connect(ui.btnSettings, &QPushButton::clicked, this, &MyCamera::btnSettingsResponsed);
	connect(ui.btnTurnLeft, &QPushButton::clicked, this, &MyCamera::btnTurnLeftResponsed);
	connect(ui.btnTurnRight, &QPushButton::clicked, this, &MyCamera::btnTurnRightResponsed);
}

void MyCamera::UpdateLanguage(eLanguage lan)
{
	if (curLanguage == lan)
		return;
	// �ı��ǩ
	if (lan == Chiness) {
		ui.btnPhotos->setText(QString::fromLocal8Bit("���"));
		ui.btnCapture->setText(QString::fromLocal8Bit("����"));
		ui.btnCut->setText(QString::fromLocal8Bit("����"));
		ui.btnSaveImage->setText(QString::fromLocal8Bit("����"));
		ui.btnDelete->setText(QString::fromLocal8Bit("ɾ��"));
		ui.btnSettings->setText(QString::fromLocal8Bit("����"));
		ui.btnTurnLeft->setText(QString::fromLocal8Bit("��ת"));
		ui.btnTurnRight->setText(QString::fromLocal8Bit("��ת"));
	}

	if (lan == English) {
		ui.btnPhotos->setText(QString::fromLocal8Bit("Album"));
		ui.btnCapture->setText(QString::fromLocal8Bit("Capture"));
		ui.btnCut->setText(QString::fromLocal8Bit("Cut"));
		ui.btnSaveImage->setText(QString::fromLocal8Bit("Save"));
		ui.btnDelete->setText(QString::fromLocal8Bit("Delete"));
		ui.btnSettings->setText(QString::fromLocal8Bit("Settings"));
		ui.btnTurnLeft->setText(QString::fromLocal8Bit("Turn Left"));
		ui.btnTurnRight->setText(QString::fromLocal8Bit("Turn Right"));
	}

	curLanguage = lan;
	return;
}

void MyCamera::btnCaptureResponsed()
{
	QMessageBox MesBox(this);
	MesBox.setText(QString::fromLocal8Bit("actived"));
	MesBox.show();
}

void MyCamera::btnCutResponsed()
{
}

void MyCamera::btnDeleteResponsed()
{
}

void MyCamera::btnPhotosResponsed()
{
}

void MyCamera::btnSaveImageResponsed()
{
}

void MyCamera::btnSettingsResponsed()
{
}

void MyCamera::btnTurnLeftResponsed()
{
}

void MyCamera::btnTurnRightResponsed()
{
}
