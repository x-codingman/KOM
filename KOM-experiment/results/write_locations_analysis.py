import os
import json
import openpyxl
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np

def convert_to_excel(recorded_data, output_file):
    """
    Convert the recorded JSON data to an Excel file.

    Parameters:
    recorded_data (dict): The recorded data.
    output_file (str): The path to the output Excel file.
    """
    # Initialize an empty DataFrame
    df = pd.DataFrame()

    for subdir, data_list in recorded_data.items():
        for data in data_list:
            # Convert each sublist to a DataFrame and set 'subdir' as a column
            temp_df = pd.DataFrame(data)
            temp_df['subdir'] = subdir
            temp_df['type'] = subdir.split("_")[0].upper()
            # Append to the main DataFrame
            df = df.append(temp_df, ignore_index=True)

    # Reorder columns to have 'subdir' as the first column
    columns = ['subdir']+ ['type'] + [col for col in df.columns if col != 'subdir' and col != 'type']
    df = df[columns]
    # Save to Excel file
    df.to_excel(output_file, index=True)
    return df

def analyze_type_writable_locations(data):
    df_sorted = df.sort_values(by=['type', 'offset', 'value_controllable'], ascending=[True, True, False])
    df_unique = df.drop_duplicates(subset=['offset', 'type'])
    print(df_unique)
    # Count total occurrences of each type
    type_counts = df_unique['type'].value_counts()

    # Count occurrences where 'value_controllable' and 'has_constraints' are True
    controllable_counts = df_unique[df_unique['value_controllable']]['type'].value_counts()
    constraints_counts = df_unique[df_unique['has_constraints']]['type'].value_counts()

    # Merging the counts into a single DataFrame for plotting
    merged_counts = pd.DataFrame({
        'Total Count': type_counts,
        'Value Controllable Count': controllable_counts,
        'Has Constraints Count': constraints_counts
    }).fillna(0)

    # Plotting
    fig, ax = plt.subplots(figsize=(12, 8))
    merged_counts.plot(kind='bar', ax=ax)
    ax.set_title('Comparison of Type Counts')
    ax.set_xlabel('Type')
    ax.set_ylabel('Count')
    plt.savefig("writable_locations_counts.png")


def plot_offset_distribution_by_size(df):
    """
    Plot the distribution of 'offset' for each 'type', with 'size' as the x-axis.

    Parameters:
    df (DataFrame): The DataFrame containing the data.
    """
    df_unique = df.drop_duplicates(subset=['type'])
    plt.figure(figsize=(12, 8))
    sns.scatterplot(data=df_unique, x='size', y='offset', hue='type')
    plt.title('Offset Distribution by Size for Each Type')
    plt.xlabel('Size')
    plt.ylabel('Offset')
    plt.legend(title='Type')
    plt.savefig("writable_locations_scatter.png")

def type_analysis_of_writable_locations(df):
    df_sorted = df.sort_values(by=['type', 'offset', 'value_controllable'], ascending=[True, True, False])
    df = calculate_offset_summary(df)
    return df

def calculate_offset_summary(df):
    """
    Calculate a summary of offset values for each type, including minimum offset, maximum offset,
    and the minimum and maximum gaps between any two offsets (not necessarily consecutive).

    Parameters:
    df (DataFrame): The DataFrame containing the data.

    Returns:
    DataFrame: A DataFrame with the summary for each type.
    """
    summary = {}
    for t in df['type'].unique():
        type_df = df[df['type'] == t]
        type_df = type_df.drop_duplicates(subset=['offset', 'type'])
        offsets = type_df['offset'].unique()
        value_controllable = type_df['value_controllable']
        has_constraints = type_df['has_constraints']
        controllable_count=0
        no_constraints_count=0
        fully_control_count = 0
        print(value_controllable)
        for i in range(len(value_controllable)):
            if value_controllable.iloc[i] == True:
                controllable_count=controllable_count+1
            if has_constraints.iloc[i] == False:
                no_constraints_count=no_constraints_count+1
            if value_controllable.iloc[i]==True and has_constraints.iloc[i]==False:
                fully_control_count = fully_control_count +1
        offsets.sort()
        min_gap = float('inf')
        max_gap = float('-inf')
        for i in range(len(offsets) - 1):
            for j in range(i + 1, len(offsets)):
                gap = offsets[j] - offsets[i]
                min_gap = min(min_gap, gap)
                max_gap = max(max_gap, gap)
        print(t)
        summary[t] = {
            'writable_count':len(offsets),
            'controllable_count':controllable_count,
            'no_constraint':no_constraints_count,
            "fully_controllable_count":fully_control_count,
            'min_offset': min(offsets),
            'max_offset': max(offsets),
            'min_gap': min_gap,
            'max_gap': max_gap
        }
    df = pd.DataFrame.from_dict(summary, orient='index')
    print(df)
    return df.astype(int)

