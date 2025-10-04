emeocv
======

Read and recognize the counter of an electricity meter with OpenCV.

![OpenCV for the electricity meter](http://www.kompf.de/cplus/images/emeocv_m.png)


Prerequisites
=============

* g++, make
* OpenCV 2, 3, 4 (Debian/Ubuntu/Raspbian: `apt-get install libopencv-dev`) - developed with OpenCV 2.3.1 and later ported to OpenCV 3.2.0 and 4.2.0
* RRDtool (`apt-get install rrdtool librrd-dev`)
* log4cpp (`apt-get install liblog4cpp5-dev`)
* imagemagick (optional, only needed to display graphs)

Build
=====

    cd emeocv
    make

Usage
=====

    emeocv [-i <dir>|-c <cam>] [-l|-t|-a|-w|-o <dir>] [-s <delay>] [-v <level>] [-d]

    Image input:
        -i <image directory> : read image files (png) from directory.
        -c <camera number> : read images from camera.

    Operation:
        -a : adjust camera.
        -o <directory> : capture images into directory.
        -l : learn OCR.
        -t : test OCR.
        -w : write OCR data to RR database. This is the normal working mode.

    Options:
        -s <n> : Sleep n milliseconds after processing of each image (default=1000).
        -v <l> : Log level. One of DEBUG, INFO, ERROR (default).
        -d : Enable debug/test mode - saves intermediate processing steps as images.

Debug Mode
==========

The debug mode (`-d` option) is particularly useful for testing and development. When enabled, it saves intermediate images from each processing step to help analyze the image processing workflow.

### Debug Output

All debug images are saved to the `debug_output/` directory with descriptive filenames that include:
- Function name
- Processing parameters
- Step sequence

### Example Debug Files

When processing an electricity meter image with debug mode enabled:

    ./emeocv -i images/ -t -d

The following debug images will be generated:

    debug_output/ImageProcessor_grayscale.png
    debug_output/ImageProcessor_rotate_degrees=0.png
    debug_output/ImageProcessor_rotate_degrees=2.5.png
    debug_output/ImageProcessor_cannyEdges_threshold1=100_threshold2=200.png
    debug_output/ImageProcessor_digit_digit_index=0_x=45_y=120_width=18_height=25.png
    debug_output/ImageProcessor_digit_digit_index=1_x=65_y=120_width=20_height=25.png
    debug_output/KNearestOcr_recognize_recognized_digit=3_result=3_distance=1250.5.png
    debug_output/KNearestOcr_recognize_recognized_digit=?_result=7_distance=750000.0.png

### Debug Image Types

- **Grayscale conversion**: Shows the original image converted to grayscale
- **Rotation steps**: Images after initial rotation and skew correction
- **Edge detection**: Result of Canny edge detection with threshold parameters
- **Individual digits**: Each detected digit region with position and size information
- **OCR recognition**: Each digit with recognition result, confidence distance, and acceptance status

This debug functionality helps with:
- **Parameter tuning**: Visualize the effect of different thresholds and settings
- **Algorithm validation**: Verify that each processing step works correctly
- **Troubleshooting**: Identify where the processing chain fails for specific images
- **Training data creation**: Extract individual digit images for OCR training


There is a tutorial that explains use case and function of the program:
[OpenCV practice: OCR for the electricity meter](https://en.kompf.de/cplus/emeocv.html) or
[OpenCV Praxis: OCR für den Stromzähler](https://www.kompf.de/cplus/emeocv.html) (in german language).

License
=======

Copyright 2015,2021 Martin Kompf

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
