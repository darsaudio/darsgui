#ifndef DARSAUDIO_H
#define DARSAUDIO_H

#include <dbus/dbus.h>
#include <QString>

#define DARS_PARAM_GLOBAL_ENABLE_STR          "global-enable"
#define DARS_PARAM_CHANNELS_PAN_STR            "channels-pan"       /* -1.0 0 1.0 */

#define DARS_PARAM_PRE_VOLUME_STR             "volume-before-dars"
#define DARS_PARAM_POST_VOLUME_STR            "volume-after-dars"

#define DARS_PARAM_BASS_ENABLE_STR           "bass-enable"
#define DARS_PARAM_BASS_MODE_STR             "bass-mode"
#define DARS_PARAM_BASS_FREQ_STR             "bass-freq"
#define DARS_PARAM_BASS_FACTOR_STR           "bass-factor"

#define DARS_PARAM_CLARITY_ENABLE_STR        "clarity-enable"
#define DARS_PARAM_CLARITY_MODE_STR          "clarity-mode"
#define DARS_PARAM_CLARITY_FACTOR_STR        "clarity-factor"


#define DARS_PARAM_AGC_ENABLE_STR            "agc-enable"
#define DARS_PARAM_AGC_RATIO_STR            "agc-ratio"
#define DARS_PARAM_AGC_VOLUME_STR              "agc-volume"
#define DARS_PARAM_AGC_MAX_GAIN_STR             "agc-max-gain"


#define DARS_PARAM_SURROUND_ENABLE_STR      "surround3d-enable"
#define DARS_PARAM_SURROUND_STEREO_STR      "surround3d-stereo-width"
#define DARS_PARAM_SURROUND_IMAGE_STR       "surround3d-stereo-image"


#define DARS_PARAM_FIREQ_ENABLE_STR          "eq-enable"
#define DARS_PARAM_FIREQ_BANDS_STR           "eq-bands"


class DarsAudio
{
public:
    DarsAudio();

    static DarsAudio *getInstance();

    QString findDarsDbusAddr();
    QString getDarsDbusProperty(const char *pname);
    QString getDarsDbusParam(const char *pname);
    int getDarsDbusParam(const char *pname, int *iv);
    int getDarsDbusParam(const char *pname, float *fv);



    void setDarsDbusParam(const char *name, const char *value);
    void setDarsDbusParam(const char *name, const int value);
    void setDarsDbusParam(const char *name, const float value);

private:
    static DarsAudio* _instance;
    QString mDarsDbusAddr;
};

#endif // DARSAUDIO_H
