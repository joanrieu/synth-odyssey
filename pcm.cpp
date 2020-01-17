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
extern int
oversampling;

// internal
std::vector<float> pcm_buffer;

// out
float pcm_out = 0;

void update_pcm() {
    pcm_buffer.push_back(vca_out);
    if (pcm_buffer.size() == oversampling) {
        pcm_out = 0;
        for (auto i = 0; i < oversampling; ++i) {
            pcm_out = pcm_out + pcm_buffer[i];
        }
        pcm_out = pcm_out / oversampling;
        pcm_buffer.clear();
        int32_t output = std::floor(pcm_out * 2147483648);
        int32_t max = 2147483647;
        int32_t min = -2147483648;
        output = std::min(max, std::max(min, output));
        std::cout.write((char*) &output, 4);
    }
}
