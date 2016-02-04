/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -N -p filemonitor_interface.h:filemonitor_interface.cpp -c FileMonitorInterface filemonitor.xml
 *
 * qdbusxml2cpp is Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef FILEMONITOR_INTERFACE_H_1436253302
#define FILEMONITOR_INTERFACE_H_1436253302

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface com.deepin.filemanager.Backend.Monitor.Manager
 */
class FileMonitorInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "com.deepin.filemanager.Backend.Monitor.Manager"; }

public:
    FileMonitorInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~FileMonitorInterface();

    Q_PROPERTY(uint FileMonitorEventAttributeChanged READ fileMonitorEventAttributeChanged)
    inline uint fileMonitorEventAttributeChanged() const
    { return qvariant_cast< uint >(property("FileMonitorEventAttributeChanged")); }

    Q_PROPERTY(uint FileMonitorEventChanged READ fileMonitorEventChanged)
    inline uint fileMonitorEventChanged() const
    { return qvariant_cast< uint >(property("FileMonitorEventChanged")); }

    Q_PROPERTY(uint FileMonitorEventChangesDoneHint READ fileMonitorEventChangesDoneHint)
    inline uint fileMonitorEventChangesDoneHint() const
    { return qvariant_cast< uint >(property("FileMonitorEventChangesDoneHint")); }

    Q_PROPERTY(uint FileMonitorEventCreated READ fileMonitorEventCreated)
    inline uint fileMonitorEventCreated() const
    { return qvariant_cast< uint >(property("FileMonitorEventCreated")); }

    Q_PROPERTY(uint FileMonitorEventDeleted READ fileMonitorEventDeleted)
    inline uint fileMonitorEventDeleted() const
    { return qvariant_cast< uint >(property("FileMonitorEventDeleted")); }

    Q_PROPERTY(uint FileMonitorEventMoved READ fileMonitorEventMoved)
    inline uint fileMonitorEventMoved() const
    { return qvariant_cast< uint >(property("FileMonitorEventMoved")); }

    Q_PROPERTY(uint FileMonitorEventPreUnmount READ fileMonitorEventPreUnmount)
    inline uint fileMonitorEventPreUnmount() const
    { return qvariant_cast< uint >(property("FileMonitorEventPreUnmount")); }

    Q_PROPERTY(uint FileMonitorEventUnmounted READ fileMonitorEventUnmounted)
    inline uint fileMonitorEventUnmounted() const
    { return qvariant_cast< uint >(property("FileMonitorEventUnmounted")); }

    Q_PROPERTY(uint FileMonitorFlagsNone READ fileMonitorFlagsNone)
    inline uint fileMonitorFlagsNone() const
    { return qvariant_cast< uint >(property("FileMonitorFlagsNone")); }

    Q_PROPERTY(uint FileMonitorFlagsSendMoved READ fileMonitorFlagsSendMoved)
    inline uint fileMonitorFlagsSendMoved() const
    { return qvariant_cast< uint >(property("FileMonitorFlagsSendMoved")); }

    Q_PROPERTY(uint FileMonitorFlagsWatchHardLinks READ fileMonitorFlagsWatchHardLinks)
    inline uint fileMonitorFlagsWatchHardLinks() const
    { return qvariant_cast< uint >(property("FileMonitorFlagsWatchHardLinks")); }

    Q_PROPERTY(uint FileMonitorFlagsWatchMounts READ fileMonitorFlagsWatchMounts)
    inline uint fileMonitorFlagsWatchMounts() const
    { return qvariant_cast< uint >(property("FileMonitorFlagsWatchMounts")); }

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<QDBusObjectPath, QString> Monitor(const QString &in0, uint in1)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0) << QVariant::fromValue(in1);
        return asyncCallWithArgumentList(QStringLiteral("Monitor"), argumentList);
    }
    inline QDBusReply<QDBusObjectPath> Monitor(const QString &in0, uint in1, QString &out1)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0) << QVariant::fromValue(in1);
        QDBusMessage reply = callWithArgumentList(QDBus::Block, QStringLiteral("Monitor"), argumentList);
        if (reply.type() == QDBusMessage::ReplyMessage && reply.arguments().count() == 2) {
            out1 = qdbus_cast<QString>(reply.arguments().at(1));
        }
        return reply;
    }

    inline QDBusPendingReply<> Unmonitor(uint in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QStringLiteral("Unmonitor"), argumentList);
    }

Q_SIGNALS: // SIGNALS
};

#endif
