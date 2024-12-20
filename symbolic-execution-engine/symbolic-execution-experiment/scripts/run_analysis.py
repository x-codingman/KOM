import subprocess
import os

# List of Python scripts to execute sequentially with custom messages
scripts = [
    {"script": "run-time-evaluation.py", "message": "Evaluating the symbolic execution runtime"},
    {"script": "modifiable_fields_analysis.py", "message": "Analayzing the modifiable fields of the system calls"},
]

def install_requirements():
    """Install the necessary Python packages"""
    required_packages = [
        "openpyxl",      
        "pandas"     
    ]
    
    # Loop through the list of packages and install each one
    for package in required_packages:
        print(f"Installing {package}...")
        try:
            # Use subprocess to run pip3 install command
            subprocess.run(["pip3", "install", package], check=True)
            print(f"{package} installed successfully.")
        except subprocess.CalledProcessError as e:
            print(f"Error installing {package}: {e}")

def run_script(script, message):
    """Run a single Python script and display the custom message"""
    print(f"###: {message}")  # Display custom message for the script
    try:
        # Use subprocess.run to execute the Python script
        result = subprocess.run(["python3", script], check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        print(f"Script {script} executed successfully.")
    except subprocess.CalledProcessError as e:
        print(f"Error executing {script}: {e}")
        print("stderr:", e.stderr.decode())

def run_all_scripts(scripts):
    """Execute all scripts sequentially"""
    for script_info in scripts:
        run_script(script_info["script"], script_info["message"])

if __name__ == "__main__":
    # Install necessary packages before running the scripts
    #install_requirements()
    
    # Run all the scripts in the list
    run_all_scripts(scripts)