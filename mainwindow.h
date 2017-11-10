#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setupInitUi();

private slots:

    void on_actionLoadConfFile_triggered();

    void on_actionSaveConfFile_triggered();

    void on_actionDarsEnable_triggered(bool checked);

    void on_ChannelPan_valueChanged(int value);

    void on_PreVolume_valueChanged(int value);

    void on_PostVolume_valueChanged(int value);

    void on_EqEnable_clicked(bool checked);

    void on_EqBand1_valueChanged(int value);

    void on_EqBand2_valueChanged(int value);

    void on_EqBand3_valueChanged(int value);

    void on_EqBand4_valueChanged(int value);

    void on_EqBand5_valueChanged(int value);

    void on_EqBand6_valueChanged(int value);

    void on_EqBand7_valueChanged(int value);

    void on_EqBand8_valueChanged(int value);

    void on_EqBand9_valueChanged(int value);

    void on_EqBand10_valueChanged(int value);

    void on_BassEnable_clicked(bool checked);

    void on_BassMode_activated(int index);

    void on_BassFactor_valueChanged(int value);

    void on_BassFreq_valueChanged(int value);

    void on_ClarityEnable_clicked(bool checked);

    void on_ClarityMode_activated(int index);

    void on_ClarityFactor_valueChanged(int value);

    void on_SurroundEnable_clicked(bool checked);

    void on_SurroundStereo_valueChanged(int value);

    void on_SurroundImage_valueChanged(int value);

    void on_AgcEnable_clicked(bool checked);

    void on_AgcRatio_valueChanged(int value);

    void on_AgcVolume_valueChanged(int value);

    void on_AgcFactor_valueChanged(int value);

    void on_MusicMode_clicked(bool checked);

    void on_MovieMode_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    QString _conf_home;
    void __eqBands_set_value(int index, int v);
    void __set_global_enable(bool e);
    void __load_conf(QString file);
};

#endif // MAINWINDOW_H
