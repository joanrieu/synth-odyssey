--------------------------------------------------------------------------------
-- ATTACK-DECAY-SUSTAIN-RELEASE ENVELOPE
--------------------------------------------------------------------------------

-- knobs
adsr_attack = 0
adsr_sustain = 0
adsr_decay = 0
adsr_release = 0

-- internal
adsr_state = 0
adsr_done = 0
adsr_todo = 0

-- out
adsr_out = 0

function update_adsr()
    if kbd_trigger then
        adsr_state = 1
        adsr_done = 0
        adsr_todo = math.floor(adsr_attack * sr)
    end
    if adsr_state == 1 then
        if adsr_todo > 0 then
            adsr_out = adsr_done / (adsr_done + adsr_todo)
        else
            adsr_state = 2
            adsr_done = 0
            adsr_todo = math.floor(adsr_decay * sr)
        end
    end
    if adsr_state == 2 then
        if adsr_todo > 0 then
            adsr_out = 1 - ((1 - adsr_sustain) * adsr_done / (adsr_done + adsr_todo))
        else
            adsr_state = 3
        end
    end
    if adsr_state == 3 then
        adsr_out = adsr_sustain
    end
    if not kbd_gate and adsr_state ~= 0 and adsr_state ~= 4 then
        adsr_state = 4
        adsr_done = 0
        adsr_todo = math.floor(adsr_release * sr)
    end
    if adsr_state == 4 then
        if adsr_todo > 0 then
            adsr_out = adsr_sustain * adsr_todo / (adsr_done + adsr_todo)
        else
            adsr_state = 0
        end
    end
    if adsr_state == 0 then
        adsr_out = 0
    else
        adsr_done = adsr_done + 1
        adsr_todo = adsr_todo - 1
    end
end
