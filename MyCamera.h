#pragma once

#include <QtWidgets/QWidget>
#include <QList>
#include <Qlabel>
#include <QMessageBox> 
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QCameraInfo>
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
	QCamera *mCamera;
	QCameraViewfinder * mCamViewFind;
	QCameraImageCapture * mCamImgCap;
	QLabel *mDisplayLabel;

	QList<QCameraInfo> mCamerasList;

	void Init();
	void InitConnecting();
	void UpdateLanguage(eLanguage);

private slots:
	void btnCaptureResponsed();
	void btnCutResponsed();
	void btnDeleteResponsed();
	void btnPhotosResponsed();
	void btnSaveImageResponsed();
	void btnSettingsResponsed();
	void btnTurnLeftResponsed();
	void btnTurnRightResponsed();
};
