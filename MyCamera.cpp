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

	gPath = QCoreApplication::applicationDirPath();

	this->setWindowTitle(QString::fromLocal8Bit("����ģʽ"));

	mCamerasList = QCameraInfo::availableCameras();
	if (mCamerasList.empty()) {
		QMessageBox MesBox(this);
		QString tmpstr;
		if (curLanguage == Chiness) tmpstr = QString::fromLocal8Bit("�޿�������ͷ");
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

void MyCamera::UpdateLanguage()
{
	// �ı��ǩ
	if (curLanguage == Chiness) {
		ui.btnPhotos->setText(QString::fromLocal8Bit("���"));
		ui.btnCapture->setText(QString::fromLocal8Bit("����"));
		ui.btnCut->setText(QString::fromLocal8Bit("����"));
		ui.btnSaveImage->setText(QString::fromLocal8Bit("����"));
		ui.btnDelete->setText(QString::fromLocal8Bit("ɾ��"));
		ui.btnSettings->setText(QString::fromLocal8Bit("����"));
		ui.btnTurnLeft->setText(QString::fromLocal8Bit("��ת"));
		ui.btnTurnRight->setText(QString::fromLocal8Bit("��ת"));
		ui.label_2->setText(QString::fromLocal8Bit("ѡ������ͷ"));

		this->setWindowTitle(QString::fromLocal8Bit("����ģʽ"));
	}

	if (curLanguage == English) {
		ui.btnPhotos->setText(QString::fromLocal8Bit("Album"));
		ui.btnCapture->setText(QString::fromLocal8Bit("Capture"));
		ui.btnCut->setText(QString::fromLocal8Bit("Cut"));
		ui.btnSaveImage->setText(QString::fromLocal8Bit("Save"));
		ui.btnDelete->setText(QString::fromLocal8Bit("Delete"));
		ui.btnSettings->setText(QString::fromLocal8Bit("Settings"));
		ui.btnTurnLeft->setText(QString::fromLocal8Bit("Turn Left"));
		ui.btnTurnRight->setText(QString::fromLocal8Bit("Turn Right"));
		ui.label_2->setText(QString::fromLocal8Bit("Select the Camera"));

		this->setWindowTitle(QString::fromLocal8Bit("Photo mode"));
	}
}

void MyCamera::btnCaptureResponsed()
{

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
	DialogSettings dialog(this);
	dialog.exec();
	UpdateLanguage();
}

void MyCamera::btnTurnLeftResponsed()
{
}

void MyCamera::btnTurnRightResponsed()
{
}
