#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "darsaudio.h"

#include <QtDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    DarsAudio *ds = DarsAudio::getInstance();
    QString name = ds->getDarsDbusProperty("Name");
    QString ver = ds->getDarsDbusProperty("Version");
    int global_enable = ds->getDarsDbusParam(DARS_PARAM_GLOBAL_ENABLE_STR).toInt();

    ui->setupUi(this);

    if (!name.isEmpty() && !ver.isEmpty()) {
        ui->statusBar->showMessage(name + "(" + ver + ")");
        if (global_enable) {
            ui->actionDarsEnable->setChecked(true);
        }
        else {
            ui->actionDarsEnable->setChecked(false);
        }
        setupInitUi();
    }
    else {
        ui->statusBar->showMessage("Can't connect to DarsAudio");
        setEnabled(false);
    }
    _conf_home = getenv("HOME");
    _conf_home += "/.config/darsaudio";
    QDir dir(_conf_home);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    setWindowIcon(QIcon(":/images/darsaudio.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupInitUi()
{
    DarsAudio *ds = DarsAudio::getInstance();
    float fv;
    int iv;
    QString name = ds->getDarsDbusProperty("Name");
    if (name.isEmpty()) {
        return;
    }

    // default is UserMode
    if (0 == ds->getDarsDbusParam(DARS_PARAM_CHANNELS_PAN_STR, &fv)) {
        QString strValue;
        strValue.sprintf("%d", static_cast<int>(fv*100.0f));
        ui->ChannelPan->setValue(static_cast<int>(fv*100.0f));
        ui->PanValue->setText(strValue);
    }
    if (0 == ds->getDarsDbusParam(DARS_PARAM_PRE_VOLUME_STR, &fv)) {
        QString strValue;
        strValue.sprintf("%d", static_cast<int>(fv*10.0f));
        ui->PreVolume->setValue(static_cast<int>(fv*10.0f));
        ui->PreVolumeValue->setText(strValue);
    }
    if (0 == ds->getDarsDbusParam(DARS_PARAM_POST_VOLUME_STR, &fv)) {
        QString strValue;
        strValue.sprintf("%d", static_cast<int>(fv*10.0f));
        ui->PostVolume->setValue(static_cast<int>(fv*10.0f));
        ui->PostVolumeValue->setText(strValue);
    }
    if (0 == ds->getDarsDbusParam(DARS_PARAM_STEREO_REVERT_STR, &iv)) {
        QString strValue;
        strValue.sprintf("%d", iv);
        ui->StereoRevert->setChecked(iv ? true : false);
    }


    // Eq
    if (0 == ds->getDarsDbusParam(DARS_PARAM_FIREQ_ENABLE_STR, &iv)) {
        if (iv) {
            ui->EqEnable->setChecked(true);
        }
        else {
            ui->EqEnable->setChecked(false);
        }
    }
    ui->EqMode->setEnabled(ui->EqEnable->isChecked());
    ui->EqBand1->setEnabled(ui->EqEnable->isChecked());
    ui->EqBand2->setEnabled(ui->EqEnable->isChecked());
    ui->EqBand3->setEnabled(ui->EqEnable->isChecked());
    ui->EqBand4->setEnabled(ui->EqEnable->isChecked());
    ui->EqBand5->setEnabled(ui->EqEnable->isChecked());
    ui->EqBand6->setEnabled(ui->EqEnable->isChecked());
    ui->EqBand7->setEnabled(ui->EqEnable->isChecked());
    ui->EqBand8->setEnabled(ui->EqEnable->isChecked());
    ui->EqBand9->setEnabled(ui->EqEnable->isChecked());
    ui->EqBand10->setEnabled(ui->EqEnable->isChecked());

    { // set Eq bands
        QString strValue = ds->getDarsDbusParam(DARS_PARAM_FIREQ_BANDS_STR);
        QStringList strList = strValue.split(",");
        QString labelStr;
        float fv;
        int iv;

        // band1
        fv = strList[0].toFloat();
        iv = static_cast<int>(fv * 100.0f);
        labelStr.sprintf("%d", iv);
        ui->EqBand1->setValue(iv);
        ui->EqValue1->setText(labelStr);

        // band2
        fv = strList[1].toFloat();
        iv = static_cast<int>(fv * 100.0f);
        labelStr.sprintf("%d", iv);
        ui->EqBand2->setValue(iv);
        ui->EqValue2->setText(labelStr);

        // band3
        fv = strList[2].toFloat();
        iv = static_cast<int>(fv * 100.0f);
        labelStr.sprintf("%d", iv);
        ui->EqBand3->setValue(iv);
        ui->EqValue3->setText(labelStr);

        // band4
        fv = strList[3].toFloat();
        iv = static_cast<int>(fv * 100.0f);
        labelStr.sprintf("%d", iv);
        ui->EqBand4->setValue(iv);
        ui->EqValue4->setText(labelStr);

        // band5
        fv = strList[4].toFloat();
        iv = static_cast<int>(fv * 100.0f);
        labelStr.sprintf("%d", iv);
        ui->EqBand5->setValue(iv);
        ui->EqValue5->setText(labelStr);

        // band6
        fv = strList[5].toFloat();
        iv = static_cast<int>(fv * 100.0f);
        labelStr.sprintf("%d", iv);
        ui->EqBand6->setValue(iv);
        ui->EqValue6->setText(labelStr);

        // band7
        fv = strList[6].toFloat();
        iv = static_cast<int>(fv * 100.0f);
        labelStr.sprintf("%d", iv);
        ui->EqBand7->setValue(iv);
        ui->EqValue7->setText(labelStr);

        // band8
        fv = strList[7].toFloat();
        iv = static_cast<int>(fv * 100.0f);
        labelStr.sprintf("%d", iv);
        ui->EqBand8->setValue(iv);
        ui->EqValue8->setText(labelStr);

        // band9
        fv = strList[8].toFloat();
        iv = static_cast<int>(fv * 100.0f);
        labelStr.sprintf("%d", iv);
        ui->EqBand9->setValue(iv);
        ui->EqValue9->setText(labelStr);

        // band10
        fv = strList[9].toFloat();
        iv = static_cast<int>(fv * 100.0f);
        labelStr.sprintf("%d", iv);
        ui->EqBand10->setValue(iv);
        ui->EqValue10->setText(labelStr);


    }

    // Bass
    iv = 0;
    if (0 == ds->getDarsDbusParam(DARS_PARAM_BASS_ENABLE_STR, &iv)) {
        on_BassEnable_clicked(iv ? true : false);
    }
    if (0 == ds->getDarsDbusParam(DARS_PARAM_BASS_MODE_STR, &iv)) {
        ui->BassMode->setCurrentIndex(iv);
    }
    if (0 == ds->getDarsDbusParam(DARS_PARAM_BASS_FREQ_STR, &iv)) {
        QString strValue;
        strValue.sprintf("%d", iv);
        ui->BassFreq->setValue(iv);
        ui->BassFreqValue->setText(strValue);
    }
    if (0 == ds->getDarsDbusParam(DARS_PARAM_BASS_FACTOR_STR, &fv)) {
        QString strValue;
        iv = static_cast<int>(fv * 10.0f);
        strValue.sprintf("%d", iv);
        ui->BassFactor->setValue(iv);
        ui->BassFactorValue->setText(strValue);
    }

    // Clarity
    iv = 0;
    if (0 == ds->getDarsDbusParam(DARS_PARAM_CLARITY_ENABLE_STR, &iv)) {
        on_ClarityEnable_clicked(iv ? true : false);
    }
    if (0 == ds->getDarsDbusParam(DARS_PARAM_CLARITY_MODE_STR, &iv)) {
        ui->ClarityMode->setCurrentIndex(iv);
    }
    if (0 == ds->getDarsDbusParam(DARS_PARAM_CLARITY_FACTOR_STR, &fv)) {
        QString strValue;
        iv = static_cast<int>(fv *10.0f);
        strValue.sprintf("%d", iv);
        ui->ClarityFactor->setValue(iv);
        ui->ClarityFactorValue->setText(strValue);
    }

    // Surround
    iv = 0;
    if (0 == ds->getDarsDbusParam(DARS_PARAM_SURROUND_ENABLE_STR, &iv)) {
        on_SurroundEnable_clicked(iv ? true : false);
    }
    ui->SurroundMode->setCurrentIndex(0);
    if (0 == ds->getDarsDbusParam(DARS_PARAM_SURROUND_STEREO_STR, &fv)) {
        QString strValue;
        iv = static_cast<int>(fv *10.0f);
        strValue.sprintf("%d", iv);
        ui->SurroundStereo->setValue(iv);
        ui->SurroundStereoValue->setText(strValue);
    }
    if (0 == ds->getDarsDbusParam(DARS_PARAM_SURROUND_IMAGE_STR, &fv)) {
        QString strValue;
        iv = static_cast<int>(fv *10.0f);
        strValue.sprintf("%d", iv);
        ui->SurroundImage->setValue(iv);
        ui->SurroundImageValue->setText(strValue);
    }

    // AGC
    iv = 0;
    if (0 == ds->getDarsDbusParam(DARS_PARAM_AGC_ENABLE_STR, &iv)) {
        on_AgcEnable_clicked(iv ? true : false);
    }
    if (0 == ds->getDarsDbusParam(DARS_PARAM_AGC_RATIO_STR, &fv)) {
        QString strValue;
        iv = static_cast<int>(fv *10.0f);
        strValue.sprintf("%d", iv);
        ui->AgcRatio->setValue(iv);
        ui->AgcRatioValue->setText(strValue);
    }
    if (0 == ds->getDarsDbusParam(DARS_PARAM_AGC_VOLUME_STR, &fv)) {
        QString strValue;
        iv = static_cast<int>(fv *10.0f);
        strValue.sprintf("%d", iv);
        ui->AgcVolume->setValue(iv);
        ui->AgcVolumeValue->setText(strValue);
    }
    if (0 == ds->getDarsDbusParam(DARS_PARAM_AGC_MAX_GAIN_STR, &fv)) {
        QString strValue;
        iv = static_cast<int>(fv *10.0f);
        strValue.sprintf("%d", iv);
        ui->AgcFactor->setValue(iv);
        ui->AgcFactorValue->setText(strValue);
    }
}



void MainWindow::on_actionLoadConfFile_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    _conf_home+"/darsaudio.conf",
                                                    tr("conf (*.conf)"));
    __load_conf(fileName);
}

