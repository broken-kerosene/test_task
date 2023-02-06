#include "matrix.h"

const int MAX_BOUNDED = 99;

matrix::matrix(int n, int m)
{
    height_ = n;
    width_ = m;
    matrix_.resize(height_);
    for(auto &line: matrix_){
        line.resize(width_);
        for(auto &elem: line){
            elem = QRandomGenerator::global()->bounded(MAX_BOUNDED);
        }
    }
}

void matrix::printMatrix() const
{
    QDebug dbg = qDebug().nospace().noquote();
    for(auto line: matrix_){
        for(auto elem: line){
            dbg << elem << " ";
        }
        dbg << "\n";
    }
}
