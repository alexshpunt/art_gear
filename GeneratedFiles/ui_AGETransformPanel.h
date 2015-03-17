/********************************************************************************
** Form generated from reading UI file 'AGETransformPanel.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AGETRANSFORMPANEL_H
#define UI_AGETRANSFORMPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ui_AGTransformPanel
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *lineLayoutPos;
    QLabel *lblPosX;
    QDoubleSpinBox *spinBoxPosX;
    QLabel *lblPosY;
    QDoubleSpinBox *spinBoxPosY;
    QLabel *lblPosZ;
    QDoubleSpinBox *spinBoxPosZ;
    QFrame *line;
    QLabel *label_2;
    QHBoxLayout *lineLayoutRot;
    QLabel *lblRotX;
    QDoubleSpinBox *spinBoxRotX;
    QLabel *lblRotY;
    QDoubleSpinBox *spinBoxRotY;
    QLabel *lblRotZ;
    QDoubleSpinBox *spinBoxRotZ;
    QFrame *line_2;
    QLabel *label_3;
    QHBoxLayout *lineLayoutScale;
    QLabel *lblScaleX;
    QDoubleSpinBox *spinBoxScaleX;
    QLabel *lblScaleY;
    QDoubleSpinBox *spinBoxScaleY;
    QLabel *lblScaleZ;
    QDoubleSpinBox *spinBoxScaleZ;
    QFrame *line_3;

    void setupUi(QWidget *ui_AGTransformPanel)
    {
        if (ui_AGTransformPanel->objectName().isEmpty())
            ui_AGTransformPanel->setObjectName(QStringLiteral("ui_AGTransformPanel"));
        ui_AGTransformPanel->setWindowModality(Qt::NonModal);
        ui_AGTransformPanel->resize(349, 178);
        ui_AGTransformPanel->setMinimumSize(QSize(349, 178));
        ui_AGTransformPanel->setMaximumSize(QSize(349, 178));
        verticalLayoutWidget = new QWidget(ui_AGTransformPanel);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 331, 164));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        lineLayoutPos = new QHBoxLayout();
        lineLayoutPos->setObjectName(QStringLiteral("lineLayoutPos"));
        lblPosX = new QLabel(verticalLayoutWidget);
        lblPosX->setObjectName(QStringLiteral("lblPosX"));
        lblPosX->setMaximumSize(QSize(15, 16777215));

        lineLayoutPos->addWidget(lblPosX);

        spinBoxPosX = new QDoubleSpinBox(verticalLayoutWidget);
        spinBoxPosX->setObjectName(QStringLiteral("spinBoxPosX"));
        spinBoxPosX->setMinimum(-64000);
        spinBoxPosX->setMaximum(64000);
        spinBoxPosX->setSingleStep(0.1);

        lineLayoutPos->addWidget(spinBoxPosX);

        lblPosY = new QLabel(verticalLayoutWidget);
        lblPosY->setObjectName(QStringLiteral("lblPosY"));
        lblPosY->setMaximumSize(QSize(15, 16777215));

        lineLayoutPos->addWidget(lblPosY);

        spinBoxPosY = new QDoubleSpinBox(verticalLayoutWidget);
        spinBoxPosY->setObjectName(QStringLiteral("spinBoxPosY"));
        spinBoxPosY->setMinimum(-64000);
        spinBoxPosY->setMaximum(64000);
        spinBoxPosY->setSingleStep(0.1);
        spinBoxPosY->setValue(0);

        lineLayoutPos->addWidget(spinBoxPosY);

        lblPosZ = new QLabel(verticalLayoutWidget);
        lblPosZ->setObjectName(QStringLiteral("lblPosZ"));
        lblPosZ->setMaximumSize(QSize(15, 16777215));

        lineLayoutPos->addWidget(lblPosZ);

        spinBoxPosZ = new QDoubleSpinBox(verticalLayoutWidget);
        spinBoxPosZ->setObjectName(QStringLiteral("spinBoxPosZ"));
        spinBoxPosZ->setMinimum(-64000);
        spinBoxPosZ->setMaximum(64000);
        spinBoxPosZ->setSingleStep(0.1);

        lineLayoutPos->addWidget(spinBoxPosZ);


        verticalLayout->addLayout(lineLayoutPos);

        line = new QFrame(verticalLayoutWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        lineLayoutRot = new QHBoxLayout();
        lineLayoutRot->setObjectName(QStringLiteral("lineLayoutRot"));
        lblRotX = new QLabel(verticalLayoutWidget);
        lblRotX->setObjectName(QStringLiteral("lblRotX"));
        lblRotX->setMaximumSize(QSize(15, 16777215));

        lineLayoutRot->addWidget(lblRotX);

        spinBoxRotX = new QDoubleSpinBox(verticalLayoutWidget);
        spinBoxRotX->setObjectName(QStringLiteral("spinBoxRotX"));
        spinBoxRotX->setMinimum(-64000);
        spinBoxRotX->setMaximum(64000);
        spinBoxRotX->setSingleStep(0.1);

        lineLayoutRot->addWidget(spinBoxRotX);

        lblRotY = new QLabel(verticalLayoutWidget);
        lblRotY->setObjectName(QStringLiteral("lblRotY"));
        lblRotY->setMaximumSize(QSize(15, 16777215));

        lineLayoutRot->addWidget(lblRotY);

        spinBoxRotY = new QDoubleSpinBox(verticalLayoutWidget);
        spinBoxRotY->setObjectName(QStringLiteral("spinBoxRotY"));
        spinBoxRotY->setMinimum(-64000);
        spinBoxRotY->setMaximum(64000);
        spinBoxRotY->setSingleStep(0.1);
        spinBoxRotY->setValue(0);

        lineLayoutRot->addWidget(spinBoxRotY);

        lblRotZ = new QLabel(verticalLayoutWidget);
        lblRotZ->setObjectName(QStringLiteral("lblRotZ"));
        lblRotZ->setMaximumSize(QSize(15, 16777215));

        lineLayoutRot->addWidget(lblRotZ);

        spinBoxRotZ = new QDoubleSpinBox(verticalLayoutWidget);
        spinBoxRotZ->setObjectName(QStringLiteral("spinBoxRotZ"));
        spinBoxRotZ->setMinimum(-64000);
        spinBoxRotZ->setMaximum(64000);
        spinBoxRotZ->setSingleStep(0.1);

        lineLayoutRot->addWidget(spinBoxRotZ);


        verticalLayout->addLayout(lineLayoutRot);

        line_2 = new QFrame(verticalLayoutWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        lineLayoutScale = new QHBoxLayout();
        lineLayoutScale->setObjectName(QStringLiteral("lineLayoutScale"));
        lblScaleX = new QLabel(verticalLayoutWidget);
        lblScaleX->setObjectName(QStringLiteral("lblScaleX"));
        lblScaleX->setMaximumSize(QSize(15, 16777215));

        lineLayoutScale->addWidget(lblScaleX);

        spinBoxScaleX = new QDoubleSpinBox(verticalLayoutWidget);
        spinBoxScaleX->setObjectName(QStringLiteral("spinBoxScaleX"));
        spinBoxScaleX->setMinimum(-64000);
        spinBoxScaleX->setMaximum(64000);
        spinBoxScaleX->setSingleStep(0.1);

        lineLayoutScale->addWidget(spinBoxScaleX);

        lblScaleY = new QLabel(verticalLayoutWidget);
        lblScaleY->setObjectName(QStringLiteral("lblScaleY"));
        lblScaleY->setMaximumSize(QSize(15, 16777215));

        lineLayoutScale->addWidget(lblScaleY);

        spinBoxScaleY = new QDoubleSpinBox(verticalLayoutWidget);
        spinBoxScaleY->setObjectName(QStringLiteral("spinBoxScaleY"));
        spinBoxScaleY->setMinimum(-64000);
        spinBoxScaleY->setMaximum(64000);
        spinBoxScaleY->setSingleStep(0.1);
        spinBoxScaleY->setValue(0);

        lineLayoutScale->addWidget(spinBoxScaleY);

        lblScaleZ = new QLabel(verticalLayoutWidget);
        lblScaleZ->setObjectName(QStringLiteral("lblScaleZ"));
        lblScaleZ->setMaximumSize(QSize(15, 16777215));

        lineLayoutScale->addWidget(lblScaleZ);

        spinBoxScaleZ = new QDoubleSpinBox(verticalLayoutWidget);
        spinBoxScaleZ->setObjectName(QStringLiteral("spinBoxScaleZ"));
        spinBoxScaleZ->setMinimum(-64000);
        spinBoxScaleZ->setMaximum(64000);
        spinBoxScaleZ->setSingleStep(0.1);

        lineLayoutScale->addWidget(spinBoxScaleZ);


        verticalLayout->addLayout(lineLayoutScale);

        line_3 = new QFrame(verticalLayoutWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_3);


        retranslateUi(ui_AGTransformPanel);

        QMetaObject::connectSlotsByName(ui_AGTransformPanel);
    } // setupUi

    void retranslateUi(QWidget *ui_AGTransformPanel)
    {
        ui_AGTransformPanel->setWindowTitle(QApplication::translate("ui_AGTransformPanel", "TransformPanel", 0));
        label->setText(QApplication::translate("ui_AGTransformPanel", "Position", 0));
        lblPosX->setText(QApplication::translate("ui_AGTransformPanel", "X:", 0));
        lblPosY->setText(QApplication::translate("ui_AGTransformPanel", "Y:", 0));
        lblPosZ->setText(QApplication::translate("ui_AGTransformPanel", "Z:", 0));
        label_2->setText(QApplication::translate("ui_AGTransformPanel", "Rotation", 0));
        lblRotX->setText(QApplication::translate("ui_AGTransformPanel", "X:", 0));
        lblRotY->setText(QApplication::translate("ui_AGTransformPanel", "Y:", 0));
        lblRotZ->setText(QApplication::translate("ui_AGTransformPanel", "Z:", 0));
        label_3->setText(QApplication::translate("ui_AGTransformPanel", "Scale", 0));
        lblScaleX->setText(QApplication::translate("ui_AGTransformPanel", "X:", 0));
        lblScaleY->setText(QApplication::translate("ui_AGTransformPanel", "Y:", 0));
        lblScaleZ->setText(QApplication::translate("ui_AGTransformPanel", "Z:", 0));
    } // retranslateUi

};

namespace Ui {
    class ui_AGTransformPanel: public Ui_ui_AGTransformPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AGETRANSFORMPANEL_H
