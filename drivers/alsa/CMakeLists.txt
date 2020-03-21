add_library(SynthAlsa SHARED alsa)
target_link_libraries(SynthAlsa SynthCore asound pthread)
