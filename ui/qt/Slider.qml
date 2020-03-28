import QtQuick 2.12

Item {
    property string name
    property int index: ([
        "vco1_tune",
        "vco1_detune",
        "vco2_tune",
        "vco2_detune",
        "lfo_freq",
        "vcf_cutoff",
        "vcf_reso",
        "hpf_cutoff",
        "vca_gain",
        "ar_attack",
        "ar_release",
        "vco1_fm1",
        "vco1_fm2",
        "vco1_pw",
        "vco1_pwm",
        "vco2_fm1",
        "vco2_fm2",
        "vco2_pw",
        "vco2_pwm",
        "sh_vco1",
        "sh_noise",
        "sh_lag",
        "mix_noise_ring",
        "mix_vco1",
        "mix_vco2",
        "vcf_mod1",
        "vcf_mod2",
        "vcf_env",
        "vca_env",
        "adsr_attack",
        "adsr_decay",
        "adsr_sustain",
        "adsr_release",
    ].indexOf(name))
    property real value: (Math.sin(index / 4) + 1) / 2

    MouseArea {
        x: 16
        y: 32
        width: 16
        height: 160
        cursorShape: "PointingHandCursor"

        onMouseYChanged: {
            value = 1 - Math.min(1, Math.max(0, mouseY / this.height))
        }
    }

    Rectangle {
        x: 22
        y: 22
        width: 4
        height: button.y
        color: "black"
    }

    Image {
        id: button
        source: "Button.png"
        scale: 0.5
        y: 10 + 160 * (1 - value)

        Behavior on y {
            NumberAnimation {
                duration: 40
            }
        }
    }
}
