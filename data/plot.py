import pandas as pd
import matplotlib.pyplot as plt

# Load the CSV file
csv_file_path = '/Users/cjdjpj/Documents/programming/Projects/malaria_proj/data/g_freqs.csv'
data = pd.read_csv(csv_file_path)

# Resetting the index so that we have a column representing the generation number
data = data.reset_index()
data.rename(columns={'index': 'Generation'}, inplace=True)

# Increase the figure size for better readability
plt.figure(figsize=(20, 10))

# Plot each column (pathogen) as a separate line, with transparency and proper labeling
for i, column in enumerate(data.columns[1:], start=1):  # Skipping the 'Generation' column, start numbering from 1
    plt.plot(data['Generation'], data[column], label=f'Series {i}', alpha=0.6)  # Slight transparency, label with series number

# Add labels and title
plt.xlabel('Generation')
plt.ylabel('Global Frequency')
plt.title('Global Frequency of Malaria Clones Over Generations')

# Adjust legend position and size
plt.legend(loc='upper right', bbox_to_anchor=(1.15, 1.02), fontsize='small', ncol=2)

# Add grid for better readability
plt.grid(True)

# Show the plot
plt.show()
