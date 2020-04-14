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
        source: "Odyssey.png"
        anchors.fill: parent
    }

    ContextMenu {}

    PresetPanel {
        x: 388
        y: 20
    }

    TransposeRibbon {
        x: 582
        y: 39
    }

    SliderH {
        name: "kbd_portamento"
        min: 0
        max: 1.5
        power: 1

        x: 709
        y: 39
    }

    Item {
        x: 934
        y: 29

        TriggerLed {}

        GateLed {
            y: 23
        }
    }

    Item {
        y: 92

        Item {
            x: 46

            Slider {
                name: "vco1_tune"
                min: 0
                max: 16
                power: 2
            }

            SliderB {
                name: "vco1_detune"
                min: 0
                max: 1
                power: 2

                x: 32
            }
        }

        Item {
            x: 222

            Slider {
                name: "vco2_tune"
                min: 0
                max: 16
                power: 2
            }

            SliderB {
                name: "vco2_detune"
                min: 0
                max: 1
                power: 2
                x: 32
            }
        }

        Item {
            x: 494

            Slider {
                name: "lfo_freq"
                min: 0
                max: 20
                power: 2
            }
        }

        Item {
            x: 682
            y: 12

            Slider {
                name: "vcf_cutoff"
                min: 0
                max: 16000
                power: 2
            }

            Slider {
                name: "vcf_reso"
                min: 0
                max: 100
                power: 2

                x: 32
            }

            Slider {
                name: "hpf_cutoff"
                min: 0
                max: 16000
                power: 2

                x: 64
            }

            Slider {
                name: "vca_gain"
                min: 0
                max: 10
                power: 1

                x: 116
            }
        }

        Item {
            x: 878

            Slider {
                name: "ar_attack"
                min: 0
                max: 1
                power: 1
            }

            Slider {
                name: "ar_release"
                min: 0
                max: 1
                power: 1

                x: 32
            }
        }
    }

    Item {
        y: 353

        Item {
            x: 46

            Slider {
                name: "vco1_fm1"
                min: 0
                max: 1
                power: 1
            }

            Slider {
                name: "vco1_fm2"
                min: 0
                max: 1
                power: 1

                x: 32
            }

            Slider {
                name: "vco1_pw"
                min: 0
                max: 1
                power: 1

                x: 64
            }

            Slider {
                name: "vco1_pwm"
                min: 0
                max: 1
                power: 1

                x: 96
            }
        }

        Item {
            x: 220

            Slider {
                name: "vco2_fm1"
                min: 0
                max: 1
                power: 1
            }

            Slider {
                name: "vco2_fm2"
                min: 0
                max: 1
                power: 1

                x: 32
            }

            Slider {
                name: "vco2_pw"
                min: 0
                max: 1
                power: 1

                x: 64
            }

            Slider {
                name: "vco2_pwm"
                min: 0
                max: 1
                power: 1

                x: 96
            }
        }

        Item {
            x: 398

            Slider {
                name: "sh_vco1"
                min: 0
                max: 1
                power: 1
            }

            Slider {
                name: "sh_noise"
                min: 0
                max: 1
                power: 1

                x: 32
            }
        }

        Item {
            x: 494

            Slider {
                name: "sh_lag"
                min: 0
                max: 1
                power: 1
            }
        }

        Item {
            x: 574

            Slider {
                name: "mix_noise_ring"
                min: 0
                max: 1
                power: 1
            }

            Slider {
                name: "mix_vco1"
                min: 0
                max: 1
                power: 1

                x: 32
            }

            Slider {
                name: "mix_vco2"
                min: 0
                max: 1
                power: 1

                x: 64
            }
        }

        Item {
            x: 682

            Slider {
                name: "vcf_mod1"
                min: 0
                max: 1
                power: 1
            }

            Slider {
                name: "vcf_mod2"
                min: 0
                max: 1
                power: 1

                x: 32
            }

            Slider {
                name: "vcf_env"
                min: 0
                max: 1
                power: 1

                x: 64
            }

            Slider {
                name: "vca_env"
                min: 0
                max: 10
                power: 1

                x: 116
            }
        }

        Item {
            x: 878

            Slider {
                name: "adsr_attack"
                min: 0
                max: 1
                power: 1
            }

            Slider {
                name: "adsr_decay"
                min: 0
                max: 1
                power: 1

                x: 32
            }

            Slider {
                name: "adsr_sustain"
                min: 0
                max: 1
                power: 1

                x: 64
            }

            Slider {
                name: "adsr_release"
                min: 0
                max: 1
                power: 1

                x: 96
            }
        }
    }

    Item {
        y: 132

        Rocker {
            name: "vco1_kbd"
            x: 162
        }

        Rocker {
            name: "vco2_sync"
            x: 336
        }

        Rocker {
            name: "noise_white"
            x: 593
        }
    }

    Item {
        y: 598

        Item {
            x: 66

            Rocker {
                name: "vco1_fm1_is_lfo_sine"
            }

            Rocker {
                name: "vco1_fm2_is_sh_out"
                x: 32
            }

            Rocker {
                name: "vco1_pwm_is_lfo"
                x: 96
            }
        }

        Item {
            x: 240

            Rocker {
                name: "vco2_fm1_is_lfo_sine"
            }

            Rocker {
                name: "vco2_fm2_is_sh_out"
                x: 32
            }

            Rocker {
                name: "vco2_pwm_is_lfo"
                x: 96
            }
        }

        Item {
            x: 418

            Rocker {
                name: "sh_vco1_saw"
            }

            Rocker {
                name: "sh_noise_gen"
                x: 32
            }

            Rocker {
                name: "sh_lfo_trigger"
                x: 96
            }
        }

        Item {
            x: 594

            Rocker {
                name: "mix_noise"
            }

            Rocker {
                name: "mix_vco1_saw"
                x: 32
            }

            Rocker {
                name: "mix_vco2_saw"
                x: 64
            }
        }

        Item {
            x: 702

            Rocker {
                name: "vcf_mod1_kbd"
            }

            Rocker {
                name: "vcf_mod2_sh"
                x: 32
            }

            Rocker {
                name: "vcf_env_adsr"
                x: 64
            }
        }

        Item {
            x: 818

            Rocker {
                name: "vca_env_ar"
            }
        }

        Item {
            x: 898

            Rocker {
                name: "adsr_kbd_trigger"
            }

            Rocker {
                name: "adsr_kbd_repeat"
                x: 48
            }

            Rocker {
                name: "ar_kbd_trigger"
                x: 96
            }
        }
    }
}
