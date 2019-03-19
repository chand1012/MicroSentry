import sys

import serial
from flask import Flask, Response, render_template, request

from camera_pi import Camera

app = Flask(__name__)
baud = 115200
arduino = serial.Serial('/dev/ttyACM0', baud)

def gen(camera):
    while True:
        frame = camera.get_frame()
        yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')
@app.route("/")
def index():
    return render_template("index.html")

@app.route("/postrequest", methods = ['POST'])
def worker():
    data = request.form['byte']
    arduino.write(bytes(data, 'utf-8'))
    return data

@app.route('/video_feed')
def video_feed():
    return Response(gen(Camera()),
                    mimetype='multipart/x-mixed-replace; boundary=frame')

if __name__=="__main__":
    app.run('0.0.0.0', "1166", debug=True, threaded=True)
