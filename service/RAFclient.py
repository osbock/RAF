#!/usr/bin/env python
import logging
import threading
import sys, os, serial, json
from socketIO_client import SocketIO, BaseNamespace, LoggingNamespace

# logging.getLogger("socketIO-client").setLevel(logging.DEBUG)
# logging.basicConfig()
    
FIREFEED_ID = "fire"
AZIMUTHFEED_ID = "azimuth"
ELEVFEED_ID = "elevation"

ser = serial.Serial("/dev/cu.usbmodem1421", 115200)

def worker():
    """work in progress"""
    for line in ser.readline():
        print line
    print "done"

class RAFNamespace(BaseNamespace):
    def on_connect(self):
        print("[Connected]")

    def on_message(self, *args):
        message = args[0]
        if isinstance(message, dict):
            data = message["data"]
            if "command" in data:
                command = data["command"]
                if "value" in data:
                    value = int(data["value"])
                    self.execute(command, value)
                else:
                    self.execute(command)

    def execute(self, command, value = 0):
        if command == FIREFEED_ID:
            print "Fire"
            ser.write(b"F")
        elif command == AZIMUTHFEED_ID:
            print ("Setting azimuth %d" % value)
            ser.write("E %d" % value)
        elif command == ELEVFEED_ID:
            print ("Setting elevation %d" % value)
            ser.write("A %d" % value)

    def on_reconnect(self):
        print("[Reconnected]")

    def on_disconnect(self):
        print("[Disconnected]")

if __name__ == "__main__":
    print "Connecting..."
    # host="http://localhost:5000"
    host="https://raf-public.herokuapp.com"
    socketIO = SocketIO(host)
    raf_namespace = socketIO.define(RAFNamespace, "/raf")
    t = threading.Thread(target=worker)
    t.start()
    socketIO.wait()

