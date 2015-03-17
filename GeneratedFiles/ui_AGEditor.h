/********************************************************************************
** Form generated from reading UI file 'AGEditor.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AGEDITOR_H
#define UI_AGEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AGEditorClass
{
public:
    QAction *actionRedo;
    QAction *actionUndo;
    QAction *actionConnect;
    QAction *actionDisconnect;
    QAction *actionSelect;
    QAction *actionSelectAndMove;
    QAction *actionSelectAndRotate;
    QAction *actionSelectAndScale;
    QAction *actionSnapToggle;
    QAction *actionAngleSnapToggle;
    QAction *actionAbs;
    QAction *actionMirror;
    QAction *actionAlign;
    QAction *actionLayers;
    QAction *actionSchematicView;
    QAction *actionX;
    QAction *actionY;
    QAction *actionZ;
    QAction *actionXZ;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_as;
    QAction *actionNew;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *AGEditorClass)
    {
        if (AGEditorClass->objectName().isEmpty())
            AGEditorClass->setObjectName(QStringLiteral("AGEditorClass"));
        AGEditorClass->resize(1048, 605);
        AGEditorClass->setStyleSheet(QLatin1String("background: rgb( 80, 80, 80 );\n"
"color: white; \n"
"\n"
""));
        AGEditorClass->setIconSize(QSize(30, 30));
        AGEditorClass->setToolButtonStyle(Qt::ToolButtonFollowStyle);
        actionRedo = new QAction(AGEditorClass);
        actionRedo->setObjectName(QStringLiteral("actionRedo"));
        actionUndo = new QAction(AGEditorClass);
        actionUndo->setObjectName(QStringLiteral("actionUndo"));
        actionConnect = new QAction(AGEditorClass);
        actionConnect->setObjectName(QStringLiteral("actionConnect"));
        actionDisconnect = new QAction(AGEditorClass);
        actionDisconnect->setObjectName(QStringLiteral("actionDisconnect"));
        actionSelect = new QAction(AGEditorClass);
        actionSelect->setObjectName(QStringLiteral("actionSelect"));
        actionSelectAndMove = new QAction(AGEditorClass);
        actionSelectAndMove->setObjectName(QStringLiteral("actionSelectAndMove"));
        actionSelectAndRotate = new QAction(AGEditorClass);
        actionSelectAndRotate->setObjectName(QStringLiteral("actionSelectAndRotate"));
        actionSelectAndScale = new QAction(AGEditorClass);
        actionSelectAndScale->setObjectName(QStringLiteral("actionSelectAndScale"));
        actionSnapToggle = new QAction(AGEditorClass);
        actionSnapToggle->setObjectName(QStringLiteral("actionSnapToggle"));
        actionAngleSnapToggle = new QAction(AGEditorClass);
        actionAngleSnapToggle->setObjectName(QStringLiteral("actionAngleSnapToggle"));
        actionAbs = new QAction(AGEditorClass);
        actionAbs->setObjectName(QStringLiteral("actionAbs"));
        actionMirror = new QAction(AGEditorClass);
        actionMirror->setObjectName(QStringLiteral("actionMirror"));
        actionAlign = new QAction(AGEditorClass);
        actionAlign->setObjectName(QStringLiteral("actionAlign"));
        actionLayers = new QAction(AGEditorClass);
        actionLayers->setObjectName(QStringLiteral("actionLayers"));
        actionSchematicView = new QAction(AGEditorClass);
        actionSchematicView->setObjectName(QStringLiteral("actionSchematicView"));
        actionX = new QAction(AGEditorClass);
        actionX->setObjectName(QStringLiteral("actionX"));
        actionX->setCheckable(true);
        actionX->setChecked(false);
        actionX->setEnabled(true);
        QIcon icon;
        icon.addFile(QStringLiteral(":/AGEditor/ToolBar/tbX.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionX->setIcon(icon);
        actionY = new QAction(AGEditorClass);
        actionY->setObjectName(QStringLiteral("actionY"));
        actionZ = new QAction(AGEditorClass);
        actionZ->setObjectName(QStringLiteral("actionZ"));
        actionXZ = new QAction(AGEditorClass);
        actionXZ->setObjectName(QStringLiteral("actionXZ"));
        actionOpen = new QAction(AGEditorClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(AGEditorClass);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave_as = new QAction(AGEditorClass);
        actionSave_as->setObjectName(QStringLiteral("actionSave_as"));
        actionNew = new QAction(AGEditorClass);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        centralWidget = new QWidget(AGEditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        AGEditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(AGEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1048, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        AGEditorClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(AGEditorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        AGEditorClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_as);

        retranslateUi(AGEditorClass);

        QMetaObject::connectSlotsByName(AGEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *AGEditorClass)
    {
        AGEditorClass->setWindowTitle(QApplication::translate("AGEditorClass", "AGEditor", 0));
        actionRedo->setText(QApplication::translate("AGEditorClass", "Redo", 0));
        actionUndo->setText(QApplication::translate("AGEditorClass", "Undo", 0));
        actionConnect->setText(QApplication::translate("AGEditorClass", "Connect", 0));
        actionDisconnect->setText(QApplication::translate("AGEditorClass", "Disconnect", 0));
        actionSelect->setText(QApplication::translate("AGEditorClass", "Select", 0));
        actionSelectAndMove->setText(QApplication::translate("AGEditorClass", "Select and Move", 0));
        actionSelectAndRotate->setText(QApplication::translate("AGEditorClass", "Select and Rotate", 0));
        actionSelectAndScale->setText(QApplication::translate("AGEditorClass", "Select and Scale", 0));
        actionSnapToggle->setText(QApplication::translate("AGEditorClass", "Snap Toggle", 0));
        actionAngleSnapToggle->setText(QApplication::translate("AGEditorClass", "Angle Snap Toggle", 0));
        actionAbs->setText(QApplication::translate("AGEditorClass", "Abs", 0));
#ifndef QT_NO_TOOLTIP
        actionAbs->setToolTip(QApplication::translate("AGEditorClass", "Edit Named Selection Sets", 0));
#endif // QT_NO_TOOLTIP
        actionMirror->setText(QApplication::translate("AGEditorClass", "Mirror", 0));
        actionAlign->setText(QApplication::translate("AGEditorClass", "Align", 0));
        actionLayers->setText(QApplication::translate("AGEditorClass", "Layers", 0));
        actionSchematicView->setText(QApplication::translate("AGEditorClass", "Schematic View", 0));
#ifndef QT_NO_TOOLTIP
        actionSchematicView->setToolTip(QApplication::translate("AGEditorClass", "Schematic View", 0));
#endif // QT_NO_TOOLTIP
        actionX->setText(QApplication::translate("AGEditorClass", "X", 0));
        actionY->setText(QApplication::translate("AGEditorClass", "Y", 0));
        actionZ->setText(QApplication::translate("AGEditorClass", "Z", 0));
        actionXZ->setText(QApplication::translate("AGEditorClass", "XZ", 0));
        actionOpen->setText(QApplication::translate("AGEditorClass", "Open...", 0));
        actionSave->setText(QApplication::translate("AGEditorClass", "Save", 0));
        actionSave_as->setText(QApplication::translate("AGEditorClass", "Save as...", 0));
        actionNew->setText(QApplication::translate("AGEditorClass", "New", 0));
        menuFile->setTitle(QApplication::translate("AGEditorClass", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class AGEditorClass: public Ui_AGEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AGEDITOR_H
