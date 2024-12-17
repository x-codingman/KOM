import pandas as pd

# Define a function to strip whitespace from all DataFrame elements
def strip_whitespace(dataframe):
    return dataframe.applymap(lambda x: x.strip() if isinstance(x, str) else x)

# Load an Excel file into a pandas DataFrame
excel_file = '/home/klee/klee_test/inter-analysis-result/output.xlsx'  # Replace with your Excel file path
df = pd.read_excel(excel_file,engine='openpyxl')

# Strip whitespace from the DataFrame
df = strip_whitespace(df)

# Use the longtable LaTeX package to enable multi-page tables
latex_longtable = df.to_latex(index=False, longtable=True, escape=False)

# Save the LaTeX table to a .tex file with UTF-8 encoding
with open('output_longtable.tex', 'w', encoding='utf-8') as f:
    # Write the LaTeX document header with the necessary packages
    f.write('\\documentclass{article}\n')
    f.write('\\usepackage[utf8]{inputenc}\n')
    f.write('\\usepackage{longtable}\n')
    f.write('\\usepackage{booktabs}\n')
    f.write('\\begin{document}\n')
    f.write(latex_longtable)
    f.write('\\end{document}\n')
