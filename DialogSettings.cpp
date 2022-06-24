#include "DialogSettings.h"

DialogSettings::DialogSettings(QWidget *parent)
	: QDialog (parent)
{
	ui.setupUi(this);

	Init();
}

DialogSettings::~DialogSettings()
{
}

void DialogSettings::Init()
{
	//	处理语言
	if (curLanguage == Chiness) this->setWindowTitle(QString::fromLocal8Bit("设置"));
	if (curLanguage == English) this->setWindowTitle(QString::fromLocal8Bit("Settings"));
	UpdateLanguage();


	//	设置当前项
	ui.cBoxLanguage->setCurrentIndex(curLanguage);
	ui.sBoxWaittingTime->setValue(gWaitTime);
	ui.lineEditPath->setText(gDir);

	//	链接信号槽
	InitConnections();
}

void DialogSettings::InitConnections()
{
	connect(ui.okButton, &QPushButton::clicked, this, &DialogSettings::btnOKResponsed);
	connect(ui.btnBrowse, &QPushButton::clicked, this, &DialogSettings::btnBrowseResponsed);
}

void DialogSettings::UpdateLanguage()
{
	// 改变标签
	if (curLanguage == Chiness) {
		ui.labDir->setText(QString::fromLocal8Bit("路径"));
		ui.labLanguage->setText(QString::fromLocal8Bit("语言"));
		ui.labWaitingTime->setText(QString::fromLocal8Bit("拍摄延迟时间"));
		ui.cancelButton->setText(QString::fromLocal8Bit("返回"));
		ui.okButton->setText(QString::fromLocal8Bit("确定"));

	}

	if (curLanguage == English) {
		ui.labDir->setText(QString::fromLocal8Bit("File Path"));
		ui.labLanguage->setText(QString::fromLocal8Bit("Language"));
		ui.labWaitingTime->setText(QString::fromLocal8Bit("Waitting Time"));
		ui.cancelButton->setText(QString::fromLocal8Bit("Cancel"));
		ui.okButton->setText(QString::fromLocal8Bit("OK"));
	}
}

void DialogSettings::btnBrowseResponsed()
{
	QString dir = QFileDialog::getExistingDirectory(this);
	ui.lineEditPath->setText(dir);
}

void DialogSettings:: btnOKResponsed() {
	curLanguage = static_cast<eLanguage> (ui.cBoxLanguage->currentIndex());
	gDir = ui.lineEditPath->text();
	gWaitTime = ui.sBoxWaittingTime->value();
	this->accept();
}