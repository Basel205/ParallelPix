import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os

def generate_graphs():
    try:
        # Load data
        df = pd.read_csv('../benchmarking/performance_logs/results.csv')
        
        # Create graphs directory
        graph_dir = '../benchmarking/graphs'
        os.makedirs(graph_dir, exist_ok=True)
        
        # Speedup Comparison
        plt.figure(figsize=(12, 8))
        sns.barplot(x='Filter', y='SerialTime', data=df, color='red', label='Serial')
        sns.barplot(x='Filter', y='ParallelTime', data=df, color='blue', label='Parallel')
        plt.title('Execution Time Comparison (Serial vs Parallel)')
        plt.ylabel('Time (seconds)')
        plt.legend()
        plt.savefig(f'{graph_dir}/time_comparison.png')
        plt.close()

        # Speedup Ratio
        df['Speedup'] = df['SerialTime'] / df['ParallelTime']
        plt.figure(figsize=(12, 8))
        sns.barplot(x='Filter', y='Speedup', data=df)
        plt.title('Parallel Speedup Ratio')
        plt.ylabel('Speedup (Serial Time / Parallel Time)')
        plt.savefig(f'{graph_dir}/speedup_ratio.png')
        plt.close()

        print("Graphs generated successfully!")
        
    except Exception as e:
        print(f"Error generating graphs: {str(e)}")

if __name__ == "__main__":
    generate_graphs()
