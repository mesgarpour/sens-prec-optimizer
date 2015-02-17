/*! \file mainwindow.cpp
    \brief the mainwindow of the application

    \see QMainWindow
    \see logger
*/
/*! \fn mainwindow::mainwindow(QString appPath, QWidget *parent)
    \brief initialises the mainwindow and the internal parameters and enforce
        the first stage of the input validation

    \param appPath the default application path
    \param parent the QWidget parent
*/
/*! \fn mainwindow::~mainwindow()
    \brief the destrctor of the UI
*/
/*! \fn void mainwindow::on_btnInput_clicked()
    \brief the 'click' action method for the 'btnInput' that opens a QFileDialog

    \see QFileDialog
*/
/*! \fn void mainwindow::on_btnOutput_clicked()
    \brief the 'click' action method for the 'btnOutput' that opens a QFileDialog

    \see QFileDialog
*/
/*! \fn void mainwindow::on_btnRun_clicked()
    \brief the 'click' action method for the 'btnRun' which execute the algorithm

    \see QFileDialog
    \see mainwindow::runAlgoIteration
*/
/*! \fn bool mainwindow::validate()
    \brief the second stage of input validatation

    \return true if it passed the validation
*/
/*! \fn void mainwindow::slot_finished()
    \brief the signal slot for the 'finished', which is called when an iteration
        of the algorithm is finished

    \see QFuture
    \see mainwindow::runAlgoIteration
*/
/*! \fn void mainwindow::runAlgoIteration()
    \brief run an algorithm iteration

    \see manager::run
*/
/*! \fn void mainwindow::reset()
    \brief reset the application
*/
/*! \fn void mainwindow::on_rbtnDataConfAdvanced_clicked(bool checked)
    \brief the 'click' action method for the 'rbtnDataConfAdvanced' to en/disable fields

    \param checked the checkbox's value
*/
/*! \fn void mainwindow::on_rbtnDataConfDefault_clicked(bool checked)
    \brief the 'click' action method for the 'rbtnDataConfDefault' to en/disable fields

    \param checked the checkbox's value
*/
/*! \fn void mainwindow::on_actionSubHelp_triggered()
    \brief the 'triger' action for the 'SubHelp' menu to open the help file

    \see mainwindow::openTextEdit
*/
/*! \fn void mainwindow::on_actionSubAbout_triggered()
    \brief the 'triger' action for the 'SubAbout' menu to open the help file

    \see mainwindow::openTextEdit
*/
/*! \fn void mainwindow::openTextEdit(std::string path, bool external)
    \brief open a textedit Interface to show a text file

    \param message the file to be outputed
    \param external TRUE if it is an external link
    \see QTextBrowser
*/
/*! \fn void mainwindow::on_btnAbort_clicked()
    \brief the 'click' action for the 'btnAbort' button to abort the execution
*/

#include <QFileDialog>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QFileInfo>
#include <QDesktopServices>
#include <QTimeLine>
#include <QtConcurrent/QtConcurrent>
#include <QTextBrowser>
#include <string>
#include <limits>
#include <time.h>
#include <iostream>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "Global.h"

