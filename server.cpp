#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);
    initServer();
    for (int i=0;i<=50 ;i++ ) {
        randomMessages.insert(i,QString::number(i));
    }
    connect(ui->pBtn_close, &QAbstractButton::clicked, this, &QWidget::close);
    connect(serverSocket,&QTcpServer::newConnection,this,&Server::sendRandomMessage);
}

Server::~Server()
{
    delete ui;
}

void Server::initServer()
{
    qDebug()<<"comienza initServer()";
    serverSocket = new QTcpServer(this);
    if (!serverSocket->listen())
    {
        qDebug()<< " error "<< serverSocket->errorString();
    }

    QString port = QString::number(serverSocket->serverPort(), 10);
    QString ipAddress = "127.0.0.1";
    QList<QHostAddress> ipAddressList = QNetworkInterface::allAddresses();
    for(int i=0;i<ipAddressList.size();i++)
    {
        if(ipAddressList.at(i) != QHostAddress::LocalHost && ipAddressList.at(i).toIPv4Address()){
            ipAddress = ipAddressList.at(i).toString();
            qDebug()<<"ip: " <<ipAddressList.at(i);
            break;
        }

    }
    QString address = "IP: " + ipAddress + "port: " + port;
    ui->lbl_Address->setText(address);
    qDebug()<<"fin de initServer()";

}
/**
 * @brief Server::sendRandomMessage
 * generar una instancia para que reciba el mensaje?
 */
void Server::sendRandomMessage()
{
    qDebug()<<"inicia sendRandomMessage()";
    //seleccionar mensaje, coger que mensaje se va a tomar
    QString randomMessage =randomMessages[QRandomGenerator::global()->bounded(randomMessages.size())];
    //pintamos el mensaje
    ui->lbl_Message->setText(randomMessage);
    //formato estandar de dato
    QByteArray aByteArray;
    //creo canal para el flujo de datos
    QDataStream qDataStream(&aByteArray,QIODevice::WriteOnly);
    qDataStream << randomMessage;
    //para atender al llamdo del cliente al otro lado
    //delegacion de la atencion al cliente
    QTcpSocket *socket = serverSocket->nextPendingConnection();//cuando llega el pedido
   //liberacion del objeto
    connect(socket,&QAbstractSocket::disconnected,socket,&QObject::deleteLater);//quien esta funcionando?
    //escritura del socket
    socket->write(aByteArray);//el flujo solo es el canal
    socket->disconnectFromHost();


    qDebug()<<"fin sendRandomMessage()";
}

