void on_uart_data_clean_clicked();
#ifndef QWIGHT_H
#define QWIGHT_H

#include <QMainWindow>

#include <QString>
#include <QTimer>
#include <QProcess>
#include <QBoxLayout>
#include <QSerialPort>
#include <QSerialPortInfo>

#include <QMediaPlayer>



namespace Ui {
class Qwight;
}

class Qwight : public QMainWindow
{
    Q_OBJECT

public:
    explicit Qwight(QWidget *parent = 0);
    ~Qwight();

private slots:
    void on_StartButton_clicked();

    void on_StopButton_clicked();

    void timerEvent();
    void on_scan_uart_clicked();

    void on_open_uart_clicked();

    void messlot();

    void on_close_uart_clicked();

    void on_uart_data_clean_clicked();

    void on_clean_time_clicked();

    void on_actionPlay_clicked();

    void on_ALL_pin_clicked();

    void on_esc_ALL_clicked();

private:
    Ui::Qwight *ui;

    /*定义定时器时间进度*/
    float mytime=0;
    QTimer * TIME_USER;//定时器指针
    int relad=0;//准备状态
    //串口
    QSerialPort m_serial;//串口指针
    int Tmark=0;//圈数标记
    int clean_mark=0;

    QMediaPlayer *player ;//设置背景音乐
};

#endif // QWIGHT_H
