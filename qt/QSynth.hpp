#pragma once

#include <QObject>

#include "../core/control.hpp"

class QSynth : public QObject {
    Q_OBJECT

    SynthController controller;

public:
    Q_INVOKABLE void setFloatControl(int index, float newValue);
    Q_INVOKABLE void setBooleanControl(int index, bool newValue);

signals:
    void floatControlChanged(int index, float newValue);
    void booleanControlChanged(int index, bool newValue);
};
