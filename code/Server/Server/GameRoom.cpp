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

	return false;
}


void GameRoom::disconnectSocket(qint8 index)
{
	QByteArray data;
	
	tcpClient[index]->disconnectFromHost();
	playerConnect[index] = 0; // clear connect signal
	playerReady[index] = 0;   // clear ready signal

	skipPlayNum = 0;
	skipLandLordNum = 0;
	turnIndex = 0;

	data[0] = CONNECT_SUCCESS;
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

	if (playerReady[0] && playerReady[1] && playerReady[2]) // all players ready
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
	data.append(person[3]); // land lord

	broadCastData(turnIndex, data);
	skipLandLordNum = 0;

	playTimer->start(TIMEOUT);
}

void GameRoom::dealCard(void)
{
	CARDSET card;
	CARDSET temp[4];

	card.setToAll();
	distribute(card, temp[0], temp[1], temp[2], temp[3]);
	
	for (qint32 i = 0; i < 4;i++)
		person[i] = temp[i].tranToSig();

	for (qint32 i = 0;i < 3;i++)
	{
		QByteArray data;
		
		data[0] = 0;
		data[1] = 0;
		data[2] = 0;
		data[(turnIndex - i + 4) % 3] = 1;

		data.append(DEAL_CARD);
		data.append(person[3]);
		data.append(person[(i + 2) % 3]); // upperhouse card
		data.append(person[i]); // self card
		data.append(person[(i + 1) % 3]); // lowerhouse card
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
	
		if (data.at(0) == CONNECT_SUCCESS)
		{
			broadcast[0] = playerConnect[(i + 2) % 3];
			broadcast[1] = playerConnect[i];
			broadcast[2] = playerConnect[(i + 1) % 3];
		}
		else if (data.at(0) == READY)
		{
			broadcast[0] = playerReady[(i + 2) % 3];
			broadcast[1] = playerReady[i];
			broadcast[2] = playerReady[(i + 1) % 3];
		}
		else
		{
			broadcast[0] = 0;
			broadcast[1] = 0;
			broadcast[2] = 0;
			broadcast[(sender - i + 4) % 3] = 1;
		}
		
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