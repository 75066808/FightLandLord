#include "window.h"


Window::Window(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	scene.setSceneRect(0, 0, 1, 1);

	initAll();

	connect(&button[ENTER_BTN], SIGNAL(clicked()), this, SLOT(connectBtnClick()));
	connect(&button[READY_BTN], SIGNAL(clicked()), this, SLOT(readyBtnClick()));
	connect(&button[QUIT_BTN], SIGNAL(clicked()), this, SLOT(disconnectBtnClick()));
	connect(&button[CHOOSE_LL_BTN], SIGNAL(clicked()), this, SLOT(chooseLandLordBtnClick()));
	
}

void Window::initWindow(void)
{
	clearScreen();
	addParentItemToScene(cardSlot, SLOT_LEFT, SLOT_TOP, SLOT_WIDTH, SLOT_HEIGHT);
	drawState();

	ui.graphicsView->setScene(&scene);
	ui.graphicsView->show();
}

void Window::windowNotificationSlot(std::shared_ptr<Signal> signal)
{
	qDebug() << "View Model to Window";

	clearScreen();
	addParentItemToScene(cardSlot, SLOT_LEFT, SLOT_TOP, SLOT_WIDTH, SLOT_HEIGHT);

	drawState();
	
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
	path = "Resources/poker/joker1.jpg";
	initItem(cardItem[0][16], path, CARD_WIDTH, CARD_HEIGHT);
	path = "Resources/poker/joker2.jpg";
	initItem(cardItem[0][17], path, CARD_WIDTH, CARD_HEIGHT);
	path = "Resources/poker/card_back.png";
	initItem(cardBackItem[0], path, CARD_WIDTH, CARD_HEIGHT);
	initItem(cardBackItem[1], path, CARD_WIDTH, CARD_HEIGHT);
	initItem(cardBackItem[2], path, CARD_WIDTH, CARD_HEIGHT);

	initItem(stateItem[READY_STATE][0], "Resources/state/readyState.jpg", STATE_WIDTH, STATE_HEIGHT);
	initItem(stateItem[READY_STATE][1], "Resources/state/readyState.jpg", STATE_WIDTH, STATE_HEIGHT);
	initItem(stateItem[READY_STATE][2], "Resources/state/readyState.jpg", STATE_WIDTH, STATE_HEIGHT);
	initItem(stateItem[SKIP_LL_STATE][0], "Resources/state/skipLLState.jpg", STATE_WIDTH, STATE_HEIGHT);
	initItem(stateItem[SKIP_LL_STATE][1], "Resources/state/skipLLState.jpg", STATE_WIDTH, STATE_HEIGHT);
	initItem(stateItem[SKIP_LL_STATE][2], "Resources/state/skipLLState.jpg", STATE_WIDTH, STATE_HEIGHT);
	initItem(stateItem[SKIP_CARD_STATE][0], "Resources/state/skipCardState.jpg", STATE_WIDTH, STATE_HEIGHT);
	initItem(stateItem[SKIP_CARD_STATE][1], "Resources/state/skipCardState.jpg", STATE_WIDTH, STATE_HEIGHT);
	initItem(stateItem[SKIP_CARD_STATE][2], "Resources/state/skipCardState.jpg", STATE_WIDTH, STATE_HEIGHT);

	initItem(headItem[FARMER_HEAD][0], "Resources/head/farmer.jpg", HEAD_WIDTH, HEAD_HEIGHT);
	initItem(headItem[FARMER_HEAD][1], "Resources/head/farmer.jpg", HEAD_WIDTH, HEAD_HEIGHT);
	initItem(headItem[FARMER_HEAD][2], "Resources/head/farmer.jpg", HEAD_WIDTH, HEAD_HEIGHT);

	initItem(headItem[LANDLORD_HEAD][0], "Resources/head/landlord.jpg", HEAD_WIDTH, HEAD_HEIGHT);
	initItem(headItem[LANDLORD_HEAD][1], "Resources/head/landlord.jpg", HEAD_WIDTH, HEAD_HEIGHT);
	initItem(headItem[LANDLORD_HEAD][2], "Resources/head/landlord.jpg", HEAD_WIDTH, HEAD_HEIGHT);


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
		initItem(numItem[i][0], path, NUM_WIDTH, NUM_HEIGHT);
		initItem(numItem[i][1], path, NUM_WIDTH, NUM_HEIGHT);
		initItem(numItem[i][2], path, NUM_WIDTH, NUM_HEIGHT);
	}
	
	
	ui.graphicsView->setStyleSheet("padding: 0px; border: 0px;");
}

