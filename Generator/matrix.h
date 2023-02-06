#ifndef MATRIX_H
#define MATRIX_H

#include <QVector>
#include <QRandomGenerator>
#include <QtDebug>

class matrix {
    QVector<QVector<int> > matrix_;
    int width_;
    int height_;
public:
    matrix(int n, int m);
    QVector<QVector<int> > getMatrix() const {return matrix_;};
    void printMatrix() const;
};

#endif // MATRIX_H
