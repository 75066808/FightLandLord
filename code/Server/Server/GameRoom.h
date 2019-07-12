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

	bool connectSocket(std::shared_ptr<QTcpSocket> tcpSocket);
	void disconnectSocket(qint8 index);

	bool checkConnect(qint8 index);
	std::shared_ptr<QTcpSocket> getSocket(qint8 index);

	void ready(qint8 index);

	void skipCard(qint8 index);
	void playCard(qint8 index);

	void skipLandLord(qint8 index);
	void chooseLandLord(qint8 index);

	void dealCard(void);
	void broadCastData(qint8 sender, QByteArray data);
	

private:
	std::shared_ptr<QTcpSocket> tcpClient[3];  // client

	qint8 playerConnect[3];  // player connect
	qint8 playerReady[3];    // player ready  
  
	qint8 skipPlayNum;     // skip times in playing card
	qint8 skipLandLordNum; // skip times in choosing landlord

	qint8 turnIndex;       // turn index

	CARDSET person[3];
	CARDSET landlord;
	CARDSET card;

	std::shared_ptr<QTimer> playTimer;
	std::shared_ptr<QTimer> chooseTimer;

private slots:
	void playTimeOut(void);
	void chooseTimeOut(void);

};

