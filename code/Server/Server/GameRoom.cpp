#include "GameRoom.h"

GameRoom::GameRoom()
{
	playerState[0] = 0;
	playerState[1] = 0;
	playerState[2] = 0;

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


bool GameRoom::connectSocket(std::shared_ptr<QTcpSocket> &tcpSocket)
{
	QByteArray data;

	for (qint32 i = 0;i < 3;i++)
	{
		if (playerState[i] == 0) // find empty connect slot
		{
			tcpClient[i] = tcpSocket;
			playerState[i] = 1;
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
	playerState[index] = 0; // clear state

	skipPlayNum = 0;
	skipLandLordNum = 0;
	turnIndex = 0;

	data[0] = CONNECT_SUCCESS;
	broadCastData(index, data); 
}

bool GameRoom::checkConnect(qint8 index)
{
	return playerState[index] != 0;
}

std::shared_ptr<QTcpSocket> GameRoom::getSocket(qint8 index)
{
	return tcpClient[index];
}


void GameRoom::ready(qint8 index)
{
	QByteArray data;

	if (playerState[index] == 1) // unready state
	{
		data[0] = READY;
		playerState[index] = 2;
		broadCastData(index, data);

		if (playerState[0] == 2&& playerState[1] == 2&& playerState[2] == 2) // all players ready
		{
			playerState[0] = 1;   // set all players to unready state
			playerState[1] = 1;
			playerState[2] = 1;
			dealCard();
			chooseTimer->start(TIMEOUT);
		}
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

void GameRoom::playCard(qint8 index, QByteArray& card)
{
	QByteArray data;

	if (playTimer->isActive())
		playTimer->stop();

	data[0] =  PLAY_CARD;
	data.append(card);
	broadCastData(index, data);
	skipPlayNum = 0;
	
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

	if (skipLandLordNum == 3) // all skips
	{
		skipLandLordNum = 0;
		dealCard(); // shuffle the cards 
		chooseTimer->start(TIMEOUT);
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

void GameRoom::broadCastData(qint8 sender, QByteArray& data)
{
	for (qint8 i = 0;i < 3;i++)
	{
		QByteArray broadcast;
		if (playerState[i] == 0)
			continue;
	
		if (data.at(0) == CONNECT_SUCCESS || data.at(0) == READY)
		{
			broadcast[0] = playerState[(i + 2) % 3];
			broadcast[1] = playerState[i];
			broadcast[2] = playerState[(i + 1) % 3];
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