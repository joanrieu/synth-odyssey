--------------------------------------------------------------------------------
-- ATTACK-RELEASE ENVELOPE
--------------------------------------------------------------------------------

-- knobs
ar_attack = 0
ar_release = 0

-- internal
ar_state = 0
ar_done = 0
ar_todo = 0

-- out
ar_out = 0

-- derived from update_adsr()
function update_ar()
    if kbd_trigger then
        ar_state = 1
        ar_done = 0
        ar_todo = math.floor(ar_attack * sr)
    end
    if ar_state == 1 then
        if ar_todo > 0 then
            ar_out = ar_done / (ar_done + ar_todo)
        else
            ar_state = 3
        end
    end
    if ar_state == 3 then
        ar_out = 1
    end
    if not kbd_gate and ar_state ~= 0 and ar_state ~= 4 then
        ar_state = 4
        ar_done = 0
        ar_todo = math.floor(ar_release * sr)
    end
    if ar_state == 4 then
        if ar_todo > 0 then
            ar_out = ar_todo / (ar_done + ar_todo)
        else
            ar_state = 0
        end
    end
    if ar_state == 0 then
        ar_out = 0
    else
        ar_done = ar_done + 1
        ar_todo = ar_todo - 1
    end
end
