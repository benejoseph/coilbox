#!/usr/bin/python3
# Drives a pulse through the coil.  It's not perfect but is sort of okay.
# I'm not proud of it, in case you missed that.
import numpy as np
import matplotlib.pyplot as plt
import scipy.signal as sig
fs_hz = 16000
pulse_duration_seconds = 2.0
freq_hz = 1.0 / (pulse_duration_seconds) # / np.pi


n_bits = 14
offset = 0.0

dtheta = 2*np.pi * freq_hz / float(fs_hz)
n2 = pulse_duration_seconds * fs_hz / 2.0
#t = np.array(range(-int(n2), int(n2)))
t = np.array(range(0,int(n2)))
theta = t * dtheta
x = ((np.cos(theta) + offset)*(2**n_bits - 1)).astype(int)
window = sig.windows.hamming(x.shape[0])
x = x * window
k = (2**n_bits - 1) / np.max(np.abs(x)) * 0.95
x =(x.astype(float) * k).astype(int)
plt.plot(t,x)
plt.show()

bb = ','.join([str(int(s)) for s in x.tolist()])

f = open('sinusoid_samples.h', 'w')
f.write('#ifndef _SINUSOID_SAMPLES_H_\n')
f.write('#define _SINUSOID_SAMPLES_H_\n')
f.write('const static int16_t kSamples[%d] = {%s};\n' % (x.shape[0], bb))
f.write('const static uint32_t kNumSamples = %d;\n' % (x.shape[0]))
f.write('const static uint32_t kSampleRateHz = %d;\n' % (fs_hz))
f.write('#endif //_SINUSOID_SAMPLES_H_\n')
f.close()
