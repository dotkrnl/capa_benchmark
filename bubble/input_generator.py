import scipy.stats as ss
import numpy as np
import matplotlib.pyplot as plt

mu, sigma = 128, 20 # mean and standard deviation
s = np.random.chisquare(200, 8000)
count, bins, ignored = plt.hist(s, 30, normed=True)
plt.plot(bins, 1/(sigma * np.sqrt(2 * np.pi)) *
                np.exp( - (bins - mu)**2 / (2 * sigma**2) ),
          linewidth=2, color='r')
plt.show()
np.savetxt("/Users/Aish/Documents/capa_benchmark/bubble/input/input_chi_200.txt",s.astype(int),delimiter=",", fmt='%d')