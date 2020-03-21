import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    minimumWidth: 1066
    maximumWidth: 1066
    minimumHeight: 700
    maximumHeight: 700
    title: qsTr("Synth Odyssey")

    Image {
        id: background
        source: "Odyssey.png"
        anchors.fill: parent
    }

    Item {
        y: 92

        Item {
            x: 46

            Slider {
                id: vco1_tune
            }

            Slider {
                id: vco1_detune
                x: 32
            }
        }

        Item {
            x: 222

            Slider {
                id: vco2_tune
            }

            Slider {
                id: vco2_detune
                x: 32
            }
        }

        Item {
            x: 494

            Slider {
                id: lfo_freq
            }
        }

        Item {
            x: 682
            y: 12

            Slider {
                id: vcf_cutoff
            }

            Slider {
                id: vcf_reso
                x: 32
            }

            Slider {
                id: hpf_cutoff
                x: 64
            }

            Slider {
                id: vca_gain
                x: 116
            }
        }

        Item {
            x: 878

            Slider {
                id: ar_attack
            }

            Slider {
                id: ar_release
                x: 32
            }
        }
    }

    Item {
        y: 353

        Item {
            x: 46

            Slider {
                id: vco1_fm1
            }

            Slider {
                id: vco1_fm2
                x: 32
            }

            Slider {
                id: vco1_pw
                x: 64
            }

            Slider {
                id: vco1_pwm
                x: 96
            }
        }

        Item {
            x: 220

            Slider {
                id: vco2_fm1
            }

            Slider {
                id: vco2_fm2
                x: 32
            }

            Slider {
                id: vco2_pw
                x: 64
            }

            Slider {
                id: vco2_pwm
                x: 96
            }
        }

        Item {
            x: 398

            Slider {
                id: sh_vco1
            }

            Slider {
                id: sh_noise
                x: 32
            }
        }

        Item {
            x: 494

            Slider {
                id: sh_lag
            }
        }

        Item {
            x: 574

            Slider {
                id: mix_noise_ring
            }

            Slider {
                id: mix_vco1
                x: 32
            }

            Slider {
                id: mix_vco2
                x: 64
            }
        }

        Item {
            x: 682

            Slider {
                id: vcf_mod1
            }

            Slider {
                id: vcf_mod2
                x: 32
            }

            Slider {
                id: vcf_env
                x: 64
            }

            Slider {
                id: vca_env
                x: 116
            }
        }

        Item {
            x: 878

            Slider {
                id: adsr_attack
            }

            Slider {
                id: adsr_decay
                x: 32
            }

            Slider {
                id: adsr_sustain
                x: 64
            }

            Slider {
                id: adsr_release
                x: 96
            }
        }
    }
}
