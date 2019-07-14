#include "GameRoom.h"

GameRoom::GameRoom()
{
	playerState[0] = 0;
	playerState[1] = 0;
	playerState[2] = 0;

	skipPlayNum = 0;
	skipLandLordNum = 0;

	turnIndex = 0;
	counter = TIME_OUT;

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
			qDebug() << i << " Connected";
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
	
	qDebug() << index << " Disconnected";

	tcpClient[index]->disconnectFromHost();
	playerState[index] = 0; // clear state
	
	skipPlayNum = 0;
	skipLandLordNum = 0;
	counter = TIME_OUT;

	if (playTimer->isActive())
		playTimer->stop();
	if (chooseTimer->isActive())
		chooseTimer->stop();

	for (qint32 i = 0;i < 3;i++)
	{
		if (i == index)
			continue;
		if (playerState[i] != 0)
			playerState[i] = 1;
	}


	skipPlayNum = 0;
	skipLandLordNum = 0;
	turnIndex = 0;

	data[0] = DISCONNECT;
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
			QThread::msleep(TIME_INT);
			playerState[0] = 3;   // set all players to play state
			playerState[1] = 3;
			playerState[2] = 3;
			dealCard();

			QThread::msleep(TIME_INT);
			data[0] = TIME_SEC;
			data[1] = -1;
			broadCastData(turnIndex, data);

			counter = TIME_TURN;
			chooseTimer->start(TIME_COUNT);
		}
	}
	
}

void GameRoom::continues(qint8 index)
{
	QByteArray data;
	if (playerState[index] == 3)
	{
		data[0] = CONT;
		playerState[index] = 1; // set to unready
		broadCastData(index, data);
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

	QThread::msleep(TIME_INT);
	data[0] = TIME_SEC;
	data[1] = -1;
	broadCastData(turnIndex, data);

	QThread::msleep(TIME_INT);
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

	counter = TIME_TURN;
	playTimer->start(TIME_COUNT);
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
	

	QThread::msleep(TIME_INT);
	person[index].resize(person[index].size() - card.size());
	if (person[index].size() == 0) // no card left
	{
		data[0] = TIME_SEC;
		data[1] = -1;
		broadCastData(turnIndex, data);

		QThread::msleep(TIME_INT);
		data[0] = WIN_GAME;
		broadCastData(turnIndex, data);
	}
	else
	{
		turnIndex = (index + 1) % 3;
		data[0] = TIME_SEC;
		data[1] = -1;
		broadCastData(turnIndex, data);

		QThread::msleep(TIME_INT);
		data[0] = PLAY_TURN; // next play also can skip 
		broadCastData(turnIndex, data);
		counter = TIME_TURN;
		playTimer->start(TIME_COUNT);
	}
	
}


void GameRoom::skipLandLord(qint8 index)
{
	QByteArray data;

	if (chooseTimer->isActive())
		chooseTimer->stop();

	data[0] = SKIP_LANDLORD;
	broadCastData(index, data);

	skipLandLordNum++;
	QThread::msleep(TIME_INT);
	if (skipLandLordNum == 3) // all skips
	{
		data[0] = TIME_SEC;
		data[1] = -1;
		broadCastData(turnIndex, data);

		QThread::msleep(TIME_INT);
		skipLandLordNum = 0;
		dealCard(); // shuffle the cards 
	}
	else
	{
		turnIndex = (index + 1) % 3;
		data[0] = TIME_SEC;
		data[1] = -1;
		broadCastData(turnIndex, data);
		
		QThread::msleep(TIME_INT);
		data[0] = CHOOSE_TURN;
		broadCastData(turnIndex, data);  // notify to next player
	}

	counter = TIME_TURN;
	chooseTimer->start(TIME_COUNT);
}

void GameRoom::chooseLandLord(qint8 index)
{
	QByteArray data;	

	if (chooseTimer->isActive())
		chooseTimer->stop();

	turnIndex = index;
	landlordIndex = index;

	data[0] = TIME_SEC;
	data[1] = -1;
	broadCastData(turnIndex, data);

	QThread::msleep(TIME_INT);
	data.resize(0);
	data[0] = DEAL_LANDLORD;
	data.append(person[3]); // land lord

	person[index].resize(person[index].size() + person[3].size()); // add land lord card
	skipLandLordNum = 0;
	broadCastData(turnIndex, data);

	counter = TIME_TURN;
	playTimer->start(TIME_COUNT);
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
	
		if (data.at(0) == CONNECT_SUCCESS || data.at(0) == READY || data.at(0) == CONT || data.at(0) == DISCONNECT)
		{
			broadcast[0] = playerState[(i + 2) % 3];
			broadcast[1] = playerState[i];
			broadcast[2] = playerState[(i + 1) % 3];
		}
		else if (data.at(0) == WIN_GAME)
		{
			if (sender == landlordIndex) // landlord win
			{
				broadcast[0] = 0;
				broadcast[1] = 0;
				broadcast[2] = 0;
				broadcast[(sender - i + 4) % 3] = 1;
			}
			else // farmer win
			{
				broadcast[0] = 1;
				broadcast[1] = 1;
				broadcast[2] = 1;
				broadcast[(landlordIndex - i + 4) % 3] = 0;
			}
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

	if (counter == -1)
	{
		data[0] = TIME_SEC;
		data[1] = counter;
		broadCastData(turnIndex, data);
		QThread::msleep(TIME_INT);

		data[0] = 0;
		data[1] = 0;
		data[2] = 0;
		data[3] = COM_PLAY;
		tcpClient[turnIndex]->write(data);
		counter = TIME_TURN;
	}
	else
	{
		data[0] = TIME_SEC;
		data[1] = counter;
		broadCastData(turnIndex, data);
		counter--;
		playTimer->start(TIME_COUNT);
	}
}


void GameRoom::chooseTimeOut(void)
{
	QByteArray data;

	if (chooseTimer->isActive())
		chooseTimer->stop();

	if (counter == -1)
	{
		data[0] = TIME_SEC;
		data[1] = counter;
		broadCastData(turnIndex, data);
		QThread::msleep(TIME_INT);

		data[0] = 0;
		data[1] = 0;
		data[2] = 0;
		data[3] = COM_CHOOSE;
		tcpClient[turnIndex]->write(data);
		counter = TIME_TURN;
	}
	else
	{
		data[0] = TIME_SEC;
		data[1] = counter;
		broadCastData(turnIndex, data);
		counter--;
		chooseTimer->start(TIME_COUNT);
	}
}