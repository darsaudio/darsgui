#include <stdlib.h>
#include "darsaudio.h"
#include <QtDebug>

DarsAudio* DarsAudio::_instance = nullptr;

DarsAudio::DarsAudio()
{
    char *addr = getenv("PULSE_DBUS_SERVER");
    if (addr) {
        mDarsDbusAddr = QString(addr);
    }
    else {
        findDarsDbusAddr();
    }

}

DarsAudio *DarsAudio::getInstance()
{
    if (!_instance) {
        _instance = new DarsAudio();
    }

    return _instance;
}

QString DarsAudio::findDarsDbusAddr()
{
    DBusError err;
    int ret = 0;
    DBusConnection *session = NULL;
    DBusMessage *msg = NULL;
    DBusMessage *reply = NULL;
    char *addr = NULL;
    DBusMessageIter iter;
    DBusMessageIter sub;
    const char *intf_STRING = "org.PulseAudio.ServerLookup1";
    const char *arg_STRING = "Address";

    dbus_error_init(&err);

    if (!mDarsDbusAddr.isEmpty()) {
        return mDarsDbusAddr;
    }

    // find it from session bus
    session = dbus_bus_get(DBUS_BUS_SESSION, &err);
    if (!session) {
        ret = -1;
        goto out;
    }
    msg = dbus_message_new_method_call(
            "org.PulseAudio1", // destination
            "/org/pulseaudio/server_lookup1", // path
            "org.freedesktop.DBus.Properties", // interface
            "Get"
            );
    if (!msg) {
        ret = -1;
        goto out;
    }
    if (!dbus_message_append_args(msg,  DBUS_TYPE_STRING, &intf_STRING,
                DBUS_TYPE_STRING, &arg_STRING, DBUS_TYPE_INVALID)) {
        ret = -1;
        goto out;
    }
    reply = dbus_connection_send_with_reply_and_block(session, msg, DBUS_TIMEOUT_INFINITE, &err );
    if (!reply) {
        ret = -1;
        goto out;
    }

    dbus_message_iter_init(reply, &iter);
    int type;
    while ((type = dbus_message_iter_get_arg_type(&iter)) != DBUS_TYPE_INVALID) {
        if (type == DBUS_TYPE_VARIANT) {
            dbus_message_iter_recurse(&iter, &sub);
            type = dbus_message_iter_get_arg_type(&sub);
            if (type == DBUS_TYPE_STRING) {
                dbus_message_iter_get_basic(&sub, &addr);
                if (addr) {
                    mDarsDbusAddr = addr;
                    ret = 0;
                    break;
                }
            }
        }
        dbus_message_iter_next(&iter);
    }

out:
    if (msg)
        dbus_message_unref(msg);
    if (reply)
        dbus_message_unref(reply);
    if (session)
        dbus_connection_unref(session);

    if (ret) {
        mDarsDbusAddr = "";
    }

    return mDarsDbusAddr;
}

QString DarsAudio::getDarsDbusProperty(const char* name)
{
    char *value = NULL;
    QString pvalue;
    DBusError err;
    DBusConnection *conn = NULL;
    DBusMessage *msg = NULL;
    DBusMessage *reply = NULL;
    DBusMessageIter iter;
    DBusMessageIter sub;
    const char *intf_STRING = "org.PulseAudio.Ext.Dars.Controller";

    dbus_error_init(&err);
    conn = dbus_connection_open_private(mDarsDbusAddr.toStdString().c_str(), &err);
    if (!conn) {
        qWarning() << "Can not connect";
        return QString("");
    }

    msg = dbus_message_new_method_call(
            "org.PulseAudio.Ext.Dars.Controller", // destination
            "/org/pulseaudio/dars", // path
            "org.freedesktop.DBus.Properties", // interface
            "Get"
            );
    if (!msg) {
        pvalue="";
        qWarning() << "dbus_message_new_method_call Error";
        goto out;
    }

    if (!dbus_message_append_args(msg,  DBUS_TYPE_STRING, &intf_STRING,
                                        DBUS_TYPE_STRING, &name, DBUS_TYPE_INVALID)) {
        pvalue = "";
        qWarning() << "dbus_message_append_args Error";
        goto out;
    }

    reply = dbus_connection_send_with_reply_and_block(conn, msg, DBUS_TIMEOUT_INFINITE, &err );
    if (!reply) {
        pvalue = "";
        qWarning() << "dbus_connection_send_with_reply_and_block Error";
        goto out;
    }

    dbus_message_iter_init(reply, &iter);
    int type;
    while ((type = dbus_message_iter_get_arg_type(&iter)) != DBUS_TYPE_INVALID) {
        if (type == DBUS_TYPE_VARIANT) {
            dbus_message_iter_recurse(&iter, &sub);
            type = dbus_message_iter_get_arg_type(&sub);
            if (type == DBUS_TYPE_STRING) {
                dbus_message_iter_get_basic(&sub, &value);
                if (value) {
                    pvalue = value;
                    break;
                }
            }
        }
        dbus_message_iter_next(&iter);
    }

out:
    if (msg)
        dbus_message_unref(msg);
    if (reply)
        dbus_message_unref(reply);
    if (conn)
        dbus_connection_close(conn);

    return pvalue;

}

