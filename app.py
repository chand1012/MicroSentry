from flask import Flask, render_template, request
import serial, sys

app = Flask(__name__)


arduino = None

if sys.platform=="win32":
    arduino = serial.Serial('COM4', 9600)
else:
    arduino = serial.Serial('/dev/ttyACM0', 9600)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/postrequest", methods = ['POST'])
def worker():
    data = request.form['byte']
    arduino.write(data)
    return data

if __name__=="__main__":
    app.run('0.0.0.0', "1166", debug=True)