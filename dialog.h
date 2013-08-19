#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
    class Dialog;
}

class QWebFrame;

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private Q_SLOTS:
    void checkTitleAndLogin(const QString &title);
    void login();
    bool fillUsername(QWebFrame *frame);
    bool fillPassword(QWebFrame *frame);
    bool selectInternetAccess(QWebFrame *frame);
    bool clickSubmit(QWebFrame *frame);

    void alreadyLoggedIn();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