void MainWindow::on_actionSaveConfFile_triggered()
{
    DarsAudio *ds = DarsAudio::getInstance();
    int iv;
    float fv;
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               _conf_home+"/darsaudio.conf",
                               tr("conf (*.conf)"));
    QFile conf(fileName);
    if (!conf.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    QTextStream out(&conf);

    if (0 == ds->getDarsDbusParam(DARS_PARAM_GLOBAL_ENABLE_STR, &iv)) {
        out << DARS_PARAM_GLOBAL_ENABLE_STR << "=" << iv << "\n";
    }
    if (0 == ds->getDarsDbusParam(DARS_PARAM_CHANNELS_PAN_STR, &fv)) {
        out << DARS_PARAM_CHANNELS_PAN_STR << "=" << fv << "\n";
    }
    if (0 == ds->getDarsDbusParam(DARS_PARAM_PRE_VOLUME_STR, &fv)) {
        out << DARS_PARAM_PRE_VOLUME_STR << "=" << fv << "\n";
    }
    if (0 == ds->getDarsDbusParam(DARS_PARAM_POST_VOLUME_STR, &fv)) {
        out << DARS_PARAM_POST_VOLUME_STR << "=" << fv << "\n";
    }
    if (0 == ds->getDarsDbusParam(DARS_PARAM_BASS_ENABLE_STR, &iv)) {
        out << DARS_PARAM_BASS_ENABLE_STR << "=" << iv << "\n";
    }
    if (0 == ds->getDarsDbusParam(DARS_PARAM_BASS_MODE_STR, &iv)) {
        out << DARS_PARAM_BASS_MODE_STR << "=" << iv << "\n";
    }
    if (0 == ds->getDarsDbusParam(DARS_PARAM_BASS_FREQ_STR, &iv)) {
        out << DARS_PARAM_BASS_FREQ_STR << "=" << iv << "\n";
    }
    if (0 == ds->getDarsDbusParam(DARS_PARAM_BASS_FACTOR_STR, &fv)) {
        out << DARS_PARAM_BASS_FACTOR_STR << "=" << fv << "\n";
    }
    if (0 == ds->getDarsDbusParam(DARS_PARAM_CLARITY_ENABLE_STR, &iv)) {
        out << DARS_PARAM_CLARITY_ENABLE_STR << "=" << iv << "\n";
    }
    if (0 == ds->getDarsDbusParam(DARS_PARAM_CLARITY_MODE_STR, &iv)) {
        out << DARS_PARAM_CLARITY_MODE_STR << "=" << iv << "\n";
    }
    if (0 == ds->getDarsDbusParam(DARS_PARAM_CLARITY_FACTOR_STR, &fv)) {
        out << DARS_PARAM_CLARITY_FACTOR_STR << "=" << fv << "\n";
    }
    if (0 == ds->getDarsDbusParam(DARS_PARAM_AGC_ENABLE_STR, &iv)) {
        out << DARS_PARAM_AGC_ENABLE_STR << "=" << iv << "\n";
    }
    if (0 == ds->getDarsDbusParam(DARS_PARAM_AGC_RATIO_STR, &fv)) {
        out << DARS_PARAM_AGC_RATIO_STR << "=" << fv << "\n";
    }
    if (0 == ds->getDarsDbusParam(DARS_PARAM_AGC_VOLUME_STR, &fv)) {
        out << DARS_PARAM_AGC_VOLUME_STR << "=" << fv << "\n";
    }
    if (0 == ds->getDarsDbusParam(DARS_PARAM_AGC_MAX_GAIN_STR, &fv)) {
        out << DARS_PARAM_AGC_MAX_GAIN_STR << "=" << fv << "\n";
    }
    if (0 == ds->getDarsDbusParam(DARS_PARAM_SURROUND_ENABLE_STR, &iv)) {
        out << DARS_PARAM_SURROUND_ENABLE_STR << "=" << iv << "\n";
    }
    if (0 == ds->getDarsDbusParam(DARS_PARAM_SURROUND_STEREO_STR, &fv)) {
        out << DARS_PARAM_SURROUND_STEREO_STR << "=" << fv << "\n";
    }
    if (0 == ds->getDarsDbusParam(DARS_PARAM_SURROUND_IMAGE_STR, &fv)) {
        out << DARS_PARAM_SURROUND_IMAGE_STR << "=" << fv << "\n";
    }
    if (0 == ds->getDarsDbusParam(DARS_PARAM_FIREQ_ENABLE_STR, &iv)) {
        out << DARS_PARAM_FIREQ_ENABLE_STR << "=" << iv << "\n";
    }
    QString eqbands = ds->getDarsDbusParam(DARS_PARAM_FIREQ_BANDS_STR);
    out << DARS_PARAM_FIREQ_BANDS_STR << "=" << eqbands << "\n";


    out.flush();
    conf.close();
}

