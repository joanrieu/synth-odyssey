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
                value: 0.5
            }

            Slider {
                id: vco1_detune
                x: 32
                value: 0.5
            }
        }

        Item {
            x: 222

            Slider {
                id: vco2_tune
                value: 0.5
            }

            Slider {
                id: vco2_detune
                x: 32
                value: 0.5
            }
        }

        Item {
            x: 494

            Slider {
                id: lfo_freq
                value: 0.5
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

    Item {
        y: 132

        Rocker {
            id: vco1_kbd
            x: 162
        }

        Rocker {
            id: vco2_sync
            x: 336
        }

        Rocker {
            id: noise_white
            x: 593
        }
    }

    Item {
        y: 598

        Item {
            x: 66

            Rocker {
                id: vco1_fm1_is_lfo_sine
            }

            Rocker {
                id: vco1_fm2_is_sh_out
                x: 32
            }

            Rocker {
                id: vco1_pwm_is_lfo
                x: 96
            }
        }

        Item {
            x: 240

            Rocker {
                id: vco2_fm1_is_lfo_sine
            }

            Rocker {
                id: vco2_fm2_is_sh_out
                x: 32
            }

            Rocker {
                id: vco2_pwm_is_lfo
                x: 96
            }
        }

        Item {
            x: 418

            Rocker {
                id: sh_vco1_saw
            }

            Rocker {
                id: sh_noise_gen
                x: 32
            }

            Rocker {
                id: sh_lfo_trigger
                x: 96
            }
        }

        Item {
            x: 594

            Rocker {
                id: mix_noise
            }

            Rocker {
                id: mix_vco1_saw
                x: 32
            }

            Rocker {
                id: mix_vco2_saw
                x: 64
            }
        }

        Item {
            x: 702

            Rocker {
                id: vcf_mod1_kbd
            }

            Rocker {
                id: vcf_mod2_sh
                x: 32
            }

            Rocker {
                id: vcf_env_adsr
                x: 64
            }
        }

        Item {
            x: 818

            Rocker {
                id: vca_env_ar
            }
        }

        Item {
            x: 898

            Rocker {
                id: adsr_kbd_trigger
            }

            Rocker {
                id: adsr_kbd_repeat
                x: 48
            }

            Rocker {
                id: ar_kbd_trigger
                x: 96
            }
        }
    }
}
