#pragma once

#include <QtWidgets/QWidget>
#include <QList>
#include <Qlabel>
#include <QMessageBox> 
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QCameraInfo>
#include <QDir>
#include <QTimer>
#include <QFileDialog> 
#include "MyLabel.h"
#include "DialogSettings.h"
#include "config.h"
#include "ui_MyCamera.h"

class MyCamera : public QWidget
{
	Q_OBJECT

public:
	MyCamera(QWidget *parent = Q_NULLPTR);
	~MyCamera();

private:
	Ui::MyCameraClass ui;
	int mIntCurImageIdx;
	int mIntRestTime;
	QCamera *mCamera;
	QCameraViewfinder * mCamViewFind;
	QCameraImageCapture * mCamImgCap;
	QList<QCameraInfo> mCamerasList;
	QStringList *mImageNamesList;
	MyLabel *mDisplayLabel;

	QTimer *mTimer;


	void Init();
	void InitConnections();
	void UpdateLanguage();
	void CreateFileDir();
	void ImageCaptured(int, QImage);
	void GetCurPathImagesList();
	void RenderImage();

private slots:
	void btnCaptureResponsed();
	void btnCutResponsed();
	void btnDeleteResponsed();
	void btnPhotosResponsed();
	void btnSaveImageResponsed();
	void btnSettingsResponsed();
	void btnTurnLeftResponsed();
	void btnTurnRightResponsed();
	void btnPreviousResponsed();
	void btnNextResponsed();
	void SwitchCamera(int cameraIdx);
	void CountTime();
};
