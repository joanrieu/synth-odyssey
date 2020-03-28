#include <iostream>

#include "QSynth.hpp"

void QSynth::setFloatControl(int index, float newValue) {
    std::cout << "float " << index << " = " << newValue << std::endl;
    emit floatControlChanged(index, newValue);
}

void QSynth::setBooleanControl(int index, bool newValue) {
    std::cout << "bool " << index << " = " << newValue << std::endl;
    emit booleanControlChanged(index, newValue);
}
