#include "GameRoom.h"

GameRoom::GameRoom()
{
	playerConnect[0] = 0;
	playerConnect[1] = 0;
	playerConnect[2] = 0;

	playerReady[0] = 0;
	playerReady[1] = 0;
	playerReady[2] = 0;

	skipPlayNum = 0;
	skipLandLordNum = 0;

	turnIndex = 0;
	playTimer = std::make_shared<QTimer>();
	chooseTimer = std::make_shared<QTimer>();

	
	connect(&*playTimer, SIGNAL(timeout()), this, SLOT(playTimeOut()));
	connect(&*chooseTimer, SIGNAL(timeout()), this, SLOT(chooseTimeOut()));
}


GameRoom::~GameRoom()
{

}


bool GameRoom::connectSocket(std::shared_ptr<QTcpSocket> tcpSocket)
{
	QByteArray data;

	for (qint32 i = 0;i < 3;i++)
	{
		if (playerConnect[i] == 0) // find empty connect slot
		{
			tcpClient[i] = tcpSocket;
			playerConnect[i] = 1;
			data[0] = CONNECT_SUCCESS;
			broadCastData(i, data); // notify success
			return true;
		}
	}
	

	data[0] = 0x00;  // full room
	data[1] = CONNECT_FAILED;
	tcpSocket->write(data);           // notify failure
	tcpSocket->disconnectFromHost();  // disconnect

	return false;
}


void GameRoom::disconnectSocket(qint8 index)
{
	QByteArray data;
	
	tcpClient[index]->disconnectFromHost();
	playerConnect[index] = 0; // clear connect signal
	playerReady[index] = 0;   // clear ready signal

	data[0] = PLAYER_QUIT;
	broadCastData(index, data); 
}

bool GameRoom::checkConnect(qint8 index)
{
	return playerConnect[index];
}

std::shared_ptr<QTcpSocket> GameRoom::getSocket(qint8 index)
{
	return tcpClient[index];
}


void GameRoom::ready(qint8 index)
{
	QByteArray data;
	data[0] = READY;
	broadCastData(index, data);

	playerReady[index] = 1;

	if (playerReady[0] && playerReady[1] && playerReady[2] ) // all players ready
	{
		QThread::msleep(100);
		playerReady[0] = 0;
		playerReady[1] = 0;
		playerReady[2] = 0;
		dealCard();
		chooseTimer->start(TIMEOUT);
	}
}


void GameRoom::skipCard(qint8 index)
{
	QByteArray data;
	
	if (playTimer->isActive())
		playTimer->stop();
	
	data[0] = SKIP_CARD;
	broadCastData(index, data);
	skipPlayNum++;
	
	QThread::msleep(100);
	turnIndex = (index + 1) % 3;
	if (skipPlayNum == 2) // if skips twice
	{
		skipPlayNum = 0;
		data[0] = PLAY_TURN_NO_SKIP; // next player can't skip
		broadCastData(turnIndex, data);
	}
	else
	{
		data[0] = PLAY_TURN; // next play also can skip 
		broadCastData(turnIndex, data);
	}


	playTimer->start(TIMEOUT);
}

void GameRoom::playCard(qint8 index)
{
	QByteArray data;

	if (playTimer->isActive())
		playTimer->stop();

	data[0] =  PLAY_CARD;
	broadCastData(index, data);
	skipPlayNum = 0;
	
	QThread::msleep(100);
	turnIndex = (index + 1) % 3;
	data[0] = PLAY_TURN; // next play also can skip 
	broadCastData(turnIndex, data);

	playTimer->start(TIMEOUT);
}



void GameRoom::skipLandLord(qint8 index)
{
	QByteArray data;

	if (chooseTimer->isActive())
		chooseTimer->stop();

	data[0] = SKIP_LANDLORD;
	broadCastData(index, data);

	skipLandLordNum++;

	QThread::msleep(100);
	if (skipLandLordNum == 3) // all skips
	{
		skipLandLordNum = 0;
		data[0] = DEAL_CARD;
		broadCastData(turnIndex, data); // shuffle the cards 

	}
	else
	{
		turnIndex = (index + 1) % 3;
		data[0] = CHOOSE_TURN;
		broadCastData(turnIndex, data);  // notify to next player
	}

	chooseTimer->start(TIMEOUT);
}

void GameRoom::chooseLandLord(qint8 index)
{
	QByteArray data;	

	if (chooseTimer->isActive())
		chooseTimer->stop();

	turnIndex = index;
	data[0] = DEAL_LANDLORD;
	data.append(landlord.tranToSig()); // land lord

	broadCastData(turnIndex, data);
	skipLandLordNum = 0;

	playTimer->start(TIMEOUT);
}

void GameRoom::dealCard(void)
{
	card.setToAll();
	distribute(card, person[0], person[1], person[2], landlord);

	QByteArray card[4];
	
	card[0] = person[0].tranToSig();
	card[1] = person[1].tranToSig();
	card[2] = person[2].tranToSig();
	card[3] = landlord.tranToSig();

	for (qint32 i = 0;i < 3;i++)
	{
		QByteArray data;
		data[0] = turnIndex;
		data[1] = DEAL_CARD;
		data.append(card[3]);
		data.append(card[(i + 2) % 3]); // upperhouse card
		data.append(card[i]); // self card
		data.append(card[(i + 1) % 3]); // lowerhouse card
		tcpClient[i]->write(data);
	}
}

void GameRoom::broadCastData(qint8 sender, QByteArray data)
{
	for (qint8 i = 0;i < 3;i++)
	{
		QByteArray broadcast;
		if (playerConnect[i] == 0)
			continue;
		
		if (sender != -1) // sender is client
			broadcast[0] = (qint8)((sender - i + 4) % 3 - 1);
		else              // sender is service
			broadcast[0] = 0x00;

		broadcast.append(data);
		tcpClient[i]->write(broadcast);
		tcpClient[i]->flush();
	}
}

void GameRoom::playTimeOut(void)
{
	QByteArray data;

	if (playTimer->isActive())
		playTimer->stop();

	data[0] = COM_PLAY;
	broadCastData(turnIndex, data);

}


void GameRoom::chooseTimeOut(void)
{
	QByteArray data;

	if (chooseTimer->isActive())
		chooseTimer->stop();

	data[0] = COM_CHOOSE;
	broadCastData(turnIndex, data);
}