--------------------------------------------------------------------------------
-- PCM OUTPUT
--------------------------------------------------------------------------------

-- internal
pcm_buffer = {}
pcm_index = 1

io.output():setvbuf("no")

function update_pcm()
    pcm_buffer[pcm_index] = vca_out
    if pcm_index == oversampling then
        pcm_index = 0
        local output = 0
        for i = 1, oversampling do
            output = output + pcm_buffer[i] / oversampling
        end
        io.write(string.pack("<i4", math.min(2^31 - 1, math.max(-2^31, math.floor(output * 2^31)))))
    end
    pcm_index = pcm_index + 1
end
