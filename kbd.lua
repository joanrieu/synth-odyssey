--------------------------------------------------------------------------------
-- KEYBOARD / SEQUENCER
--------------------------------------------------------------------------------

-- knobs
kbd_portamento = 0
kbd_transpose = 0
kbd_sequencer = true

-- internal
kbd_freq_target = 0

-- out
kbd_trigger = false
kbd_gate = false
kbd_freq = 0

update_kbd = coroutine.wrap(
    function()
        local D2 = 73.42
        local A1 = 55.00
        local F1 = 43.65
        local D1 = 36.71
        local samples_per_note = 0.18 * sr
        local melody = {
            A1, A1, A1, A1, A1, A1, A1, A1, A1, A1, A1, A1, A1, A1, A1, A1,
            F1, F1, F1, F1, F1, F1, F1, F1, F1, F1, F1, F1, F1, F1, F1, F1,
            D1, D1, D1, D1, D1, D1, D1, D1, D1, D1, D1, D1, D1, D1, D1, D1,
            D2, D2, D2, D2, D2, D2, D2, D2, D2, D2, D2, D2, D2, D2, D2, D2,
        }
        while true do
            for i = 1, #melody do
                for j = 1, samples_per_note do
                    if kbd_sequencer then
                        kbd_trigger = j == 1
                        kbd_gate = j < samples_per_note
                        kbd_freq_target = melody[i]
                    end
                    local a = 1 - 10 ^ (-2 - kbd_portamento * sr / 2e4)
                    local transpose = kbd_transpose >= 0 and 2 ^ kbd_transpose or 1 / 2 ^ -kbd_transpose
                    kbd_freq = a * kbd_freq + (1 - a) * kbd_freq_target * transpose
                    coroutine.yield()
                end
            end
        end
    end
)
