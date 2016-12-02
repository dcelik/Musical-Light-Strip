
import numpy
from multiprocessing import Pool
import alsaaudio, time, audioop
try:
    import RPi.GPIO as GPIO
except RuntimeError, ImportError:
    print "Error: GPIO did not initialize properly"
import numpy
import alsaaudio, time, audioop


audio_signal = []

def listen_audio_input():
    inp = alsaaudio.PCM(alsaaudio.PCM_CAPTURE,alsaaudio.PCM_NONBLOCK)
    inp.setchannels(1)
    inp.setrate(8000)
    inp.setformat(alsaaudio.PCM_FORMAT_S16_LE)
    inp.setperiodsize(8)

    while True:
        l,data = inp.read()
        if l:
            # Return the maximum of the absolute value of all samples in a fragment.
            print audioop.max(data, 2)
            audio_signal = audioop.max(data, 2)
        time.sleep(.001)