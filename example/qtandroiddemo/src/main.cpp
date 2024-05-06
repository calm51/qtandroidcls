#include "mainwindow.h"

#include <QApplication>

#include "QtAndroid"
#include <QtAndroidExtras>
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>


#include <qtandroidcls/qtandroidcls.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtAndroidCls *qac = QtAndroidCls::instance("ca/calm/qtandroiddemo/qtandroiddemo");
    MainWindow w;
    w.show();
    qac->up_statusbar_height();
    // W_startscreen *w_ss = new W_startscreen(&w);
    // w_ss->showFullScreen();
    QTimer::singleShot(50,[&](){
        qac->to_statusbar_text_white();
        QtAndroid::hideSplashScreen(100);
        // w_ss->exec();
        qac->to_statusbar_text_black();
    });

    return a.exec();
}
