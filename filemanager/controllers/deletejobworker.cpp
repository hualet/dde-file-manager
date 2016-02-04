#include "deletejobworker.h"
#include "dbusinterface/deletejob_interface.h"
#include "dbusinterface/fileoperations_interface.h"
#include "dialogs/confirmdeletedialog.h"
#include "../app/global.h"

DeletejobWorker::DeletejobWorker(const QStringList &files, QObject *parent):
    QObject(parent),
    m_deletefiles(files)
{
    m_progressTimer = new QTimer;
    m_progressTimer->setInterval(1000);
    m_time = new QTime;
    initConnect();
}

void DeletejobWorker::initConnect(){
    connect(this, SIGNAL(startJob()), this, SLOT(start()));
    connect(this, SIGNAL(finished()), this, SLOT(handleFinished()));
    connect(m_progressTimer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
    connect(signalManager, SIGNAL(abortDeleteTask(QMap<QString,QString>)),
            this, SLOT(handleTaskAborted(QMap<QString,QString>)));
}

void DeletejobWorker::start(){
    deleteFiles(m_deletefiles);
}

void DeletejobWorker::deleteFiles(const QStringList &files){
    qDebug() << "delete" <<files;
    QDBusPendingReply<QString, QDBusObjectPath, QString> reply = dbusController->getFileOperationsInterface()->NewDeleteJob(files, false, "", "", "");
    reply.waitForFinished();
    if (!reply.isError()){
        QString service = reply.argumentAt(0).toString();
        QString path = qdbus_cast<QDBusObjectPath>(reply.argumentAt(1)).path();
        qDebug() << "delete files" << files << path;

        m_deletejobPath = path;
        m_jobDetail.insert("jobPath", path);
        m_jobDetail.insert("type", "delete");

        m_deleteJobInterface = new DeleteJobInterface(service, path, QDBusConnection::sessionBus(), this);
        connectDeleteJobSignal();
        m_deleteJobInterface->Execute();

        m_progressTimer->start();
        m_time->start();
        emit signalManager->deleteJobAdded(m_jobDetail);
    }else{
        qCritical() << reply.error().message();
    }
}

void DeletejobWorker::connectDeleteJobSignal(){
    if (m_deleteJobInterface){
        connect(m_deleteJobInterface, SIGNAL(Done()), this, SLOT(deleteJobExcuteFinished()));
        connect(m_deleteJobInterface, SIGNAL(Aborted()), this, SLOT(deleteJobAbortFinished()));
        connect(m_deleteJobInterface, SIGNAL(Deleting(QString)), this, SLOT(onDeletingFile(QString)));
        connect(m_deleteJobInterface, SIGNAL(TotalAmount(qlonglong,ushort)),
                this, SLOT(setTotalAmount(qlonglong,ushort)));
        connect(m_deleteJobInterface, SIGNAL(ProcessedAmount(qlonglong,ushort)),
                this, SLOT(onDeletingProcessAmount(qlonglong,ushort)));
        connect(m_deleteJobInterface, SIGNAL(ProcessedPercent(qlonglong)),
                this, SLOT(onProcessedPercent(qlonglong)));
    }
}

void DeletejobWorker::disconnectDeleteJobSignal(){
    if (m_deleteJobInterface){
        disconnect(m_deleteJobInterface, SIGNAL(Done()), this, SLOT(deleteJobExcuteFinished()));
        disconnect(m_deleteJobInterface, SIGNAL(Aborted()), this, SLOT(deleteJobAbortFinished()));
        disconnect(m_deleteJobInterface, SIGNAL(Deleting(QString)), this, SLOT(onDeletingFile(QString)));
        disconnect(m_deleteJobInterface, SIGNAL(TotalAmount(qlonglong,ushort)),
                this, SLOT(setTotalAmount(qlonglong,ushort)));
        disconnect(m_deleteJobInterface, SIGNAL(ProcessedAmount(qlonglong,ushort)),
                this, SLOT(onDeletingProcessAmount(qlonglong,ushort)));
        disconnect(m_deleteJobInterface, SIGNAL(ProcessedPercent(qlonglong)),
                this, SLOT(onProcessedPercent(qlonglong)));
    }
}


void DeletejobWorker::deleteJobExcuteFinished(){
    disconnectDeleteJobSignal();
    m_deleteJobInterface->deleteLater();
    m_deleteJobInterface = NULL;
    m_deletefiles.clear();
    m_progressTimer->stop();
    emit finished();
    qDebug() << "delete job finished";
}

void DeletejobWorker::deleteJobAbort(){
    if (m_deleteJobInterface){
        m_progressTimer->stop();
        m_deleteJobInterface->Abort();
    }
}

void DeletejobWorker::deleteJobAbortFinished(){
    deleteJobExcuteFinished();
    qDebug() << "delete job aborted";
}


void DeletejobWorker::onDeletingFile(QString file){
    emit signalManager->deletingFileChaned(file);
    qDebug() << "onDeletingFile" << file;

    m_jobDataDetail.insert("file", QFileInfo(decodeUrl(file)).fileName());
    qDebug() << "onCopyingFile" << file;
    if (m_jobDetail.contains("jobPath")){
        emit signalManager->deleteJobDataUpdated(m_jobDetail, m_jobDataDetail);
    }

}

void DeletejobWorker::setTotalAmount(qlonglong amount, ushort type){
    qDebug() << "========="<< amount << type;
    if (type == 0){
        m_totalAmout = amount;
    }
}

void DeletejobWorker::onDeletingProcessAmount(qlonglong progress, ushort info){
    if (info == 0){
        m_currentProgress = progress;
    }
    qDebug() << "onDeletingProcessAmount" << progress << info;
}

void DeletejobWorker::onProcessedPercent(qlonglong percent){
    m_processedPercent = percent;
    m_jobDataDetail.insert("progress", QString::number(percent));
    qDebug() << percent;
}

void DeletejobWorker::handleTimeout(){
    float speed;
    int remainTime;
    QString speedString;
    if (m_currentProgress - m_lastProgress > 1024 *1024){
        speed = (m_currentProgress - m_lastProgress) / (1024 * 1024);
        speedString = QString("%1 M/s").arg(QString::number(speed));
    }else{
        speed = (m_currentProgress - m_lastProgress) / 1024;
        speedString = QString("%1 Kb/s").arg(QString::number(speed));
    }
    if (m_currentProgress - m_lastProgress > 0){
        remainTime = (m_totalAmout - m_currentProgress) / (m_currentProgress - m_lastProgress);
    }
    m_lastProgress = m_currentProgress;

    m_jobDataDetail.insert("speed", speedString);
    m_jobDataDetail.insert("remainTime", QString("%1 s").arg(QString::number(remainTime)));
    emit signalManager->deleteJobDataUpdated(m_jobDetail, m_jobDataDetail);
}

void DeletejobWorker::handleFinished(){
    if (m_jobDetail.contains("jobPath")){
        emit signalManager->deleteJobRemoved(m_jobDetail);
    }
}

void DeletejobWorker::handleTaskAborted(const QMap<QString, QString> &jobDetail){
    if (jobDetail == m_jobDetail){
        deleteJobAbort();
    }
}

DeletejobWorker::~DeletejobWorker()
{

}
