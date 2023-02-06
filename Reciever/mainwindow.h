#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QDateTime>
#include <QTimer>
#include <QDataStream>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVector<QVector<int> > matrixTranspose() const;

public slots:
    void reciveDatagrams();
    void showLogs();
    void calcDataSpeed();

private slots:
    void on_action_triggered();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QUdpSocket *socket;
    QTimer *timer;

    quint32 id_, startid_, stopid_;
    int  count_, m_, n_;
    QDateTime time_;
    QVector<QVector<int> > matrix_;
    double msg_size_;
};
#endif // MAINWINDOW_H
