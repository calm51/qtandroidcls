#include <QString>
#include <QGuiApplication>
#include <QDebug>
#include <QScreen>
#include "QtAndroid"
#include <QtAndroidExtras>
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>


#ifndef QTANDROIDCLS_H
#define QTANDROIDCLS_H


class QtAndroidCls;
extern QtAndroidCls *qtandroidcls_instance;

class QtAndroidCls : public QObject{
    Q_OBJECT

public:
    QtAndroidCls(const QtAndroidCls&) = delete;
    QtAndroidCls& operator=(const QtAndroidCls&) = delete;
    static QtAndroidCls* instance(const QString &android_classname="") {
        if (qtandroidcls_instance){
            return qtandroidcls_instance;
        }
        qtandroidcls_instance = new QtAndroidCls(android_classname);
        return qtandroidcls_instance;
        //        static QtAndroidCls instance(android_classname);
        //        return &instance;
    }
    ~QtAndroidCls();

    QByteArray android_classname;
    QByteArray android_signture_instance;
    jclass android_class;
    QAndroidJniEnvironment env;

    // =======================

    void up_statusbar_height();
    qint32 get_statusbar_qwiget_height();
    qint32 statusbar_qwiget_height(const qint32 &statusBarHeight);

    void to_statusbar_text_white();
    void to_statusbar_text_black();

    Q_INVOKABLE void toast(const QString &s);
    void speak(const QString &s);
    void notify(const QString &title, const QString &msg);
    void vibrate(const qint32 &t=-1); // -1=长震动 0=取消震动 x=震动秒数

    bool register_native_method(const QString &method_name, const QString &method_target, void* method);

    void move_to_background();


    // =======================

    static void emit_statusbarHeightChanged(JNIEnv *env, jobject obj, jint i){
        emit QtAndroidCls::instance()->statusbarHeightChanged(QtAndroidCls::instance()->statusbar_qwiget_height(i));
    }

private:
    QtAndroidCls(const QString &android_classname);


signals:
    void statusbarHeightChanged(qint32 i);


};

#endif
