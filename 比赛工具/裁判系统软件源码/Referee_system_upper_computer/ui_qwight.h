/********************************************************************************
** Form generated from reading UI file 'qwight.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QWIGHT_H
#define UI_QWIGHT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Qwight
{
public:
    QAction *action;
    QAction *action_V1_0;
    QAction *action2023;
    QWidget *centralWidget;
    QLabel *label_2;
    QLCDNumber *lcdNumber;
    QLabel *label_3;
    QLabel *label;
    QPushButton *uart_data_clean;
    QComboBox *model;
    QLabel *system_state;
    QLabel *label_5;
    QSplitter *splitter;
    QPushButton *StartButton;
    QPushButton *StopButton;
    QPushButton *clean_time;
    QTextEdit *textEdit;
    QTextBrowser *textBrowser;
    QLabel *label_4;
    QPushButton *actionPlay;
    QPushButton *ALL_pin;
    QPushButton *esc_ALL;
    QPushButton *scan_uart;
    QLabel *label_6;
    QComboBox *choose_uart;
    QLabel *label_7;
    QComboBox *uart_poart;
    QPushButton *open_uart;
    QLabel *uart_relay;
    QPushButton *close_uart;
    QLabel *label_8;
    QLabel *label_9;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Qwight)
    {
        if (Qwight->objectName().isEmpty())
            Qwight->setObjectName(QStringLiteral("Qwight"));
        Qwight->setWindowModality(Qt::WindowModal);
        Qwight->resize(1920, 990);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Qwight->sizePolicy().hasHeightForWidth());
        Qwight->setSizePolicy(sizePolicy);
        Qwight->setMinimumSize(QSize(720, 480));
        Qwight->setMaximumSize(QSize(1920, 1020));
        Qwight->setSizeIncrement(QSize(1920, 1080));
        Qwight->setBaseSize(QSize(800, 800));
        Qwight->setStyleSheet(QString::fromUtf8("background-image: url(:/new/prefix1/Pinture_and_ioc/\350\223\235\347\264\253\350\211\262\347\247\221\346\212\200\346\217\222\347\224\273\345\205\203\345\256\207\345\256\231Plog.png);"));
        Qwight->setIconSize(QSize(36, 36));
        action = new QAction(Qwight);
        action->setObjectName(QStringLiteral("action"));
        action_V1_0 = new QAction(Qwight);
        action_V1_0->setObjectName(QStringLiteral("action_V1_0"));
        action2023 = new QAction(Qwight);
        action2023->setObjectName(QStringLiteral("action2023"));
        centralWidget = new QWidget(Qwight);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(360, 390, 171, 201));
        QFont font;
        font.setPointSize(50);
        label_2->setFont(font);
        label_2->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lcdNumber = new QLCDNumber(centralWidget);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(540, 290, 631, 361));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\346\200\235\346\272\220\345\256\213\344\275\223 VF"));
        font1.setPointSize(14);
        lcdNumber->setFont(font1);
        lcdNumber->setToolTipDuration(-1);
        lcdNumber->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-image: url(:/new/prefix1/Pinture_and_ioc/\350\203\214\346\231\257.jpg);"));
        lcdNumber->setSmallDecimalPoint(true);
        lcdNumber->setDigitCount(7);
        lcdNumber->setSegmentStyle(QLCDNumber::Flat);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(1180, 400, 151, 191));
        QFont font2;
        font2.setPointSize(80);
        label_3->setFont(font2);
        label_3->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
""));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(1400, 320, 119, 23));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\346\200\235\346\272\220\345\256\213\344\275\223 VF"));
        font3.setPointSize(12);
        font3.setBold(true);
        font3.setWeight(75);
        label->setFont(font3);
        label->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        uart_data_clean = new QPushButton(centralWidget);
        uart_data_clean->setObjectName(QStringLiteral("uart_data_clean"));
        uart_data_clean->setGeometry(QRect(1400, 620, 261, 61));
        QFont font4;
        font4.setPointSize(15);
        uart_data_clean->setFont(font4);
        uart_data_clean->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        model = new QComboBox(centralWidget);
        model->setObjectName(QStringLiteral("model"));
        model->setGeometry(QRect(1460, 740, 131, 51));
        QFont font5;
        font5.setFamily(QString::fromUtf8("\346\200\235\346\272\220\345\256\213\344\275\223 VF"));
        font5.setPointSize(20);
        model->setFont(font5);
        model->setStyleSheet(QLatin1String("color: rgb(62, 43, 190);\n"
"selection-color: rgb(73, 60, 211);"));
        system_state = new QLabel(centralWidget);
        system_state->setObjectName(QStringLiteral("system_state"));
        system_state->setGeometry(QRect(550, 700, 611, 33));
        QFont font6;
        font6.setPointSize(20);
        system_state->setFont(font6);
        system_state->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 140, 231, 101));
        label_5->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix1/Pinture_and_ioc/\346\240\241\345\276\275.png);"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setGeometry(QRect(540, 760, 621, 91));
        splitter->setOrientation(Qt::Horizontal);
        StartButton = new QPushButton(splitter);
        StartButton->setObjectName(QStringLiteral("StartButton"));
        QFont font7;
        font7.setFamily(QString::fromUtf8("\346\200\235\346\272\220\345\256\213\344\275\223 VF"));
        font7.setPointSize(15);
        StartButton->setFont(font7);
        StartButton->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        splitter->addWidget(StartButton);
        StopButton = new QPushButton(splitter);
        StopButton->setObjectName(QStringLiteral("StopButton"));
        StopButton->setFont(font7);
        StopButton->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        splitter->addWidget(StopButton);
        clean_time = new QPushButton(splitter);
        clean_time->setObjectName(QStringLiteral("clean_time"));
        clean_time->setFont(font7);
        clean_time->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        splitter->addWidget(clean_time);
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(1400, 550, 256, 61));
        QFont font8;
        font8.setPointSize(23);
        textEdit->setFont(font8);
        textEdit->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(1400, 355, 256, 192));
        textBrowser->setFont(font8);
        textBrowser->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(1460, 690, 131, 41));
        label_4->setFont(font7);
        label_4->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        actionPlay = new QPushButton(centralWidget);
        actionPlay->setObjectName(QStringLiteral("actionPlay"));
        actionPlay->setGeometry(QRect(220, 810, 141, 41));
        actionPlay->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        ALL_pin = new QPushButton(centralWidget);
        ALL_pin->setObjectName(QStringLiteral("ALL_pin"));
        ALL_pin->setGeometry(QRect(0, 0, 75, 23));
        ALL_pin->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: rgb(62, 43, 190);"));
        esc_ALL = new QPushButton(centralWidget);
        esc_ALL->setObjectName(QStringLiteral("esc_ALL"));
        esc_ALL->setGeometry(QRect(80, 0, 75, 23));
        esc_ALL->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: rgb(70, 55, 205);"));
        scan_uart = new QPushButton(centralWidget);
        scan_uart->setObjectName(QStringLiteral("scan_uart"));
        scan_uart->setGeometry(QRect(40, 630, 141, 41));
        scan_uart->setFont(font4);
        scan_uart->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: rgb(73, 60, 211);"));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(40, 680, 141, 21));
        label_6->setFont(font4);
        label_6->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        choose_uart = new QComboBox(centralWidget);
        choose_uart->setObjectName(QStringLiteral("choose_uart"));
        choose_uart->setGeometry(QRect(42, 710, 141, 41));
        choose_uart->setFont(font8);
        choose_uart->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: rgb(73, 60, 211);"));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(220, 670, 131, 31));
        QFont font9;
        font9.setFamily(QString::fromUtf8("\346\200\235\346\272\220\345\256\213\344\275\223 VF"));
        font9.setPointSize(15);
        font9.setKerning(true);
        label_7->setFont(font9);
        label_7->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        uart_poart = new QComboBox(centralWidget);
        uart_poart->setObjectName(QStringLiteral("uart_poart"));
        uart_poart->setGeometry(QRect(220, 710, 141, 41));
        QFont font10;
        font10.setPointSize(18);
        uart_poart->setFont(font10);
        uart_poart->setStyleSheet(QLatin1String("background-color: rgb(73, 60, 211);\n"
"color: rgb(255, 255, 255);"));
        open_uart = new QPushButton(centralWidget);
        open_uart->setObjectName(QStringLiteral("open_uart"));
        open_uart->setGeometry(QRect(40, 760, 141, 41));
        open_uart->setFont(font4);
        open_uart->setStyleSheet(QLatin1String("background-color: rgb(62, 43, 190);\n"
"color: rgb(255, 255, 255);"));
        uart_relay = new QLabel(centralWidget);
        uart_relay->setObjectName(QStringLiteral("uart_relay"));
        uart_relay->setGeometry(QRect(220, 760, 141, 31));
        QFont font11;
        font11.setPointSize(13);
        uart_relay->setFont(font11);
        uart_relay->setStyleSheet(QLatin1String("alternate-background-color: rgb(149, 209, 255);\n"
"color: rgb(255, 255, 255);"));
        close_uart = new QPushButton(centralWidget);
        close_uart->setObjectName(QStringLiteral("close_uart"));
        close_uart->setGeometry(QRect(40, 810, 141, 41));
        close_uart->setFont(font4);
        close_uart->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: rgb(73, 60, 211);"));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(300, 140, 101, 101));
        label_8->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix1/Pinture_and_ioc/\347\253\213\345\210\233EDA1.png);\n"
""));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(260, 180, 31, 31));
        label_9->setFont(font6);
        label_9->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        Qwight->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Qwight);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1920, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        Qwight->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Qwight);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Qwight->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Qwight);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Qwight->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(action);
        menu->addAction(action_V1_0);
        menu->addAction(action2023);

        retranslateUi(Qwight);

        QMetaObject::connectSlotsByName(Qwight);
    } // setupUi

    void retranslateUi(QMainWindow *Qwight)
    {
        Qwight->setWindowTitle(QApplication::translate("Qwight", "\347\224\265\344\277\241\347\247\221\345\215\217\345\276\252\350\277\271\350\275\246\350\243\201\345\210\244\347\263\273\347\273\237", Q_NULLPTR));
        action->setText(QApplication::translate("Qwight", "\344\275\234\350\200\205\357\274\232\345\210\230\351\221\253\350\266\205", Q_NULLPTR));
        action_V1_0->setText(QApplication::translate("Qwight", "\347\211\210\346\234\254\345\217\267\357\274\232V1.0", Q_NULLPTR));
        action2023->setText(QApplication::translate("Qwight", "2023.4.30", Q_NULLPTR));
        label_2->setText(QApplication::translate("Qwight", "\347\224\250\346\227\266\357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("Qwight", "\347\247\222", Q_NULLPTR));
        label->setText(QApplication::translate("Qwight", "\344\270\262\345\217\243\346\266\210\346\201\257\350\256\260\345\275\225\357\274\232", Q_NULLPTR));
        uart_data_clean->setText(QApplication::translate("Qwight", "\346\270\205\351\231\244\344\277\241\346\201\257", Q_NULLPTR));
        model->clear();
        model->insertItems(0, QStringList()
         << QApplication::translate("Qwight", "\344\270\200\345\234\210", Q_NULLPTR)
         << QApplication::translate("Qwight", "\344\270\244\345\234\210", Q_NULLPTR)
        );
        system_state->setText(QApplication::translate("Qwight", "\347\263\273\347\273\237\346\234\252\345\207\206\345\244\207 \347\202\271\345\207\273\345\207\206\345\244\207\345\220\216\345\217\257\345\274\200\345\247\213\346\257\224\350\265\233", Q_NULLPTR));
        label_5->setText(QString());
        StartButton->setText(QApplication::translate("Qwight", "\345\207\206\345\244\207", Q_NULLPTR));
        StopButton->setText(QApplication::translate("Qwight", "\346\232\202\345\201\234", Q_NULLPTR));
        clean_time->setText(QApplication::translate("Qwight", "\346\270\205\351\231\244\346\227\266\351\227\264", Q_NULLPTR));
        label_4->setText(QApplication::translate("Qwight", "\346\257\224\350\265\233\346\250\241\345\274\217\357\274\232", Q_NULLPTR));
        actionPlay->setText(QApplication::translate("Qwight", "BGM", Q_NULLPTR));
        ALL_pin->setText(QApplication::translate("Qwight", "\345\205\250\345\261\217", Q_NULLPTR));
        esc_ALL->setText(QApplication::translate("Qwight", "\351\200\200\345\207\272\345\205\250\345\261\217", Q_NULLPTR));
        scan_uart->setText(QApplication::translate("Qwight", "\346\211\253\346\217\217\344\270\262\345\217\243", Q_NULLPTR));
        label_6->setText(QApplication::translate("Qwight", "\344\270\262\345\217\243\345\217\267\351\200\211\346\213\251\357\274\232", Q_NULLPTR));
        label_7->setText(QApplication::translate("Qwight", "\346\263\242\347\211\271\347\216\207", Q_NULLPTR));
        uart_poart->clear();
        uart_poart->insertItems(0, QStringList()
         << QApplication::translate("Qwight", "115200", Q_NULLPTR)
         << QApplication::translate("Qwight", "9600", Q_NULLPTR)
        );
        open_uart->setText(QApplication::translate("Qwight", "\346\211\223\345\274\200\344\270\262\345\217\243", Q_NULLPTR));
        uart_relay->setText(QApplication::translate("Qwight", "\344\270\262\345\217\243\347\212\266\346\200\201", Q_NULLPTR));
        close_uart->setText(QApplication::translate("Qwight", "\345\205\263\351\227\255\344\270\262\345\217\243", Q_NULLPTR));
        label_8->setText(QString());
        label_9->setText(QApplication::translate("Qwight", "\303\227", Q_NULLPTR));
        menu->setTitle(QApplication::translate("Qwight", "\345\205\263\344\272\216", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Qwight: public Ui_Qwight {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QWIGHT_H
