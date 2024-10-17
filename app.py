from flask import Flask, render_template, send_file

app = Flask(__name__)

# Route for the main dashboard
@app.route('/')
def index():
    return render_template('index.html')

# Route for CIA 1 (Search Algorithms)
@app.route('/cia1')
def cia1():
    return render_template('cia1.html')

# Route for CIA 2 (Alpha-Beta Pruning and Min-Max)
@app.route('/cia2')
def cia2():
    return render_template('cia2.html')

# Route to serve specific files (C files or Python scripts)
@app.route('/get_file/<filename>')
def get_file(filename):
    # Provide the correct path based on CIA 1 or CIA 2
    path = f'files/{filename}'
    return send_file(path, as_attachment=True)

if __name__ == '__main__':
    app.run(debug=True)
