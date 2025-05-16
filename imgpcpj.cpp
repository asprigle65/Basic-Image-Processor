#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;


// Function to apply brightness and contrast adjustment
Mat adjustContrastBrightness(const Mat& input, double alpha, int beta) {
    Mat output;
    input.convertTo(output, -1, alpha, beta);
    return output;
}

// Function to apply histogram equalization (for grayscale)
Mat histogramEqualization(const Mat& input) {
    Mat gray, equalized;
    cvtColor(input, gray, COLOR_BGR2GRAY);
    equalizeHist(gray, equalized);
    return equalized;
}

// Function to apply Gaussian blur
Mat denoiseImage(const Mat& input) {
    Mat output;
    GaussianBlur(input, output, Size(5, 5), 0);
    return output;
}

// Function to apply edge detection
Mat detectEdges(const Mat& input) {
    Mat gray, edges;
    cvtColor(input, gray, COLOR_BGR2GRAY);
    Canny(gray, edges, 100, 200);
    return edges;
}

// Function to apply sharpening filter
Mat sharpenImage(const Mat& input) {
    Mat output;
    Mat kernel = (Mat_<float>(3,3) <<
                   0, -1, 0,
                  -1, 5, -1,
                   0, -1, 0);
    filter2D(input, output, input.depth(), kernel);
    return output;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Usage: ./image_processor <image_path>" << endl;
        return -1;
    }

    Mat image = imread(argv[1]);
    if (image.empty()) {
        cout << "Error loading image!" << endl;
        return -1;
    }

    cout << "\nImage Processing Menu:\n";
    cout << "1. Invert Image\n";
    cout << "2. Adjust Contrast & Brightness\n";
    cout << "3. Histogram Equalization\n";
    cout << "4. Gaussian Blur (Denoise)\n";
    cout << "5. Edge Detection (Canny)\n";
    cout << "6. Sharpen Image\n";
    cout << "Enter your choice (1-6): ";

    int choice;
    cin >> choice;

    Mat result;
    string winTitle, outFilename;

    switch (choice) {
        case 1:
            bitwise_not(image, result);
            winTitle = "Inverted";
            outFilename = "output_inverted.jpg";
            break;
        case 2:
            result = adjustContrastBrightness(image, 1.5, 30);
            winTitle = "Contrast & Brightness";
            outFilename = "output_contrast.jpg";
            break;
        case 3:
            result = histogramEqualization(image);
            winTitle = "Histogram Equalization";
            outFilename = "output_histogram_equalized.jpg";
            break;
        case 4:
            result = denoiseImage(image);
            winTitle = "Gaussian Blur (Denoise)";
            outFilename = "output_denoised.jpg";
            break;
        case 5:
            result = detectEdges(image);
            winTitle = "Canny Edge Detection";
            outFilename = "output_edges.jpg";
            break;
        case 6:
            result = sharpenImage(image);
            winTitle = "Sharpened";
            outFilename = "output_sharpened.jpg";
            break;
        default:
            cout << "Invalid choice!" << endl;
            return -1;
    }

    imshow(winTitle, result);
    imwrite(outFilename, result);
    cout << "Saved result as: " << outFilename << endl;

    waitKey(0);
    destroyAllWindows();

    return 0;
}


