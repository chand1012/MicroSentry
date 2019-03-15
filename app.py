from flask import Flask, render_template, request
import serial, sys

app = Flask(__name__)

lastcommand = None
arduino = None

if sys.platform=="win32":
    arduino = serial.Serial("COM3", 9600)
else:
    arduino = serial.Serial('/dev/ttyACM0', 9600)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/postrequest", methods = ['POST'])
def worker():
    data = request.form['byte']
    if data!=lastcommand:
        arduino.write(bytes(data, 'utf-8'))
        lastcommand = data
    return data

if __name__=="__main__":
    app.run('0.0.0.0', "1166", debug=True)