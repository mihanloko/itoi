//
// Created by mikhail on 02.05.2021.
//

#include "DataSaver.h"
#include "DetectorUtil.h"

vector<InterestingPoint> DataSaver::saveData(DoubleImage &image, vector<vector<double>> &mins, vector<InterestingPoint> &points, const QString& method) {
    DoubleImage minImage(image.getWidth(), image.getHeight());
    int ind = 0;
    for (const vector<double>& r : mins) {
        for (double d: r) {
            minImage.getData()[ind++] = d;
        }
    }
    Image::fromDouble(minImage.normalize(255).getData(), minImage.getWidth(), minImage.getHeight())
    .saveToFile(method + "_map_" + image.getName());
    DoubleImage localMaximumsImage(image.getWidth(), image.getHeight());
    for (InterestingPoint &point: points) {
        localMaximumsImage(point.getX(), point.getY()) = 1;
    }
    Image::fromDouble(localMaximumsImage.normalize(255).getData(), minImage.getWidth(), minImage.getHeight())
            .saveToFile(method + "_localMaximums_" + image.getName());
    auto filtered = DetectorUtil::filter(points, 100, min(image.getHeight() / 2, image.getWidth() / 2));
    DoubleImage filteredImage(image.getWidth(), image.getHeight());
    for (InterestingPoint &point: filtered) {
        filteredImage(point.getX(), point.getY()) = 1;
    }
    Image::fromDouble(filteredImage.normalize(255).getData(), minImage.getWidth(), minImage.getHeight())
            .saveToFile(method + "_filtered_" + image.getName());

    auto result = method + "_result_" + image.getName();
    QImage res(image.getWidth(), image.getHeight(), QImage::Format_RGB32);
    auto normilized = image.normalize(255);
    for (int x = 0; x < image.getWidth(); x++) {
        for (int y = 0; y < image.getHeight(); y++) {
            double pixel = normilized(x, y);
            res.setPixel(x, y, qRgb(pixel, pixel, pixel));
        }
    }

    int w = image.getWidth();
    int h = image.getHeight();
    for (InterestingPoint &point: filtered) {
        int x = point.getX();
        int y = point.getY();
        for (int i = 1; i < 3; i++) {
            if (x + i < w) {
                res.setPixel(x + i, y, qRgb(0, 0, 255));
            }
            if (x - i > -1) {
                res.setPixel(x - i, y, qRgb(0, 0, 255));
            }
            if (y + i < h) {
                res.setPixel(x, y + i, qRgb(0, 0, 255));
            }
            if (y - i > -1) {
                res.setPixel(x, y - i, qRgb(0, 0, 255));
            }
        }
    }
    res.save("resources/out/" + result);

    return filtered;
}
