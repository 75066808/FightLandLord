
#include "window.h"

Window::Window(QWidget *parent): QMainWindow(parent)
{
	ui.setupUi(this);
}


Window::~Window()
{

}

void Window::initWindow(void)
{
	scene.setSceneRect(0, 0, 1, 1);
	drawBackGround();

	buttonItems.initButtons(scene, width(), height());
	numItems.initNum(width(), height());
	cardItems.initCard(width(), height());
	headItems.initHead(width(), height());
	stateItems.initState(width(), height());

	connect(&buttonItems.getButton(ENTER_BTN), SIGNAL(clicked()), this, SLOT(connectBtnClick()));
	connect(&buttonItems.getButton(READY_BTN), SIGNAL(clicked()), this, SLOT(readyBtnClick()));
	connect(&buttonItems.getButton(QUIT_BTN), SIGNAL(clicked()), this, SLOT(disconnectBtnClick()));
	connect(&buttonItems.getButton(CHOOSE_LL_BTN), SIGNAL(clicked()), this, SLOT(chooseLandLordBtnClick()));
	connect(&buttonItems.getButton(SKIP_LL_BTN), SIGNAL(clicked()), this, SLOT(skipLandLordBtnClick()));
	connect(&buttonItems.getButton(PLAY_CARD_BTN), SIGNAL(clicked()), this, SLOT(playCardBtnClick()));
	connect(&buttonItems.getButton(SKIP_CARD_BTN), SIGNAL(clicked()), this, SLOT(skipCardBtnClick()));
	connect(&buttonItems.getButton(PROCEED_BTN), SIGNAL(clicked()), this, SLOT(proceedBtnClick()));
	connect(&buttonItems.getButton(END_BTN), SIGNAL(clicked()), this, SLOT(endBtnClick()));

	updateWindow(std::make_shared<Signal>());

	ui.graphicsView->setScene(&scene);
	ui.graphicsView->show();

}




