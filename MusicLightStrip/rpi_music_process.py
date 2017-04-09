
import numpy
from multiprocessing import Process
import alsaaudio, time, audioop
try:
    import RPi.GPIO as GPIO
except RuntimeError, ImportError:
    print "Error: GPIO did not initialize properly"
import numpy
import alsaaudio, time, audioop


audio_signal = []

def listen_audio_input(input):
    while True:
        l,data = input.read()
        if l:
            # Return the maximum of the absolute value of all samples in a fragment.
            print audioop.max(data, 2)
            audio_signal = audioop.max(data, 2)
        time.sleep(.001)

def create_audio_process():
    inp = alsaaudio.PCM(alsaaudio.PCM_CAPTURE,alsaaudio.PCM_NONBLOCK)
    inp.setchannels(1)
    inp.setrate(8000)
    inp.setformat(alsaaudio.PCM_FORMAT_S16_LE)
    inp.setperiodsize(8)

    p = Process(target = listen_audio_input, args=(inp))
    p.start()
    p.join()

