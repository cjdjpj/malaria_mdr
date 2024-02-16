import pandas as pd
import matplotlib.pyplot as plt
import csv

# Load the CSV file
csv_file_path = '../data/g_freqs.csv'
data = pd.read_csv(csv_file_path)

# Resetting the index so that we have a column representing the generation number
data = data.reset_index()
data.rename(columns={'index': 'Generation'}, inplace=True)

# Increase the figure size for better readability
plt.figure(figsize=(20, 10))

# Plot each column (pathogen) as a separate line, with transparency and proper labeling
surviving_clones = []
for i, column in enumerate(data.columns[1:], start=1):  # Skipping the 'Generation' column, start numbering from 1
    line = plt.plot(data['Generation'], data[column], alpha=0.6, label=f'Clone_{i}')[0]  # Set label for the clones
    if any(data[column].iloc[-1:] > 0.02):
        surviving_clones.append(i)  # Add clone number to the list for surviving clones

# Add labels and title
plt.xlabel('Generation')
plt.ylabel('Global Frequency')
plt.title('Global Frequency of Malaria Clones Over Generations')

# Add the surviving clones to the legend with correct colors and numbers
plt.legend(title='Surviving Clones', loc='upper right', bbox_to_anchor=(1.12, 1.02),
           handles=[line for line in plt.gca().get_lines() if int(line.get_label().split('_')[1]) in surviving_clones])

# Add grid for better readability
plt.grid(True)

# Show the plot
plt.show()
