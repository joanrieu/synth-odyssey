#pragma once

#include <QObject>

class QSynth : public QObject {
    Q_OBJECT

public:
    Q_INVOKABLE void setFloatControl(int index, float newValue);
    Q_INVOKABLE void setBooleanControl(int index, bool newValue);

signals:
    void floatControlChanged(int index, float newValue);
    void booleanControlChanged(int index, bool newValue);
};
