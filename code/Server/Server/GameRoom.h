#pragma once
#include <QtNetwork/QTcpSocket>
#include <QTimerEvent>  
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

	void readyStart(qint8 index);
	void readyFinish(void);

	void skipCard(qint8 index);
	void playCard(qint8 index);
	void playNextTurn(void);

	void skipLandLord(qint8 index);
	void chooseLandLord(qint8 index);
	void chooseNextTurn(void);


	void dealCardFinish(void);
	void dealLandLordFinish(void);

	void broadCastData(qint8 sender, QByteArray data);
	virtual void timerEvent(QTimerEvent *event);

private:
	QTcpSocket *tcpClient[3];   // clients
	qint8 tcpConnect[3];        // connect signal
	qint8 turnNum;             // turn index
	qint8 readyNum;            // number of ready clients
	qint8 playerNum;           // number of players
	qint8 skipPlayNum;         // skip times in playing card
	qint8 skipLandLordNum;     // skip times in choosing landlord
	qint8 dealCardOverNum;     // number of players who finish dealing card
	qint8 dealLandLordOverNum; // number of players who finish dealing landlord card

	qint32 timerID;             // timer for each turn
	qint8 curNum;               // current player ( start timing )
	qint8 timeOut;              // time out signal


	//qint32 card[54]; // card
};

