#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMediaPlayer>
#include <QUrl>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MPlayer = new QMediaPlayer();
    audioOutput = new QAudioOutput();
    MPlayer -> setAudioOutput(audioOutput);

    ui->pushButton_Play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->pushButton_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    ui->pushButton_Stop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->pushButton_Seek_Back->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    ui->pushButton_Seek_Forward->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    ui -> pushButton_Volume -> setIcon(style()->standardIcon(QStyle::SP_MediaVolume));

    ui-> horizontalSlider_Audio_Volume->setMinimum(0);
    ui-> horizontalSlider_Audio_Volume->setMaximum(100);
    ui-> horizontalSlider_Audio_Volume->setValue(30);

    double vol = ui->horizontalSlider_Audio_Volume->value() / 100.0;
    audioOutput->setVolume(vol);
    std::cout << "start up\n" << "start up volume: " << vol << std::endl;

    connect(MPlayer, &QMediaPlayer::durationChanged, this, &MainWindow::durationChanged);
    connect(MPlayer, &QMediaPlayer::positionChanged, this, &MainWindow::positionChanged);
    ui -> horizontalSlider_Audio_File_Duration -> setRange(0, MPlayer->duration()/1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateDuration(qint64 duration)
{
    QString timestr;
    if(duration || Mduration){
        QTime CurrentTime((duration/3600) % 60, (duration/60)% 60, duration % 60, (duration * 1000) % 1000);
        QTime totalTime((Mduration / 3600) % 60, (Mduration / 60) % 60, Mduration % 60, (Mduration * 1000) % 1000);
        QString format = "mm:ss";
        if (Mduration > 3600){
            format = "hh:mm:ss";
        }
        ui -> label_Value_1->setText(CurrentTime.toString(format));
        ui -> label_Value_2->setText(totalTime.toString(format));

    }
}

void MainWindow::durationChanged(qint64 duration)
{
    Mduration = duration / 1000;
    ui -> horizontalSlider_Audio_File_Duration -> setMaximum(Mduration);
}

void MainWindow::positionChanged(qint64 progress)
{
    if(!ui->horizontalSlider_Audio_File_Duration->isSliderDown()){
        ui-> horizontalSlider_Audio_File_Duration -> setValue(progress / 1000);
    }
    updateDuration(progress / 1000);
}

void MainWindow::on_pushButton_Volume_clicked()
{
    if (Is_Muted == false){
        ui -> pushButton_Volume -> setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
        Is_Muted = true;
        audioOutput->setMuted(false);
    } else {
        ui -> pushButton_Volume -> setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
        Is_Muted = false;
        audioOutput->setMuted(true);
    }
}


void MainWindow::on_actionOpen_Audio_File_triggered()
{
    QString FileName = QFileDialog::getOpenFileName(this, tr("Select Audio File"),"", tr("MP3 Files (*.mp3)"));
    MPlayer->setSource(QUrl(FileName));
    QFileInfo fileinfo(FileName);
    ui->label_File_Name->setText(fileinfo.fileName());

}


void MainWindow::on_pushButton_Play_clicked()
{
    MPlayer->play();
}


void MainWindow::on_pushButton_Stop_clicked()
{
    MPlayer->stop();
}


void MainWindow::on_pushButton_Pause_clicked()
{
    MPlayer->pause();
}


void MainWindow::on_pushButton_Seek_Forward_clicked()
{
}


void MainWindow::on_pushButton_Seek_Back_clicked()
{

}


void MainWindow::on_horizontalSlider_Audio_File_Duration_valueChanged(int value)
{

}


void MainWindow::on_horizontalSlider_Audio_Volume_valueChanged(int value)
{
    double volume = value/100.0;
    audioOutput->setVolume(volume);
    std::cout << volume << std::endl;
}


void MainWindow::on_horizontalSlider_Audio_File_Duration_sliderMoved(int position)
{
    MPlayer -> setPosition(position * 1000);
}

