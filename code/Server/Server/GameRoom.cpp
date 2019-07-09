#include "GameRoom.h"

GameRoom::GameRoom()
{
	tcpConnect[0] = 0;
	tcpConnect[1] = 0;
	tcpConnect[2] = 0;

	readyNum = 0;
	playerNum = 0;
	skipPlayNum = 0;
	skipLandLordNum = 0;
	dealCardOverNum = 0;
	dealLandLordOverNum = 0;

	turnIndex = 0;
	playTimer = new QTimer(this);
	chooseTimer = new QTimer(this);

	
	connect(playTimer, SIGNAL(timeout()), this, SLOT(playTimeOut()));
	connect(chooseTimer, SIGNAL(timeout()), this, SLOT(chooseTimeOut()));
}


GameRoom::~GameRoom()
{
	delete playTimer;
	delete chooseTimer;
}


bool GameRoom::connectSocket(QTcpSocket *tcpSocket)
{
	if (playerNum == 3) // full room 
	{
		QByteArray data;
		data[0] = 0x00;
		data[1] = CONNECT_FAILED;
		tcpSocket->write(data);           // notify failure
		tcpSocket->disconnectFromHost();  // disconnect
		return false;
	}
	else // unfull room
	{
		for (qint32 i = 0;i < 3;i++)
		{
			if (tcpConnect[i] == 0)
			{
				tcpClient[i] = tcpSocket;
				tcpConnect[i] = 1;
				break;
			}
		}
		
		QByteArray data;
		data[0] = CONNECT_SUCCESS;
		card.setToAll();
		distribute(card, person[0], person[1], person[2], landlord);

		data.append(person[0].tranToSig());
		broadCastData(playerNum, data); // notify success

		playerNum++;  // increase play number
		return true;
	}
}


void GameRoom::disconnectSocket(qint8 index)
{
	QByteArray data;
	
	tcpClient[index]->disconnectFromHost();
	playerNum--;           // decrease the player
	tcpConnect[index] = 0; // set the connect signal
	data[0] = PLAYER_QUIT;
	broadCastData(index, data); 
}

bool GameRoom::checkConnect(qint8 index)
{
	return tcpConnect[index];
}

QTcpSocket *GameRoom::getSocket(qint8 index)
{
	return tcpClient[index];
}


void GameRoom::ready(qint8 index)
{
	QByteArray data;
	data[0] = READY;
	broadCastData(index, data);
	readyNum++;

	QThread::msleep(100);
	if (readyNum == 3) // all players ready
	{
		readyNum = 0;
		data[0] = DEAL_CARD;
		broadCastData(turnIndex, data);
	}
}




void GameRoom::skipCard(qint8 index)
{
	qint8 next;
	QByteArray data;
	data[0] = SKIP_CARD;
	broadCastData(index, data);

	skipPlayNum++;
	
	QThread::msleep(100);
	next = (index + 1) % 3;
	if (skipPlayNum == 2) // if skips twice
	{
		skipPlayNum = 0;
		data[0] = PLAY_TURN_NO_SKIP; // next player can't skip
		broadCastData(next, data);
	}
	else
	{
		data[0] = PLAY_TURN; // next play also can skip 
		broadCastData(next, data);
	}

}

void GameRoom::playCard(qint8 index)
{
	qint8 next;
	QByteArray data;
	data[0] =  PLAY_CARD;
	broadCastData(index, data);

	skipPlayNum = 0;
	
	QThread::msleep(100);
	next = (index + 1) % 3;
	data[0] = PLAY_TURN; // next play also can skip 
	broadCastData(next, data);
}



void GameRoom::skipLandLord(qint8 index)
{
	qint8 next;
	QByteArray data;
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
		next = (index + 1) % 3;
		data[0] = CHOOSE_TURN;
		broadCastData(next, data);  // notify to next player
	}

}

void GameRoom::chooseLandLord(qint8 index)
{
	QByteArray data;	
	data[0] = CHOOSE_LANDLORD;
	broadCastData(index, data);
	skipLandLordNum = 0;
}





void GameRoom::broadCastData(qint8 sender, QByteArray data)
{
	for (qint8 i = 0;i < 3;i++)
	{
		QByteArray broadcast;
		if (tcpConnect[i] == 0)
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
	
}


void GameRoom::chooseTimeOut(void)
{

}