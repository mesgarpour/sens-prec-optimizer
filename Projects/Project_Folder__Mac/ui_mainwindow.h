/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainwindow
{
public:
    QAction *actionHelp;
    QAction *actionSubHelp;
    QAction *actionSubAbout;
    QWidget *centralWidget;
    QLineEdit *fldInput;
    QLineEdit *fldOutput;
    QPushButton *btnInput;
    QPushButton *btnOutput;
    QLabel *lblInput;
    QLabel *lblOutput;
    QGroupBox *boxDataConfigs;
    QLineEdit *fldTotalRelevancy;
    QLabel *lblRelevancy;
    QCheckBox *cBoxDefaultConfig;
    QLabel *lblRelevancyConfig;
    QLabel *lblTotalRelevancy;
    QPushButton *btnRun;
    QGroupBox *boxAlgoConfigs;
    QLabel *lblCombStart;
    QLineEdit *fldCombStart;
    QLineEdit *fldCombSmaller;
    QLabel *lblCombSmaller;
    QLabel *lblPercent_1;
    QGroupBox *gBoxFilterOutput;
    QLabel *lblSens;
    QCheckBox *cBoxDefaultMinSens;
    QLabel *lblPercent_2;
    QLineEdit *fldMinSens;
    QLabel *lblMinSens;
    QLabel *lblDefaultMinSens;
    QTextEdit *txtLog;
    QGroupBox *boxOutputConfigs;
    QLabel *lblFilterReport;
    QCheckBox *cBoxFilterReport;
    QLabel *lblPercent_3;
    QLabel *lblFilterSens;
    QLineEdit *fldFilterSens;
    QProgressBar *progressBar;
    QPushButton *btnAbort;
    QMenuBar *menuBar;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *mainwindow)
    {
        if (mainwindow->objectName().isEmpty())
            mainwindow->setObjectName(QStringLiteral("mainwindow"));
        mainwindow->resize(594, 650);
        mainwindow->setMinimumSize(QSize(594, 600));
        mainwindow->setMaximumSize(QSize(594, 650));
        actionHelp = new QAction(mainwindow);
        actionHelp->setObjectName(QStringLiteral("actionHelp"));
        actionHelp->setCheckable(true);
        actionSubHelp = new QAction(mainwindow);
        actionSubHelp->setObjectName(QStringLiteral("actionSubHelp"));
        actionSubAbout = new QAction(mainwindow);
        actionSubAbout->setObjectName(QStringLiteral("actionSubAbout"));
        centralWidget = new QWidget(mainwindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        fldInput = new QLineEdit(centralWidget);
        fldInput->setObjectName(QStringLiteral("fldInput"));
        fldInput->setGeometry(QRect(100, 10, 431, 21));
        fldOutput = new QLineEdit(centralWidget);
        fldOutput->setObjectName(QStringLiteral("fldOutput"));
        fldOutput->setGeometry(QRect(100, 50, 431, 21));
        btnInput = new QPushButton(centralWidget);
        btnInput->setObjectName(QStringLiteral("btnInput"));
        btnInput->setGeometry(QRect(540, 10, 41, 21));
        btnOutput = new QPushButton(centralWidget);
        btnOutput->setObjectName(QStringLiteral("btnOutput"));
        btnOutput->setGeometry(QRect(540, 50, 41, 21));
        lblInput = new QLabel(centralWidget);
        lblInput->setObjectName(QStringLiteral("lblInput"));
        lblInput->setGeometry(QRect(12, 12, 59, 16));
        lblOutput = new QLabel(centralWidget);
        lblOutput->setObjectName(QStringLiteral("lblOutput"));
        lblOutput->setGeometry(QRect(12, 47, 76, 16));
        boxDataConfigs = new QGroupBox(centralWidget);
        boxDataConfigs->setObjectName(QStringLiteral("boxDataConfigs"));
        boxDataConfigs->setGeometry(QRect(10, 90, 573, 81));
        fldTotalRelevancy = new QLineEdit(boxDataConfigs);
        fldTotalRelevancy->setObjectName(QStringLiteral("fldTotalRelevancy"));
        fldTotalRelevancy->setEnabled(false);
        fldTotalRelevancy->setGeometry(QRect(510, 50, 51, 21));
        lblRelevancy = new QLabel(boxDataConfigs);
        lblRelevancy->setObjectName(QStringLiteral("lblRelevancy"));
        lblRelevancy->setGeometry(QRect(10, 20, 251, 20));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        lblRelevancy->setFont(font);
        cBoxDefaultConfig = new QCheckBox(boxDataConfigs);
        cBoxDefaultConfig->setObjectName(QStringLiteral("cBoxDefaultConfig"));
        cBoxDefaultConfig->setGeometry(QRect(510, 20, 31, 20));
        cBoxDefaultConfig->setChecked(true);
        lblRelevancyConfig = new QLabel(boxDataConfigs);
        lblRelevancyConfig->setObjectName(QStringLiteral("lblRelevancyConfig"));
        lblRelevancyConfig->setGeometry(QRect(430, 20, 71, 20));
        QFont font1;
        font1.setItalic(false);
        lblRelevancyConfig->setFont(font1);
        lblRelevancyConfig->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblTotalRelevancy = new QLabel(boxDataConfigs);
        lblTotalRelevancy->setObjectName(QStringLiteral("lblTotalRelevancy"));
        lblTotalRelevancy->setGeometry(QRect(420, 50, 81, 20));
        lblTotalRelevancy->setFont(font1);
        lblTotalRelevancy->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        btnRun = new QPushButton(centralWidget);
        btnRun->setObjectName(QStringLiteral("btnRun"));
        btnRun->setGeometry(QRect(430, 460, 61, 21));
        QFont font2;
        font2.setBold(true);
        font2.setWeight(75);
        btnRun->setFont(font2);
        boxAlgoConfigs = new QGroupBox(centralWidget);
        boxAlgoConfigs->setObjectName(QStringLiteral("boxAlgoConfigs"));
        boxAlgoConfigs->setGeometry(QRect(10, 180, 573, 181));
        lblCombStart = new QLabel(boxAlgoConfigs);
        lblCombStart->setObjectName(QStringLiteral("lblCombStart"));
        lblCombStart->setGeometry(QRect(10, 20, 491, 20));
        lblCombStart->setFont(font1);
        lblCombStart->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        fldCombStart = new QLineEdit(boxAlgoConfigs);
        fldCombStart->setObjectName(QStringLiteral("fldCombStart"));
        fldCombStart->setGeometry(QRect(510, 20, 41, 21));
        fldCombSmaller = new QLineEdit(boxAlgoConfigs);
        fldCombSmaller->setObjectName(QStringLiteral("fldCombSmaller"));
        fldCombSmaller->setGeometry(QRect(510, 50, 41, 21));
        lblCombSmaller = new QLabel(boxAlgoConfigs);
        lblCombSmaller->setObjectName(QStringLiteral("lblCombSmaller"));
        lblCombSmaller->setGeometry(QRect(10, 50, 491, 20));
        lblCombSmaller->setFont(font1);
        lblCombSmaller->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblPercent_1 = new QLabel(boxAlgoConfigs);
        lblPercent_1->setObjectName(QStringLiteral("lblPercent_1"));
        lblPercent_1->setGeometry(QRect(551, 20, 16, 20));
        QFont font3;
        font3.setItalic(true);
        lblPercent_1->setFont(font3);
        lblPercent_1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        gBoxFilterOutput = new QGroupBox(boxAlgoConfigs);
        gBoxFilterOutput->setObjectName(QStringLiteral("gBoxFilterOutput"));
        gBoxFilterOutput->setGeometry(QRect(10, 90, 551, 81));
        gBoxFilterOutput->setFont(font);
        lblSens = new QLabel(gBoxFilterOutput);
        lblSens->setObjectName(QStringLiteral("lblSens"));
        lblSens->setGeometry(QRect(0, 20, 211, 20));
        lblSens->setFont(font);
        lblSens->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        cBoxDefaultMinSens = new QCheckBox(gBoxFilterOutput);
        cBoxDefaultMinSens->setObjectName(QStringLiteral("cBoxDefaultMinSens"));
        cBoxDefaultMinSens->setGeometry(QRect(490, 20, 31, 20));
        cBoxDefaultMinSens->setChecked(true);
        lblPercent_2 = new QLabel(gBoxFilterOutput);
        lblPercent_2->setObjectName(QStringLiteral("lblPercent_2"));
        lblPercent_2->setGeometry(QRect(530, 50, 16, 20));
        lblPercent_2->setFont(font3);
        lblPercent_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        fldMinSens = new QLineEdit(gBoxFilterOutput);
        fldMinSens->setObjectName(QStringLiteral("fldMinSens"));
        fldMinSens->setEnabled(false);
        fldMinSens->setGeometry(QRect(490, 50, 41, 21));
        lblMinSens = new QLabel(gBoxFilterOutput);
        lblMinSens->setObjectName(QStringLiteral("lblMinSens"));
        lblMinSens->setGeometry(QRect(410, 50, 71, 20));
        lblMinSens->setFont(font1);
        lblMinSens->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblDefaultMinSens = new QLabel(gBoxFilterOutput);
        lblDefaultMinSens->setObjectName(QStringLiteral("lblDefaultMinSens"));
        lblDefaultMinSens->setGeometry(QRect(230, 20, 251, 20));
        lblDefaultMinSens->setFont(font1);
        lblDefaultMinSens->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        txtLog = new QTextEdit(centralWidget);
        txtLog->setObjectName(QStringLiteral("txtLog"));
        txtLog->setEnabled(true);
        txtLog->setGeometry(QRect(10, 490, 571, 101));
        boxOutputConfigs = new QGroupBox(centralWidget);
        boxOutputConfigs->setObjectName(QStringLiteral("boxOutputConfigs"));
        boxOutputConfigs->setGeometry(QRect(10, 370, 571, 81));
        lblFilterReport = new QLabel(boxOutputConfigs);
        lblFilterReport->setObjectName(QStringLiteral("lblFilterReport"));
        lblFilterReport->setGeometry(QRect(90, 20, 411, 20));
        lblFilterReport->setFont(font1);
        lblFilterReport->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        cBoxFilterReport = new QCheckBox(boxOutputConfigs);
        cBoxFilterReport->setObjectName(QStringLiteral("cBoxFilterReport"));
        cBoxFilterReport->setGeometry(QRect(510, 20, 31, 20));
        cBoxFilterReport->setChecked(true);
        lblPercent_3 = new QLabel(boxOutputConfigs);
        lblPercent_3->setObjectName(QStringLiteral("lblPercent_3"));
        lblPercent_3->setGeometry(QRect(550, 50, 16, 20));
        lblPercent_3->setFont(font3);
        lblPercent_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblFilterSens = new QLabel(boxOutputConfigs);
        lblFilterSens->setObjectName(QStringLiteral("lblFilterSens"));
        lblFilterSens->setGeometry(QRect(260, 50, 241, 20));
        lblFilterSens->setFont(font1);
        lblFilterSens->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        fldFilterSens = new QLineEdit(boxOutputConfigs);
        fldFilterSens->setObjectName(QStringLiteral("fldFilterSens"));
        fldFilterSens->setEnabled(true);
        fldFilterSens->setGeometry(QRect(510, 50, 41, 21));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(10, 460, 411, 23));
        progressBar->setValue(24);
        btnAbort = new QPushButton(centralWidget);
        btnAbort->setObjectName(QStringLiteral("btnAbort"));
        btnAbort->setGeometry(QRect(520, 460, 61, 21));
        mainwindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(mainwindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 594, 22));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        mainwindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(mainwindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainwindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(mainwindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        mainwindow->setStatusBar(statusBar);
        QWidget::setTabOrder(fldInput, btnInput);
        QWidget::setTabOrder(btnInput, fldOutput);
        QWidget::setTabOrder(fldOutput, btnOutput);
        QWidget::setTabOrder(btnOutput, fldMinSens);
        QWidget::setTabOrder(fldMinSens, btnRun);

        menuBar->addAction(menuHelp->menuAction());
        menuHelp->addAction(actionSubHelp);
        menuHelp->addAction(actionSubAbout);

        retranslateUi(mainwindow);

        QMetaObject::connectSlotsByName(mainwindow);
    } // setupUi

    void retranslateUi(QMainWindow *mainwindow)
    {
        mainwindow->setWindowTitle(QApplication::translate("mainwindow", "SensPrecOptimizer", 0));
        actionHelp->setText(QApplication::translate("mainwindow", "Help", 0));
        actionHelp->setShortcut(QApplication::translate("mainwindow", "Alt+H", 0));
        actionSubHelp->setText(QApplication::translate("mainwindow", "Help", 0));
        actionSubAbout->setText(QApplication::translate("mainwindow", "About", 0));
#ifndef QT_NO_TOOLTIP
        fldInput->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        fldInput->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        fldInput->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_ACCESSIBILITY
        fldInput->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
#ifndef QT_NO_ACCESSIBILITY
        fldInput->setAccessibleDescription(QString());
#endif // QT_NO_ACCESSIBILITY
        fldInput->setText(QString());
        fldOutput->setText(QString());
        btnInput->setText(QApplication::translate("mainwindow", "...", 0));
        btnOutput->setText(QApplication::translate("mainwindow", "...", 0));
        lblInput->setText(QApplication::translate("mainwindow", "Input File", 0));
        lblOutput->setText(QApplication::translate("mainwindow", "Output Path", 0));
        boxDataConfigs->setTitle(QApplication::translate("mainwindow", "Configure Data", 0));
        fldTotalRelevancy->setText(QApplication::translate("mainwindow", "1", 0));
        lblRelevancy->setText(QApplication::translate("mainwindow", "Total Number of Relevant Documents:", 0));
        cBoxDefaultConfig->setText(QString());
        lblRelevancyConfig->setText(QApplication::translate("mainwindow", "Default", 0));
        lblTotalRelevancy->setText(QApplication::translate("mainwindow", "Custom", 0));
        btnRun->setText(QApplication::translate("mainwindow", "Run", 0));
        boxAlgoConfigs->setTitle(QApplication::translate("mainwindow", "Configure Algorithm", 0));
        lblCombStart->setText(QApplication::translate("mainwindow", "Combinations Iterations - The Starting Point ", 0));
        fldCombStart->setText(QApplication::translate("mainwindow", "75", 0));
        fldCombSmaller->setText(QApplication::translate("mainwindow", "0", 0));
        lblCombSmaller->setText(QApplication::translate("mainwindow", "Combinations Iterations - The Number of Additional Smaller Neighbours ", 0));
        lblPercent_1->setText(QApplication::translate("mainwindow", "%", 0));
        gBoxFilterOutput->setTitle(QApplication::translate("mainwindow", "Runtime Filtering of Output", 0));
        lblSens->setText(QApplication::translate("mainwindow", "Acceptable Minumum Sensitivity:", 0));
        cBoxDefaultMinSens->setText(QString());
        lblPercent_2->setText(QApplication::translate("mainwindow", "%", 0));
        fldMinSens->setText(QApplication::translate("mainwindow", "5", 0));
        lblMinSens->setText(QApplication::translate("mainwindow", "Custom", 0));
        lblDefaultMinSens->setText(QApplication::translate("mainwindow", "Default", 0));
        boxOutputConfigs->setTitle(QApplication::translate("mainwindow", "Configure Output Filter", 0));
        lblFilterReport->setText(QApplication::translate("mainwindow", "Short Report by Minimising Search Strategies' Length", 0));
        cBoxFilterReport->setText(QString());
        lblPercent_3->setText(QApplication::translate("mainwindow", "%", 0));
        lblFilterSens->setText(QApplication::translate("mainwindow", "Report within Sensitivity Range of ", 0));
        fldFilterSens->setText(QApplication::translate("mainwindow", "100", 0));
        btnAbort->setText(QApplication::translate("mainwindow", "Abort", 0));
        menuHelp->setTitle(QApplication::translate("mainwindow", "Help", 0));
        mainToolBar->setWindowTitle(QApplication::translate("mainwindow", "SenPrecOptim", 0));
    } // retranslateUi

};

namespace Ui {
    class mainwindow: public Ui_mainwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
