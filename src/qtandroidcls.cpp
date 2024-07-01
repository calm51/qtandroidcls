
#include "qtandroidcls.h"



// 状态栏背景颜色
// https://github.com/jpnurmi/qtstatusbar/tree/master

// 清单
// https://developer.android.com/guide/topics/manifest/application-element.html


QtAndroidCls *qtandroidcls_instance = nullptr;
QtAndroidCls::~QtAndroidCls(){}
QtAndroidCls::QtAndroidCls(const QString &android_classname) : QObject(){
    this->android_classname = android_classname.toUtf8();
    this->android_signture_instance = (QString("()L")+android_classname+QString(";")).toUtf8();
    this->android_class = this->env->FindClass(this->android_classname);

    //    auto lambda1 = std::function<void(JNIEnv *env, jobject obj, jint i)>([this](JNIEnv *env, jobject obj, jint i){
    //        emit this->statusbarHeightChanged(i);
    //    });void* lambdaPtr = reinterpret_cast<void*>(&lambda1);
    this->register_native_method("statusbarHeightChanged", "(I)V", (void*)(this->emit_statusbarHeightChanged));
}


void QtAndroidCls::up_statusbar_height(){
    QAndroidJniObject activity = QtAndroid::androidActivity();
    activity.callMethod<jint>("upStatusbarHeight", "()V");
}
qint32 QtAndroidCls::get_statusbar_qwiget_height(){
    QAndroidJniObject _javaClass = QAndroidJniObject::callStaticObjectMethod(this->android_classname, "instance", this->android_signture_instance);
    jobject javaObject = _javaClass.object<jobject>();
    jclass javaClass = this->env->FindClass(this->android_classname);
    jfieldID intFieldID = this->env->GetFieldID(javaClass, "statusbarHeight", "I");
    qint32 statusBarHeight = this->env->GetIntField(javaObject, intFieldID);
    return this->statusbar_qwiget_height(statusBarHeight);
}

qint32 QtAndroidCls::statusbar_qwiget_height(const qint32 &statusBarHeight){
    qreal pixelRatio = QGuiApplication::primaryScreen()->devicePixelRatio();
    qint32 widgetHeight = statusBarHeight / pixelRatio;
    return widgetHeight;
}


jint registerNativeMethod(JNIEnv* env, jclass clazz, const char* methodName, const char* methodSignature, void* methodPtr) {
    /*
static const JNINativeMethod gMethods[] = { {"function", "()V", (void*)function} };
jint mj = Environment->RegisterNatives(j_class, gMethods, sizeof(gMethods) / sizeof(gMethods[0]));
*/
    JNINativeMethod method = {methodName, methodSignature, methodPtr};
    return env->RegisterNatives(clazz, &method, 1);
}
bool QtAndroidCls::register_native_method(const QString &method_name, const QString &method_target, void *method){
    bool success = false;
    QtAndroid::runOnAndroidThreadSync([=, &success](){
        jint mj = registerNativeMethod(this->env, this->android_class, method_name.toUtf8().data(), method_target.toUtf8().data(), reinterpret_cast<void*>(method));
        if (mj == JNI_OK){
            success = true;
        }
    });
    return success;
}

void QtAndroidCls::move_to_background() {
    QtAndroid::runOnAndroidThread([this]() {
        QAndroidJniObject activity = QtAndroid::androidActivity();
        if (activity.isValid()) {
            activity.callMethod<jboolean>("move_task_to_back", "(Z)Z", true);
        }

    });
}

void QtAndroidCls::to_statusbar_text_white(){
    QtAndroid::runOnAndroidThread([]() {
        QAndroidJniObject activity = QtAndroid::androidActivity();
        activity.callMethod<void>("toStatusbarTextWhite", "()V");
    });
}
void QtAndroidCls::to_statusbar_text_black(){
    QtAndroid::runOnAndroidThread([]() {
        QAndroidJniObject activity = QtAndroid::androidActivity();
        activity.callMethod<void>("toStatusbarTextBlack", "()V");
    });
}

void QtAndroidCls::toast(const QString &s){
    QAndroidJniObject javaToast = QAndroidJniObject::fromString(s);
    QAndroidJniObject activity = QtAndroid::androidActivity();
    activity.callMethod<void>("toast","(Ljava/lang/String;)V",javaToast.object());
    // QAndroidJniObject::callStaticMethod<void>("com/a/","toast","(Ljava/lang/String;)V",javaToast.object());
}

void QtAndroidCls::speak(const QString &s){
    QAndroidJniObject js = QAndroidJniObject::fromString(s);
    QAndroidJniObject activity = QtAndroid::androidActivity();
    activity.callMethod<void>("speak","(Ljava/lang/String;)V",js.object());
}

void QtAndroidCls::notify(const QString &title, const QString &msg){
    QAndroidJniObject jtitle = QAndroidJniObject::fromString(title);
    QAndroidJniObject jmsg = QAndroidJniObject::fromString(msg);
    QAndroidJniObject activity = QtAndroid::androidActivity();
    activity.callMethod<void>("notify","(Ljava/lang/String;Ljava/lang/String;)V",jtitle.object(),jmsg.object());
}

void QtAndroidCls::vibrate(const qint32 &t){
    QAndroidJniObject activity = QtAndroid::androidActivity();
    activity.callMethod<void>("vibrate", "(I)V", t);
    //    QTimer * tr = new QTimer(this);
    //    connect(tr,&QTimer::timeout,[=](){
    //        QAndroidJniObject activity = QtAndroid::androidActivity();
    //        activity.callMethod<void>("vibrate", "(I)V", 0);
    //        tr->stop();
    //        tr->deleteLater();
    //    });
    //    tr->start(200);
}