void Window::updateWindow(std::shared_ptr<Signal> signal)
{
	qint32 width = this->width();
	qint32 height = this->height();

	if (signal->signalType == DEAL_LANDLORD)
		cardItems.setLandLord(width, height, landLordCard);
	if(signal->signalType == DEAL_CARD)
		cardItems.resetLandLord(width, height);


	if (*selfStatus != SELF_DIS_CONNECT)
	{
		if (*landLord == SELF)
			headItems.drawSelfHead(scene, LANDLORD_HEAD, width, height); // draw landlord head
		else
			headItems.drawSelfHead(scene, FARMER_HEAD, width, height); // draw farmer head
		if (*upperStatus != UPPER_DIS_CONNECT)
		{
			if (*landLord == UPPERHOUSE)
				headItems.drawUpperHead(scene, LANDLORD_HEAD, width, height); // draw landlord head
			else
				headItems.drawUpperHead(scene, FARMER_HEAD, width, height); // draw farmer head
		}

		if (*lowerStatus != LOWER_DIS_CONNECT)
		{
			if (*landLord == LOWERHOUSE)
				headItems.drawLowerHead(scene, LANDLORD_HEAD, width, height); // draw landlord head
			else
				headItems.drawLowerHead(scene, FARMER_HEAD, width, height); // draw landlord head
		}

		if (*selfStatus != SELF_CONNECT && *selfStatus != SELF_READY)
		{
			cardItems.drawSelfCard(scene, width, height, onHandNum, onHandCard, onHandSelected);
			numItems.drawUpperNum(scene, *upperNum, width, height);
			numItems.drawLowerNum(scene, *lowerNum, width, height);
			cardItems.drawLandLordCard(scene, width, height);
		}
	}

	switch (*selfStatus)
	{
	case SELF_DIS_CONNECT:
		buttonItems.setButtonNum(1);
		buttonItems.drawButton(scene, ENTER_BTN, width, height);
		break;
	case SELF_CONNECT:
		buttonItems.setButtonNum(2);
		buttonItems.drawButton(scene, READY_BTN, width, height);
		buttonItems.drawButton(scene, QUIT_BTN, width, height);
		break;
	case SELF_READY:
		stateItems.drawSelfState(scene, READY_STATE, width, height);
		break;
	case SELF_CHOOSE_TURN:
		buttonItems.setButtonNum(2);
		buttonItems.drawButton(scene, CHOOSE_LL_BTN, width, height);
		buttonItems.drawButton(scene, SKIP_LL_BTN, width, height);
		if (*timeSec != -1)
			numItems.drawSelfClock(scene, *timeSec, width, height);
		break;
	case SELF_SKIP_LAND:
		stateItems.drawSelfState(scene, SKIP_LL_STATE, width, height);
		break;
	case SELF_NOSKIP_TURN:
		buttonItems.setButtonNum(1);
		buttonItems.drawButton(scene, PLAY_CARD_BTN, width, height);
		if (!signal->valid)
			stateItems.drawSelfState(scene, INVALID_STATE, width, height);
		if (*timeSec != -1)
			numItems.drawSelfClock(scene, *timeSec, width, height);
		break;
	case SELF_TURN:
		buttonItems.setButtonNum(2);
		buttonItems.drawButton(scene, PLAY_CARD_BTN, width, height);
		buttonItems.drawButton(scene, SKIP_CARD_BTN, width, height);
		if (!signal->valid)
			stateItems.drawSelfState(scene, INVALID_STATE, width, height);
		if (*timeSec != -1)
			numItems.drawSelfClock(scene, *timeSec, width, height);
		break;
	case SELF_PLAY:
		cardItems.drawSelfPlayCard(scene, width, height, selfHandOutNum, selfHandOut);
		break;
	case SELF_SKIP:
		stateItems.drawSelfState(scene, SKIP_CARD_STATE, width, height);
		break;
	case SELF_LOSE:
		stateItems.drawSelfState(scene, LOSE_STATE, width, height);
		buttonItems.setButtonNum(2);
		buttonItems.drawButton(scene, PROCEED_BTN, width, height);
		buttonItems.drawButton(scene, END_BTN, width, height);
		break;
	case SELF_WIN:
		stateItems.drawSelfState(scene, WIN_STATE, width, height);
		buttonItems.setButtonNum(2);
		buttonItems.drawButton(scene, PROCEED_BTN, width, height);
		buttonItems.drawButton(scene, END_BTN, width, height);
		break;

	default:
		break;
	}


	switch (*upperStatus)
	{

	case UPPER_READY:
		if (*selfStatus != SELF_DIS_CONNECT)
			stateItems.drawUpperState(scene, READY_STATE, width, height);
		break;
	case UPPER_PLAY:
		cardItems.drawUpperPlayCard(scene, width, height, upperHandOutNum, upperHandOut);
		break;
	case UPPER_SKIP_LAND:
		stateItems.drawUpperState(scene, SKIP_LL_STATE, width, height);
		break;
	case UPPER_SKIP:
		stateItems.drawUpperState(scene, SKIP_CARD_STATE, width, height);
		break;
	case UPPER_CHOOSE_TURN:
	case UPPER_TURN:
	case UPPER_NOSKIP_TURN:
		if (*timeSec != -1)
			numItems.drawUpperClock(scene, *timeSec, width, height);
		break;
	default:
		break;

	}

	switch (*lowerStatus)
	{
	case LOWER_READY:
		if (*selfStatus != SELF_DIS_CONNECT)
			stateItems.drawLowerState(scene, READY_STATE, width, height);
		break;
	case LOWER_PLAY:
		cardItems.drawLowerPlayCard(scene, width, height, lowerHandOutNum, lowerHandOut);
		break;
	case LOWER_SKIP_LAND:
		stateItems.drawLowerState(scene, SKIP_LL_STATE, width, height);
		break;
	case LOWER_SKIP:
		stateItems.drawLowerState(scene, SKIP_CARD_STATE, width, height);
		break;
	case LOWER_CHOOSE_TURN:
	case LOWER_TURN:
	case LOWER_NOSKIP_TURN:
		if (*timeSec != -1)
			numItems.drawLowerClock(scene, *timeSec, width, height);
		break;
	default:
		break;
	}

}



void Window::clearWindow(void)
{
	buttonItems.clearButton();
	numItems.clearNum(scene);
	cardItems.clearCard(scene);
	headItems.clearHead(scene);
	stateItems.clearState(scene);
}


