import shlex
import subprocess
import concurrent.futures
import os
import time
from multiprocessing import Pool

output_dir = "../results/output/"
test_files_dir = "../IR_files/"
test_info_dir = "../results/test-info-output/"

func_names = []

command_clean_dir = [
    "rm", 
    "-rf", 
    test_info_dir + "*"
]

# Execute the clean command
subprocess.run(" ".join(command_clean_dir), shell=True, check=True)

# Gather all function names
for dirpath, dirnames, filenames in os.walk(test_files_dir):
    for file in filenames:
        if ".linked.bc" in file: 
            new_name = file.replace(".linked.bc", "")
            func_names.append(new_name)


def run_command(func_name):
    """
    Execute a single command for a given function.
    """
    # Clean previous output
    command_clean_dir = [
        "rm", 
        "-rf", 
        output_dir + shlex.quote(func_name)
    ]
    subprocess.run(command_clean_dir, check=True)

    temp_output_path = output_dir + shlex.quote(func_name) + "_temp_output.txt"
    os.makedirs(output_dir, exist_ok=True)

    with open(temp_output_path, "w") as temp_file:
        # Prepare the command to run KLEE
        command = [
             "../../build/bin/klee",
            "--search=dfs", 
            "-debug-print-instructions=all:stderr",
            "--test-info-output-dir=" + test_info_dir + shlex.quote(func_name),
            "--output-dir=" + output_dir + shlex.quote(func_name),
            "--test-target-name=" + shlex.quote(func_name),
            test_files_dir + shlex.quote(func_name) + ".linked.bc"
        ]
        subprocess.run(command, stdout=temp_file, stderr=temp_file)

    output_path = output_dir + shlex.quote(func_name) + "_output.txt"
    with open(output_path, "w") as output_file:
        # Run the tail command and redirect the output to your target file
        subprocess.run(["tail", "-n", "40", temp_output_path], stdout=output_file)


def show_progress(futures, total_tasks, start_time):
    """
    Track progress and display remaining tasks along with elapsed time.
    This will dynamically update the output on the same line.
    """
    completed_tasks = 0
    while completed_tasks < total_tasks:
        time.sleep(1)  # Pause for a second before checking progress
        completed_tasks = sum(future.done() for future in futures)  # Check how many tasks are done
        remaining_tasks = total_tasks - completed_tasks
        elapsed_time = time.time() - start_time
        elapsed_time_str = format_time(elapsed_time)
        
        # Use '\r' to overwrite the line in the console
        print(f"\rProgress: {completed_tasks}/{total_tasks} tasks completed. "
              f"{remaining_tasks} tasks remaining. Time elapsed: {elapsed_time_str}", end="")


def format_time(seconds):
    """
    Format time in seconds to a readable format (HH:MM:SS).
    """
    hours = int(seconds // 3600)
    minutes = int((seconds % 3600) // 60)
    seconds = int(seconds % 60)
    return f"{hours:02}:{minutes:02}:{seconds:02}"


# Main execution
if __name__ == "__main__":
    start_time = time.time()  # Record the start time

    with concurrent.futures.ProcessPoolExecutor(max_workers=4) as executor:
        futures = [executor.submit(run_command, func_name) for func_name in func_names]
        show_progress(futures, len(func_names), start_time)