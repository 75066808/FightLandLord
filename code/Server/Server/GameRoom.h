#pragma once
#include <QtNetwork/QTcpSocket>
#include <QThread>
#include <QTimer>  
#include "common.h"

#define TIMEOUT 15000


class GameRoom : public QObject
{
	Q_OBJECT;

public:
	GameRoom();
	~GameRoom();

	bool connectSocket(QTcpSocket *tcpSocket);
	void disconnectSocket(qint8 index);

	bool checkConnect(qint8 index);
	QTcpSocket *getSocket(qint8 index);

	void ready(qint8 index);

	void skipCard(qint8 index);
	void playCard(qint8 index);

	void skipLandLord(qint8 index);
	void chooseLandLord(qint8 index);

	void broadCastData(qint8 sender, QByteArray data);

private:
	QTcpSocket *tcpClient[3];  // clients
	qint8 tcpConnect[3];       // connect signal

	qint8 readyNum;            // number of ready clients
	qint8 playerNum;           // number of players
	qint8 skipPlayNum;         // skip times in playing card
	qint8 skipLandLordNum;     // skip times in choosing landlord
	qint8 dealCardOverNum;     // number of players who finish dealing card
	qint8 dealLandLordOverNum; // number of players who finish dealing landlord card

	qint8 turnIndex;             // turn index

	CARDSET person[3];
	CARDSET person2;
	CARDSET person3;
	CARDSET landlord;

	CARDSET card;

	QTimer *playTimer;
	QTimer *chooseTimer;

private slots:
	void playTimeOut(void);
	void chooseTimeOut(void);

};

