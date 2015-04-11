/********************************************************************************
** Form generated from reading UI file 'AGSceneLoadingWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AGSCENELOADINGWIDGET_H
#define UI_AGSCENELOADINGWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AGSceneLoadingWidget
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QProgressBar *progressBar_2;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QWidget *AGSceneLoadingWidget)
    {
        if (AGSceneLoadingWidget->objectName().isEmpty())
            AGSceneLoadingWidget->setObjectName(QStringLiteral("AGSceneLoadingWidget"));
        AGSceneLoadingWidget->setWindowModality(Qt::ApplicationModal);
        AGSceneLoadingWidget->resize(372, 139);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AGSceneLoadingWidget->sizePolicy().hasHeightForWidth());
        AGSceneLoadingWidget->setSizePolicy(sizePolicy);
        AGSceneLoadingWidget->setMinimumSize(QSize(372, 139));
        AGSceneLoadingWidget->setMaximumSize(QSize(372, 139));
        AGSceneLoadingWidget->setStyleSheet(QLatin1String("background: rgb( 80, 80, 80 );\n"
"color: white; \n"
"\n"
""));
        verticalLayoutWidget = new QWidget(AGSceneLoadingWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 351, 125));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(16777215, 20));

        verticalLayout->addWidget(label_2);

        progressBar_2 = new QProgressBar(verticalLayoutWidget);
        progressBar_2->setObjectName(QStringLiteral("progressBar_2"));
        progressBar_2->setMaximumSize(QSize(16777215, 20));
        progressBar_2->setValue(0);

        verticalLayout->addWidget(progressBar_2);

        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(16777215, 20));

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        progressBar = new QProgressBar(verticalLayoutWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setMaximumSize(QSize(16777215, 20));
        progressBar->setValue(0);
        progressBar->setOrientation(Qt::Horizontal);
        progressBar->setTextDirection(QProgressBar::TopToBottom);

        horizontalLayout->addWidget(progressBar);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(AGSceneLoadingWidget);

        QMetaObject::connectSlotsByName(AGSceneLoadingWidget);
    } // setupUi

    void retranslateUi(QWidget *AGSceneLoadingWidget)
    {
        AGSceneLoadingWidget->setWindowTitle(QApplication::translate("AGSceneLoadingWidget", "Loading", 0));
        label_2->setText(QApplication::translate("AGSceneLoadingWidget", "Total progress", 0));
        label->setText(QApplication::translate("AGSceneLoadingWidget", "Loading ...", 0));
        pushButton->setText(QApplication::translate("AGSceneLoadingWidget", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class AGSceneLoadingWidget: public Ui_AGSceneLoadingWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AGSCENELOADINGWIDGET_H