mainwindow::mainwindow(QString appPath, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainwindow),
    m_appPath(appPath)
{
    ui->setupUi(this);
    QDoubleValidator *doubleValidator = new QDoubleValidator(0, 100, 2, this);

    //QLineEdit Validators
    ui->fldTotalRelevancy->setValidator(
                new QIntValidator(1, std::numeric_limits<int>::max(), this));
    ui->fldCombStart->setValidator(doubleValidator);
    ui->fldCombSmaller->setValidator(doubleValidator);
    ui->fldMinSens->setValidator(doubleValidator);
    ui->fldFilterSens->setValidator(doubleValidator);
    ui->progressBar->setRange(0, 0);

    //QLineEdit Masks
    //ui->fldInput->setInputMask();
    //ui->fldOutput->setInputMask();
    ui->fldTotalRelevancy->setInputMask("0000000000000");
    ui->fldCombStart->setInputMask("000");
    ui->fldCombSmaller->setInputMask("00");
    ui->fldMinSens->setInputMask("000.00");
    ui->fldFilterSens->setInputMask("000.00");

    //QLineEdit Max Length
    ui->fldTotalRelevancy->setMaxLength(13);
    ui->fldCombStart->setMaxLength(3);
    ui->fldCombSmaller->setMaxLength(2);
    ui->fldMinSens->setMaxLength(6);
    ui->fldFilterSens->setMaxLength(6);

    //set
    ui->fldTotalRelevancy->setEnabled(false);
    ui->fldFilterSens->setEnabled(true);
    ui->txtLog->setReadOnly(true);
    ui->fldInput->setText(m_appPath);
    ui->fldOutput->setText(m_appPath);
    //ui->fldTotalRelevancy->set

    //The progress-bar
    ui->progressBar->hide();
    ui->progressBar->setValue(0);
    ui->lblTotalRelevancy->setVisible(false);
    ui->fldTotalRelevancy->setVisible(false);
    ui->lblMinSens->setVisible(false);
    ui->fldMinSens->setVisible(false);
    ui->lblPercent_2->setVisible(false);
    QObject::connect(&m_futureWatcher,
                     SIGNAL(finished()),
                     this,
                     SLOT(slot_finished()));
}

mainwindow::~mainwindow()
{
    delete ui;
}

void mainwindow::on_btnInput_clicked()
{
    QString inputFile = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                m_appPath, //"/home",
                tr("Comma Seperated File (*.csv)"));
    ui->fldInput->setText(inputFile);
}

void mainwindow::on_btnOutput_clicked()
{
    QString outputDir = QFileDialog::getExistingDirectory(
                this,
                tr("Open Directory"),
                m_appPath, //"/home",
                QFileDialog::ShowDirsOnly |
                QFileDialog::DontResolveSymlinks);
    ui->fldOutput->setText(outputDir);
}

void mainwindow::on_btnRun_clicked()
{
    //Set the parameters
    ui->btnRun->setEnabled(false);
    m_parameters.reset();
    m_parameters.m_config.inputFile = ui->fldInput->text().toStdString();
    m_parameters.m_config.outputDir = ui->fldOutput->text().toStdString();
    m_parameters.m_config.defaultInputDataConfig = ui->cBoxDefaultConfig->isChecked();
    if(!ui->cBoxDefaultConfig->isChecked())
    {
        m_parameters.m_config.totalDocRelevancy = ui->fldTotalRelevancy->text().toInt();
    }
    m_parameters.m_config.combStart = ui->fldCombStart->text().toFloat();
    m_parameters.m_config.combSmaller = ui->fldCombSmaller->text().toInt();
    m_parameters.m_config.defaultMinSensitivity = ui->cBoxDefaultMinSens->isChecked();
    if(ui->cBoxDefaultMinSens->isChecked())
    {
        m_parameters.m_config.minSensitiviy = ui->fldMinSens->text().toFloat();
    }
    m_parameters.m_config.filterMinimizeLength = ui->cBoxFilterReport->isChecked();
    m_parameters.m_config.filterSensRange = ui->fldFilterSens->text().toFloat();

    //Run the Algorithm
    if(validate())
    {
        ui->txtLog->clear();
        ui->progressBar->show();
        m_logMsg = m_AlgoManager.set(m_parameters);
        if(m_logMsg.errors == true)
        {
            m_msgBox.setText(QString::fromStdString(
                                 "Error in settings/data interupted the algorithm!\n" +
                                 m_logMsg.message));
            m_msgBox.exec();
            reset();
            return;
        }
        runAlgoIteration();
    }else
    {
        reset();
    }
}


