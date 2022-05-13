/********************************************************************************
** Form generated from reading UI file 'fs01_qt.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FS01_QT_H
#define UI_FS01_QT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_fs01_qt
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *fs01_qt)
    {
        if (fs01_qt->objectName().isEmpty())
            fs01_qt->setObjectName(QStringLiteral("fs01_qt"));
        fs01_qt->resize(400, 300);
        menuBar = new QMenuBar(fs01_qt);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        fs01_qt->setMenuBar(menuBar);
        mainToolBar = new QToolBar(fs01_qt);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        fs01_qt->addToolBar(mainToolBar);
        centralWidget = new QWidget(fs01_qt);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        fs01_qt->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(fs01_qt);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        fs01_qt->setStatusBar(statusBar);

        retranslateUi(fs01_qt);

        QMetaObject::connectSlotsByName(fs01_qt);
    } // setupUi

    void retranslateUi(QMainWindow *fs01_qt)
    {
        fs01_qt->setWindowTitle(QApplication::translate("fs01_qt", "fs01_qt", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class fs01_qt: public Ui_fs01_qt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FS01_QT_H