void Window::windowNotificationSlot(std::shared_ptr<Signal> signal)
{
	//qDebug() << "View Model to Window";

	clearWindow();
	updateWindow(signal);
}


void Window::resizeEvent(QResizeEvent* size)
{
	static qreal preWidth = width();
	static qreal preHeight = height();

	qreal curWidth = width();
	qreal curHeight = height();

	ui.graphicsView->scale(curWidth / preWidth, curHeight / preHeight);

	preWidth = curWidth;
	preHeight = curHeight;
}



void Window::drawBackGround(void)
{
	QPixmap pim("Resources/background/background.jpg");
	scene.setBackgroundBrush(pim);
}


void Window::connectBtnClick(void)
{
	//qDebug() << "Connect button Click";

	std::shared_ptr<Signal> signal = std::make_shared<Signal>();

	signal->signalType = CONNECT;
	emit windowCommandSignal(signal);
}

void Window::disconnectBtnClick(void)
{
	std::shared_ptr<Signal> signal = std::make_shared<Signal>();

	signal->signalType = DISCONNECT;
	emit windowCommandSignal(signal);
}

void Window::readyBtnClick(void)
{
	//qDebug() << "Ready button Click";
	std::shared_ptr<Signal> signal = std::make_shared<Signal>();

	signal->signalType = READY;
	emit windowCommandSignal(signal);
}


void Window::chooseLandLordBtnClick(void)
{
	//qDebug() << "Choose LandLord button Click";
	std::shared_ptr<Signal> signal = std::make_shared<Signal>();

	signal->signalType = CHOOSE_LANDLORD;
	emit windowCommandSignal(signal);
}

void Window::skipLandLordBtnClick(void)
{
	//qDebug() << "Skip LandLord button Click";
	std::shared_ptr<Signal> signal = std::make_shared<Signal>();

	signal->signalType = SKIP_LANDLORD;
	emit windowCommandSignal(signal);
}

void Window::playCardBtnClick(void)
{
	//qDebug() << "Play Card button Click";
	std::shared_ptr<Signal> signal = std::make_shared<Signal>();

	signal->signalType = PLAY_CARD;
	emit windowCommandSignal(signal);
}

void Window::skipCardBtnClick(void)
{
	//qDebug() << "Skip Card button Click";
	std::shared_ptr<Signal> signal = std::make_shared<Signal>();

	signal->signalType = SKIP_CARD;
	emit windowCommandSignal(signal);
}

void Window::proceedBtnClick(void)
{
	std::shared_ptr<Signal> signal = std::make_shared<Signal>();

	signal->signalType = CONT;
	emit windowCommandSignal(signal);
}

void Window::endBtnClick(void)
{
	qDebug() << "endBtn clicked." ;
	std::shared_ptr<Signal> signal = std::make_shared<Signal>();

	signal->signalType = DISCONNECT;
	emit windowCommandSignal(signal);
}


void customScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	QTransform transform;
	QGraphicsItem *item;

	QGraphicsScene::mousePressEvent(event);
	//qreal orignal_x = this->itemAt(event->scenePos(), transform)->pos().rx();
	//qreal orignal_y = this->itemAt(event->scenePos(), transform)->pos().ry();
	//this->itemAt(event->scenePos(), transform)->setPos(orignal_x, orignal_y - 30);
	item = this->itemAt(event->scenePos(), transform);
	//int indexOfCard = item->childItems().indexOf(//tems(Qt::AscendingOrder).indexOf(item);
	//item->setPos(event->scenePos().x(), event->scenePos().y() - 30);
	//qreal original_x = (qreal) item->pos().x()+1;
	//qreal original_y = (qreal) item->pos().y()+1;

	if (item && item->parentItem())
	{
		std::shared_ptr<Signal> signal = std::make_shared<Signal>();
		signal->signalType = SELECT;
		signal->cardTransfer[0] = item->parentItem()->childItems().indexOf(item);
		emit windowCommandSignal(signal);
		//qDebug() << "index of this item is " << index;
	}

	//event->
	//item->setPos(original_x, original_y - 30); */
	
}
