#include <iostream>

#include "QSynth.hpp"

void QSynth::setFloatControl(int index, float newValue) {
    Control control;
    control.type = ControlType::FLOAT;
    control.cv.float_cv.control = FloatControl(index);
    control.cv.float_cv.value = newValue;
    controller.push_control(control);
    emit floatControlChanged(index, newValue);
}

void QSynth::setBooleanControl(int index, bool newValue) {
    Control control;
    control.type = ControlType::FLOAT;
    control.cv.boolean_cv.control = BooleanControl(index);
    control.cv.boolean_cv.value = newValue;
    controller.push_control(control);
    emit booleanControlChanged(index, newValue);
}
