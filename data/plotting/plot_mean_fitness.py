import pandas as pd
import matplotlib.pyplot as plt

# load data and process
csv_file_path = '../mean_fitness.csv'
data = pd.read_csv(csv_file_path, header=None)
data = data.iloc[1:]

print(data)

# settings
plt.style.use('ggplot')
plt.figure(figsize=(10, 10))
plt.rcParams['savefig.dpi'] = 300

# plot data
plt.plot(data.iloc[:])

# setting labels
plt.xlabel('Transmission cycles', fontsize=12)
plt.ylabel('Mean fitness (unitless)', fontsize=12)
plt.title('Mean fitness of infected hosts across generations', fontsize=12)

# grid
plt.grid(True)

plt.show()