void MainWindow::on_actionDarsEnable_triggered(bool checked)
{
    const char *v = checked ? "1" : "0";
    int iv = 0;
    DarsAudio *ds = DarsAudio::getInstance();
    ds->setDarsDbusParam(DARS_PARAM_GLOBAL_ENABLE_STR, v);

    if (0 == ds->getDarsDbusParam(DARS_PARAM_GLOBAL_ENABLE_STR, &iv)) {
        bool isGloablEnable = iv ? true : false;
        ui->actionDarsEnable->setChecked(isGloablEnable);
    }
}

void MainWindow::on_ChannelPan_valueChanged(int value)
{
    QString strValue;
    float fv = value / 100.0f;
    DarsAudio *ds = DarsAudio::getInstance();

    ds->setDarsDbusParam(DARS_PARAM_CHANNELS_PAN_STR, fv);
    if (0 == ds->getDarsDbusParam(DARS_PARAM_CHANNELS_PAN_STR, &fv)) {
        strValue.sprintf("%d", static_cast<int>(fv*100.0f));
        ui->PanValue->setText(strValue);
    }
    __set_global_enable(true);
}

void MainWindow::on_PreVolume_valueChanged(int value)
{
    QString strValue;
    float fv = value / 10.0f;
    DarsAudio *ds = DarsAudio::getInstance();

    ds->setDarsDbusParam(DARS_PARAM_PRE_VOLUME_STR, fv);
    if (0 == ds->getDarsDbusParam(DARS_PARAM_PRE_VOLUME_STR, &fv)) {
        strValue.sprintf("%d", static_cast<int>(fv*10.0f));
        ui->PreVolumeValue->setText(strValue);
    }
    __set_global_enable(true);
}

