#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);
}

Server::~Server()
{
    delete ui;
}

void Server::initServer()
{
    qDebug()<<"comienza initServer()";
    qDebug()<<"fin de initServer()";
}

void Server::sendRandomMessage()
{
    qDebug()<<"inicia sendRandomMessage()";
    qDebug()<<"fin sendRandomMessage()";
}

