#pragma once
#include <QtNetwork/QTcpSocket>
#include <QThread>
#include <QTimer>  
#include "common.h"

#define TIMEOUT 15000
#define TIME_INT 100

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
	void playCard(qint8 index, QByteArray card);

	void skipLandLord(qint8 index);
	void chooseLandLord(qint8 index);

	void dealCard(void);
	void broadCastData(qint8 sender, QByteArray data);
	

private:
	std::shared_ptr<QTcpSocket> tcpClient[3];  // client

	qint8 playerState[3];  // player state 0: unconnected 1: unready 2:ready
  
	qint8 skipPlayNum;     // skip times in playing card
	qint8 skipLandLordNum; // skip times in choosing landlord

	qint8 turnIndex;       // turn index

	QByteArray person[4];

	std::shared_ptr<QTimer> playTimer;
	std::shared_ptr<QTimer> chooseTimer;

private slots:
	void playTimeOut(void);
	void chooseTimeOut(void);

};

