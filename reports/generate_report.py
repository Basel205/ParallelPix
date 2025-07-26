# from jinja2 import Template
# import pandas as pd
# import os

# def generate_report():
#     # Load benchmark data
#     df = pd.read_csv('../benchmarking/performance_logs/results.csv')
#     avg_speedup = df.groupby('Filter')['SerialTime'].mean() / df.groupby('Filter')['ParallelTime'].mean()

#     # Create report directory if it doesn't exist
#     report_dir = '../reports/generated'
#     os.makedirs(report_dir, exist_ok=True)

#     # Generate Markdown report
#     template = """
#     # Image Processing Performance Report

#     ## System Specifications
#     - **CPU**: AMD Ryzen 9
#     - **Cores**: 8
#     - **Memory**: 16 GB

#     ## Performance Summary
#     | Filter       | Avg Speedup |
#     |--------------|-------------|
#     {% for filter, speedup in speedups.items() %}
#     | {{ filter }} | {{ "%.2f"|format(speedup) }}x |
#     {% endfor %}

#     ## Observations
#     - Parallel processing significantly improves performance for larger image sizes.
#     - Filters like "blur" and "anime" benefit most from parallelization.

#     ## Graphs
#     ![Execution Time Comparison](../benchmarking/graphs/time_comparison.png)
#     ![Parallel Speedup Ratio](../benchmarking/graphs/speedup_ratio.png)
#     """

#     template = Template(template)
#     markdown_report = template.render(speedups=avg_speedup.to_dict())

#     # Save Markdown report
#     with open(f'{report_dir}/final_report.md', 'w') as f:
#         f.write(markdown_report)

# if __name__ == "__main__":
#     generate_report()


from jinja2 import Template
import pandas as pd
import subprocess
import os

def get_system_info():
    return {
        "cpu": subprocess.getoutput("wmic cpu get name").split("\n")[2].strip(),
        "cores": subprocess.getoutput("wmic cpu get NumberOfCores").split()[-1],
        "memory": subprocess.getoutput("wmic memorychip get capacity").split()[-1]
    }

def generate_report():
    df = pd.read_csv('../benchmarking/performance_logs/results.csv')
    avg_speedup = df.groupby('Filter')['SerialTime'].mean() / df.groupby('Filter')['ParallelTime'].mean()
    
    template = Template("""
    # Image Processing Performance Report
    
    ## System Specifications
    - CPU: {{ cpu_info.cpu }}
    - Cores: {{ cpu_info.cores }}
    - Memory: {{ cpu_info.memory }} GB
    
    ## Performance Summary
    {% for filter, speedup in speedups.items() %}
    - {{ filter }}: {{ "%.2f"|format(speedup) }}x speedup
    {% endfor %}
    
    ## CPU Utilization
    Average CPU usage during parallel processing: {{ df['AvgCPUUsage'].mean()|round(1) }}%
    """)
    
    report = template.render(
        cpu_info=get_system_info(),
        speedups=avg_speedup.to_dict(),
        df=df
    )
    
    with open('../reports/generated/final_report.md', 'w') as f:
        f.write(report)

if __name__ == "__main__":
    generate_report()
