#include "window.h"


Window::Window(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(buttonClick()));
	
	scene.setSceneRect(0, 0, 1, 1);

	colorName[0] = "spade";
	colorName[1] = "heart";
	colorName[2] = "club";
	colorName[3] = "diamond";

	for (qint8 value = 3;value < 18;value++)
	{
		if (value >= 3 && value <= 10)
			valueName[value] = QString::number(value);
		else if (value == 11)
			valueName[value] = "J";
		else if (value == 12)
			valueName[value] = "Q";
		else if (value == 13)
			valueName[value] = "K";
		else if (value == 14)
			valueName[value] = "A";
		else if (value == 15)
			valueName[value] = "2";
		else if (value == 16)
			valueName[value] = "joker1";
		else
			valueName[value] = "joker2";
	}

	QPixmap pixmap;
	for (qint32 color = 0;color < 4;color++)
	{
		for (qint32 value = 3;value <= 15;value++)
		{
			QString path;
			path.append("poker_resource/");
			path.append(colorName[color]);
			path.append(valueName[value]);
			pixmap.load(path, "jpg");
			initItem(pixmap, cardItem[color][value], 0.1, 0.15);
		}
	}

	pixmap.load("poker_resource/joker1", "jpg");
	initItem(pixmap, cardItem[0][16], 0.1, 0.15);

	pixmap.load("poker_resource/joker2", "jpg");
	initItem(pixmap, cardItem[0][17], 0.1, 0.15);

	addParentItemToScene(cardSlot, 0.2, 0.6, 0.6, 0.2);

}






void Window::windowNotificationSlot(std::shared_ptr<Signal> signal)
{
	qDebug() << "View Model to Window";

	qreal x = 0.2;
	qreal y = 0.1;

	for (qint32 i = 0; i < *onHandNum;i++)
	{
		qint32 color = onHandCard->cards[i].color;
		qint32 value = onHandCard->cards[i].i;
		addItemToParentItem(cardItem[color][value], cardSlot, x, y);
		x += 0.03;
	}

	ui.graphicsView->setScene(&scene);
	ui.graphicsView->show();
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


void Window::initItem(QPixmap pixmap, QGraphicsPixmapItem &item, qreal rw, qreal rh)
{
	item.setPixmap(pixmap.scaled(rw*width(), rh*height()));
}

void Window::addParentItemToScene(QGraphicsRectItem &parent, qreal rx, qreal ry, qreal rw, qreal rh)
{
	parent.setRect(QRectF(rx*width(), ry*height(), rw*width(), rh*height()));
	//parent.setVisible(false);
	scene.addItem(&parent);
}

void Window::addItemToParentItem(QGraphicsPixmapItem &item, QGraphicsRectItem &parent, qreal rx, qreal ry)
{
	item.setPos(parent.rect().left() + rx*parent.rect().width(), parent.rect().top() + ry*parent.rect().height());
	item.setParentItem(&parent);
}


void Window::buttonClick(void)
{
	qDebug() << "Button Click" << endl;
	std::shared_ptr<Signal> signal = std::make_shared<Signal>();

	signal->signalType = CONNECT;
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
	int index = item->parentItem()->childItems().indexOf(item);

	//event->
	//item->setPos(original_x, original_y - 30);
	qDebug() << "index of this item is " << index;
}
