#!/usr/bin/python3
import numpy as np

fs_hz = 16000
freq_hz = 15
duration_seconds = 1.0
n_bits = 14


t = np.linspace(0, freq_hz*2*np.pi, int( duration_seconds * fs_hz))
x = (np.sin(t)*(2**n_bits - 1)).astype(int)
bb = ','.join([str(int(s)) for s in x.tolist()])

f = open('sinusoid_samples.h', 'w')
f.write('#ifndef _SINUSOID_SAMPLES_H_\n')
f.write('#define _SINUSOID_SAMPLES_H_\n')
f.write('const static int16_t kSamples[%d] = {%s};\n' % (x.shape[0], bb))
f.write('const static uint32_t kNumSamples = %d;\n' % (x.shape[0]))
f.write('const static uint32_t kSampleRateHz = %d;\n' % (fs_hz))
f.write('#endif //_SINUSOID_SAMPLES_H_\n')
f.close()
