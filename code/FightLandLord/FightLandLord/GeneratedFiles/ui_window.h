/********************************************************************************
** Form generated from reading UI file 'window.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FightLandLordClass
{
public:
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QPushButton *btnShowCard;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *FightLandLordClass)
    {
        if (FightLandLordClass->objectName().isEmpty())
            FightLandLordClass->setObjectName(QString::fromUtf8("FightLandLordClass"));
        FightLandLordClass->resize(1870, 980);
        centralWidget = new QWidget(FightLandLordClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(10, 130, 1261, 791));
        btnShowCard = new QPushButton(centralWidget);
        btnShowCard->setObjectName(QString::fromUtf8("btnShowCard"));
        btnShowCard->setGeometry(QRect(560, 50, 131, 41));
        FightLandLordClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(FightLandLordClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1870, 26));
        FightLandLordClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(FightLandLordClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        FightLandLordClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(FightLandLordClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        FightLandLordClass->setStatusBar(statusBar);

        retranslateUi(FightLandLordClass);

        QMetaObject::connectSlotsByName(FightLandLordClass);
    } // setupUi

    void retranslateUi(QMainWindow *FightLandLordClass)
    {
        FightLandLordClass->setWindowTitle(QCoreApplication::translate("FightLandLordClass", "FightLandLord", nullptr));
        btnShowCard->setText(QCoreApplication::translate("FightLandLordClass", "Show Card", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FightLandLordClass: public Ui_FightLandLordClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H
