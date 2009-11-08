/********************************************************************************
** Form generated from reading ui file 'mainwindow.ui'
**
** Created: Sat Nov 7 22:37:49 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGraphicsView>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListView>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionStart_Recording;
    QAction *actionStop_Recording;
    QAction *actionSettings;
    QAction *actionAbout;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_8;
    QSlider *Volume;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_3;
    QFrame *ControlsPanel;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *FastUp;
    QPushButton *FreqUp;
    QPushButton *Frequency;
    QPushButton *FreqDown;
    QPushButton *FastDown;
    QFrame *ButtonsPanel;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *ShowRecording;
    QPushButton *ShowVisualization;
    QPushButton *ShowPresets;
    QPushButton *Mute;
    QSpacerItem *horizontalSpacer;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *Visualization;
    QListView *Presets;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *Record;
    QPushButton *SavePreset;
    QPushButton *RemovePreset;
    QPushButton *Settings;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(610, 372);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setBaseSize(QSize(600, 400));
        QIcon icon;
        icon.addPixmap(QPixmap(QString::fromUtf8(":/finny/assets/radioshark.png")), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setIconSize(QSize(24, 24));
        MainWindow->setAnimated(true);
        actionStart_Recording = new QAction(MainWindow);
        actionStart_Recording->setObjectName(QString::fromUtf8("actionStart_Recording"));
        actionStop_Recording = new QAction(MainWindow);
        actionStop_Recording->setObjectName(QString::fromUtf8("actionStop_Recording"));
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName(QString::fromUtf8("actionSettings"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(100);
        sizePolicy1.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy1);
        centralwidget->setBaseSize(QSize(0, 200));
        centralwidget->setAutoFillBackground(true);
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(3, 0, 0, 0);
        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_8 = new QHBoxLayout(widget_2);
        horizontalLayout_8->setSpacing(3);
        horizontalLayout_8->setMargin(0);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        Volume = new QSlider(widget_2);
        Volume->setObjectName(QString::fromUtf8("Volume"));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        Volume->setFont(font);
        Volume->setSingleStep(5);
        Volume->setOrientation(Qt::Vertical);
        Volume->setInvertedAppearance(false);
        Volume->setInvertedControls(false);
        Volume->setTickPosition(QSlider::TicksBothSides);

        horizontalLayout_8->addWidget(Volume);

        widget_3 = new QWidget(widget_2);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        verticalLayout_3 = new QVBoxLayout(widget_3);
        verticalLayout_3->setSpacing(3);
        verticalLayout_3->setMargin(3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        ControlsPanel = new QFrame(widget_3);
        ControlsPanel->setObjectName(QString::fromUtf8("ControlsPanel"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(ControlsPanel->sizePolicy().hasHeightForWidth());
        ControlsPanel->setSizePolicy(sizePolicy2);
        ControlsPanel->setFrameShape(QFrame::Box);
        horizontalLayout_2 = new QHBoxLayout(ControlsPanel);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        FastUp = new QPushButton(ControlsPanel);
        FastUp->setObjectName(QString::fromUtf8("FastUp"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(FastUp->sizePolicy().hasHeightForWidth());
        FastUp->setSizePolicy(sizePolicy3);
        QIcon icon1;
        icon1.addPixmap(QPixmap(QString::fromUtf8(":/finny/assets/fast_left_up.png")), QIcon::Normal, QIcon::Off);
        FastUp->setIcon(icon1);
        FastUp->setIconSize(QSize(64, 64));
        FastUp->setAutoRepeat(true);
        FastUp->setAutoExclusive(true);
        FastUp->setAutoRepeatDelay(1000);
        FastUp->setFlat(true);

        horizontalLayout_2->addWidget(FastUp);

        FreqUp = new QPushButton(ControlsPanel);
        FreqUp->setObjectName(QString::fromUtf8("FreqUp"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(FreqUp->sizePolicy().hasHeightForWidth());
        FreqUp->setSizePolicy(sizePolicy4);
        FreqUp->setMouseTracking(true);
        QIcon icon2;
        icon2.addPixmap(QPixmap(QString::fromUtf8(":/finny/assets/left_up.png")), QIcon::Normal, QIcon::Off);
        FreqUp->setIcon(icon2);
        FreqUp->setIconSize(QSize(64, 64));
        FreqUp->setAutoRepeat(true);
        FreqUp->setAutoExclusive(true);
        FreqUp->setAutoRepeatDelay(1000);
        FreqUp->setFlat(true);

        horizontalLayout_2->addWidget(FreqUp);

        Frequency = new QPushButton(ControlsPanel);
        Frequency->setObjectName(QString::fromUtf8("Frequency"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(Frequency->sizePolicy().hasHeightForWidth());
        Frequency->setSizePolicy(sizePolicy5);
        Frequency->setBaseSize(QSize(300, 75));
        QFont font1;
        font1.setPointSize(18);
        font1.setBold(true);
        font1.setWeight(75);
        Frequency->setFont(font1);
        Frequency->setFlat(true);

        horizontalLayout_2->addWidget(Frequency);

        FreqDown = new QPushButton(ControlsPanel);
        FreqDown->setObjectName(QString::fromUtf8("FreqDown"));
        sizePolicy4.setHeightForWidth(FreqDown->sizePolicy().hasHeightForWidth());
        FreqDown->setSizePolicy(sizePolicy4);
        FreqDown->setLayoutDirection(Qt::RightToLeft);
        QIcon icon3;
        icon3.addPixmap(QPixmap(QString::fromUtf8(":/finny/assets/right_up.png")), QIcon::Normal, QIcon::Off);
        FreqDown->setIcon(icon3);
        FreqDown->setIconSize(QSize(64, 64));
        FreqDown->setAutoRepeat(true);
        FreqDown->setAutoExclusive(true);
        FreqDown->setAutoRepeatDelay(1000);
        FreqDown->setFlat(true);

        horizontalLayout_2->addWidget(FreqDown);

        FastDown = new QPushButton(ControlsPanel);
        FastDown->setObjectName(QString::fromUtf8("FastDown"));
        sizePolicy3.setHeightForWidth(FastDown->sizePolicy().hasHeightForWidth());
        FastDown->setSizePolicy(sizePolicy3);
        QIcon icon4;
        icon4.addPixmap(QPixmap(QString::fromUtf8(":/finny/assets/fast_right_up.png")), QIcon::Normal, QIcon::Off);
        FastDown->setIcon(icon4);
        FastDown->setIconSize(QSize(64, 64));
        FastDown->setAutoRepeat(true);
        FastDown->setAutoExclusive(true);
        FastDown->setAutoRepeatDelay(1000);
        FastDown->setFlat(true);

        horizontalLayout_2->addWidget(FastDown);


        verticalLayout_3->addWidget(ControlsPanel);

        ButtonsPanel = new QFrame(widget_3);
        ButtonsPanel->setObjectName(QString::fromUtf8("ButtonsPanel"));
        sizePolicy2.setHeightForWidth(ButtonsPanel->sizePolicy().hasHeightForWidth());
        ButtonsPanel->setSizePolicy(sizePolicy2);
        ButtonsPanel->setFrameShape(QFrame::Box);
        ButtonsPanel->setFrameShadow(QFrame::Plain);
        horizontalLayout_4 = new QHBoxLayout(ButtonsPanel);
        horizontalLayout_4->setSpacing(3);
        horizontalLayout_4->setMargin(3);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        ShowRecording = new QPushButton(ButtonsPanel);
        ShowRecording->setObjectName(QString::fromUtf8("ShowRecording"));
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setWeight(75);
        ShowRecording->setFont(font2);
        ShowRecording->setCheckable(true);
        ShowRecording->setChecked(false);

        horizontalLayout_4->addWidget(ShowRecording);

        ShowVisualization = new QPushButton(ButtonsPanel);
        ShowVisualization->setObjectName(QString::fromUtf8("ShowVisualization"));
        QFont font3;
        font3.setBold(true);
        font3.setWeight(75);
        ShowVisualization->setFont(font3);
        ShowVisualization->setCheckable(true);
        ShowVisualization->setChecked(true);

        horizontalLayout_4->addWidget(ShowVisualization);

        ShowPresets = new QPushButton(ButtonsPanel);
        ShowPresets->setObjectName(QString::fromUtf8("ShowPresets"));
        ShowPresets->setFont(font2);
        ShowPresets->setCheckable(true);
        ShowPresets->setChecked(true);

        horizontalLayout_4->addWidget(ShowPresets);

        Mute = new QPushButton(ButtonsPanel);
        Mute->setObjectName(QString::fromUtf8("Mute"));
        Mute->setFont(font2);
        QIcon icon5;
        icon5.addPixmap(QPixmap(QString::fromUtf8(":/finny/assets/speaker.png")), QIcon::Normal, QIcon::Off);
        Mute->setIcon(icon5);
        Mute->setCheckable(true);

        horizontalLayout_4->addWidget(Mute);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);


        verticalLayout_3->addWidget(ButtonsPanel);

        widget_4 = new QWidget(widget_3);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        sizePolicy3.setHeightForWidth(widget_4->sizePolicy().hasHeightForWidth());
        widget_4->setSizePolicy(sizePolicy3);
        horizontalLayout = new QHBoxLayout(widget_4);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        Visualization = new QGraphicsView(widget_4);
        Visualization->setObjectName(QString::fromUtf8("Visualization"));
        sizePolicy.setHeightForWidth(Visualization->sizePolicy().hasHeightForWidth());
        Visualization->setSizePolicy(sizePolicy);
        Visualization->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Visualization->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Visualization->setOptimizationFlags(QGraphicsView::DontAdjustForAntialiasing|QGraphicsView::DontClipPainter|QGraphicsView::DontSavePainterState);

        horizontalLayout->addWidget(Visualization);

        Presets = new QListView(widget_4);
        Presets->setObjectName(QString::fromUtf8("Presets"));
        sizePolicy.setHeightForWidth(Presets->sizePolicy().hasHeightForWidth());
        Presets->setSizePolicy(sizePolicy);
        Presets->setMaximumSize(QSize(16777215, 16777215));
        QFont font4;
        font4.setPointSize(14);
        Presets->setFont(font4);
        Presets->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Presets->setAlternatingRowColors(true);

        horizontalLayout->addWidget(Presets);


        verticalLayout_3->addWidget(widget_4);

        widget_5 = new QWidget(widget_3);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(widget_5->sizePolicy().hasHeightForWidth());
        widget_5->setSizePolicy(sizePolicy6);
        horizontalLayout_5 = new QHBoxLayout(widget_5);
        horizontalLayout_5->setSpacing(3);
        horizontalLayout_5->setMargin(0);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        Record = new QPushButton(widget_5);
        Record->setObjectName(QString::fromUtf8("Record"));
        Record->setFont(font2);
        Record->setCheckable(true);

        horizontalLayout_5->addWidget(Record);

        SavePreset = new QPushButton(widget_5);
        SavePreset->setObjectName(QString::fromUtf8("SavePreset"));
        SavePreset->setFont(font2);

        horizontalLayout_5->addWidget(SavePreset);

        RemovePreset = new QPushButton(widget_5);
        RemovePreset->setObjectName(QString::fromUtf8("RemovePreset"));
        RemovePreset->setFont(font2);

        horizontalLayout_5->addWidget(RemovePreset);

        Settings = new QPushButton(widget_5);
        Settings->setObjectName(QString::fromUtf8("Settings"));
        Settings->setFont(font2);
        QIcon icon6;
        icon6.addPixmap(QPixmap(QString::fromUtf8(":/finny/assets/settings.png")), QIcon::Normal, QIcon::Off);
        Settings->setIcon(icon6);

        horizontalLayout_5->addWidget(Settings);


        verticalLayout_3->addWidget(widget_5);


        horizontalLayout_8->addWidget(widget_3);


        verticalLayout->addWidget(widget_2);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        sizePolicy3.setHeightForWidth(statusbar->sizePolicy().hasHeightForWidth());
        statusbar->setSizePolicy(sizePolicy3);
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(FreqUp, SIGNAL(pressed()), MainWindow, SLOT(OnFreqUp()));
        QObject::connect(FreqDown, SIGNAL(pressed()), MainWindow, SLOT(OnFreqDown()));
        QObject::connect(Mute, SIGNAL(toggled(bool)), Volume, SLOT(setDisabled(bool)));
        QObject::connect(Volume, SIGNAL(valueChanged(int)), MainWindow, SLOT(OnVolume(int)));
        QObject::connect(Mute, SIGNAL(toggled(bool)), MainWindow, SLOT(OnMute(bool)));
        QObject::connect(Record, SIGNAL(toggled(bool)), MainWindow, SLOT(OnRecord(bool)));
        QObject::connect(ShowPresets, SIGNAL(toggled(bool)), SavePreset, SLOT(setVisible(bool)));
        QObject::connect(SavePreset, SIGNAL(pressed()), MainWindow, SLOT(OnSavePreset()));
        QObject::connect(Presets, SIGNAL(clicked(QModelIndex)), MainWindow, SLOT(OnPreset(QModelIndex)));
        QObject::connect(Settings, SIGNAL(pressed()), MainWindow, SLOT(OnSettings()));
        QObject::connect(ShowPresets, SIGNAL(toggled(bool)), RemovePreset, SLOT(setVisible(bool)));
        QObject::connect(FastUp, SIGNAL(pressed()), MainWindow, SLOT(OnFastUp()));
        QObject::connect(FastDown, SIGNAL(pressed()), MainWindow, SLOT(OnFastDown()));
        QObject::connect(ShowRecording, SIGNAL(toggled(bool)), Record, SLOT(setVisible(bool)));
        QObject::connect(RemovePreset, SIGNAL(pressed()), MainWindow, SLOT(OnRemovePreset()));
        QObject::connect(Frequency, SIGNAL(pressed()), MainWindow, SLOT(OnBandChange()));
        QObject::connect(ShowVisualization, SIGNAL(toggled(bool)), Visualization, SLOT(setVisible(bool)));
        QObject::connect(ShowPresets, SIGNAL(toggled(bool)), Presets, SLOT(setVisible(bool)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Finny - the RadioShark2 Manager", 0, QApplication::UnicodeUTF8));
        actionStart_Recording->setText(QApplication::translate("MainWindow", "Start Recording", 0, QApplication::UnicodeUTF8));
        actionStop_Recording->setText(QApplication::translate("MainWindow", "Stop Recording", 0, QApplication::UnicodeUTF8));
        actionSettings->setText(QApplication::translate("MainWindow", "Settings", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0, QApplication::UnicodeUTF8));
        FastUp->setText(QString());
        FreqUp->setText(QString());
        Frequency->setText(QString());
        FreqDown->setText(QString());
        FastDown->setText(QString());
        ShowRecording->setText(QApplication::translate("MainWindow", "Recording", 0, QApplication::UnicodeUTF8));
        ShowVisualization->setText(QApplication::translate("MainWindow", "Visualization", 0, QApplication::UnicodeUTF8));
        ShowPresets->setText(QApplication::translate("MainWindow", "Presets", 0, QApplication::UnicodeUTF8));
        Mute->setText(QApplication::translate("MainWindow", "Mute", 0, QApplication::UnicodeUTF8));
        Record->setText(QApplication::translate("MainWindow", "Record", 0, QApplication::UnicodeUTF8));
        SavePreset->setText(QApplication::translate("MainWindow", "Save Preset", 0, QApplication::UnicodeUTF8));
        RemovePreset->setText(QApplication::translate("MainWindow", "RemovePreset", 0, QApplication::UnicodeUTF8));
        Settings->setText(QApplication::translate("MainWindow", "Settings", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
