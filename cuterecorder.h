#ifndef CUTERECORDER_H
#define CUTERECORDER_H

#include <QMainWindow>
#include <QMultimedia>
#include <QMediaRecorder>
#include <QCamera>
#include <QAudioRecorder>

namespace Ui {
class CuteRecorder;
}

class CuteRecorder : public QMainWindow
{
    Q_OBJECT

public:
    explicit CuteRecorder(QWidget *parent = nullptr);
    QMediaRecorder *videoRecorder;
    QCamera *camera;
    QVideoEncoderSettings vSettings;
    QAudioEncoderSettings aSettings;
    QAudioRecorder *aud;
    void test();
    QList<QString> getAudioDevices();
    ~CuteRecorder();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

public slots:
    void displayErrorMessage();
    bool checkCameraAvailability();
    void onStateChanged();
private:
    Ui::CuteRecorder *ui;
};

#endif // CUTERECORDER_H
