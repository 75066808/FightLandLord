#include "window.h"


Window::Window(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	scene.setSceneRect(0, 0, 1, 1);

	QPixmap pim("Resources/background/background.jpg");

	scene.setBackgroundBrush(pim);

	initAll();

	connect(&button[ENTER_BTN], SIGNAL(clicked()), this, SLOT(connectBtnClick()));
	connect(&button[READY_BTN], SIGNAL(clicked()), this, SLOT(readyBtnClick()));
	connect(&button[QUIT_BTN], SIGNAL(clicked()), this, SLOT(disconnectBtnClick()));
	connect(&button[CHOOSE_LL_BTN], SIGNAL(clicked()), this, SLOT(chooseLandLordBtnClick()));
	connect(&button[SKIP_LL_BTN], SIGNAL(clicked()), this, SLOT(skipLandLordBtnClick()));
	connect(&button[PLAY_CARD_BTN], SIGNAL(clicked()), this, SLOT(playCardBtnClick()));
	connect(&button[SKIP_CARD_BTN], SIGNAL(clicked()), this, SLOT(skipCardBtnClick()));
	connect(&button[LOSE_BTN], SIGNAL(clicked()), this, SLOT(loseBtnClick()));
	connect(&button[WIN_BTN], SIGNAL(clicked()), this, SLOT(winBtnClick()));

}


Window::~Window()
{

}

void Window::initWindow(void)
{
	clearScreen();
	drawState(std::make_shared<Signal>());

	ui.graphicsView->setScene(&scene);
	ui.graphicsView->show();
}

