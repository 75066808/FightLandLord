#include "Server.h"

Server::Server(QWidget *parent) : QMainWindow(parent), tcpServer(this), logFile("Log/log.txt")
{
	ui.setupUi(this);
	connect(&tcpServer, SIGNAL(newConnection()), this, SLOT(connectionSlot()));
	tcpServer.listen(QHostAddress::Any, PORT_NUM);
}

Server::~Server()
{
	
}

void Server::connectionSlot(void)
{
	qint32 roomNum;
	std::shared_ptr<QTcpSocket> socket = std::shared_ptr<QTcpSocket>(tcpServer.nextPendingConnection());

	logFile.open(QIODevice::Append | QIODevice::Text);

	for (roomNum = 0;roomNum < rooms.size();roomNum++)
	{
		if (rooms.at(roomNum)->connectSocket(socket, roomNum, logFile)) // has unfull room
		{
		
			for (qint32 i = 0;i < rooms.size();i++)
				rooms.at(i)->printRoomState(i, logFile);
			logFile.write(QString("\n").toUtf8());
			
			connect(&*socket, SIGNAL(readyRead()), this, SLOT(serverNotificationSlot()));
			connect(&*socket, SIGNAL(disconnected()), this, SLOT(disconnectionSlot()));
			break;
		}
	}

	if (roomNum == rooms.size()) // no unfull room
	{
		rooms.push_back(std::make_shared<GameRoom>());
		rooms.at(roomNum)->connectSocket(socket, roomNum, logFile);

		for (qint32 i = 0;i < rooms.size();i++)
			rooms.at(i)->printRoomState(i, logFile);
		logFile.write(QString("\n").toUtf8());

		connect(&*socket, SIGNAL(readyRead()), this, SLOT(serverNotificationSlot()));
		connect(&*socket, SIGNAL(disconnected()), this, SLOT(disconnectionSlot()));
	}

	logFile.close();

}

void Server::disconnectionSlot(void)
{
	logFile.open(QIODevice::Append | QIODevice::Text);

	for (qint32 roomNum = 0;roomNum < rooms.size(); roomNum++) // for each room
	{
		for (qint32 index = 0;index < 3;index++) // check unconnected
		{
			if (rooms.at(roomNum)->checkConnect(index) &&
				rooms.at(roomNum)->getSocket(index)->state() == QAbstractSocket::UnconnectedState)
			{			
				rooms.at(roomNum)->disconnectSocket(index, roomNum, logFile);

				for (qint32 i = 0;i < rooms.size();i++)
					rooms.at(i)->printRoomState(i, logFile);

				logFile.write(QString("\n").toUtf8());
			}
		}
	}
	
	logFile.close();

}

void Server::serverNotificationSlot(void)
{
	for (qint32 roomNum = 0;roomNum < rooms.size(); roomNum++) // for each room
	{
		for (qint32 index = 0;index < 3;index++) // for each connection
		{
			if (!rooms.at(roomNum)->checkConnect(index))
				continue;

			QByteArray data = rooms.at(roomNum)->getSocket(index)->readAll(); // check all clients

			if (data.isEmpty()) // no data in buffer
				continue;

			processClientData(roomNum,index, data);  // deal the special notify
		}
	}
	
}


void Server::processClientData(qint32 roomNum, qint32 sender, QByteArray &data)
{

	switch (data.at(0))
	{
		case READY: // player ready
			rooms.at(roomNum)->ready(sender);
			break;

		case PLAY_CARD: // player plays card
			rooms.at(roomNum)->playCard(sender, data.mid(1));
			break;

		case SKIP_CARD: // play skips card
			rooms.at(roomNum)->skipCard(sender);
			break;

		case CHOOSE_LANDLORD: // player chooses landlord
			rooms.at(roomNum)->chooseLandLord(sender);
			break;

		case SKIP_LANDLORD: // player skips landlord
			rooms.at(roomNum)->skipLandLord(sender);
			break;

		case CONT:
			rooms.at(roomNum)->continues(sender);
			break;

		default:
			return;
	}
}
