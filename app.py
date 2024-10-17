from flask import Flask, render_template, request
import subprocess
import os

app = Flask(__name__)

# Root directory for files
ROOT_DIR = os.path.dirname(os.path.abspath(__file__))

# Home Page - CIA Options
@app.route('/')
def index():
    return render_template('index.html')

# CIA 1 - Search Algorithms (C programs)
@app.route('/cia1', methods=['GET', 'POST'])
def cia1():
    if request.method == 'POST':
        algo = request.form['algorithm']
        user_input = request.form['user_input']
        output = run_c_algorithm(algo, user_input)
        return render_template('cia1.html', output=output)
    return render_template('cia1.html')

# CIA 2 - Alpha-Beta Pruning & Min-Max (Python programs)
@app.route('/cia2', methods=['GET', 'POST'])
def cia2():
    if request.method == 'POST':
        algo = request.form['algorithm']
        user_input = request.form['user_input']
        output = run_python_algorithm(algo, user_input)
        return render_template('cia2.html', output=output)
    return render_template('cia2.html')

# Helper function to run C algorithms
def run_c_algorithm(algo, user_input):
    try:
        # Define the path to the C file
        file_path = os.path.join(ROOT_DIR, 'files', algo)
        
        # Compile the C program
        compile_cmd = f"gcc {file_path} -o {file_path}.out"
        subprocess.run(compile_cmd, shell=True, check=True)

        # Execute the compiled binary with user input
        result = subprocess.run([f"{file_path}.out"], input=user_input, text=True, capture_output=True, check=True)
        return result.stdout
    except subprocess.CalledProcessError as e:
        return f"Error: {e}"

# Helper function to run Python algorithms
def run_python_algorithm(algo, user_input):
    try:
        # Define the path to the Python file
        file_path = os.path.join(ROOT_DIR, 'files', algo)
        
        # Run the Python script with user input
        result = subprocess.run(['python3', file_path], input=user_input, text=True, capture_output=True, check=True)
        return result.stdout
    except subprocess.CalledProcessError as e:
        return f"Error: {e}"

if __name__ == '__main__':
    app.run(debug=True)