bool mainwindow::validate()
{
    if((m_parameters.m_config.inputFile.length() == 0) ||
            (m_parameters.m_config.outputDir.length() == 0) ||
            (m_parameters.m_config.combStart <= 0) ||
            (m_parameters.m_config.combStart > 100) ||
            (m_parameters.m_config.combSmaller > MAX_FSS) ||
            (m_parameters.m_config.minSensitiviy < 0) ||
            (m_parameters.m_config.minSensitiviy > 100) ||
            (m_parameters.m_config.filterSensRange < 0) ||
            (m_parameters.m_config.filterSensRange > 100) ||
            (!m_parameters.m_config.defaultInputDataConfig &&
             (m_parameters.m_config.totalDocRelevancy < 1)))
    {
        m_msgBox.setText(QString::fromStdString("Invalid field(s)!"));
        m_msgBox.exec();
        return false;
    }

    //Check file
    QFileInfo inputFileInfo(m_parameters.m_config.inputFile.c_str());
    if((inputFileInfo.suffix() != QString::fromStdString("csv")) ||
            (!inputFileInfo.exists()))
    {
        m_msgBox.setText(QString::fromStdString("Invalid input file!"));
        m_msgBox.exec();
        return false;
    }
    return true;
}

void mainwindow::slot_finished()
{
    std::string msg;

    try{
        if(!m_future.isCanceled())
        {
            m_future.waitForFinished();
            m_logMsg = m_future.result();
            msg = m_logMsg.message;
            if(m_logMsg.errors == true){throw;}
            ui->txtLog->append(QString::fromStdString(msg));

            if(m_logMsg.iteration > 0)
            {
                runAlgoIteration();
                return;
            }
        }
    }catch(...)
    {
        m_future.cancel();
        m_msgBox.setText(QString::fromStdString(
                             "Error in settings/data interupted the algorithm!\n" +
                             msg));
        m_msgBox.exec();
    }

    reset();
    return;
}

void mainwindow::runAlgoIteration()
{
    m_future = QtConcurrent::run(
                &m_AlgoManager,
                &manager::run);
    m_futureWatcher.setFuture(m_future);
}

void mainwindow::reset()
{
    try
    {
        m_future.cancel();
        m_parameters.reset();
        ui->progressBar->hide();
        ui->btnRun->setEnabled(true);
        m_logMsg = logger::strcAlgoReport();
    }catch(...)
    {
        m_msgBox.setText(QString::fromStdString(
                             "Error in resetting the processes!\n"));
        m_msgBox.exec();
    }
}

void mainwindow::on_cBoxDefaultConfig_clicked(bool checked)
{
    ui->fldTotalRelevancy->setEnabled(!checked);
    ui->lblTotalRelevancy->setVisible(!checked);
    ui->fldTotalRelevancy->setVisible(!checked);
}

void mainwindow::on_cBoxDefaultMinSens_clicked(bool checked)
{
    ui->fldMinSens->setEnabled(!checked);
    ui->lblMinSens->setVisible(!checked);
    ui->fldMinSens->setVisible(!checked);
    ui->lblPercent_2->setVisible(!checked);
}

void mainwindow::on_actionSubHelp_triggered()
{
    openTextEdit(HELP_PATH, true);
}

void mainwindow::on_actionSubAbout_triggered()
{
    openTextEdit(ABOUT_PATH);
}

void mainwindow::openTextEdit(std::string path, bool external)
{
    QString qPath = QString::fromStdString(path);
    QTextBrowser *b = new QTextBrowser();

    if(external)
    {
        b->setOpenExternalLinks(external);
        QDesktopServices::openUrl(QUrl(qPath, QUrl::TolerantMode));

    }else
    {
        b->setSource(qPath);
        b->setEnabled(true);
        b->show();
    }
}

void mainwindow::on_btnAbort_clicked()
{
    if(m_logMsg.iteration > 0 &&
            !m_future.isCanceled())
    {
        reset();
        ui->txtLog->append(QString::fromStdString("\n\nAborted!"));
    }
}
