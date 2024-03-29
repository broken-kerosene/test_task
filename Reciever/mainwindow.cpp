#include "mainwindow.h"
#include "ui_mainwindow.h"

const int TENMSSEC = 1e4;
const int TENSEC = 10;
const int MBIT = 1e6;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QUdpSocket(this);
    timer = new QTimer(this);

    timer->start(TENMSSEC); //time specified in ms
    connect(timer, SIGNAL(timeout()), this, SLOT(calcDataSpeed()));
    startid_ = 0;
    stopid_ = 0;
    count_ = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_triggered()
{
    QCoreApplication::quit();
}

void MainWindow::on_pushButton_clicked()
{
    socket->close();
    socket = new QUdpSocket(this);
    int port = ui->spinBox->value();
    socket->bind(QHostAddress::LocalHost, port);
    connect(timer, SIGNAL(timeout()), this, SLOT(showLogs()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(reciveDatagrams()));
}

void MainWindow::reciveDatagrams()
{
    QByteArray buffer;
    QHostAddress sender;
    quint16 senderPort;
    while(socket->hasPendingDatagrams()){
        buffer.resize(socket->pendingDatagramSize());
        socket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);
        msg_size_ = buffer.size()*8;
        ui->label_3->setText(QString::number(msg_size_));
        QDataStream in(buffer);
        in >> id_ >> time_ >> m_ >> n_ >> matrix_;
        //cold start startid_ issue
        if(startid_ == 0)
            startid_ = id_;
        QVector<QVector<int> > newMatrix = matrixTranspose();
        count_++;
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    disconnect(socket, SIGNAL(readyRead()), this, SLOT(reciveDatagrams()));
    disconnect(timer, SIGNAL(timeout()), this, SLOT(showLogs()));
    socket->close();
}

QVector<QVector<int> > MainWindow::matrixTranspose() const
{
    QVector<QVector<int> > newMatrix;
    newMatrix.resize(m_);
    for(int i=0; i<m_; ++i){
        newMatrix[i].resize(n_);
        for(int j=0; j<n_; ++j){
            newMatrix[i][j] = matrix_[j][i];
        }
    }
    return newMatrix;
}

void MainWindow::showLogs()
{
    stopid_ = id_;
    QString row = "Count of transpose: " + QString::number(count_) + "\t";
    row.append("\tstart id: " + QString::number(startid_));
    row.append("\tstop id: " + QString::number(stopid_));
    ui->listWidget->addItem(row);
    ui->listWidget->scrollToBottom();
    count_ = 0;
    startid_ = id_;
}
void MainWindow::calcDataSpeed()
{
    double tmp;
    tmp = count_ * msg_size_ /TENSEC/MBIT;
    ui->label_5->setText(QString::number(tmp));
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->listWidget->clear();
}