void MainWindow::on_PostVolume_valueChanged(int value)
{
    QString strValue;
    float fv = value / 10.0f;
    DarsAudio *ds = DarsAudio::getInstance();

    ds->setDarsDbusParam(DARS_PARAM_POST_VOLUME_STR, fv);
    if (0 == ds->getDarsDbusParam(DARS_PARAM_POST_VOLUME_STR, &fv)) {
        strValue.sprintf("%d", static_cast<int>(fv*10.0f));
        ui->PostVolumeValue->setText(strValue);
    }
    __set_global_enable(true);
}

void MainWindow::on_EqEnable_clicked(bool checked)
{
    DarsAudio *ds = DarsAudio::getInstance();
    int iv = checked ? 1 : 0;

    ds->setDarsDbusParam(DARS_PARAM_FIREQ_ENABLE_STR, iv);
    if (0 == ds->getDarsDbusParam(DARS_PARAM_FIREQ_ENABLE_STR, &iv)) {
        ui->EqEnable->setChecked(iv ? true : false);
    }
    ui->EqMode->setEnabled(ui->EqEnable->isChecked());
    ui->EqBand1->setEnabled(checked);
    ui->EqBand2->setEnabled(checked);
    ui->EqBand3->setEnabled(checked);
    ui->EqBand4->setEnabled(checked);
    ui->EqBand5->setEnabled(checked);
    ui->EqBand6->setEnabled(checked);
    ui->EqBand7->setEnabled(checked);
    ui->EqBand8->setEnabled(checked);
    ui->EqBand9->setEnabled(checked);
    ui->EqBand10->setEnabled(checked);

    __set_global_enable(true);
}

