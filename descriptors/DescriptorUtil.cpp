//
// Created by mikhail on 17.05.2021.
//

#include "DescriptorUtil.h"

DoubleImage DescriptorUtil::getGradient(DoubleImage &image, bool normalize) {
    auto first = FiltersImplementation::derivativeX(image);
    auto second = FiltersImplementation::derivativeY(image);
    auto gradient = DoubleImage(first.getWidth(), first.getHeight());
    for (int i = 0; i < gradient.size(); i++) {
        auto firstPixel = first.getData()[i];
        auto secondPixel = second.getData()[i];
        gradient.getData()[i] = sqrt(firstPixel * firstPixel + secondPixel * secondPixel);
    }
    return normalize ? gradient.normalize() : gradient;
}

MatchData DescriptorUtil::match(vector<Descriptor> &firstList, vector<Descriptor> &secondList) {
    vector<pair<InterestingPoint, InterestingPoint>> pointsMatching;

    for (auto &item : firstList) {
        auto closest = getClosest(item, secondList);
        if (closest == nullptr)
            continue;
        pointsMatching.emplace_back(item.getPoint(), closest->getPoint());
    }

    return MatchData(pointsMatching, firstList, secondList);
}

Descriptor* DescriptorUtil::getClosest(Descriptor &descriptor,vector<Descriptor> &descriptors) {
    vector<double> distances;
    distances.reserve(descriptors.size());
    for (auto &patchDescriptor : descriptors) {
        distances.push_back(Descriptor::distance(descriptor, patchDescriptor));
    }
    int a = getMinIndex(distances, -1);
    int b = getMinIndex(distances, a);

    double r = distances[a] / distances[b];
    return (r <= 0.5) ? &descriptors[a] : nullptr;
}

int DescriptorUtil::getMinIndex(vector<double> distances, int excludeIndex) {
    int selectedIndex = -1;
    for (int i = 0; i < distances.size(); i++)
        if (i != excludeIndex && (selectedIndex == -1 || distances[i] < distances[selectedIndex]))
            selectedIndex = i;

    return selectedIndex;
}

QImage DescriptorUtil::markMatching(DoubleImage &a, DoubleImage &b, MatchData& data) {
    Image imageA = Image::fromDouble(a.normalize(255).getData(), a.getWidth(), a.getHeight());
    Image imageB = Image::fromDouble(b.normalize(255).getData(), b.getWidth(), b.getHeight());
    auto markedImageA = DataSaver::markDescriptors(data.getDescriptorsA(), imageA);
    auto markedImageB = DataSaver::markDescriptors(data.getDescriptorsB(), imageB);
    QImage resultImage = QImage(markedImageA.width() + markedImageB.width(),
                                max(markedImageA.height(), markedImageB.height()),
                                QImage::Format_RGB32);
    QPainter painter(&resultImage);
    painter.drawImage(QRect(0, 0, markedImageA.width(), markedImageA.height()), markedImageA);
    painter.drawImage(QRect(markedImageA.width(), 0, markedImageA.width(), markedImageA.height()),
                      markedImageB);

    painter.setPen(QColor(0, 255, 0));
    for (auto pointsPair : data.getPointsPairs()) {

        auto pointA = pointsPair.first;
        auto pointB = pointsPair.second;
        painter.drawLine(pointA.getX(), pointA.getY(), pointB.getX() + markedImageA.width(), pointB.getY());
    }
    return resultImage;
}

DoubleImage DescriptorUtil::getGradient(DoubleImage &first, DoubleImage &second,
                            double (*counterFunc)(double, double)) {
    auto gradient = DoubleImage(first.getWidth(), first.getHeight());

    for (int i = 0; i < gradient.size(); i++) {
        auto firstPixel = first.getData()[i];
        auto secondPixel = second.getData()[i];
        gradient.getData()[i] = counterFunc(firstPixel, secondPixel);
    }

    return gradient;
}

DoubleImage DescriptorUtil::getGradient(DoubleImage &first, DoubleImage &second) {
    return getGradient(first, second, [](double firstPixel, double secondPixel) {
        return sqrt((firstPixel * firstPixel) + (secondPixel * secondPixel));
    });
}

DoubleImage DescriptorUtil::getGradientAngle(DoubleImage &first, DoubleImage &second) {
    return getGradient(first, second, [](double firstPixel, double secondPixel) {
        return atan2(firstPixel, secondPixel);
    });
}
