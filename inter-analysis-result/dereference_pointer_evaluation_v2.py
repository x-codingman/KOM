import os
import json
import pandas as pd

def collect_json_data(root_folder):
    data = []

    for subdir, dirs, files in os.walk(root_folder):
        subfolder_name = os.path.basename(subdir)
        for file in files:
            if file.endswith(".json"):
                file_path = os.path.join(subdir, file)
                with open(file_path, 'r') as f:
                    json_data = json.load(f)
                    if json_data['name'] != "lazy_alloc1":
                        continue
                    
                    for key, value in json_data.items():
                        if key.startswith("dereference location"):
                            can_value_be_forged_id = value.get("can_value_be_forged_id")
                            if can_value_be_forged_id == True:
                        # Add subfolder name as an index
                                if value.get("constraints")==[]:
                                        num = 0
                                else:
                                        num = len(value.get("constraints"))
                                value["constraints"] = num
                                value["system call name"] = subfolder_name
                                data.append(value)
    
    return data

def json_to_dataframe(json_data):
    # Normalize JSON data to flatten nested structures
    df = pd.json_normalize(json_data)
    return df

def save_to_excel(df, output_file):
    df.to_excel(output_file, index=False)

def main(input_folder, output_file):
    json_data = collect_json_data(input_folder)
    df = json_to_dataframe(json_data)
    save_to_excel(df, output_file)
    print(f"Data has been successfully saved to {output_file}")

if __name__ == "__main__":
    input_folder = '/home/klee/threadx/symbolic_execution/output'  # Replace with your input folder path
    output_file = 'tables-v3/dereference_pointer_evaluation_v2.xlsx'  # Replace with your desired output file name
    main(input_folder, output_file)