void MainWindow::on_EqBand1_valueChanged(int value)
{
    DarsAudio *ds = DarsAudio::getInstance();

    __eqBands_set_value(0, value);
    {
        QString strValue = ds->getDarsDbusParam(DARS_PARAM_FIREQ_BANDS_STR);
        QStringList strList = strValue.split(",");
        QString labelStr;
        float fv;
        int iv;

        // band1
        fv = strList[0].toFloat();
        iv = static_cast<int>(fv * 100.0f);
        labelStr.sprintf("%d", iv);
        ui->EqBand1->setValue(iv);
        ui->EqValue1->setText(labelStr);
    }
}

void MainWindow::__eqBands_set_value(int index, int value)
{
    DarsAudio *ds = DarsAudio::getInstance();
    QString strElm;
    float fv = value / 100.0f;

    QString strValue = ds->getDarsDbusParam(DARS_PARAM_FIREQ_BANDS_STR);
    QStringList strList = strValue.split(",");

    strElm.sprintf("%f", fv);

    strList[index] = strElm;

    strValue = strList[0] + "," + strList[1] + "," + strList[2] + "," + strList[3] + "," + strList[4] +
            "," + strList[5]+ "," + strList[6] + "," + strList[7] + "," + strList[8] + "," + strList[9];

    ds->setDarsDbusParam(DARS_PARAM_FIREQ_BANDS_STR, strValue.toStdString().c_str());

}

void MainWindow::__set_global_enable(bool e)
{
    int iv = e ? 1 : 0;
    DarsAudio *ds = DarsAudio::getInstance();
    ds->setDarsDbusParam(DARS_PARAM_GLOBAL_ENABLE_STR, iv);

    if (0 == ds->getDarsDbusParam(DARS_PARAM_GLOBAL_ENABLE_STR, &iv)) {
        bool isGloablEnable = iv ? true : false;
        ui->actionDarsEnable->setChecked(isGloablEnable);
    }

}

