import os
import re
directory = "/home/klee/threadx/symbolic_execution/test-info-output"

def file_content(file_path):
    with open(file_path, 'rb') as file:
        return file.read()

def list_json_files(directory):
    json_files = []

    for root, dirs, files in os.walk(directory):
        json_files_by_size = {}

        for file in files:
            if file.endswith(".json"):
                json_filepath = os.path.join(root, file)
                json_files.append(json_filepath)
                json_file_size = os.path.getsize(json_filepath)
                json_files_by_size.setdefault(json_file_size, []).append(json_filepath)
        
        # filter duplicate files
        for size, files in json_files_by_size.items():
            if len(files) > 1:
                checked = set()
                for i in range(len(files)):
                    if files[i] not in checked:
                        for j in range(i+1, len(files)):
                            if file_content(files[i]) == file_content(files[j]):
                                json_files.remove(files[j])
                                checked.add(files[j])

    return json_files

# e.g., description_block_allocate_7_lazy_alloc1
def extract_api_info(file_path):
    pattern = r"/description_(.+?)_(\d+)_(\w+)\.json$"
    match = re.search(pattern, file_path)
    if match:
        return match.group(1), match.group(3)
    else:
        return None, None

def main():
    
    json_files = list_json_files(directory)

    with open("jsonFilesPathNew.txt", "w") as f:
        for file_path in json_files:
            api_name, mo_name = extract_api_info(file_path)
            if mo_name == "lazy_alloc1":
                f.write(file_path + '\n')
                f.write(api_name + '\n')
                f.write(mo_name + '\n')

    print(f"All .json files have been recorded to jsonFilesPath.txt.")

if __name__ == "__main__":
    main()
