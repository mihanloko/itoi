#include <QApplication>
#include <QDebug>
#include <QImage>
#include <fstream>
#include <iostream>

using namespace std;

int main() {
    ifstream o("test.txt");
    string s;
    o >> s;
    cout << s;
    qDebug() << QT_VERSION_STR;
    return 1;
}