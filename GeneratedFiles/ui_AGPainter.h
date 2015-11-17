/********************************************************************************
** Form generated from reading UI file 'AGPainter.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AGPAINTER_H
#define UI_AGPAINTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AGPainter
{
public:
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *mainLayout;
    QVBoxLayout *mainVLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *hlBrushTitle;
    QFrame *line;
    QLabel *lbBrush;
    QFrame *line_2;
    QVBoxLayout *vlBrush;
    QLabel *lbRadius;
    QHBoxLayout *hlBrushRadius;
    QSlider *hsRadius;
    QDoubleSpinBox *sbRadius;
    QLabel *lbHardness;
    QHBoxLayout *hlBrushHardness;
    QSlider *hsHardness;
    QDoubleSpinBox *sbHardness;
    QHBoxLayout *hlFilterTitle;
    QFrame *line_3;
    QLabel *lbFilter;
    QFrame *line_4;
    QVBoxLayout *vlFilter;
    QHBoxLayout *hlFilterOptions;
    QLabel *lbSaturation;
    QSlider *hsSaturation;
    QLabel *lbColor;
    QPushButton *pbColor;
    QHBoxLayout *hlFilterButtons;
    QPushButton *pbReset;
    QPushButton *pbSave;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *hlMaterials;
    QFrame *line_7;
    QLabel *lbMaterials;
    QFrame *line_8;
    QVBoxLayout *vlMaterials;
    QHBoxLayout *horizontalLayout;
    QPushButton *pbAdd;
    QPushButton *pbRemove;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *AGPainter)
    {
        if (AGPainter->objectName().isEmpty())
            AGPainter->setObjectName(QStringLiteral("AGPainter"));
        AGPainter->resize(343, 306);
        horizontalLayoutWidget_3 = new QWidget(AGPainter);
        horizontalLayoutWidget_3->setObjectName(QStringLiteral("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(10, 10, 311, 274));
        mainLayout = new QHBoxLayout(horizontalLayoutWidget_3);
        mainLayout->setObjectName(QStringLiteral("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainVLayout = new QVBoxLayout();
        mainVLayout->setObjectName(QStringLiteral("mainVLayout"));
        verticalSpacer = new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Minimum);

        mainVLayout->addItem(verticalSpacer);

        hlBrushTitle = new QHBoxLayout();
        hlBrushTitle->setSpacing(5);
        hlBrushTitle->setObjectName(QStringLiteral("hlBrushTitle"));
        line = new QFrame(horizontalLayoutWidget_3);
        line->setObjectName(QStringLiteral("line"));
        line->setMaximumSize(QSize(16777215, 10));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        hlBrushTitle->addWidget(line);

        lbBrush = new QLabel(horizontalLayoutWidget_3);
        lbBrush->setObjectName(QStringLiteral("lbBrush"));
        lbBrush->setMaximumSize(QSize(29, 50));
        lbBrush->setTextFormat(Qt::AutoText);
        lbBrush->setScaledContents(true);
        lbBrush->setAlignment(Qt::AlignCenter);
        lbBrush->setWordWrap(false);
        lbBrush->setMargin(0);
        lbBrush->setIndent(0);
        lbBrush->setOpenExternalLinks(false);

        hlBrushTitle->addWidget(lbBrush);

        line_2 = new QFrame(horizontalLayoutWidget_3);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setMaximumSize(QSize(16777215, 10));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        hlBrushTitle->addWidget(line_2);


        mainVLayout->addLayout(hlBrushTitle);

        vlBrush = new QVBoxLayout();
        vlBrush->setObjectName(QStringLiteral("vlBrush"));
        lbRadius = new QLabel(horizontalLayoutWidget_3);
        lbRadius->setObjectName(QStringLiteral("lbRadius"));

        vlBrush->addWidget(lbRadius);

        hlBrushRadius = new QHBoxLayout();
        hlBrushRadius->setObjectName(QStringLiteral("hlBrushRadius"));
        hsRadius = new QSlider(horizontalLayoutWidget_3);
        hsRadius->setObjectName(QStringLiteral("hsRadius"));
        hsRadius->setOrientation(Qt::Horizontal);

        hlBrushRadius->addWidget(hsRadius);

        sbRadius = new QDoubleSpinBox(horizontalLayoutWidget_3);
        sbRadius->setObjectName(QStringLiteral("sbRadius"));

        hlBrushRadius->addWidget(sbRadius);


        vlBrush->addLayout(hlBrushRadius);

        lbHardness = new QLabel(horizontalLayoutWidget_3);
        lbHardness->setObjectName(QStringLiteral("lbHardness"));

        vlBrush->addWidget(lbHardness);

        hlBrushHardness = new QHBoxLayout();
        hlBrushHardness->setObjectName(QStringLiteral("hlBrushHardness"));
        hsHardness = new QSlider(horizontalLayoutWidget_3);
        hsHardness->setObjectName(QStringLiteral("hsHardness"));
        hsHardness->setOrientation(Qt::Horizontal);

        hlBrushHardness->addWidget(hsHardness);

        sbHardness = new QDoubleSpinBox(horizontalLayoutWidget_3);
        sbHardness->setObjectName(QStringLiteral("sbHardness"));

        hlBrushHardness->addWidget(sbHardness);


        vlBrush->addLayout(hlBrushHardness);


        mainVLayout->addLayout(vlBrush);

        hlFilterTitle = new QHBoxLayout();
        hlFilterTitle->setSpacing(5);
        hlFilterTitle->setObjectName(QStringLiteral("hlFilterTitle"));
        line_3 = new QFrame(horizontalLayoutWidget_3);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setMaximumSize(QSize(16777215, 10));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        hlFilterTitle->addWidget(line_3);

        lbFilter = new QLabel(horizontalLayoutWidget_3);
        lbFilter->setObjectName(QStringLiteral("lbFilter"));
        lbFilter->setMaximumSize(QSize(27, 15));
        lbFilter->setTextFormat(Qt::AutoText);
        lbFilter->setScaledContents(true);
        lbFilter->setAlignment(Qt::AlignCenter);
        lbFilter->setWordWrap(false);
        lbFilter->setMargin(0);
        lbFilter->setIndent(0);
        lbFilter->setOpenExternalLinks(false);

        hlFilterTitle->addWidget(lbFilter);

        line_4 = new QFrame(horizontalLayoutWidget_3);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setMaximumSize(QSize(16777215, 10));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        hlFilterTitle->addWidget(line_4);


        mainVLayout->addLayout(hlFilterTitle);

        vlFilter = new QVBoxLayout();
        vlFilter->setObjectName(QStringLiteral("vlFilter"));
        hlFilterOptions = new QHBoxLayout();
        hlFilterOptions->setObjectName(QStringLiteral("hlFilterOptions"));
        lbSaturation = new QLabel(horizontalLayoutWidget_3);
        lbSaturation->setObjectName(QStringLiteral("lbSaturation"));

        hlFilterOptions->addWidget(lbSaturation);

        hsSaturation = new QSlider(horizontalLayoutWidget_3);
        hsSaturation->setObjectName(QStringLiteral("hsSaturation"));
        hsSaturation->setOrientation(Qt::Horizontal);

        hlFilterOptions->addWidget(hsSaturation);

        lbColor = new QLabel(horizontalLayoutWidget_3);
        lbColor->setObjectName(QStringLiteral("lbColor"));

        hlFilterOptions->addWidget(lbColor);

        pbColor = new QPushButton(horizontalLayoutWidget_3);
        pbColor->setObjectName(QStringLiteral("pbColor"));

        hlFilterOptions->addWidget(pbColor);


        vlFilter->addLayout(hlFilterOptions);

        hlFilterButtons = new QHBoxLayout();
        hlFilterButtons->setObjectName(QStringLiteral("hlFilterButtons"));
        pbReset = new QPushButton(horizontalLayoutWidget_3);
        pbReset->setObjectName(QStringLiteral("pbReset"));

        hlFilterButtons->addWidget(pbReset);

        pbSave = new QPushButton(horizontalLayoutWidget_3);
        pbSave->setObjectName(QStringLiteral("pbSave"));

        hlFilterButtons->addWidget(pbSave);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hlFilterButtons->addItem(horizontalSpacer_2);


        vlFilter->addLayout(hlFilterButtons);

        hlMaterials = new QHBoxLayout();
        hlMaterials->setSpacing(5);
        hlMaterials->setObjectName(QStringLiteral("hlMaterials"));
        line_7 = new QFrame(horizontalLayoutWidget_3);
        line_7->setObjectName(QStringLiteral("line_7"));
        line_7->setMaximumSize(QSize(16777215, 10));
        line_7->setFrameShape(QFrame::HLine);
        line_7->setFrameShadow(QFrame::Sunken);

        hlMaterials->addWidget(line_7);

        lbMaterials = new QLabel(horizontalLayoutWidget_3);
        lbMaterials->setObjectName(QStringLiteral("lbMaterials"));
        lbMaterials->setMaximumSize(QSize(50, 15));
        lbMaterials->setTextFormat(Qt::AutoText);
        lbMaterials->setScaledContents(true);
        lbMaterials->setAlignment(Qt::AlignCenter);
        lbMaterials->setWordWrap(false);
        lbMaterials->setMargin(0);
        lbMaterials->setIndent(0);
        lbMaterials->setOpenExternalLinks(false);

        hlMaterials->addWidget(lbMaterials);

        line_8 = new QFrame(horizontalLayoutWidget_3);
        line_8->setObjectName(QStringLiteral("line_8"));
        line_8->setMaximumSize(QSize(16777215, 10));
        line_8->setFrameShape(QFrame::HLine);
        line_8->setFrameShadow(QFrame::Sunken);

        hlMaterials->addWidget(line_8);


        vlFilter->addLayout(hlMaterials);


        mainVLayout->addLayout(vlFilter);

        vlMaterials = new QVBoxLayout();
        vlMaterials->setObjectName(QStringLiteral("vlMaterials"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pbAdd = new QPushButton(horizontalLayoutWidget_3);
        pbAdd->setObjectName(QStringLiteral("pbAdd"));

        horizontalLayout->addWidget(pbAdd);

        pbRemove = new QPushButton(horizontalLayoutWidget_3);
        pbRemove->setObjectName(QStringLiteral("pbRemove"));

        horizontalLayout->addWidget(pbRemove);


        vlMaterials->addLayout(horizontalLayout);


        mainVLayout->addLayout(vlMaterials);


        mainLayout->addLayout(mainVLayout);

        horizontalSpacer = new QSpacerItem(12, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        mainLayout->addItem(horizontalSpacer);


        retranslateUi(AGPainter);

        QMetaObject::connectSlotsByName(AGPainter);
    } // setupUi

    void retranslateUi(QWidget *AGPainter)
    {
        AGPainter->setWindowTitle(QApplication::translate("AGPainter", "Painter", 0));
        lbBrush->setText(QApplication::translate("AGPainter", "Brush", 0));
        lbRadius->setText(QApplication::translate("AGPainter", "Radius:", 0));
        lbHardness->setText(QApplication::translate("AGPainter", "Hardness:", 0));
        lbFilter->setText(QApplication::translate("AGPainter", "Filter", 0));
        lbSaturation->setText(QApplication::translate("AGPainter", "Saturation:", 0));
        lbColor->setText(QApplication::translate("AGPainter", "Color:", 0));
        pbColor->setText(QString());
        pbReset->setText(QApplication::translate("AGPainter", "Reset", 0));
        pbSave->setText(QApplication::translate("AGPainter", "Save", 0));
        lbMaterials->setText(QApplication::translate("AGPainter", "Materials", 0));
        pbAdd->setText(QApplication::translate("AGPainter", "Add", 0));
        pbRemove->setText(QApplication::translate("AGPainter", "Remove", 0));
    } // retranslateUi

};

namespace Ui {
    class AGPainter: public Ui_AGPainter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AGPAINTER_H
