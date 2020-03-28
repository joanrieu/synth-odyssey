import QtQuick 2.12

Item {
    property string name
    property int index: ([
        "vco1_kbd",
        "vco2_sync",
        "noise_white",
        "vco1_fm1_is_lfo_sine",
        "vco1_fm2_is_sh_out",
        "vco1_pwm_is_lfo",
        "vco2_fm1_is_lfo_sine",
        "vco2_fm2_is_sh_out",
        "vco2_pwm_is_lfo",
        "sh_vco1_saw",
        "sh_noise_gen",
        "sh_lfo_trigger",
        "mix_noise",
        "mix_vco1_saw",
        "mix_vco2_saw",
        "vcf_mod1_kbd",
        "vcf_mod2_sh",
        "vcf_env_adsr",
        "vca_env_ar",
        "adsr_kbd_trigger",
        "adsr_kbd_repeat",
        "ar_kbd_trigger",
    ].indexOf(name))
    property bool value: index % 2

    MouseArea {
        width: 8
        height: 29
        onClicked: value = !value
        cursorShape: "PointingHandCursor"
    }

    Rectangle {
        width: 8
        height: 12
        color: "black"
        opacity: !value

        Behavior on opacity {
            NumberAnimation {
                duration: 200
            }
        }
    }

    Rectangle {
        y: 17
        width: 8
        height: 12
        color: "black"
        opacity: value

        Behavior on opacity {
            NumberAnimation {
                duration: 200
            }
        }
    }
}