void Window::drawState(void)
{
	//  0.5 - (btn_width / 2 + (n - 1) / 2 * (btn_int + btn_width))

	if (*selfStatus != SELF_DIS_CONNECT && *selfStatus != SELF_CONNECT && *selfStatus != SELF_READY)
	{
		drawSelfCard();
		addItemToScene(numItem[*upperNum][0], UPPER_NUM_LEFT, UPPER_NUM_TOP);
		addItemToScene(numItem[*lowerNum][1], LOWER_NUM_RIGHT - NUM_HEIGHT , LOWER_NUM_TOP);
		drawLandLordCard(true);
	}

	switch (*selfStatus)
	{
	case SELF_DIS_CONNECT:
		addItemToScene(headItem[FARMER_HEAD][1], SELF_HEAD_LEFT, SELF_HEAD_TOP);
		setButtonNum(1);
		drawButton(button[ENTER_BTN]);
		break;
	case SELF_CONNECT:
		addItemToScene(headItem[FARMER_HEAD][1], SELF_HEAD_LEFT, SELF_HEAD_TOP);
		setButtonNum(2);
		drawButton(button[READY_BTN]);
		drawButton(button[QUIT_BTN]);
		break;
	case SELF_READY:
		addItemToScene(headItem[FARMER_HEAD][1], SELF_HEAD_LEFT, SELF_HEAD_TOP);
		addItemToScene(stateItem[READY_STATE][1], 0.5 - (BTN_WIDTH / 2), BTN_TOP);
		break;
	case SELF_CHOOSE_TURN:
		addItemToScene(headItem[FARMER_HEAD][1], SELF_HEAD_LEFT, SELF_HEAD_TOP);
		setButtonNum(2);
		drawButton(button[CHOOSE_LL_BTN]);
		drawButton(button[SKIP_LL_BTN]);
		break;
	case SELF_NOT_CHOOSE_TURN:
		addItemToScene(headItem[FARMER_HEAD][1], SELF_HEAD_LEFT, SELF_HEAD_TOP);
		drawSelfCard();
		break;
	case SELF_NOSKIP_TURN:
		addItemToScene(headItem[FARMER_HEAD][1], SELF_HEAD_LEFT, SELF_HEAD_TOP);
		setButtonNum(1);
		drawButton(button[PLAY_CARD_BTN]);
		break;
	case SELF_TURN:
		addItemToScene(headItem[FARMER_HEAD][1], SELF_HEAD_LEFT, SELF_HEAD_TOP);
		setButtonNum(2);
		drawButton(button[PLAY_CARD_BTN]);
		drawButton(button[SKIP_CARD_BTN]);
	case SELF_PLAY:
		addItemToScene(headItem[FARMER_HEAD][1], SELF_HEAD_LEFT, SELF_HEAD_TOP);
		drawSelfPlayCard();
		break;
	case SELF_SKIP:
		addItemToScene(headItem[FARMER_HEAD][1], SELF_HEAD_LEFT, SELF_HEAD_TOP);
		addItemToScene(stateItem[SKIP_CARD_STATE][1], 0.5 - (BTN_WIDTH / 2), BTN_TOP);
		break;	
	default:
		break;
	}


	switch(*upperStatus)
	{
	case UPPER_DIS_CONNECT:
		break;
	case UPPER_CONNECT:
		if (*selfStatus != SELF_DIS_CONNECT)
			addItemToScene(headItem[FARMER_HEAD][0], UPPER_HEAD_LEFT, UPPER_HEAD_TOP);
		break;
	case UPPER_READY:
		if (*selfStatus != SELF_DIS_CONNECT)
		{
			addItemToScene(headItem[FARMER_HEAD][0], UPPER_HEAD_LEFT, UPPER_HEAD_TOP);
			addItemToScene(stateItem[READY_STATE][0], UPPER_STATE_LEFT, UPPER_STATE_TOP);
		}
		break;
	case UPPER_CHOOSE_TURN:
		addItemToScene(headItem[FARMER_HEAD][0], UPPER_HEAD_LEFT, UPPER_HEAD_TOP);
		break;
	case UPPER_NOT_CHOOSE_TURN:
		addItemToScene(headItem[FARMER_HEAD][0], UPPER_HEAD_LEFT, UPPER_HEAD_TOP);
		break;
	case UPPER_TURN:
		addItemToScene(headItem[FARMER_HEAD][0], UPPER_HEAD_LEFT, UPPER_HEAD_TOP);
		break;
	case UPPER_NOSKIP_TURN:
		addItemToScene(headItem[FARMER_HEAD][0], UPPER_HEAD_LEFT, UPPER_HEAD_TOP);
		break;
	case UPPER_PLAY:
		addItemToScene(headItem[FARMER_HEAD][0], UPPER_HEAD_LEFT, UPPER_HEAD_TOP);
		drawUpperPlayCard();
		break;
	case UPPER_SKIP:
		addItemToScene(headItem[FARMER_HEAD][0], UPPER_HEAD_LEFT, UPPER_HEAD_TOP);
		addItemToScene(stateItem[SKIP_CARD_STATE][0], UPPER_STATE_LEFT, UPPER_STATE_TOP);
		break;
	default:
		break;

	}

	switch (*lowerStatus)
	{
	case LOWER_DIS_CONNECT:
		break;
	case LOWER_CONNECT:
		if (*selfStatus != SELF_DIS_CONNECT)
			addItemToScene(headItem[FARMER_HEAD][2], LOWER_HEAD_RIGHT - HEAD_WIDTH, LOWER_HEAD_TOP);
		break;
	case LOWER_READY:
		if (*selfStatus != SELF_DIS_CONNECT)
		{
			addItemToScene(headItem[FARMER_HEAD][2], LOWER_HEAD_RIGHT - HEAD_WIDTH, LOWER_HEAD_TOP);
			addItemToScene(stateItem[READY_STATE][2], LOWER_STATE_RIGHT - STATE_WIDTH, LOWER_STATE_TOP);
		}
		break;
	case LOWER_CHOOSE_TURN:
		addItemToScene(headItem[FARMER_HEAD][2], LOWER_HEAD_RIGHT - HEAD_WIDTH, LOWER_HEAD_TOP);
		break;
	case LOWER_NOT_CHOOSE_TURN:
		addItemToScene(headItem[FARMER_HEAD][2], LOWER_HEAD_RIGHT - HEAD_WIDTH, LOWER_HEAD_TOP);
		break;
	case LOWER_TURN:
		addItemToScene(headItem[FARMER_HEAD][2], UPPER_HEAD_LEFT, UPPER_HEAD_TOP);
		break;
	case LOWER_NOSKIP_TURN:
		addItemToScene(headItem[FARMER_HEAD][2], UPPER_HEAD_LEFT, UPPER_HEAD_TOP);
		break;
	case LOWER_PLAY:
		addItemToScene(headItem[FARMER_HEAD][2], UPPER_HEAD_LEFT, UPPER_HEAD_TOP);
		drawLowerPlayCard();
		break;
	case LOWER_SKIP:
		addItemToScene(headItem[FARMER_HEAD][2], UPPER_HEAD_LEFT, UPPER_HEAD_TOP);
		addItemToScene(stateItem[SKIP_CARD_STATE][2], LOWER_STATE_RIGHT - STATE_WIDTH, LOWER_STATE_TOP);
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
			addItemToParentItem(cardItem[color][value], cardSlot, left, top + ON_HAND_RISE);
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
		addItemToParentItem(cardItem[color][value], cardSlot, left, top);
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
		addItemToParentItem(cardItem[color][value], cardSlot, left, top);
		left += UPPER_PLAY_INT;
	}

}

