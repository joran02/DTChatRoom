#include "MainWin.h"
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
MainWin::MainWin(QWidget *parent)
    : QWidget(parent), loginDlg(this)
{
    initMember();
    initMsgGrpBx();
    initInputGrpBx();
    connectSlots();

    vMainLayout.setSpacing(10);
    vMainLayout.addWidget(&msgGrpBx);
    vMainLayout.addWidget(&inputGrpBx);

    setWindowTitle(tr("D.T.SoftWare ChatRoom"));
    setLayout(&vMainLayout);
    setMinimumSize(550, 400);
    resize(550, 400);
}

void MainWin::initMember()
{
    m_client.setHandler(this);
}

void MainWin::initMsgGrpBx()
{
    QHBoxLayout* hbl = new QHBoxLayout();

    hbl->setContentsMargins(2, 5, 2, 2);
    hbl->addWidget(&msgEditor);

    msgEditor.setReadOnly(true);

    msgGrpBx.setLayout(hbl);
    msgGrpBx.setTitle(tr("Chat Message"));
}

void MainWin::initInputGrpBx()
{
    QGridLayout* gl = new QGridLayout();

    gl->setSpacing(10);
    gl->addWidget(&inputEdit, 0, 0, 1, 5);
    gl->addWidget(&statusLbl, 1, 0, 1, 3);
    gl->addWidget(&logInOutBtn, 1, 3);
    gl->addWidget(&sendBtn, 1, 4);

    inputEdit.setFixedHeight(23);
    inputEdit.setEnabled(false);
    statusLbl.setText(tr("status: outline"));
    logInOutBtn.setFixedHeight(30);
    logInOutBtn.setText(tr("Login"));
    sendBtn.setFixedHeight(30);
    sendBtn.setText(tr("send"));
    sendBtn.setEnabled(false);

    inputGrpBx.setFixedHeight(100);
    inputGrpBx.setLayout(gl);
    inputGrpBx.setTitle(tr("UserName"));
}

void MainWin::sendBtnClicked()
{

}

void MainWin::logInOutBtnClicked()
{
    if( loginDlg.exec() == QDialog::Accepted )
    {
        QString user = loginDlg.getUser().trimmed();
        QString pwd = loginDlg.getPwd();
        if( m_client.connectTo("127.0.0.1", 8890) ){
            setCtrlEnabled(true);
        }
        else{
            QMessageBox::critical(this, "Failed", "Cannot Connect to Server!");
        }
    }
}

void MainWin::handle(QTcpSocket &obj, TextMessage &message)
{
    qDebug() << message.type();
    qDebug() << message.data();
}

void MainWin::connectSlots()
{
    connect(&sendBtn, SIGNAL(clicked(bool)), this, SLOT(sendBtnClicked()));
    connect(&logInOutBtn, SIGNAL(clicked(bool)), this, SLOT(logInOutBtnClicked()));
}

void MainWin::setCtrlEnabled(bool enabled)
{
    inputEdit.setEnabled(enabled);
    statusLbl.setText(enabled ? "Status: OnLine" : "Status: OutLine");
    logInOutBtn.setText(enabled ? "Logout" : "LoginIn");
    sendBtn.setEnabled(enabled);
}

MainWin::~MainWin()
{

}