void MainWindow::__load_conf(QString file)
{
    DarsAudio *ds = DarsAudio::getInstance();
    QFile conf(file);
    if (!conf.exists()) {
        return;
    }
    if (!conf.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QTextStream in (&conf);

    while(!in.atEnd()) {
        QString cmd = in.readLine();
        QStringList cmdList = cmd.split("=");
        ds->setDarsDbusParam(cmdList[0].toStdString().c_str(), cmdList[1].toStdString().c_str());
    }
    setupInitUi();
}

void MainWindow::on_EqBand2_valueChanged(int value)
{
    DarsAudio *ds = DarsAudio::getInstance();

    __eqBands_set_value(1, value);
    {
        QString strValue = ds->getDarsDbusParam(DARS_PARAM_FIREQ_BANDS_STR);
        QStringList strList = strValue.split(",");
        QString labelStr;
        float fv;
        int iv;

        // band1
        fv = strList[1].toFloat();
        iv = static_cast<int>(fv * 100.0f);
        labelStr.sprintf("%d", iv);
        ui->EqBand2->setValue(iv);
        ui->EqValue2->setText(labelStr);
    }

}

void MainWindow::on_EqBand3_valueChanged(int value)
{
    DarsAudio *ds = DarsAudio::getInstance();

    __eqBands_set_value(2, value);
    {
        QString strValue = ds->getDarsDbusParam(DARS_PARAM_FIREQ_BANDS_STR);
        QStringList strList = strValue.split(",");
        QString labelStr;
        float fv;
        int iv;

        // band1
        fv = strList[2].toFloat();
        iv = static_cast<int>(fv * 100.0f);
        labelStr.sprintf("%d", iv);
        ui->EqBand3->setValue(iv);
        ui->EqValue3->setText(labelStr);
    }
}

void MainWindow::on_EqBand4_valueChanged(int value)
{
    DarsAudio *ds = DarsAudio::getInstance();

    __eqBands_set_value(3, value);
    {
        QString strValue = ds->getDarsDbusParam(DARS_PARAM_FIREQ_BANDS_STR);
        QStringList strList = strValue.split(",");
        QString labelStr;
        float fv;
        int iv;

        // band1
        fv = strList[3].toFloat();
        iv = static_cast<int>(fv * 100.0f);
        labelStr.sprintf("%d", iv);
        ui->EqBand4->setValue(iv);
        ui->EqValue4->setText(labelStr);
    }

}

void MainWindow::on_EqBand5_valueChanged(int value)
{
    DarsAudio *ds = DarsAudio::getInstance();

    __eqBands_set_value(4, value);
    {
        QString strValue = ds->getDarsDbusParam(DARS_PARAM_FIREQ_BANDS_STR);
        QStringList strList = strValue.split(",");
        QString labelStr;
        float fv;
        int iv;

        // band1
        fv = strList[4].toFloat();
        iv = static_cast<int>(fv * 100.0f);
        labelStr.sprintf("%d", iv);
        ui->EqBand5->setValue(iv);
        ui->EqValue5->setText(labelStr);
    }

}

void MainWindow::on_EqBand6_valueChanged(int value)
{
    DarsAudio *ds = DarsAudio::getInstance();

    __eqBands_set_value(5, value);
    {
        QString strValue = ds->getDarsDbusParam(DARS_PARAM_FIREQ_BANDS_STR);
        QStringList strList = strValue.split(",");
        QString labelStr;
        float fv;
        int iv;

        // band1
        fv = strList[5].toFloat();
        iv = static_cast<int>(fv * 100.0f);
        labelStr.sprintf("%d", iv);
        ui->EqBand6->setValue(iv);
        ui->EqValue6->setText(labelStr);
    }
}

void MainWindow::on_EqBand7_valueChanged(int value)
{
    DarsAudio *ds = DarsAudio::getInstance();

    __eqBands_set_value(6, value);
    {
        QString strValue = ds->getDarsDbusParam(DARS_PARAM_FIREQ_BANDS_STR);
        QStringList strList = strValue.split(",");
        QString labelStr;
        float fv;
        int iv;

        // band1
        fv = strList[6].toFloat();
        iv = static_cast<int>(fv * 100.0f);
        labelStr.sprintf("%d", iv);
        ui->EqBand7->setValue(iv);
        ui->EqValue7->setText(labelStr);
    }

}

void MainWindow::on_EqBand8_valueChanged(int value)
{
    DarsAudio *ds = DarsAudio::getInstance();

    __eqBands_set_value(7, value);
    {
        QString strValue = ds->getDarsDbusParam(DARS_PARAM_FIREQ_BANDS_STR);
        QStringList strList = strValue.split(",");
        QString labelStr;
        float fv;
        int iv;

        // band1
        fv = strList[7].toFloat();
        iv = static_cast<int>(fv * 100.0f);
        labelStr.sprintf("%d", iv);
        ui->EqBand8->setValue(iv);
        ui->EqValue8->setText(labelStr);
    }

}

void MainWindow::on_EqBand9_valueChanged(int value)
{
    DarsAudio *ds = DarsAudio::getInstance();

    __eqBands_set_value(8, value);
    {
        QString strValue = ds->getDarsDbusParam(DARS_PARAM_FIREQ_BANDS_STR);
        QStringList strList = strValue.split(",");
        QString labelStr;
        float fv;
        int iv;

        // band1
        fv = strList[8].toFloat();
        iv = static_cast<int>(fv * 100.0f);
        labelStr.sprintf("%d", iv);
        ui->EqBand9->setValue(iv);
        ui->EqValue9->setText(labelStr);
    }

}

void MainWindow::on_EqBand10_valueChanged(int value)
{
    DarsAudio *ds = DarsAudio::getInstance();

    __eqBands_set_value(9, value);
    {
        QString strValue = ds->getDarsDbusParam(DARS_PARAM_FIREQ_BANDS_STR);
        QStringList strList = strValue.split(",");
        QString labelStr;
        float fv;
        int iv;

        // band1
        fv = strList[9].toFloat();
        iv = static_cast<int>(fv * 100.0f);
        labelStr.sprintf("%d", iv);
        ui->EqBand10->setValue(iv);
        ui->EqValue10->setText(labelStr);
    }

}

void MainWindow::on_BassEnable_clicked(bool checked)
{
    DarsAudio *ds = DarsAudio::getInstance();
    int iv = checked ? 1 : 0;

    ds->setDarsDbusParam(DARS_PARAM_BASS_ENABLE_STR, iv);

    iv = 0;
    if (0 == ds->getDarsDbusParam(DARS_PARAM_BASS_ENABLE_STR, &iv)) {
        bool isEnabled = iv ? true : false;
        ui->BassEnable->setChecked(isEnabled);
        ui->BassFactor->setEnabled(isEnabled);
        ui->BassFreq->setEnabled(isEnabled);
        ui->BassMode->setEnabled(isEnabled);
        if (isEnabled) {
            __set_global_enable(true);
        }
    }

}

void MainWindow::on_BassMode_activated(int index)
{
    DarsAudio *ds = DarsAudio::getInstance();
    int iv = 0;

    ds->setDarsDbusParam(DARS_PARAM_BASS_MODE_STR, index);

    if (0 == ds->getDarsDbusParam(DARS_PARAM_BASS_MODE_STR, &iv)) {
        ui->BassMode->setCurrentIndex(index);
    }
    __set_global_enable(true);
}

void MainWindow::on_BassFactor_valueChanged(int value)
{
    DarsAudio *ds = DarsAudio::getInstance();
    float fv = value / 10.0f;

    ds->setDarsDbusParam(DARS_PARAM_BASS_FACTOR_STR, fv);

    if (0 == ds->getDarsDbusParam(DARS_PARAM_BASS_FACTOR_STR, &fv)) {
        QString strValue;
        int iv = static_cast<int>(fv * 10.0f);
        strValue.sprintf("%d", iv);
        ui->BassFactor->setValue(iv);
        ui->BassFactorValue->setText(strValue);
    }
    __set_global_enable(true);

}

void MainWindow::on_BassFreq_valueChanged(int value)
{
    int iv = 0;
    DarsAudio *ds = DarsAudio::getInstance();

    ds->setDarsDbusParam(DARS_PARAM_BASS_FREQ_STR, value);

    if (0 == ds->getDarsDbusParam(DARS_PARAM_BASS_FREQ_STR, &iv)) {
        QString strValue;
        strValue.sprintf("%d", iv);

        ui->BassFreq->setValue(iv);
        ui->BassFreqValue->setText(strValue);
    }
    __set_global_enable(true);

}

void MainWindow::on_ClarityEnable_clicked(bool checked)
{
    int iv = checked ? 1 : 0;
    DarsAudio *ds = DarsAudio::getInstance();

    ds->setDarsDbusParam(DARS_PARAM_CLARITY_ENABLE_STR, iv);

    if (0 == ds->getDarsDbusParam(DARS_PARAM_CLARITY_ENABLE_STR, &iv)) {
        ui->ClarityEnable->setChecked(iv ? true : false);
        ui->ClarityMode->setEnabled(iv ? true : false);
        ui->ClarityFactor->setEnabled(iv ? true : false);
    }
    __set_global_enable(true);
}

void MainWindow::on_ClarityMode_activated(int index)
{
    DarsAudio *ds = DarsAudio::getInstance();
    int iv = 0;

    ds->setDarsDbusParam(DARS_PARAM_CLARITY_MODE_STR, index);

    if (0 == ds->getDarsDbusParam(DARS_PARAM_CLARITY_MODE_STR, &iv)) {
        ui->BassMode->setCurrentIndex(index);
    }
    __set_global_enable(true);
}

void MainWindow::on_ClarityFactor_valueChanged(int value)
{
    DarsAudio *ds = DarsAudio::getInstance();
    float fv = value / 10.0f;

    ds->setDarsDbusParam(DARS_PARAM_CLARITY_FACTOR_STR, fv);

    if (0 == ds->getDarsDbusParam(DARS_PARAM_CLARITY_FACTOR_STR, &fv)) {
        QString strValue;
        int iv = static_cast<int>(fv * 10.0f);
        strValue.sprintf("%d", iv);
        ui->ClarityFactor->setValue(iv);
        ui->ClarityFactorValue->setText(strValue);
    }
    __set_global_enable(true);
}

void MainWindow::on_SurroundEnable_clicked(bool checked)
{
    int iv = checked ? 1 : 0;
    DarsAudio *ds = DarsAudio::getInstance();

    ds->setDarsDbusParam(DARS_PARAM_SURROUND_ENABLE_STR, iv);

    if (0 == ds->getDarsDbusParam(DARS_PARAM_SURROUND_ENABLE_STR, &iv)) {
        bool isEnabled = iv ? true : false;
        ui->SurroundEnable->setChecked(isEnabled);
        ui->SurroundMode->setEnabled(isEnabled);
        ui->SurroundImage->setEnabled(isEnabled);
        ui->SurroundStereo->setEnabled(isEnabled);
    }
    __set_global_enable(true);
}

void MainWindow::on_SurroundStereo_valueChanged(int value)
{
    DarsAudio *ds = DarsAudio::getInstance();
    float fv = value / 10.0f;

    ds->setDarsDbusParam(DARS_PARAM_SURROUND_STEREO_STR, fv);

    if (0 == ds->getDarsDbusParam(DARS_PARAM_SURROUND_STEREO_STR, &fv)) {
        QString strValue;
        int iv = static_cast<int>(fv * 10.0f);
        strValue.sprintf("%d", iv);
        ui->SurroundStereo->setValue(iv);
        ui->SurroundStereoValue->setText(strValue);
    }
    __set_global_enable(true);
}

void MainWindow::on_SurroundImage_valueChanged(int value)
{
    DarsAudio *ds = DarsAudio::getInstance();
    float fv = value / 10.0f;

    ds->setDarsDbusParam(DARS_PARAM_SURROUND_IMAGE_STR, fv);

    if (0 == ds->getDarsDbusParam(DARS_PARAM_SURROUND_IMAGE_STR, &fv)) {
        QString strValue;
        int iv = static_cast<int>(fv * 10.0f);
        strValue.sprintf("%d", iv);
        ui->SurroundImage->setValue(iv);
        ui->SurroundImageValue->setText(strValue);
    }
    __set_global_enable(true);
}

void MainWindow::on_AgcEnable_clicked(bool checked)
{
    int iv = checked ? 1 : 0;
    DarsAudio *ds = DarsAudio::getInstance();

    ds->setDarsDbusParam(DARS_PARAM_AGC_ENABLE_STR, iv);

    if (0 == ds->getDarsDbusParam(DARS_PARAM_AGC_ENABLE_STR, &iv)) {
        bool isEnabled = iv ? true : false;
        ui->AgcEnable->setChecked(isEnabled);
        ui->AgcFactor->setEnabled(isEnabled);
        ui->AgcRatio->setEnabled(isEnabled);
        ui->AgcVolume->setEnabled(isEnabled);
    }
    __set_global_enable(true);
}

void MainWindow::on_AgcRatio_valueChanged(int value)
{
    DarsAudio *ds = DarsAudio::getInstance();
    float fv = value / 10.0f;

    ds->setDarsDbusParam(DARS_PARAM_AGC_RATIO_STR, fv);

    if (0 == ds->getDarsDbusParam(DARS_PARAM_AGC_RATIO_STR, &fv)) {
        QString strValue;
        int iv = static_cast<int>(fv * 10.0f);
        strValue.sprintf("%d", iv);
        ui->AgcRatio->setValue(iv);
        ui->AgcRatioValue->setText(strValue);
    }
    __set_global_enable(true);
}

void MainWindow::on_AgcVolume_valueChanged(int value)
{
    DarsAudio *ds = DarsAudio::getInstance();
    float fv = value / 10.0f;

    ds->setDarsDbusParam(DARS_PARAM_AGC_VOLUME_STR, fv);

    if (0 == ds->getDarsDbusParam(DARS_PARAM_AGC_VOLUME_STR, &fv)) {
        QString strValue;
        int iv = static_cast<int>(fv * 10.0f);
        strValue.sprintf("%d", iv);
        ui->AgcVolume->setValue(iv);
        ui->AgcVolumeValue->setText(strValue);
    }
    __set_global_enable(true);
}

void MainWindow::on_AgcFactor_valueChanged(int value)
{
    DarsAudio *ds = DarsAudio::getInstance();
    float fv = value / 10.0f;

    ds->setDarsDbusParam(DARS_PARAM_AGC_MAX_GAIN_STR, fv);

    if (0 == ds->getDarsDbusParam(DARS_PARAM_AGC_MAX_GAIN_STR, &fv)) {
        QString strValue;
        int iv = static_cast<int>(fv * 10.0f);
        strValue.sprintf("%d", iv);
        ui->AgcFactor->setValue(iv);
        ui->AgcFactorValue->setText(strValue);
    }
    __set_global_enable(true);
}

void MainWindow::on_MusicMode_clicked(bool checked)
{
    QString f;
    if (!checked) {
        return;
    }
    f = _conf_home + "/music_mode.conf";
    QFile conf(f);

    if (!conf.exists()) {
        return;
    }

    __load_conf(f);
}

void MainWindow::on_MovieMode_clicked(bool checked)
{
    QString f;
    if (!checked) {
        return;
    }
    f = _conf_home + "/movie_mode.conf";
    QFile conf(f);

    if (!conf.exists()) {
        return;
    }

    __load_conf(f);
}

void MainWindow::on_StereoRevert_clicked(bool checked)
{
    DarsAudio *ds = DarsAudio::getInstance();
    int iv = checked ? 1 : 0;

    ds->setDarsDbusParam(DARS_PARAM_STEREO_REVERT_STR, iv);

    if (0 == ds->getDarsDbusParam(DARS_PARAM_STEREO_REVERT_STR, &iv)) {
        QString strValue;
        strValue.sprintf("%d", iv);
        ui->StereoRevert->setChecked(iv ? true : false);
    }
    __set_global_enable(true);
}
