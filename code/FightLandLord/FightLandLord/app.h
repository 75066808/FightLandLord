#pragma once
#include <QtNetwork>
#include <QtWidgets/QApplication>

#include "window.h"
#include "viewmodel.h"
#include "common.h"

#define IP_NUM "127.0.0.1"
#define PORT_NUM 6000


// app state type
#define UNENTER_STATE            0x00
#define ENTER_FINISH_STATE       0x01
#define UNREADY_STATE            0x02
#define READY_FINISH_STATE       0x03
#define READY_STATE              0x04
#define CHOOSE_TURN_STATE        0x05
#define CHOOSE_PRE_STATE         0x06
#define PLAY_TURN_STATE          0x07
#define PLAY_PRE_STATE           0x08
#define PLAY_TURN_NO_SKIP_STATE  0x09
#define PLAY_PRE_NO_SKIP_STATE   0x0A
#define TURN_FINISH_STATE        0x0B

class App: public QObject
{
	Q_OBJECT;

public:
	App(int argc, char *argv[]);
	~App();

	int run(void);

private:
	QTcpSocket *tcpSocket;
	QApplication app;
	Window window;
	Player player;
	qint8 state;

signals:
    void appToWindowSignal(Singal &signal);
	void appToViewModelSignal(Singal &signal);
	
private slots:
	void windowToAppSlot(Singal &signal);
	void viewModelToAppSlot(Singal &signal);
	void readServerData(void);
};

