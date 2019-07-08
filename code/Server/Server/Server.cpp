#include "Server.h"

Server::Server(QWidget *parent) : QMainWindow(parent), tcpServer(this)
{
	ui.setupUi(this);
	connect(&tcpServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
	tcpServer.listen(QHostAddress::Any, PORT_NUM);
}


void Server::acceptConnection(void)
{
	QTcpSocket *socket = tcpServer.nextPendingConnection();
	if (room.connectSocket(socket))
	{
		connect(socket, SIGNAL(readyRead()), this, SLOT(readClientData()));
		connect(socket, SIGNAL(disconnect()), this, SLOT(dealDisconnection()));
	}
}

void Server::dealDisconnection(void)
{
	for (qint32 index = 0;index < 3;index++)
	{
		if (room.getSocket(index)->state() == QAbstractSocket::UnconnectedState && room.checkConnect(index))
			room.disconnectSocket(index);
	}
}

void Server::readClientData(void)
{
	for (qint32 index = 0;index < 3;index++)
	{
		if (!room.checkConnect(index))
			continue;

		QByteArray data = room.getSocket(index)->readAll(); // check all clients

		if (data.isEmpty())
			continue;

		room.broadCastData(index, data); // broad cast to all players
		QThread::msleep(100);
		dealClientData(index, data[0]);  // deal the special notify
	}
}




void Server::dealClientData(qint32 sender, qint8 signal)
{
	QByteArray transData;
	
	switch (signal)
	{

	case READY: // player ready
		room.ready();
		break;

	case PLAY_CARD: // player plays card
		room.playCard();
		break;

	case SKIP_CARD: // play skips card
		room.skipCard();
		break;

	case CHOOSE_LANDLORD: // player chooses landlord
		room.chooseLandLord(sender);
		break;

	case SKIP_LANDLORD: // player skips landlord
		room.skipLandLord();
		break;

	case DEAL_CARD_OVER: // finish dealing the card to player
		room.dealCardOver();
		break;

	case DEAL_LANLOARD_OVER: // finish dealing the landlord card to player
		room.dealLandLordOver();
		break;

	default:
		break;
	}

}
