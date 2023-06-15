#include "qwight.h"
#include "ui_qwight.h"

Qwight::Qwight(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Qwight)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/new/prefix/小车.svg"));

    /*定时器任务设置*/
    TIME_USER = new QTimer;
    connect(TIME_USER,&QTimer::timeout,this,&Qwight::timerEvent);

    /*串口任务设置*/

    /*背景音乐设置*/
    player = new QMediaPlayer(this);
    player->setMedia(QUrl("qrc:/music/Summoning_Glory.mp3"));
    player->setVolume(50);//音量
    player->play();
    ui->label->setAttribute(Qt::WA_TranslucentBackground);
    ui->label_2->setAttribute(Qt::WA_TranslucentBackground);
    ui->label_3->setAttribute(Qt::WA_TranslucentBackground);
    ui->label_4->setAttribute(Qt::WA_TranslucentBackground);
    ui->uart_relay->setAttribute(Qt::WA_TranslucentBackground);
    ui->label_7->setAttribute(Qt::WA_TranslucentBackground);
    ui->system_state->setAttribute(Qt::WA_TranslucentBackground);
    ui->lcdNumber->setAttribute(Qt::WA_TranslucentBackground);

}

Qwight::~Qwight()
{
    delete ui;
}
/*手动准备*/
void Qwight::on_StartButton_clicked()
{
    relad=1;
    if(relad==1&& clean_mark==0)
    ui->system_state->setText("系统已准备，可以开始比赛");
    else
    ui->system_state->setText("请清零后准备");
}
/*手动暂停*/
void Qwight::on_StopButton_clicked()
{
    TIME_USER->stop();
}

/*
 * 计时器刷新程序
 */
void Qwight::timerEvent()
{
       mytime+=1;

       ui->lcdNumber->display((double) mytime/100);
}

/*
 * 刷新串口
 */
void Qwight::on_scan_uart_clicked()
{
    ui->choose_uart->clear();
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
            ui->choose_uart->addItem(info.portName());
    }
}
//打开串口
void Qwight::on_open_uart_clicked()
{
    m_serial.setPortName(ui->choose_uart->currentText());
    m_serial.setBaudRate(ui->uart_poart->currentText().toInt());

    m_serial.open(QIODevice::ReadWrite);

    if(m_serial.isOpen())
    {
        ui->uart_relay->setText("串口打开成功");
        connect(&m_serial,&QSerialPort::readyRead,this,Qwight::messlot);
    }
    else
    {
        ui->uart_relay->setText("串口已关闭");
    }
}
QByteArray Float2Byte(float currentData)
{
    QByteArray outputdata;

    outputdata.resize(sizeof(currentData));    //重新调整QByteArray的大小
    memcpy(outputdata.data(),&currentData,sizeof(currentData));
    return outputdata;
}
void Qwight::messlot()
{
    QByteArray array = m_serial.readAll();
    QByteArray user_timr;
    ui->textBrowser->insertPlainText(array);
    if(relad==1&&clean_mark==0)//清零状态且处于准备状态
    {
        if((array=="pass")&&(ui->model->currentText()=="两圈"))
        {
            if(Tmark==0)
            {
            TIME_USER->start(10);
            Tmark++;
            ui->textBrowser->insertPlainText("第一圈\n");
            }
            else if(Tmark==1)
            {
            Tmark++;
            ui->textBrowser->insertPlainText("第二圈\n");
            }
            else if(Tmark==2)
            {
            TIME_USER->stop();
            ui->textBrowser->insertPlainText(" end\n");
            ui->textEdit->setText("成绩是:"+QString::number(mytime/100)+"秒\n");
            Tmark=0;//圈数清零
            relad=0;//预备状态清零
            ui->system_state->setText("比赛结束 请清零后重新准备");
            clean_mark=1;//强制清零标记
            }
        }
        if((array=="pass")&&(ui->model->currentText()=="一圈"))
        {
            if(Tmark==0)
            {
            TIME_USER->start(10);
            Tmark++;
            ui->textBrowser->insertPlainText("第一圈\n");
            }
            else if(Tmark==1)
            {
            TIME_USER->stop();
            ui->textEdit->setText("成绩是:"+QString::number(mytime/100)+"秒\n");
            Tmark=0;
             relad=0;//预备状态清零
             ui->system_state->setText("比赛结束 请清零后重新准备");
             ui->textBrowser->insertPlainText(" end\n");
             clean_mark=1;
            }
        }

    }

}

void Qwight::on_close_uart_clicked()
{
    m_serial.close();
    if(m_serial.isOpen())
    {
        ui->uart_relay->setText("串口打开成功");
        connect(&m_serial,&QSerialPort::readyRead,this,Qwight::messlot);
    }
    else
    {
        ui->uart_relay->setText("串口已关闭");

    }
}

void Qwight::on_uart_data_clean_clicked()
{
    ui->textBrowser->clear();
}

void Qwight::on_clean_time_clicked()
{
    mytime=0;
    ui->lcdNumber->display(0);
    clean_mark=0;
    ui->system_state->setText("已清零");
}



void Qwight::on_actionPlay_clicked()
{

}

void Qwight::on_ALL_pin_clicked()
{
    showFullScreen();
}

void Qwight::on_esc_ALL_clicked()
{
    showNormal();
}
