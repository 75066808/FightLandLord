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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FightLandLordClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *FightLandLordClass)
    {
        if (FightLandLordClass->objectName().isEmpty())
            FightLandLordClass->setObjectName(QString::fromUtf8("FightLandLordClass"));
        FightLandLordClass->resize(600, 400);
        menuBar = new QMenuBar(FightLandLordClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        FightLandLordClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(FightLandLordClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        FightLandLordClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(FightLandLordClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        FightLandLordClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(FightLandLordClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        FightLandLordClass->setStatusBar(statusBar);

        retranslateUi(FightLandLordClass);

        QMetaObject::connectSlotsByName(FightLandLordClass);
    } // setupUi

    void retranslateUi(QMainWindow *FightLandLordClass)
    {
        FightLandLordClass->setWindowTitle(QCoreApplication::translate("FightLandLordClass", "FightLandLord", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FightLandLordClass: public Ui_FightLandLordClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H
