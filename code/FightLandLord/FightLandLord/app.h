#pragma once
#include <QtNetwork>
#include <QtWidgets/QApplication>

#include "window.h"

#define IP_NUM "127.0.0.1"
#define PORT_NUM 6000


// signal type between client and server
#define CONNECT_SUCCESS    0x00
#define CONNECT_FAILED     0x01
#define READY              0x02
#define PLAY_TURN          0x03
#define PLAY_TURN_NO_SKIP  0x04
#define CHOOSE_TURN        0x05
#define PLAY_CARD          0x06
#define SKIP_CARD          0x07
#define CHOOSE_LANDLORD    0x08
#define SKIP_LANDLORD      0x09
#define DEAL_CARD          0x0A
#define DEAL_LANDLORD      0x0B
#define DEAL_CARD_OVER     0x0C
#define DEAL_LANLOARD_OVER 0x0D
#define LOSE_GAME          0x0E
#define WIN_GAME           0x10
#define PLAYER_QUIT        0x11
#define TIME_OUT           0x12

// app state type
#define UNENTER_STATE            0x00
#define UNREADY_STATE            0x01
#define READY_STATE              0x02
#define DEAL_CARD_STATE          0x03
#define CHOOSE_TURN_STATE        0x04
#define PLAY_TURN_STATE          0x05
#define PLAY_TURN_NO_SKIP_STATE  0x06
#define TURN_FINISH_STATE        0x07

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
	qint8 state;


signals:
	void connectSignal(qint8 player);
	void disconnectSignal(qint8 player);
	void readySignal(qint8 player);
	void chooseLandLordSignal(qint8 player);
	void skipLandLordSignal(qint8 player);
	void playCardSignal(qint8 player, QByteArray card);
	void skipCardSignal(qint8 player);

	void playTurnSignal(qint8 player);
	void playTurnNoSkipSignal(qint8 player);
	void chooseTurnSignal(qint8 player);

	void dealCardSignal(QByteArray card);
	void dealLandLordCardSignal(QByteArray card);

	void winGameSignal(void);
	void loseGameSignal(void);

	void quitSignal(qint8 player);


private slots:
	void connectSlot(void);
	void disconnectSlot(void);
	void readySlot(void);
	void chooseLandLordSlot(void);
	void skipLandLordSlot(void);
	void playCardSlot(QByteArray card);
	void skipCardSlot(void);
	void readServerData(void);

	void dealCardOverSlot(void);
	void dealLandLordCardOverSlot(void);


};

