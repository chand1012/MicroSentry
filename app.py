from flask import Flask, render_template, request
import serial, sys

app = Flask(__name__)
baud = 115200
lastcommand = ''
arduino = None

arduino = serial.Serial('/dev/ttyACM0', baud)
#arduino = serial.Serial('COM3', baud)
@app.route("/")
def index():
    return render_template("index.html")

@app.route("/postrequest", methods = ['POST'])
def worker():
    global lastcommand
    data = request.form['byte']
    if data!=lastcommand:
        arduino.write(bytes(data, 'utf-8'))
        lastcommand = data
    return data

if __name__=="__main__":
    app.run('0.0.0.0', "1166", debug=True)