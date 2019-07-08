#pragma once
#include <QtNetwork/QTcpSocket>
#include <QTimerEvent>  


#define TIMEOUT 15000

#define LOWERHOUSE -1
#define SELF 0
#define UPPERHOUSE 1

// signal type between server and client
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
#define PLAYER_QUIT        0X11
#define TIME_OUT           0x12

class GameRoom : public QObject
{
	Q_OBJECT;

public:
	GameRoom();
	~GameRoom();

	bool connectSocket(QTcpSocket *tcpSocket);
	void disconnectSocket(qint32 index);

	bool checkConnect(qint32 index);
	QTcpSocket *getSocket(qint32 index);

	void ready(void);

	void skipCard(void);
	void playCard(void);

	void skipLandLord(void);
	void chooseLandLord(qint32 index);

	void dealCardOver(void);
	void dealLandLordOver(void);

	void broadCastData(qint32 sender, QByteArray data);
	virtual void timerEvent(QTimerEvent *event);

private:
	QTcpSocket *tcpClient[3];   // clients
	qint8 tcpConnect[3];        // connect signal
	qint32 turnNum;             // turn index
	qint32 readyNum;            // number of ready clients
	qint32 playerNum;           // number of players
	qint32 skipPlayNum;         // skip times in playing card
	qint32 skipLandLordNum;     // skip times in choosing landlord
	qint32 dealCardOverNum;     // number of players who finish dealing card
	qint32 dealLandLordOverNum; // number of players who finish dealing landlord card

	qint32 timerID;             // timer for each turn
	qint32 curNum;              // current player ( start timing )
	qint8 timeOut;              // time out signal


	//qint32 card[54]; // card
};

