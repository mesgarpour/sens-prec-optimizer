#ifndef mainwindow_H
#define mainwindow_H

#include <Qmainwindow>
#include <QMessageBox>
#include <QFutureWatcher>
#include <QString>
#include "parameters.h"
#include "manager.h"
#include "logger.h"

namespace Ui
{
    class mainwindow;
}

class mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainwindow(QString appPath, QWidget *parent = 0);
    ~mainwindow();
    parameters getPrameters();

private:
    bool validate();
    void runAlgoIteration();
    void reset();

private slots:
    void on_btnInput_clicked();
    void on_btnOutput_clicked();
    void on_btnRun_clicked();
    void on_cBoxDefaultConfig_clicked(bool checked);
    void on_cBoxDefaultMinSens_clicked(bool checked);
    void on_actionSubHelp_triggered();
    void on_actionSubAbout_triggered();
    void on_btnAbort_clicked();
    void slot_finished();

private:
    Ui::mainwindow *ui; ///< user-interface instance
    manager m_AlgoManager; ///< algorithm manger instance
    QFutureWatcher<void> m_futureWatcher; ///< 'future' watcher of the threaded task
    logger::strcAlgoReport m_logMsg; ///< log instance
    QMessageBox m_msgBox; ///< message box instance
    parameters m_parameters; ///< parameter instance
    QFuture<logger::strcAlgoReport> m_future; ///< 'future' parameter for the thread
    QString m_appPath; ///< application path
    void openTextEdit(std::string path,
                      bool external = false);

signals://virtual signal functions
    void finished();
};

#endif // mainwindow_H
