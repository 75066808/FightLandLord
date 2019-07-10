#include "window.h"


Window::Window(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.btnShowCard, SIGNAL(clicked()), this, SLOT(buttonClick()));
}

void Window::setCurrentCardsInHand(const qint8* cards)
{
	currentCardsInHand = cards;
}


void Window::windowNotificationSlot(std::shared_ptr<Signal> signal)
{
	qDebug() << "View Model to Window";
	QPixmap *cardTempPixmap = new QPixmap();

	QGraphicsScene *Scene = new QGraphicsScene();

	qreal init_x = 10;
	qreal init_y = 10;

	//int cardNum = 15;

	size_t cardCnt = 0;

	Scene->setSceneRect(300, -100, 1, 1);

	addHandInScene(cardTempPixmap, Scene);

	//addCardInScene(init_x + i*20, init_y, cardTempPixmap, Scene);


	ui.graphicsView->setScene(Scene);

	ui.graphicsView->show();
	
}

void Window::addCardInScene(qreal x, qreal y, QPixmap* cardTempPixmap, QGraphicsScene* Scene)
{
	//cardTempPixmap->load("poker_resource/joker1", "jpg");
	Scene->addPixmap(*cardTempPixmap)->setPos(x, y);

}

void Window::buttonClick(void)
{
	qDebug() << "Button Click" << endl;
	std::shared_ptr<Signal> signal = std::make_shared<Signal>();

	signal->signalType = CONNECT;
	emit windowCommandSignal(signal);
}

void Window::addHandInScene(QPixmap *cardTempPixmap, QGraphicsScene *Scene)
{
	qreal init_x = 10;
	qreal init_y = 10;

	size_t cardCnt = 0;

	for (size_t i = 3; i < 18; i++)
	{
		if (currentCardsInHand[i] == 0)
			continue;
		else
		{
			switch (i)
			{
			case 3:

				for (size_t j = 0; j < currentCardsInHand[i]; j++)
				{
					cardTempPixmap->load("poker_resource/club3", "jpg");
					addCardInScene(init_x + (cardCnt - 1 + j) * 20, init_y, cardTempPixmap, Scene);
				}
				cardCnt += currentCardsInHand[i];
				break;
			case 4:

				for (size_t j = 0; j < currentCardsInHand[i]; j++)
				{
					cardTempPixmap->load("poker_resource/club4", "jpg");
					addCardInScene(init_x + (cardCnt - 1 + j) * 20, init_y, cardTempPixmap, Scene);
				}
				cardCnt += currentCardsInHand[i];
				break;
			case 5:

				for (size_t j = 0; j < currentCardsInHand[i]; j++)
				{
					cardTempPixmap->load("poker_resource/club5", "jpg");
					addCardInScene(init_x + (cardCnt - 1 + j) * 20, init_y, cardTempPixmap, Scene);
				}
				cardCnt += currentCardsInHand[i];
				break;
			case 6:
				for (size_t j = 0; j < currentCardsInHand[i]; j++)
				{
					cardTempPixmap->load("poker_resource/club6", "jpg");
					addCardInScene(init_x + (cardCnt - 1 + j) * 20, init_y, cardTempPixmap, Scene);
				}
				cardCnt += currentCardsInHand[i];
				break;
			case 7:

				for (size_t j = 0; j < currentCardsInHand[i]; j++)
				{
					cardTempPixmap->load("poker_resource/club7", "jpg");
					addCardInScene(init_x + (cardCnt - 1 + j) * 20, init_y, cardTempPixmap, Scene);
				}
				cardCnt += currentCardsInHand[i];
				break;
			case 8:

				for (size_t j = 0; j < currentCardsInHand[i]; j++)
				{
					cardTempPixmap->load("poker_resource/club8", "jpg");
					addCardInScene(init_x + (cardCnt - 1 + j) * 20, init_y, cardTempPixmap, Scene);
				}
				cardCnt += currentCardsInHand[i];
				break;
			case 9:

				for (size_t j = 0; j < currentCardsInHand[i]; j++)
				{
					cardTempPixmap->load("poker_resource/club9", "jpg");
					addCardInScene(init_x + (cardCnt - 1 + j) * 20, init_y, cardTempPixmap, Scene);
				}
				cardCnt += currentCardsInHand[i];
				break;
			case 10:
				for (size_t j = 0; j < currentCardsInHand[i]; j++)
				{
					cardTempPixmap->load("poker_resource/club10", "jpg");
					addCardInScene(init_x + (cardCnt - 1 + j) * 20, init_y, cardTempPixmap, Scene);
				}
				cardCnt += currentCardsInHand[i];
				break;
			case 11:

				for (size_t j = 0; j < currentCardsInHand[i]; j++)
				{
					cardTempPixmap->load("poker_resource/clubJ", "jpg");
					addCardInScene(init_x + (cardCnt - 1 + j) * 20, init_y, cardTempPixmap, Scene);
				}
				cardCnt += currentCardsInHand[i];
				break;
			case 12:
				for (size_t j = 0; j < currentCardsInHand[i]; j++)
				{
					cardTempPixmap->load("poker_resource/clubQ", "jpg");
					addCardInScene(init_x + (cardCnt - 1 + j) * 20, init_y, cardTempPixmap, Scene);
				}
				cardCnt += currentCardsInHand[i];
				break;
			case 13:
				for (size_t j = 0; j < currentCardsInHand[i]; j++)
				{
					cardTempPixmap->load("poker_resource/clubK", "jpg");
					addCardInScene(init_x + (cardCnt - 1 + j) * 20, init_y, cardTempPixmap, Scene);
				}
				cardCnt += currentCardsInHand[i];
				break;
			case 14:
				for (size_t j = 0; j < currentCardsInHand[i]; j++)
				{
					cardTempPixmap->load("poker_resource/clubA", "jpg");
					addCardInScene(init_x + (cardCnt - 1 + j) * 20, init_y, cardTempPixmap, Scene);
				}
				cardCnt += currentCardsInHand[i];
				break;
			case 15:
				for (size_t j = 0; j < currentCardsInHand[i]; j++)
				{
					cardTempPixmap->load("poker_resource/club2", "jpg");
					addCardInScene(init_x + (cardCnt - 1 + j) * 20, init_y, cardTempPixmap, Scene);
				}
				cardCnt += currentCardsInHand[i];
				break;
			case 16:
				for (size_t j = 0; j < currentCardsInHand[i]; j++)
				{
					cardTempPixmap->load("poker_resource/joker1", "jpg");
					addCardInScene(init_x + (cardCnt - 1 + j) * 20, init_y, cardTempPixmap, Scene);
				}
				cardCnt += currentCardsInHand[i];
				break;
			case 17:
				for (size_t j = 0; j < currentCardsInHand[i]; j++)
				{
					cardTempPixmap->load("poker_resource/joker2", "jpg");
					addCardInScene(init_x + (cardCnt - 1 + j) * 20, init_y, cardTempPixmap, Scene);
				}
				cardCnt += currentCardsInHand[i];
				break;
			default:
				break;
			}
		}
	}
}
