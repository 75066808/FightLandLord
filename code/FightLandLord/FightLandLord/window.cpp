#include "window.h"
#include <QMessageBox>

Window::Window(QWidget *parent)
	: QMainWindow(parent)
{
	ui->setupUi(this);
	connect(ui->pushButtonTestSignal, SIGNAL(clicked()), this, SLOT(SignalComing()));
}


void Window::SignalComing()
{
	QMessageBox::information(this, tr("Signal Sent"), tr("Signal Received!"));
}