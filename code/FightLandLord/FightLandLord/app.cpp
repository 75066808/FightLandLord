#include "app.h"


App::App(int argc, char *argv[]): app(argc, argv)
{
	state = UNENTER_STATE;
	connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readSeverData()));
}

App::~App()
{

}

int App::run(void)
{
	window.show();
	return app.exec();
}

void App::connectSlot(void)
{
	if (state == UNENTER_STATE)
	{
		tcpSocket->abort(); // disconnect current connection
		tcpSocket->connectToHost(QHostAddress(IP_NUM), PORT_NUM); // send connect request
	}
}

void App::disconnectSlot(void)
{
	if (state != UNENTER_STATE)
	{
		tcpSocket->disconnectFromHost(); // disconnect from host
	}
}

void App::readySlot(void)
{
	if (state == UNREADY_STATE) // in unready state
	{
		QByteArray data;
		data[0] = READY;
		tcpSocket->write(data); // send ready signal
	}
}

void App::chooseLandLordSlot(void)
{
	if (state == CHOOSE_TURN_STATE) // in choose turn
	{
		QByteArray data;
		data[0] = CHOOSE_LANDLORD;
		tcpSocket->write(data);
	}
}

void App::skipLandLordSlot(void)
{
	if (state == CHOOSE_TURN_STATE) // in choose turn
	{
		QByteArray data;
		data[0] = SKIP_LANDLORD;
		tcpSocket->write(data); // send skip landlord signal
	}
}

void App::playCardSlot(QByteArray card)
{
	if (state == PLAY_TURN_NO_SKIP_STATE || state == PLAY_TURN_STATE) // in play turn
	{
		QByteArray data;
		data[0] = PLAY_CARD;
		tcpSocket->write(data); // send play card signal
	}
}

void App::skipCardSlot(void)
{
	if (state == PLAY_TURN_STATE) // in play turn ( enable skipping )
	{
		QByteArray data;
		data[0] = SKIP_CARD;
		tcpSocket->write(data); // send skip card signal
	}
}

void App::dealCardOverSlot(void) 
{
	QByteArray data;
	data[0] = DEAL_CARD_OVER;
	tcpSocket->write(data); // send deal over signal
}

void App::dealLandLordCardOverSlot(void)
{
	QByteArray data;
	data[0] = DEAL_LANLOARD_OVER;
	tcpSocket->write(data); // send deal landlord over signal
}

void App::readServerData(void)
{
	QByteArray data = tcpSocket->readAll(); // read from server

	switch (data.at(1)) // check signal type
	{
	case CONNECT_SUCCESS:
		if (data.at(0) == 0) // for self player
			state = UNREADY_STATE; // enter the room
		emit connectSignal(data[1]);
		break;

	case CONNECT_FAILED:
		emit disconnectSignal(data[1]);
		break;

	case READY:
		if (data.at(0) == 0) // for self player
			state = READY_STATE; // ready for play
		emit readySignal(data[1]);
		break;

	case PLAY_TURN:
		if (data.at(0) == 0) // for self player
			state = PLAY_TURN_STATE; // in play turn ( can skip )
		emit playTurnSignal(data[1]);
		break;

	case PLAY_TURN_NO_SKIP:
		if (data.at(0) == 0) // for self player
			state = PLAY_TURN_NO_SKIP_STATE; // in play turn ( can't skip )
		emit playTurnNoSkipSignal(data[1]);
		break;

	case CHOOSE_TURN:
		if (data.at(0) == 0) // for self player
			state = CHOOSE_TURN_STATE; // in choose turn
		emit chooseTurnSignal(data[1]);
		break;

	case PLAY_CARD:
		if (data.at(0) == 0) // for self player
			state = TURN_FINISH_STATE; // play turn finished
		emit playCardSignal(data[1], data);
		break;

	case SKIP_CARD:
		if (data.at(0) == 0) // for self player
			state = TURN_FINISH_STATE; // play turn finished
		emit skipCardSignal(data[1]);
		break;

	case CHOOSE_LANDLORD:
		if (data.at(0) == 0)  // for self player
			state = TURN_FINISH_STATE; // choose turn finished
		emit chooseLandLordSignal(data[1]);
		break;

	case SKIP_LANDLORD:
		if (data.at(0) == 0) // for self player
			state = TURN_FINISH_STATE; // choose turn finished
		emit skipLandLordSignal(data[1]);
		break;

	case DEAL_CARD:
		state = DEAL_CARD_STATE; // start dealing 
		emit dealCardSignal(data);
		break;

	case DEAL_LANDLORD:
		if (data.at(0) == 0)
		{
			state = DEAL_CARD_STATE; // start dealing landlord card
			emit dealLandLordCardSignal(data);
		}
		break;

	case LOSE_GAME:
		state = UNREADY_STATE; // lose game
		emit loseGameSignal();
		break;

	case WIN_GAME:
		state = UNREADY_STATE; // win game
		emit winGameSignal();
		break;

	case PLAYER_QUIT:
		state = UNREADY_STATE; // set player to unready
		emit quitSignal(data[0]);
		break;


	case TIME_OUT:
		if (state == PLAY_TURN_NO_SKIP_STATE || state == PLAY_TURN_STATE)
		{
			QByteArray data;
			data[0] = PLAY_CARD;    // complusorily play card ( or skip )
			tcpSocket->write(data); // send play card signal
			state = TURN_FINISH_STATE;
		}
		else if(state == CHOOSE_TURN_STATE)
		{
			QByteArray data;
			data[0] = SKIP_LANDLORD; // complusorily choose landlord 
			tcpSocket->write(data);  // send skip landlord signal
			state = TURN_FINISH_STATE;
		}

	default:
		return;
	}
}