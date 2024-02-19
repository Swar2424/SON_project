import numpy as np
import sounddevice as sd
import time

def generate_sine_wave(frequency, duration, amplitude, sample_rate):
    t = np.linspace(0, duration, int(sample_rate * duration), endpoint=False)
    wave = amplitude * np.sin(2 * np.pi * frequency * t)
    return wave

def generate_piano_sound(note, duration, sample_rate):
    fundamental_freq = 440 * (2 ** ((note - 49) / 12))  # Calculate frequency for piano note
    harmonics = [1, 0.5, 0.3, 0.2, 0.1]  # Amplitude ratios for harmonics
    amplitudes = [1] + [h * 0.3 for h in harmonics]  # Amplitudes for fundamental and harmonics
    envelope = np.concatenate([np.linspace(0, 1, int(sample_rate * 0.01)), np.linspace(1, 0.7, int(sample_rate * 0.02)), np.linspace(0.7, 0, int(sample_rate * 0.97))])
    sound = np.zeros(int(duration * sample_rate))
    
    for harmonic, amplitude in zip(range(1, len(amplitudes) + 1), amplitudes):
        sound += generate_sine_wave(fundamental_freq * harmonic, duration, amplitude, sample_rate) * envelope
    
    return sound

# Example usage
note = 60  # MIDI note number (middle C)
duration = 2  # Duration of the sound in seconds
sample_rate = 44100  # Sample rate in Hz

piano_sound = generate_piano_sound(note, duration, sample_rate)

# Play the sound
sd.play(piano_sound, sample_rate)
time.sleep(duration)
