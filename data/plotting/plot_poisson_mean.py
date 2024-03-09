import pandas as pd
import matplotlib.pyplot as plt

csv_file_path = '../poisson_mean.csv'
data = pd.read_csv(csv_file_path, header=None)

plt.plot(data, label='Poisson mean')

print(data)

plt.xlabel('Generation')
plt.ylabel('Poisson mean')
plt.title('Poisson mean (moi) over generations')
plt.grid(True)

plt.show()
