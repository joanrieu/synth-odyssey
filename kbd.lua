--------------------------------------------------------------------------------
-- KEYBOARD / SEQUENCER
--------------------------------------------------------------------------------

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
        local samples_per_note = 1 * sr
        local melody = {
            D1, D1, D2, A1, D1, D1, F1, A1,
            D1, D1, D2, A1, D1, D2, A1, A1
        }
        while true do
            for i = 1, #melody do
                for j = 1, samples_per_note do
                    kbd_trigger = j == 1
                    kbd_gate = j < samples_per_note / 2
                    kbd_freq = melody[i]
                    coroutine.yield()
                end
            end
        end
    end
)
