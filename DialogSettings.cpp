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
	//	��������
	if (curLanguage == Chiness) this->setWindowTitle(QString::fromLocal8Bit("����"));
	if (curLanguage == English) this->setWindowTitle(QString::fromLocal8Bit("Settings"));
	UpdateLanguage();


	//	���õ�ǰ��
	ui.cBoxLanguage->setCurrentIndex(curLanguage);
	ui.sBoxWaittingTime->setValue(gWaitTime);
	ui.lineEditPath->setText(gPath);

	//	�����źŲ�
	InitConnecting();
}

void DialogSettings::InitConnecting()
{
	connect(ui.okButton, &QPushButton::clicked, this, &DialogSettings::btnOKResponsed);
}

void DialogSettings::UpdateLanguage()
{
	// �ı��ǩ
	if (curLanguage == Chiness) {
		ui.labDir->setText(QString::fromLocal8Bit("·��"));
		ui.labLanguage->setText(QString::fromLocal8Bit("����"));
		ui.labWaitingTime->setText(QString::fromLocal8Bit("�����ӳ�ʱ��"));
		ui.cancelButton->setText(QString::fromLocal8Bit("����"));
		ui.okButton->setText(QString::fromLocal8Bit("ȷ��"));

	}

	if (curLanguage == English) {
		ui.labDir->setText(QString::fromLocal8Bit("File Path"));
		ui.labLanguage->setText(QString::fromLocal8Bit("Language"));
		ui.labWaitingTime->setText(QString::fromLocal8Bit("Waitting Time"));
		ui.cancelButton->setText(QString::fromLocal8Bit("Cancel"));
		ui.okButton->setText(QString::fromLocal8Bit("OK"));
	}
}

void DialogSettings:: btnOKResponsed() {
	curLanguage = static_cast<eLanguage> (ui.cBoxLanguage->currentIndex());
	gPath = ui.lineEditPath->text();
	gWaitTime = ui.sBoxWaittingTime->value();
	this->accept();
}