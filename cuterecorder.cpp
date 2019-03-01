#include "cuterecorder.h"
#include "ui_cuterecorder.h"

#include <QString>
#include <QCameraInfo>
#include <QUrl>

CuteRecorder::CuteRecorder(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CuteRecorder),
    vSettings(QVideoEncoderSettings()),
  aud(new QAudioRecorder(this))
{
    ui->setupUi(this);
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
        qDebug() << "availableCameras =";
        foreach (const QCameraInfo &cameraInfo, cameras) {
            qDebug() << cameraInfo;
            if (cameraInfo == QCameraInfo::defaultCamera())
                qDebug() << "----------pass";
                qDebug() << cameraInfo;
                camera = new QCamera(cameraInfo);
        }
        camera->setCaptureMode(QCamera::CaptureVideo);

        camera->start();
        videoRecorder = new QMediaRecorder(camera);

        qDebug() << "ok constructor";
        connect(videoRecorder, SIGNAL(error(QMediaRecorder::Error)),
                    this, SLOT(displayErrorMessage()));
        connect(videoRecorder, SIGNAL(stateChanged(QMediaRecorder::State)), this, SLOT(onStateChanged()) );

        qDebug() << "DRERBBUUGG\n";

        QList<QString> q = aud->audioInputs();
        foreach(QString s, q)
               qDebug() << s;

        qDebug() << "DOOOOONE\n";
}

CuteRecorder::~CuteRecorder()
{
    delete ui;
    delete videoRecorder;
    delete camera;

}
void CuteRecorder::onStateChanged()
{
    qDebug() << "uh state changed";
}
void CuteRecorder::displayErrorMessage()
{
        qDebug() << " ERRRRRRRRRRORR";
}

void CuteRecorder::on_pushButton_clicked()
{
    camera->setCaptureMode(QCamera::CaptureVideo);

    camera->start();
    qDebug() <<"\n availability==" << videoRecorder->availability();

    /*

       qDebug() << "READY YOUR ARMS\n";
    qDebug() << "a - codecs";
        QList<QString> codecs = videoRecorder->supportedAudioCodecs();
        foreach (const QString &cod, codecs)
            qDebug() << cod;

        qDebug() << "\n a - sample rates";
            QList<int> a = videoRecorder->supportedAudioSampleRates();
            foreach (int cod, a)
                qDebug() << cod;


            qDebug() << "\n v - codecs";
                codecs = videoRecorder->supportedVideoCodecs();
                foreach (const QString &cod, codecs)
                    qDebug() << cod;


                qDebug() << "\n container";
                    codecs = videoRecorder->supportedContainers();
                    foreach (const QString &cod, codecs)
                        qDebug() << cod;

                    qDebug() << "\n a - sample rates";
                         QList<QSize> b = videoRecorder->supportedResolutions();
                        foreach (QSize cod, b)
                            qDebug() << cod;
*/

    videoRecorder->setOutputLocation(QUrl("file:///home/akhilam512/vid/lmao"));
    qDebug() << "output location\n";
    qDebug() << videoRecorder->outputLocation();
    qDebug() <<"\n availability==" << videoRecorder->availability();

    if(videoRecorder->state() == QMediaRecorder::StoppedState) {
  /*      QAudioEncoderSettings aSettings = videoRecorder->audioSettings();
        QVideoEncoderSettings vSettings = videoRecorder->videoSettings();
        QString container = "video/mpeg";
        aSettings.setCodec("audio/mpeg, mpegversion=(int)4");
        aSettings.setBitRate(48000);
        aSettings.setQuality(QMultimedia::NormalQuality);
        aSettings.setEncodingMode((QMultimedia::ConstantQualityEncoding));
        aSettings.setSampleRate(44100);  // no data?
        aSettings.setChannelCount(1);

        vSettings.setFrameRate(24);
        vSettings.setCodec("video/mpeg, mpegversion=(int)4, systemstream=(boolean)false");
       vSettings.setQuality(QMultimedia::NormalQuality);
        vSettings.setResolution(QSize(640, 480));


        videoRecorder->setEncodingSettings(aSettings, vSettings, container);
*/
        if(checkCameraAvailability()) {
            qDebug() << "AVAILABLE!";
        }
        qDebug() <<"\n availability==" << videoRecorder->availability();

     qDebug() << "EEE"<< videoRecorder->error();
        videoRecorder->record();
        qDebug() << "EEE"<< videoRecorder->error();
        qDebug() <<"\n availability==" << videoRecorder->availability();

    }
    else {
        videoRecorder->stop();
    }


}
bool CuteRecorder::checkCameraAvailability()
{
    if (QCameraInfo::availableCameras().count() > 0)
        return true;
    else
        return false;
}
void CuteRecorder::on_pushButton_2_clicked()
{
    if (videoRecorder->state() != QMediaRecorder::PausedState) {
        videoRecorder->stop();
        camera->stop();
    }
    else
        videoRecorder->record();
}
