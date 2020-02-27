from scipy import *
from scipy.io.wavfile import read
import matplotlib.pyplot as plot
import numpy as np
from scipy.signal import butter, lfilter
from scipy.signal import find_peaks

# Def du filtre passe bande
def butter_bandpass(lowcut, highcut, fs, order=5):
    nyq = 0.5 * fs
    low = lowcut / nyq
    high = highcut / nyq
    b, a = butter(order, [low, high], btype='band')
    return b, a

# Fonction pour appliquer le passe bande
def butter_bandpass_filter(data, lowcut, highcut, fs, order=5):
    b, a = butter_bandpass(lowcut, highcut, fs, order=order)
    y = lfilter(b, a, data)
    return y

# def butter_highpass(cutoff, fs, order=5):
#     nyq = 0.5 * fs
#     normal_cutoff = cutoff / nyq
#     b, a = butter(order, normal_cutoff, btype='high', analog=False)
#     return b, a
#
# def butter_highpass_filter(data, cutoff, fs, order=5):
#     b, a = butter_highpass(cutoff, fs, order=order)
#     y = lfilter(b, a, data)
#     return y

# Lecture des enregistrements audio
sampling_rate,signal = read('C:\\Users\\terii\\Documents\\Challenge IoT\\mouche.wav')
sampling_rate,signal = read('C:\\Users\\terii\\Documents\\Challenge IoT\\abeille250_2.wav')
sampling_rate,signal = read('C:\\Users\\terii\\Documents\\Challenge IoT\\abeille250_1.wav')
sampling_rate,signal = read('C:\\Users\\terii\\Documents\\Challenge IoT\\abeille250_3.wav')

frequence_interet = 250 # Frequence propre de l'insecte que l'on veut observer
# Np = 10

signal = signal/max(abs(signal)) # normalisation du signal
FenAcq = signal.size # taille du signal echantilloné

#signal = butter_highpass_filter(signal, frequence_interet-100, sampling_rate, order=6)
#signal = butter_bandpass_filter(signal, frequence_interet-20, frequence_interet+20, sampling_rate, order=3)

signal_FFT = abs(fft.fft(signal)) # fft
signal_freq = fft.fftfreq(FenAcq,1/sampling_rate) # axe frequence

signal_FFT = signal_FFT[0:len(signal_FFT)//2] # suppression des negatifs car paire
signal_freq = signal_freq[0:len(signal_freq)//2]

#peaks, _ = find_peaks(signal_FFT, distance=550,height=0.1)

max_spectre = max(signal_FFT) # max de la fft signal origine

signal_filtre = butter_bandpass_filter(signal, frequence_interet-20, frequence_interet+20, sampling_rate, order=3) # coupe bande centré sur freq interet

signal_filtre_FFT = abs(fft.fft(signal_filtre)) # fft

signal_filtre_FFT = signal_filtre_FFT[0:len(signal_filtre_FFT)//2] # suppression des negatifs

max_spectre_filtre = max(signal_filtre_FFT) # amplitude de la freq d'interet

rapport=max_spectre_filtre/max_spectre # rapport qui caracterise la richesse frequentiel de la frequence d'interet

reponse=(rapport>0.1)

# Caracterisation si abeille ou pas
if (reponse == True):
    print("Il y a des abeilles autour de l'arbre")
else:
    print("Il n'y a pas d'abeilles autour de l'arbre")


## Graphes des fft origine et signal filtre

plot.semilogx(signal_freq,signal_FFT)
#plot.semilogx(signal_freq[peaks[0:Np]], signal_FFT[peaks[0:Np]], "x")
plot.show()

plot.semilogx(signal_freq,signal_filtre_FFT)
plot.show()