def plot_offset_scatter(df):
    """
    Plot a scatter plot for 'offset' values, grouped by 'type'. Each rectangle represents an offset,
    with the width of the rectangle indicating the 'width' of the offset, scaled to match the 'size'.
    Each type is represented in a different color, and offsets with 'value_controllable' True 
    are marked in a distinct color. Includes a legend to distinguish types and controllable offsets.
    Overlapping points are replaced, not overlaid.

    Parameters:
    df (DataFrame): DataFrame containing 'type', 'size', 'offset', 'width', and 'value_controllable' information.
    """
    plt.figure(figsize=(10, 6))

    # Check if 'value_controllable' column exists and convert to boolean if necessary
    if 'value_controllable' in df.columns:
        df['value_controllable'] = df['value_controllable'].astype(bool)
    else:
        # If the column doesn't exist, treat all as False
        df['value_controllable'] = False

    # Unique types and colors
    types = df['type'].unique()
    colors = plt.cm.rainbow(np.linspace(0, 1, len(types)))
    type_color_map = {t: colors[i] for i, t in enumerate(types)}

    # A distinct color for 'value_controllable' offsets (e.g., bright green)
    controllable_color = 'limegreen'

    # Standard height for the rectangles, adjusted to reduce vertical spacing
    standard_height = 0.5  # Decreased for reduced vertical spacing

    # Determine the scaling factor for the width
    max_width = df['width'].max()
    scale_factor = 10 / max_width  # Adjust the denominator as needed for desired scale

    # Plotting each offset as a rectangle
    for t in types:
        type_df = df[df['type'] == t].drop_duplicates(subset=['offset'])
        
        for _, row in type_df.iterrows():
            color = controllable_color if row['value_controllable'] else type_color_map[t]
            scaled_width = row['width'] * scale_factor
            plt.barh(y=t, width=scaled_width, left=row['offset'] * scale_factor - scaled_width/2, 
                     height=standard_height, color=color, edgecolor='black')

    # Adding custom legend
    handles = [plt.Rectangle((0,0),1,1, color=type_color_map[t]) for t in types]
    handles.append(plt.Rectangle((0,0),1,1, color=controllable_color))
    labels = list(types) + ['Value Controllable']
    plt.legend(handles, labels)

    plt.xlabel('Scaled Offset')
    plt.ylabel('Type')
    # Removed the title
    plt.savefig("offsets_distribution_for_each_type.png")



def traverse_and_record_json_data(directory):
    """
    Traverse all subdirectories in the given directory, read JSON files,
    and record data as specified.

    Parameters:
    directory (str): The root directory to start traversal.

    Returns:
    dict: A dictionary containing subdirectory names and their JSON data.
    """
    data = {}

    # Traverse the directory
    for root, dirs, files in os.walk(directory):
        for subdir in dirs:
            subdirectory_path = os.path.join(root, subdir)
            data[subdir] = []
            subdir_data=[]
            # Traverse each subdirectory for JSON files
            for file in os.listdir(subdirectory_path):
                if file.endswith('.json'):
                    json_path = os.path.join(subdirectory_path, file)
                    
                    # Read and record JSON data
                    with open(json_path, 'r') as f:
                        
                        json_data = json.load(f)
                        if json_data['name'] != "lazy_alloc1":
                            continue
                        if subdir_data == []:
                            for key, value in json_data.items():
                                if key.startswith("writable location"):
                                    flag = True
                                    if value.get("constraints")==[]:
                                        flag = False
                                    else:
                                        flag = len(value.get("constraints"))
                                    subdir_data.append({"name":json_data["name"],"size":json_data["size"],"width":int(value.get("width"))/8,"offset":int(value.get("offset_in_mo"))/2,"value_controllable":value.get("value_controllable"),"can_value_be_forged_id": value.get("can_value_be_forged_id"),"has_constraints":flag})
                        for key, value in json_data.items():
                                if key.startswith("writable location"):
                                    is_coverd = False
                                    for i in range(len(subdir_data)):
                                        if subdir_data[i]["offset"] == value.get("offset_in_mo"):
                                            is_coverd = True
                                            flag = True
                                            if value.get("constraints")==[]:
                                                flag = False
                                                if subdir_data[i]["has_constraints"] != False:
                                                    subdir_data[i]["has_constraints"] = False
                                                    #print(subdirectory_path)
                                                    print("Change has_constraints!!!")
                                            if value.get("value_controllable") == True:
                                                if subdir_data[i]["value_controllable"]==False:
                                                    subdir_data[i]["value_controllable"]=True
                                                    print("Change value controllable!!!")
                                    if is_coverd == False:
                                        flag = True
                                        print("Uncoverd location!")
                                        if value.get("constraints")==[]:
                                            flag = False
                                        else:
                                            flag = len(value.get("constraints"))
                                        subdir_data.append({"name":json_data["name"],"size":json_data["size"],"width":int(value.get("width"))/8,"offset":int(value.get("offset_in_mo"))/2,"value_controllable":value.get("value_controllable"),"can_value_be_forged_id": value.get("can_value_be_forged_id"),"has_constraints":flag})

                        # for key, value in json_data.items():
                        #     if key == "value_controllable" and value == "true"
                        #     if key.startswith("writable location"):
                        #         if value.get("constraints")==[]:
                        #             count+=1
                        
            data[subdir].append(subdir_data)

    return data

# Example usage:
directory = '/home/klee/threadx/symbolic_execution/test-info-output'
recorded_data = traverse_and_record_json_data(directory)
output_file = 'writable_location_each_syscall_analysis.xlsx'
df = convert_to_excel(recorded_data, output_file)
# plot_offset_scatter(df)
# analyze_type_writable_locations(df)
# df = type_analysis_of_writable_locations(df)

# df.to_excel('writable_location_type_analysis.xlsx', index=True)
#print(recorded_data) # This will print the recorded data according to the requirement.
