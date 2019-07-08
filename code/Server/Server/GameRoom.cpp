#include "GameRoom.h"

GameRoom::GameRoom()
{
	tcpConnect[0] = 0;
	tcpConnect[1] = 0;
	tcpConnect[2] = 0;

	turnNum = 0;
	readyNum = 0;
	playerNum = 0;
	skipPlayNum = 0;
	skipLandLordNum = 0;
	dealCardOverNum = 0;
	dealLandLordOverNum = 0;
}


GameRoom::~GameRoom()
{

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
				break;
			}
		}
		
		QByteArray data;
		data[0] = CONNECT_SUCCESS;
		broadCastData(playerNum, data); // notify success

		playerNum++;  // increase play number
		return true;
	}
}


void GameRoom::disconnectSocket(qint32 index)
{
	QByteArray data;
	
	tcpClient[index]->disconnectFromHost();
	playerNum--; // decrease the player
	tcpConnect[index] = 0; // set the connect signal
	data[0] = PLAYER_QUIT;
	broadCastData(index, data); 
}

bool GameRoom::checkConnect(qint32 index)
{
	return tcpConnect[index];
}

QTcpSocket *GameRoom::getSocket(qint32 index)
{
	return tcpClient[index];
}


void GameRoom::ready(void)
{
	QByteArray data;
	readyNum++;
	if (readyNum == 3) // all players ready
	{
		readyNum = 0;
		data[0] = DEAL_CARD;
		broadCastData(-1, data);
	}
}

void GameRoom::skipCard(void)
{
	QByteArray data;
	skipPlayNum++;
	turnNum = (turnNum + 1) % 3;
	data[0] = 0x00;
	if (skipPlayNum == 2) // if skips twice
	{
		skipPlayNum = 0;
		data[1] = PLAY_TURN_NO_SKIP; // next player can't skip
		tcpClient[turnNum]->write(data); // notify next player
	}
	else
	{
		data[1] = PLAY_TURN; // next play also can skip 
		tcpClient[turnNum]->write(data); // notify next player
	}
}

void GameRoom::playCard(void)
{
	qint32 odTimer;
	QByteArray data;

	odTimer = timerID;
	timerID = startTimer(TIMEOUT); // start timing
	killTimer(odTimer);

	turnNum = (turnNum + 1) % 3;
	data[0] = 0x00;
	data[1] = PLAY_TURN;
	tcpClient[turnNum]->write(data); // notify next player
	
	
}

void GameRoom::skipLandLord(void)
{
	QByteArray data;
	skipLandLordNum++;
	turnNum = (turnNum + 1) % 3;
	if (skipLandLordNum == 3) // all skips
	{
		skipLandLordNum = 0;
		data[0] = DEAL_CARD;
		broadCastData(-1, data); // shuffle the cards 

	}
	else
	{
		data[0] = 0x00;
		data[1] = CHOOSE_TURN;
		tcpClient[turnNum]->write(data); // notify to next player
	}
}

void GameRoom::chooseLandLord(qint32 index)
{
	QByteArray data;
	turnNum = index; // set it as the start trun number
	data[0] = 0x00;
	data[1] = DEAL_LANDLORD;
	tcpClient[turnNum]->write(data);  // notify to deal landlord card
}

void GameRoom::dealCardOver(void)
{
	QByteArray data;
	dealCardOverNum++;
	if (dealCardOverNum == 3) // finish dealing the card to all player
	{
		dealCardOverNum = 0;
		data[0] = 0x00;
		data[1] = CHOOSE_TURN;
		tcpClient[turnNum]->write(data); // notify player to choose landlord
	}
}

void GameRoom::dealLandLordOver(void)
{
	QByteArray data;
	dealLandLordOverNum++;
	if (dealLandLordOverNum == 1)
	{
		dealCardOverNum = 0;
		data[0] = 0x00;
		data[1] = PLAY_TURN_NO_SKIP;
		tcpClient[turnNum]->write(data); // notify player(landlord) to play card, can't skip 
	}
}

void GameRoom::broadCastData(qint32 sender, QByteArray data)
{
	for (qint32 i = 0;i < 3;i++)
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

void GameRoom::timerEvent(QTimerEvent *event)
{
	if (event->timerId() == timerID) 
	{
		QByteArray data;
		data[0] = 0x00;
		data[1] = TIME_OUT;
		tcpClient[turnNum]->write(data); // notify player time out
	}
}