QString DarsAudio::getDarsDbusParam(const char *name)
{
    char *value = NULL;
    QString pvalue="";
    DBusError err;
    DBusConnection *conn = NULL;
    DBusMessage *msg = NULL;
    DBusMessage *reply = NULL;
    DBusMessageIter iter;
    DBusMessageIter sub;
    const char *intf_STRING = "org.PulseAudio.Ext.Dars.Controller";

    dbus_error_init(&err);
    conn = dbus_connection_open_private(mDarsDbusAddr.toStdString().c_str(), &err);
    if (!conn) {
        qWarning() << "Can not connect";
        return QString("");
    }

    msg = dbus_message_new_method_call(
            "org.PulseAudio.Ext.Dars.Controller", // destination
            "/org/pulseaudio/dars", // path
            "org.PulseAudio.Ext.Dars.Controller", // interface
            "GetParam"
            );
    if (!msg) {
        value = NULL;
        pvalue="";
        goto out;
    }

    if (!dbus_message_append_args(msg, DBUS_TYPE_STRING, &name, DBUS_TYPE_INVALID)) {
        value = NULL;
        pvalue="";
        goto out;
    }

    reply = dbus_connection_send_with_reply_and_block(conn, msg, DBUS_TIMEOUT_INFINITE, &err );
    if (!reply) {
        value = NULL;
        pvalue = "";
        goto out;
    }
    if (!dbus_message_get_args(reply, &err, DBUS_TYPE_STRING, &value, DBUS_TYPE_INVALID)) {
        value = NULL;
        pvalue = "";
        goto out;
    }

    pvalue = value;

out:
    if (msg)
        dbus_message_unref(msg);
    if (reply)
        dbus_message_unref(reply);
    if (conn)
        dbus_connection_close(conn);

    return pvalue;

}

int DarsAudio::getDarsDbusParam(const char *pname, int *iv)
{
    QString value;
    if (!pname || !iv) {
        return -1;
    }

    value = getDarsDbusParam(pname);
    if (value.isEmpty()) {
        return -1;
    }
    *iv = value.toInt();

    return 0;
}

int DarsAudio::getDarsDbusParam(const char *pname, float *fv)
{
    QString value;
    if (!pname || !fv) {
        return -1;
    }

    value = getDarsDbusParam(pname);
    if (value.isEmpty()) {
        return -1;
    }
    *fv = value.toFloat();

    return 0;
}

void DarsAudio::setDarsDbusParam(const char *param, const char *value)
{
    DBusError err;
    DBusConnection *conn = NULL;
    DBusMessage *msg = NULL;
    DBusMessage *reply = NULL;
    DBusMessageIter iter;
    DBusMessageIter sub;

    dbus_error_init(&err);
    conn = dbus_connection_open_private(mDarsDbusAddr.toStdString().c_str(), &err);
    if (!conn) {
        qWarning() << "Can not connect";
        return;
    }

    msg = dbus_message_new_method_call(
            "org.PulseAudio.Ext.Dars.Controller", // destination
            "/org/pulseaudio/dars", // path
            "org.PulseAudio.Ext.Dars.Controller", // interface
            "SetParam"
            );
    if (!msg) {
        goto out;
    }

    if (!dbus_message_append_args(msg,
                DBUS_TYPE_STRING, &param,
                DBUS_TYPE_STRING, &value, DBUS_TYPE_INVALID)) {
        goto out;
    }

    reply = dbus_connection_send_with_reply_and_block(conn, msg, DBUS_TIMEOUT_INFINITE, &err );
    if (!reply) {
        goto out;
    }


out:
    if (msg)
        dbus_message_unref(msg);
    if (reply)
        dbus_message_unref(reply);
    if (conn)
        dbus_connection_close(conn);

    return;


}

void DarsAudio::setDarsDbusParam(const char *name, const int value)
{
    QString strV;
    if (!name) {
        return;
    }

    strV.sprintf("%d", value);
    setDarsDbusParam(name, strV.toStdString().c_str());
}

void DarsAudio::setDarsDbusParam(const char *name, const float value)
{
    QString strV;
    if (!name) {
        return;
    }

    strV.sprintf("%.2f", static_cast<double>(value));
    setDarsDbusParam(name, strV.toStdString().c_str());
}
