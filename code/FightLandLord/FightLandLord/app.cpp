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

void App::windowToAppSlot(Singal &signal)
{
	QByteArray data;

	switch (signal.signalType)
	{
	case ORIGIN:
		switch (signal.signalCotent)
		{
		case CONNECT:
			if (state == UNENTER_STATE)
			{
				tcpSocket->abort(); // disconnect current connection
				tcpSocket->connectToHost(QHostAddress(IP_NUM), PORT_NUM); // send connect request
			}
			break;
		case DISCONNECT:
			if (state != UNENTER_STATE)
			{
				tcpSocket->disconnectFromHost(); // disconnect from host
			}
			break;
		case READY:
			if (state == UNREADY_STATE) // in unready state
			{
				data[0] = BROADCAST;
				data[1] = READY;
				tcpSocket->write(data); // broadcast ready signal
			}
			break;
		case CHOOSE_LANDLORD:
			if (state == CHOOSE_TURN_STATE) // in choose turn
			{
				data[0] = BROADCAST;
				data[1] = CHOOSE_LANDLORD;
				tcpSocket->write(data);
			}
			break;
		case SKIP_LANDLORD:
			if (state == CHOOSE_TURN_STATE) // in choose turn
			{
				data[0] = BROADCAST;
				data[1] = SKIP_LANDLORD;
				tcpSocket->write(data); // broadcast skip landlord
			}
			break;
		case PLAY_CARD:
			if (state == PLAY_TURN_NO_SKIP_STATE || state == PLAY_TURN_STATE) // in play turn
			{
				signal.signalType = CHECK;
				emit appToViewModelSignal(signal); // send to viewmodel to check
			}
			break;
		case SKIP_CARD:
			if (state == PLAY_TURN_STATE) // in play turn ( enable skipping )
			{
				signal.signalType = CHECK;
				emit appToViewModelSignal(signal); // send to viewmodel to check
			}
			break;
		default:
			return;
		}
		break;

	case MODIFY_FEEDBACK:
		if (signal.playerType == SELF)
		{
			switch (signal.signalCotent)
			{
			case CONNECT_SUCCESS:
				state = UNREADY_STATE;
				break;
			case READY:
				state = READY_STATE;
				break;
			case PLAY_TURN:
				state = PLAY_TURN_STATE;
				break;
			case PLAY_TURN_NO_SKIP:
				state = PLAY_PRE_NO_SKIP_STATE;
				break;
			case CHOOSE_TURN:
				state = CHOOSE_TURN_STATE;
				break;
			case LOSE_GAME:
			case WIN_GAME:
			case PLAYER_QUIT:
				state = UNREADY_STATE;
				break;
			default:
				return;
			}
		}
		

		data[0] = ALL_FINISH;
		data[1] = signal.signalCotent;
		tcpSocket->write(data); // signal chain is finished
		break;

	default:
		return;
	}
}


void App::viewModelToAppSlot(Singal &signal)
{
	QByteArray data;

	switch (signal.signalType)
	{
	case CHECK_FEEDBACK:
		if (signal.legal == 1) // legal
		{
			data[0] = BROADCAST;
			data[1] = signal.signalCotent;
			tcpSocket->write(data); // broadcast signal
		}
		break;
	case MODIFY_FEEDBACK:
		signal.signalType = MODIFY;
		emit appToWindowSignal(signal); // send modify signal to window
		break;
	default:
		return;
	}
}





void App::readServerData(void)
{
	Singal signal;
	QByteArray data = tcpSocket->readAll(); // read from server

	signal.signalType = MODIFY;
	signal.playerType = data[0];
	signal.signalCotent = data[1];

	switch (data.at(1)) // check signal type
	{
	case CONNECT_SUCCESS:
		if (data.at(0) == SELF) // for self player
			state = ENTER_FINISH_STATE; // enter the room	
		emit appToViewModelSignal(signal);
		break;

	case CONNECT_FAILED:
		emit appToViewModelSignal(signal);
		break;

	case READY:
		if (data.at(0) == SELF) // for self player
			state = READY_FINISH_STATE; // ready for play
		emit appToViewModelSignal(signal);
		break;

	case PLAY_TURN:
		if (data.at(0) == SELF) // for self player
			state = PLAY_PRE_STATE; // in play turn ( can skip )
		emit appToViewModelSignal(signal);
		break;

	case PLAY_TURN_NO_SKIP:
		if (data.at(0) == SELF) // for self player
			state = PLAY_PRE_NO_SKIP_STATE; // in play turn ( can't skip )
		emit appToViewModelSignal(signal);
		break;

	case CHOOSE_TURN:
		if (data.at(0) == SELF) // for self player
			state = CHOOSE_PRE_STATE; // in choose turn
		emit appToViewModelSignal(signal);
		break;

	case PLAY_CARD:
		if (data.at(0) == SELF) // for self player
			state = TURN_FINISH_STATE; // play turn finished
		emit appToViewModelSignal(signal);
		break;

	case SKIP_CARD:
		if (data.at(0) == SELF) // for self player
			state = TURN_FINISH_STATE; // play turn finished
		emit appToViewModelSignal(signal);
		break;

	case CHOOSE_LANDLORD:
		if (data.at(0) == SELF)  // for self player
			state = TURN_FINISH_STATE; // choose turn finished
		emit appToViewModelSignal(signal);
		break;

	case SKIP_LANDLORD:
		if (data.at(0) == SELF) // for self player
			state = TURN_FINISH_STATE; // choose turn finished
		emit appToViewModelSignal(signal);
		break;

	case DEAL_CARD:
		emit appToViewModelSignal(signal); // start dealing 
		break;

	case DEAL_LANDLORD:
		if (data.at(0) == SELF)
			emit appToViewModelSignal(signal); // start dealing landlord card
		break;

	case LOSE_GAME:
		state = ENTER_FINISH_STATE; // lose game
		emit appToViewModelSignal(signal);
		break;

	case WIN_GAME:
		state = ENTER_FINISH_STATE; // win game
		emit appToViewModelSignal(signal);
		break;

	case PLAYER_QUIT:
		state = ENTER_FINISH_STATE; // set player to unready
		emit appToViewModelSignal(signal);
		break;


	case TIME_OUT:
		switch (state)
		{
		case PLAY_TURN_STATE:
			state = TURN_FINISH_STATE;
			signal.playerType = SELF;
			signal.signalCotent = COM_PLAY;
			emit appToViewModelSignal(signal); // compulsory to play ( can skip )

		case PLAY_TURN_NO_SKIP_STATE:
			state = TURN_FINISH_STATE;
			signal.playerType = SELF;
			signal.signalCotent = COM_PLAY_NO_SKIP;
			emit appToViewModelSignal(signal); // compulsory to play ( no skip )

		case CHOOSE_TURN_STATE:
			state = TURN_FINISH_STATE;
			signal.playerType = SELF;
			signal.signalCotent = COM_CHOOSE;
			emit appToViewModelSignal(signal); // compulsory to choose

		default:
			return;

		}
	default:
		return;
	}
}