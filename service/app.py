#!/usr/bin/env python

import os
from flask import Flask, render_template
from flask_socketio import SocketIO, emit

app = Flask(__name__)
app.config['SECRET_KEY'] = 'abracadabra'
socketio = SocketIO(app)

@app.route("/")
def index():
    return render_template('index.html')

@socketio.on('event', namespace='/raf')
def raf_message(message):
    emit('message', {'data': message})

@socketio.on('broadcast_event', namespace='/raf')
def raf_message(message):
    emit('message', {'data': message}, broadcast=True)

@socketio.on('connect', namespace='/raf')
def raf_connect():
    emit('message', {'data': 'Connected'})

@socketio.on('disconnect', namespace='/raf')
def raf_disconnect():
    print('Client disconnected')

if __name__ == "__main__":
    port = int(os.environ['PORT'])
    socketio.run(app, "0.0.0.0", port)
