/*
 * Config.h
 *
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>

class Config {
public:
    Config();
    void saveConfig();
    void loadConfig();

    bool getTestMode() const { return _testMode; }
    void setTestMode(bool mode) { _testMode = mode; }

    bool getAreaOfInterest() const { return _areaOfInterest; }
    void setAreaOfInterest(bool mode) { _areaOfInterest = mode; }

    bool getCropDigits() const { return _cropDigits; }
    void setCropDigits(bool mode) { _cropDigits = mode; }

    bool getPerspectiveCorrection() const { return _perspectiveCorrection; }
    void setPerspectiveCorrection(bool mode) { _perspectiveCorrection = mode; }

    int getDigitMaxHeight() const {
        return _digitMaxHeight;
    }

    int getDigitMinHeight() const {
        return _digitMinHeight;
    }

    int getDigitYAlignment() const {
        return _digitYAlignment;
    }

    std::string getTrainingDataFilename() const {
        return _trainingDataFilename;
    }

    float getOcrMaxDist() const {
        return _ocrMaxDist;
    }

    int getRotationDegrees() const {
        return _rotationDegrees;
    }

    int getCannyThreshold1() const {
        return _cannyThreshold1;
    }

    int getCannyThreshold2() const {
        return _cannyThreshold2;
    }

private:
    int _rotationDegrees;
    float _ocrMaxDist;
    int _digitMinHeight;
    int _digitMaxHeight;
    int _digitYAlignment;
    int _cannyThreshold1;
    int _cannyThreshold2;
    std::string _trainingDataFilename;
    bool _testMode = false;
    bool _areaOfInterest = false;
    bool _cropDigits = false;
    bool _perspectiveCorrection = false;
};

#endif /* CONFIG_H_ */
