# Amplitude-Pulser-Plugin
Your plugin should have two Sliders to control:

    the amplitude pulser LFO frequency, ranged from 0.0 to 10.0Hz
    the phase offset between the left and right LFOs, ranged from 0 to 180 degrees

Note that when your amplitude pulser LFO frequency is 0.0Hz, you must either suppress use of the LFO signal, or set the LFO phase angles to pi/2 so that the LFO sample values are always 1.0 and produce a unity-gain output.
