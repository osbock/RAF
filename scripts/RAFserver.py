# Example of using the MQTT client class to subscribe to a feed and print out
# any changes made to the feed.  Edit the variables below to configure the key,
# username, and feed to subscribe to for changes.

# Import standard python modules.
import sys, os, serial

# Import Adafruit IO MQTT client.
from Adafruit_IO import MQTTClient


# Set to your Adafruit IO key & username below.
ADAFRUIT_IO_KEY = os.getenv('IO_KEY','nokey')
ADAFRUIT_IO_USERNAME = os.getenv('IO_USERNAME','nouser')

if (ADAFRUIT_IO_KEY == 'nokey' or ADAFRUIT_IO_USERNAME == 'nouser'):
    print('no user or key environment variable')
    sys.exit()
    
FIREFEED_ID = 'Fire'
AZIMUTHFEED_ID = 'Azimuth'
ELEVFEED_ID = 'Elevation'

ser = serial.Serial('/dev/cu.usbmodem1411',115200)

# Define callback functions which will be called when certain events happen.
def connected(client):
    # Connected function will be called when the client is connected to Adafruit IO.
    # This is a good place to subscribe to feed changes.  The client parameter
    # passed to this function is the Adafruit IO MQTT client so you can make
    # calls against it easily.
    print 'Connected to Adafruit IO!  Listening for {0} changes...'.format(FIREFEED_ID)
    # Subscribe to changes on a feed named DemoFeed.
    client.subscribe(FIREFEED_ID)
    client.subscribe(AZIMUTHFEED_ID)
    client.subscribe(ELEVFEED_ID)

def disconnected(client):
    # Disconnected function will be called when the client disconnects.
    print 'Disconnected from Adafruit IO!'
    client.connect()

def message(client, feed_id, payload):
    # Message function will be called when a subscribed feed has a new value.
    # The feed_id parameter identifies the feed, and the payload parameter has
    # the new value.
    print 'Feed {0} received new value: {1}'.format(feed_id, payload)
    if feed_id == FIREFEED_ID:
        if int(payload) == 1:
            print "Fire"
            ser.write(b'F')
    if feed_id == AZIMUTHFEED_ID:
        degrees = int(payload)
        print ("Setting azimuth %d" % degrees)
        command = ('A %d' % degrees)
        print command
        ser.write(command)
    if feed_id == ELEVFEED_ID:
        degrees = int(payload)
        print ("Setting elevationh %d" % degrees)
        command = ('E %d' % degrees)
        print command
        ser.write(command)
# Create an MQTT client instance.
client = MQTTClient(ADAFRUIT_IO_USERNAME, ADAFRUIT_IO_KEY)

# Setup the callback functions defined above.
client.on_connect    = connected
client.on_disconnect = disconnected
client.on_message    = message

# Connect to the Adafruit IO server.
print "try to connect"
client.connect()

# Start a message loop that blocks forever waiting for MQTT messages to be
# received.  Note there are other options for running the event loop like doing
# so in a background thread--see the mqtt_client.py example to learn more.
client.loop_blocking()
