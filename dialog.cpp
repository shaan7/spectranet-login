#include "dialog.h"
#include "ui_dialog.h"

#include <QWebFrame>
#include <QTimer>

#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(ui->webView, SIGNAL(titleChanged(QString)), SLOT(checkTitleAndLogin(QString)));
    ui->webView->setUrl(QUrl("http://1.254.254.254"));
}

void Dialog::checkTitleAndLogin(const QString &title)
{
    if (title == "New Customer Login Page") {
        connect(ui->webView, SIGNAL(loadFinished(bool)), SLOT(login()));
    }
}

void Dialog::login()
{
    qDebug() << "Logging in";
    if (sender()) {
        disconnect(sender());
    }

    if (!fillUsername(ui->webView->page()->currentFrame())) {
        QTimer::singleShot(1000, this, SLOT(login()));
    }
    fillPassword(ui->webView->page()->currentFrame());

    if (!selectInternetAccess(ui->webView->page()->currentFrame())) {
        QTimer::singleShot(0, this, SLOT(alreadyLoggedIn()));
        return;
    }

    qDebug() << clickSubmit(ui->webView->page()->currentFrame());
}

bool Dialog::fillUsername(QWebFrame *frame)
{
    return frame->evaluateJavaScript("document.forms[0].username.value = '';").toBool();
}

bool Dialog::fillPassword(QWebFrame *frame)
{
    return frame->evaluateJavaScript("document.forms[0].password.value = '';").toBool();
}

bool Dialog::selectInternetAccess(QWebFrame *frame)
{
    frame->evaluateJavaScript("document.forms[0].type.value = 2;");
    return frame->evaluateJavaScript("document.forms[0].type.value == 2;").toBool();
}

bool Dialog::clickSubmit(QWebFrame *frame)
{
    frame->evaluateJavaScript("document.forms[0].elements[4].click();").toBool();
}

void Dialog::alreadyLoggedIn()
{
    qDebug() << "Already logged in!";
}

Dialog::~Dialog()
{
    delete ui;
}