void Window::windowNotificationSlot(std::shared_ptr<Signal> signal)
{
	//qDebug() << "View Model to Window";

	clearScreen();
	drawState(signal);
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



void Window::initAll(void)
{
	QString colorName[4];
	QString valueName[16];
	QString tempName("JQKA2");

	colorName[0] = "spade";
	colorName[1] = "heart";
	colorName[2] = "club";
	colorName[3] = "diamond";

	for (qint8 value = 3;value < 16;value++)
	{
		if (value >= 3 && value <= 10)
			valueName[value] = QString::number(value);
		else
			valueName[value] = tempName[value - 11];
	}

	for (qint32 color = 0;color < 4;color++)
	{
		for (qint32 value = 3;value <= 15;value++)
		{
			QString path;
			path.append("Resources/poker/");
			path.append(colorName[color]);
			path.append(valueName[value]);
			path.append(".jpg");
			initItem(cardItem[color][value], path, CARD_WIDTH, CARD_HEIGHT);
		}
	}

	QString path;
	path = "Resources/poker/joker2.jpg";
	initItem(cardItem[0][16], path, CARD_WIDTH, CARD_HEIGHT);
	path = "Resources/poker/joker1.jpg";
	initItem(cardItem[0][17], path, CARD_WIDTH, CARD_HEIGHT);
	path = "Resources/poker/card_back.png";
	initItem(landlordItem[0], path, CARD_WIDTH, CARD_HEIGHT);
	initItem(landlordItem[1], path, CARD_WIDTH, CARD_HEIGHT);
	initItem(landlordItem[2], path, CARD_WIDTH, CARD_HEIGHT);

	initItem(stateItem[READY_STATE][UPPERHOUSE], "Resources/state/readyState.png", STATE_WIDTH, STATE_HEIGHT);
	initItem(stateItem[READY_STATE][SELF], "Resources/state/readyState.png", STATE_WIDTH, STATE_HEIGHT);
	initItem(stateItem[READY_STATE][LOWERHOUSE], "Resources/state/readyState.png", STATE_WIDTH, STATE_HEIGHT);
	initItem(stateItem[SKIP_LL_STATE][UPPERHOUSE], "Resources/state/skipLLState.jpg", STATE_WIDTH, STATE_HEIGHT);
	initItem(stateItem[SKIP_LL_STATE][SELF], "Resources/state/skipLLState.jpg", STATE_WIDTH, STATE_HEIGHT);
	initItem(stateItem[SKIP_LL_STATE][LOWERHOUSE], "Resources/state/skipLLState.jpg", STATE_WIDTH, STATE_HEIGHT);
	initItem(stateItem[SKIP_CARD_STATE][UPPERHOUSE], "Resources/state/skipCardState.jpg", STATE_WIDTH, STATE_HEIGHT);
	initItem(stateItem[SKIP_CARD_STATE][SELF], "Resources/state/skipCardState.jpg", STATE_WIDTH, STATE_HEIGHT);
	initItem(stateItem[SKIP_CARD_STATE][LOWERHOUSE], "Resources/state/skipCardState.jpg", STATE_WIDTH, STATE_HEIGHT);
	initItem(stateItem[INVALID_STATE][UPPERHOUSE], "Resources/state/invalidState.jpg", STATE_WIDTH, STATE_HEIGHT);
	initItem(stateItem[INVALID_STATE][SELF], "Resources/state/invalidState.jpg", STATE_WIDTH, STATE_HEIGHT);
	initItem(stateItem[INVALID_STATE][LOWERHOUSE], "Resources/state/invalidState.jpg", STATE_WIDTH, STATE_HEIGHT);

	initItem(headItem[FARMER_HEAD][UPPERHOUSE], "Resources/head/farmer.png", HEAD_WIDTH, HEAD_HEIGHT);
	initItem(headItem[FARMER_HEAD][SELF], "Resources/head/farmer.png", HEAD_WIDTH, HEAD_HEIGHT);
	initItem(headItem[FARMER_HEAD][LOWERHOUSE], "Resources/head/farmer.png", HEAD_WIDTH, HEAD_HEIGHT);

	initItem(headItem[LANDLORD_HEAD][UPPERHOUSE], "Resources/head/landlord.png", HEAD_WIDTH, HEAD_HEIGHT);
	initItem(headItem[LANDLORD_HEAD][SELF], "Resources/head/landlord.png", HEAD_WIDTH, HEAD_HEIGHT);
	initItem(headItem[LANDLORD_HEAD][LOWERHOUSE], "Resources/head/landlord.png", HEAD_WIDTH, HEAD_HEIGHT);



	initButton(button[ENTER_BTN], "border-image: url(:/Button/Resources/button/connect.jpg);", BTN_WIDTH, BTN_HEIGHT);
	initButton(button[READY_BTN], "border-image: url(:/Button/Resources/button/ready.jpg);", BTN_WIDTH, BTN_HEIGHT);
	initButton(button[QUIT_BTN], "border-image: url(:/Button/Resources/button/disconnect.jpg);", BTN_WIDTH, BTN_HEIGHT);
	initButton(button[CHOOSE_LL_BTN], "border-image: url(:/Button/Resources/button/chooseLL.jpg);", BTN_WIDTH, BTN_HEIGHT);
	initButton(button[SKIP_LL_BTN], "border-image: url(:/Button/Resources/button/skipLL.jpg);", BTN_WIDTH, BTN_HEIGHT);
	initButton(button[PLAY_CARD_BTN], "border-image: url(:/Button/Resources/button/playCard.jpg);", BTN_WIDTH, BTN_HEIGHT);
	initButton(button[SKIP_CARD_BTN], "border-image: url(:/Button/Resources/button/skipCard.jpg);", BTN_WIDTH, BTN_HEIGHT);
	initButton(button[LOSE_BTN], "border-image: url(:/Button/Resources/button/lose.jpg);", BTN_WIDTH, BTN_HEIGHT);
	initButton(button[WIN_BTN], "border-image: url(:/Button/Resources/button/win.jpg);", BTN_WIDTH, BTN_HEIGHT);

	for (qint8 i = 0;i < NUM_NUM;i++)
	{
		QString path = "Resources/number/";
		path.append(QString::number(i));
		path.append(".png");
		initItem(numItem[i][UPPERHOUSE], path, NUM_WIDTH, NUM_HEIGHT);
		initItem(numItem[i][SELF], path, NUM_WIDTH, NUM_HEIGHT);
		initItem(numItem[i][LOWERHOUSE], path, NUM_WIDTH, NUM_HEIGHT);
	}
	
}

void Window::drawState(std::shared_ptr<Signal> signal)
{
	if (signal->signalType == DEAL_LANDLORD)
	{
		//landlordItem[0] = cardItem[landLordCard->cards[0].color][landLordCard->cards[0].i];
	}


	addParentItemToScene(cardSlot, SLOT_LEFT, SLOT_TOP, SLOT_WIDTH, SLOT_HEIGHT);
	addItemToScene(headItem[FARMER_HEAD][SELF], SELF_HEAD_LEFT, SELF_HEAD_TOP);

	if (*selfStatus != SELF_DIS_CONNECT)
	{
		if(*upperStatus != UPPER_DIS_CONNECT)
			addItemToScene(headItem[FARMER_HEAD][UPPERHOUSE], UPPER_HEAD_LEFT, UPPER_HEAD_TOP);
		if(*lowerStatus != LOWER_DIS_CONNECT)
			addItemToScene(headItem[FARMER_HEAD][LOWERHOUSE], LOWER_HEAD_RIGHT - HEAD_WIDTH, LOWER_HEAD_TOP);
		if (*selfStatus != SELF_CONNECT && *selfStatus != SELF_READY)
		{
			drawSelfCard();
			addItemToScene(numItem[*upperNum][UPPERHOUSE], UPPER_NUM_LEFT, UPPER_NUM_TOP);
			addItemToScene(numItem[*lowerNum][LOWERHOUSE], LOWER_NUM_RIGHT - NUM_WIDTH, LOWER_NUM_TOP);
			drawLandLordCard();
		}
	}

	switch (*selfStatus)
	{
	case SELF_DIS_CONNECT:
		setButtonNum(1);
		drawButton(button[ENTER_BTN]);
		break;
	case SELF_CONNECT:
		setButtonNum(2);
		drawButton(button[READY_BTN]);
		drawButton(button[QUIT_BTN]);
		break;
	case SELF_READY:
		addItemToScene(stateItem[READY_STATE][SELF], 0.5 - (STATE_WIDTH / 2), SELF_STATE_TOP);
		break;
	case SELF_CHOOSE_TURN:
		setButtonNum(2);
		drawButton(button[CHOOSE_LL_BTN]);
		drawButton(button[SKIP_LL_BTN]);
		break;
	case SELF_SKIP_LAND:
		addItemToScene(stateItem[SKIP_LL_STATE][SELF], 0.5 - (STATE_WIDTH / 2), SELF_STATE_TOP);
		break;
	case SELF_NOSKIP_TURN:
		setButtonNum(1);
		drawButton(button[PLAY_CARD_BTN]);
		if (!signal->valid)
			addItemToScene(stateItem[INVALID_STATE][SELF], 0.5 - (STATE_WIDTH / 2), SELF_STATE_TOP);
		break;
	case SELF_TURN:
		setButtonNum(2);
		drawButton(button[PLAY_CARD_BTN]);
		drawButton(button[SKIP_CARD_BTN]);
		if (!signal->valid)
			addItemToScene(stateItem[INVALID_STATE][SELF], 0.5 - (STATE_WIDTH / 2), SELF_STATE_TOP);
		break;
	case SELF_PLAY:
		drawSelfPlayCard();
		break;
	case SELF_SKIP:
		addItemToScene(stateItem[SKIP_CARD_STATE][SELF], 0.5 - (STATE_WIDTH / 2), SELF_STATE_TOP);
		break;	
	default:
		break;
	}


	switch(*upperStatus)
	{

	case UPPER_READY:
		if (*selfStatus != SELF_DIS_CONNECT)
			addItemToScene(stateItem[READY_STATE][UPPERHOUSE], UPPER_STATE_LEFT, UPPER_STATE_TOP);
		break;
	case UPPER_PLAY:
		drawUpperPlayCard();
		break;
	case UPPER_SKIP_LAND:
		addItemToScene(stateItem[SKIP_LL_STATE][UPPERHOUSE], UPPER_STATE_LEFT, UPPER_STATE_TOP);
		break;
	case UPPER_SKIP:
		addItemToScene(stateItem[SKIP_CARD_STATE][UPPERHOUSE], UPPER_STATE_LEFT, UPPER_STATE_TOP);
		break;
	default:
		break;

	}

	switch (*lowerStatus)
	{
	case LOWER_READY:
		if (*selfStatus != SELF_DIS_CONNECT)
			addItemToScene(stateItem[READY_STATE][LOWERHOUSE], LOWER_STATE_RIGHT - STATE_WIDTH, LOWER_STATE_TOP);
		break;
	case LOWER_PLAY:
		drawLowerPlayCard();
		break;
	case LOWER_SKIP_LAND:
		addItemToScene(stateItem[SKIP_LL_STATE][LOWERHOUSE], LOWER_STATE_RIGHT - STATE_WIDTH, LOWER_STATE_TOP);
		break;
	case LOWER_SKIP:
		addItemToScene(stateItem[SKIP_CARD_STATE][LOWERHOUSE], LOWER_STATE_RIGHT - STATE_WIDTH, LOWER_STATE_TOP);
		break;
	default:
		break;
	}

}

void Window::drawSelfCard(void)
{
	qreal top = ON_HAND_TOP;
	qreal left = 0.5 - ((*onHandNum - 1) * ON_HAND_INT + CARD_WIDTH / SLOT_WIDTH) / 2;

	for (qint32 i = 0; i < *onHandNum;i++)
	{
		qint32 color = onHandCard->cards[i].color;
		qint32 value = onHandCard->cards[i].i;
		if (onHandSelected->bools[i] != 1)
			addItemToParentItem(cardItem[color][value], cardSlot, left, top);
		else
			addItemToParentItem(cardItem[color][value], cardSlot, left, top - ON_HAND_RISE);
		left += ON_HAND_INT;
	}
}

void Window::drawSelfPlayCard(void)
{
	qreal top = SELF_PLAY_TOP;
	qreal left = 0.5 - ((*selfHandOutNum - 1) * SELF_PLAY_INT + CARD_WIDTH) / 2;

	for (qint32 i = 0; i < *selfHandOutNum;i++)
	{
		qint32 color = selfHandOut->cards[i].color;
		qint32 value = selfHandOut->cards[i].i;
		addItemToScene(cardItem[color][value], left, top);
		left += SELF_PLAY_INT;
	}
}

void Window::drawUpperPlayCard(void)
{
	qreal top = UPPER_PLAY_TOP;
	qreal left = UPPER_PLAY_LEFT;

	for (qint32 i = 0; i < *upperHandOutNum;i++)
	{
		qint32 color = upperHandOut->cards[i].color;
		qint32 value = upperHandOut->cards[i].i;
		addItemToScene(cardItem[color][value], left, top);
		left += UPPER_PLAY_INT;
	}

}

void Window::drawLowerPlayCard(void)
{
	qreal top = LOWER_PLAY_TOP;
	qreal left = LOWER_PLAY_RIGHT - CARD_WIDTH - (*lowerHandOutNum - 1)*LOWER_PLAY_INT;

	for (qint32 i = 0; i < *lowerHandOutNum;i++)
	{
		qint32 color = lowerHandOut->cards[i].color;
		qint32 value = lowerHandOut->cards[i].i;
		addItemToScene(cardItem[color][value], left, top);
		left += LOWER_PLAY_INT;
	}
}

void Window::drawBackGround(void)
{

}

void Window::setButtonNum(qint8 num)
{
	drawBtnNum = num;
}

void Window::drawButton(QPushButton &button)
{
	static qreal top;
	static qreal left; 
	static bool over = true;

	if (over)
	{
		top = BTN_TOP;
		left = 0.5 - (BTN_WIDTH / 2 + (qreal)(drawBtnNum - 1) / 2 * (BTN_INT + BTN_WIDTH));
		over = false;
	}
	else
	{
		left += BTN_INT + BTN_WIDTH;
	}

	addButtonToScene(button, left, top);
	drawBtnNum--;

	if (drawBtnNum == 0)
		over = true;
}

void Window::drawLandLordCard(void)
{
	qreal top = LL_TOP;
	qreal left = 0.5 - (2 * LL_INT + CARD_WIDTH) / 2;

	for (qint32 i = 0; i < 3;i++)
	{
		addItemToScene(landlordItem[i], left, top);
		left += SELF_PLAY_INT;
	}
}


void Window::clearScreen(void)
{
	auto itemList = scene.items();
	auto childList = cardSlot.childItems();

	for (qint32 i = 0;i < COLOR_NUM;i++)
	{
		for (qint32 j = 0;j < POKER_NUM;j++)
		{
			if (itemList.contains(&cardItem[i][j]))
				scene.removeItem(&cardItem[i][j]);
			if (childList.contains(&cardItem[i][j]))
				cardItem[i][j].setParentItem(nullptr);
		}
	}
			
		
	for (qint32 i = 0;i < STATE_NUM;i++)
		for (qint32 j = 0;j < PLAYER_NUM;j++)
			if (itemList.contains(&stateItem[i][j]))
				scene.removeItem(&stateItem[i][j]);

	for (qint32 i = 0;i < HEAD_NUM;i++)
		for (qint32 j = 0;j < PLAYER_NUM;j++)
			if (itemList.contains(&headItem[i][j]))
				scene.removeItem(&headItem[i][j]);


	for (qint32 i = 0;i < NUM_NUM;i++)
		for (qint32 j = 0;j < PLAYER_NUM;j++)
			if (itemList.contains(&numItem[i][j]))
				scene.removeItem(&numItem[i][j]);

	for (qint32 i = 0;i < PLAYER_NUM;i++)
		if (itemList.contains(&landlordItem[i]))
			scene.removeItem(&landlordItem[i]);

	for (qint32 i = 0;i < BTN_NUM;i++)
		button[i].setVisible(false);

	if (itemList.contains(&cardSlot))
		scene.removeItem(&cardSlot);
}



void Window::initItem(QGraphicsPixmapItem &item, QString path, qreal rw, qreal rh)
{
	item.setPixmap(QPixmap(path).scaled(rw*width(), rh*height()));
}

void Window::initButton(QPushButton &button, QString path, qreal rw, qreal rh)
{
	button.setStyleSheet(path);
	button.setGeometry(0, 0, rw*width(), rh*height());
	button.setVisible(false);
	scene.addWidget(&button);
}

void Window::addItemToScene(QGraphicsPixmapItem &item, qreal rx, qreal ry)
{
	item.setPos(rx*width(), ry*height());
	scene.addItem(&item);
}

void Window::addParentItemToScene(QGraphicsRectItem &parent, qreal rx, qreal ry, qreal rw, qreal rh)
{
	parent.setRect(QRectF(rx*width(), ry*height(), rw*width(), rh*height()));
	scene.addItem(&parent);
}

void Window::addItemToParentItem(QGraphicsPixmapItem &item, QGraphicsRectItem &parent, qreal rx, qreal ry)
{
	int x = parent.rect().left() + rx * parent.rect().width();
	int y = parent.rect().top() + ry * parent.rect().height();
	item.setPos(parent.rect().left() + rx * parent.rect().width(), parent.rect().top() + ry * parent.rect().height());
	item.setParentItem(&parent);
}

void Window::addButtonToScene(QPushButton &button, qreal rx, qreal ry)
{
	button.setGeometry(rx*width(), ry*height(), button.width(), button.height());
	button.setVisible(true);
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

void Window::loseBtnClick(void)
{

}

void Window::winBtnClick(void)
{

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
