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

    // Crop parameters for digit processing
    double getCropPercentHorizontal() const {
        return _cropPercentHorizontal;
    }
    void setCropPercentHorizontal(double percent) {
        _cropPercentHorizontal = percent;
    }

    double getCropPercentVertical() const {
        return _cropPercentVertical;
    }
    void setCropPercentVertical(double percent) {
        _cropPercentVertical = percent;
    }

    double getCropPercentHorizontalAOI() const {
        return _cropPercentHorizontalAOI;
    }
    void setCropPercentHorizontalAOI(double percent) {
        _cropPercentHorizontalAOI = percent;
    }

    double getCropPercentVerticalAOI() const {
        return _cropPercentVerticalAOI;
    }
    void setCropPercentVerticalAOI(double percent) {
        _cropPercentVerticalAOI = percent;
    }

    // Morphological operation parameters for fragment filtering
    int getMorphKernelSizeDivisor() const {
        return _morphKernelSizeDivisor;
    }
    void setMorphKernelSizeDivisor(int divisor) {
        _morphKernelSizeDivisor = divisor;
    }

    int getMorphIterations() const {
        return _morphIterations;
    }
    void setMorphIterations(int iterations) {
        _morphIterations = iterations;
    }

    double getMorphSizeRatioThreshold() const {
        return _morphSizeRatioThreshold;
    }
    void setMorphSizeRatioThreshold(double threshold) {
        _morphSizeRatioThreshold = threshold;
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
    
    // Crop parameters for digit processing
    double _cropPercentHorizontal = 0.1;      // 10% standard horizontal crop
    double _cropPercentVertical = 0.02;       // 2% standard vertical crop
    double _cropPercentHorizontalAOI = 0.15;  // 15% AOI digit horizontal crop
    double _cropPercentVerticalAOI = 0.02;    // 2% AOI digit vertical crop
    
    // Morphological operation parameters for fragment filtering
    int _morphKernelSizeDivisor = 15;          // Kernel size = min(width,height) / divisor (default 15)
    int _morphIterations = 1;                  // Number of dilation/erosion iterations (default 1)
    double _morphSizeRatioThreshold = 0.4;     // Threshold for similar-sized contours (default 0.4)
};

#endif /* CONFIG_H_ */