void Window::drawLowerPlayCard(void)
{
	qreal top = LOWER_PLAY_TOP;
	qreal right = LOWER_PLAY_RIGHT - CARD_WIDTH;

	for (qint32 i = 0; i < *upperHandOutNum;i++)
	{
		qint32 color = upperHandOut->cards[i].color;
		qint32 value = upperHandOut->cards[i].i;
		addItemToParentItem(cardItem[color][value], cardSlot, right, top);
		right -= LOWER_PLAY_INT;
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

void Window::drawLandLordCard(bool show)
{
	qreal top = LL_TOP;
	qreal left = 0.5 - (2 * LL_INT + CARD_WIDTH) / 2;

	for (qint32 i = 0; i < 3;i++)
	{
		addItemToParentItem(cardBackItem[i], cardSlot, left, top);
		left += SELF_PLAY_INT;
	}
}


void Window::clearScreen(void)
{
	auto itemList = scene.items();

	for (qint32 i = 0;i < itemList.size();i++)
		scene.removeItem(itemList[i]);

}



void Window::initItem(QGraphicsPixmapItem &item, QString path, qreal rw, qreal rh)
{
	item.setPixmap(QPixmap(path).scaled(rw*width(), rh*height()));
}

void Window::initButton(QPushButton &button, QString path, qreal rw, qreal rh)
{
	button.setStyleSheet(path);
	button.setGeometry(0, 0, rw*width(), rh*height());
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
	item.setPos(parent.rect().left() + rx * parent.rect().width(), parent.rect().top() + ry * parent.rect().height());
	item.setParentItem(&parent);
}

void Window::addButtonToScene(QPushButton &button, qreal rx, qreal ry)
{
	button.setGeometry(rx*width(), ry*height(), button.width(), button.height());
	scene.addWidget(&button);
}


void Window::connectBtnClick(void)
{
	qDebug() << "Connect button Click";

	std::shared_ptr<Signal> signal = std::make_shared<Signal>();

	signal->signalType = CONNECT;
	emit windowCommandSignal(signal);

	button[0].setFocus();
}

void Window::disconnectBtnClick(void)
{

}

void Window::readyBtnClick(void)
{
	qDebug() << "Ready button Click";
	std::shared_ptr<Signal> signal = std::make_shared<Signal>();

	signal->signalType = READY;
	emit windowCommandSignal(signal);
}


void Window::chooseLandLordBtnClick(void)
{
	qDebug() << "Choose LandLord button Click";
	std::shared_ptr<Signal> signal = std::make_shared<Signal>();

	signal->signalType = CHOOSE_LANDLORD;
	emit windowCommandSignal(signal);
}

void Window::skipLandLordBtnClick(void)
{
	qDebug() << "Skip LandLord button Click";
	std::shared_ptr<Signal> signal = std::make_shared<Signal>();

	signal->signalType = SKIP_LANDLORD;
	emit windowCommandSignal(signal);
}

void Window::playCardBtnClick(void)
{

}

void Window::skipCardBtnClick(void)
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
		int index = item->parentItem()->childItems().indexOf(item);
		qDebug() << "index of this item is " << index;
	}

	//event->
	//item->setPos(original_x, original_y - 30); */
	
}
