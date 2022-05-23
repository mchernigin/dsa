import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns


orig_data = pd.read_csv('results.csv')
data = orig_data.drop(columns=orig_data.columns[0])

quick_sort = data.iloc[0]
merge_sort = data.iloc[2]
heap_sort = data.iloc[1]

quick_sort.plot()
heap_sort.plot()
merge_sort.plot()

ax = sns.lineplot()
ax.set_xlabel('Number of elements', fontsize=14)
ax.set_ylabel('Time', fontsize=14)

plt.legend(labels=["Quick Sort", "Merge Sort", "Heap Sort"])

plt.savefig('graph.png', dpi=600)

plt.clf()

fig, ax = plt.subplots()

# hide axes
fig.patch.set_visible(False)
ax.axis('off')
ax.axis('tight')

ax.table(cellText=orig_data.values, colLabels=orig_data.columns, loc='center')

fig.tight_layout()

plt.savefig('table.png', dpi=600)
