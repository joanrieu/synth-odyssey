////////////////////////////////////////////////////////////////////////////////
// PCM OUTPUT
////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

// in
extern float
sr,
vca_out;

// out
float
sr = 44100;

void update_pcm() {
    int32_t output = std::floor(vca_out * 2147483648);
    int32_t max = 2147483647;
    int32_t min = -2147483648;
    output = std::min(max, std::max(min, output));
    std::cout.write((char*) &output, 4);
}
