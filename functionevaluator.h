#ifndef FUNCTIONEVALUATOR_H
#define FUNCTIONEVALUATOR_H

#include <QChar>
#include <QDebug>
#include <QList>
#include <QPointF>
#include <QRegularExpression>
#include <QString>
#include <QStringList>
#include <QVector>
#include <cmath>

#define X_STEP 0.1

class FunctionEvaluator {
public:
  void setEquation(QString equation);
  void setMinX(float number);
  void setMaxX(float number);
  QList<QPointF> evaluatEquation();
  FunctionEvaluator();

private:
  QString equation;
  float maximumX, minimumX;
  QStringList splitTerms(QString equation);
  QVector<QChar> splitSigns(QString equation);
  QVector<float> rangeOfX(float min_x, float max_x, float step = 1);
  float evaluatTerm(QString term, QChar sign, float x_value);
};

#endif // FUNCTIONEVALUATOR_H
