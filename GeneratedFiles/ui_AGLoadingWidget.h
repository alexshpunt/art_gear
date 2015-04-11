/********************************************************************************
** Form generated from reading UI file 'AGLoadingWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AGLOADINGWIDGET_H
#define UI_AGLOADINGWIDGET_H

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

class Ui_AGLoadingWidget
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QWidget *AGLoadingWidget)
    {
        if (AGLoadingWidget->objectName().isEmpty())
            AGLoadingWidget->setObjectName(QStringLiteral("AGLoadingWidget"));
        AGLoadingWidget->setWindowModality(Qt::ApplicationModal);
        AGLoadingWidget->resize(369, 118);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AGLoadingWidget->sizePolicy().hasHeightForWidth());
        AGLoadingWidget->setSizePolicy(sizePolicy);
        AGLoadingWidget->setMinimumSize(QSize(369, 118));
        AGLoadingWidget->setMaximumSize(QSize(369, 118));
        AGLoadingWidget->setFocusPolicy(Qt::StrongFocus);
        AGLoadingWidget->setStyleSheet(QLatin1String("background: rgb( 80, 80, 80 );\n"
"color: white; \n"
"\n"
""));
        verticalLayoutWidget = new QWidget(AGLoadingWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 351, 101));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
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


        retranslateUi(AGLoadingWidget);

        QMetaObject::connectSlotsByName(AGLoadingWidget);
    } // setupUi

    void retranslateUi(QWidget *AGLoadingWidget)
    {
        AGLoadingWidget->setWindowTitle(QApplication::translate("AGLoadingWidget", "Loading", 0));
        label->setText(QApplication::translate("AGLoadingWidget", "Loading ...", 0));
        pushButton->setText(QApplication::translate("AGLoadingWidget", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class AGLoadingWidget: public Ui_AGLoadingWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AGLOADINGWIDGET_H
