import os
import pandas as pd



def time_tranform(time_str):

    # Split the time string into its components
    hours, minutes, seconds = [int(i) for i in time_str.split(":")]

    # Calculate total seconds
    total_seconds = hours * 3600 + minutes * 60 + seconds
    return total_seconds

def extract_info(directory):

    df = pd.DataFrame(columns=['System Call', 'Elapsed', 'Explored Paths', 'Avg. Constructs Per Query', 
                               'Total Queries', 'Valid Queries', 'Invalid Queries', 'Query Cex',
                               'Total Instructions', 'Completed Paths', 'Partially Completed Paths', 
                               'Generated Tests'])


    for folder in os.listdir(directory):
        folder_path = os.path.join(directory, folder)
        if os.path.isdir(folder_path):
            info_file = os.path.join(folder_path, "info")
            
            if os.path.isfile(info_file):
                with open(info_file, 'r') as file:
                    content = file.read()

                    # Extract information
                    try:
                        elapsed = content.split('Elapsed: ')[1].split('\n')[0]
                        explored_paths = content.split('explored paths = ')[1].split('\n')[0]
                        avg_constructs = content.split('avg. constructs per query = ')[1].split('\n')[0]
                        total_queries = content.split('total queries = ')[1].split('\n')[0]
                        valid_queries = content.split('valid queries = ')[1].split('\n')[0]
                        invalid_queries = content.split('invalid queries = ')[1].split('\n')[0]
                        query_cex = content.split('query cex = ')[1].split('\n')[0]
                        total_instructions = content.split('total instructions = ')[1].split('\n')[0]
                        completed_paths = content.split('completed paths = ')[1].split('\n')[0]
                        partially_completed_paths = content.split('partially completed paths = ')[1].split('\n')[0]
                        generated_tests = content.split('generated tests = ')[1].split('\n')[0]

                        df = df.append({'System Call': folder, 'Elapsed': time_tranform(elapsed), 'Explored Paths': explored_paths, 
                                        'Avg. Constructs Per Query': avg_constructs, 'Total Queries': total_queries, 
                                        'Valid Queries': valid_queries, 'Invalid Queries': invalid_queries, 
                                        'Query Cex': query_cex, 'Total Instructions': total_instructions, 
                                        'Completed Paths': completed_paths, 'Partially Completed Paths': partially_completed_paths, 
                                        'Generated Tests': generated_tests}, ignore_index=True)
                    except IndexError:
                        df = df.append({'System Call': folder, 'Elapsed': 'NA', 'Explored Paths': 'NA', 
                                        'Avg. Constructs Per Query': 'NA', 'Total Queries': 'NA', 
                                        'Valid Queries': 'NA', 'Invalid Queries': 'NA', 
                                        'Query Cex': 'NA', 'Total Instructions': 'NA', 
                                        'Completed Paths': 'NA', 'Partially Completed Paths': 'NA', 
                                        'Generated Tests': 'NA'}, ignore_index=True)

    return df


directory_path = '/home/klee/klee_src/KOM-experiment/results/output'
dataframe = extract_info(directory_path)

dataframe.to_excel('/home/klee/klee_src/KOM-experiment/results/symbolic-execution-run-time-evaluation.xlsx', index=False)
print("The runtime result is saved in symbolic-execution-run-time-evaluation.xlsx")
