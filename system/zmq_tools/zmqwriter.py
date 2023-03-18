import sys, os
import time
import zmq
import optparse

from zmq_tools import *
from google.protobuf import json_format

if __name__ == '__main__':

    parser = optparse.OptionParser(description='Send IPC ZMQ messages')

    parser.add_option('-f', '--file', action='store', help='JSON formated file', default='')
    parser.add_option('-t', '--time', action='store', help='Time in milliseconds for periodic sending', default='0')

    options, args = parser.parse_args()

    if options.file == '':
        print('ERROR: You should give a file as a argument')
        parser.print_help()
        sys.exit(-1)

    if not os.path.isfile(options.file):
        print('File {} does not exist'.format(options.file))
        sys.exit(-1)

    json = ''
    with open(options.file, 'r') as f:
        json = f.read()

    msgName = os.path.basename(options.file).split('.json')[0]
    msg = getMessageByName(msgName)
    json_format.Parse(json, msg)

    context = zmq.Context()
    pub = context.socket(zmq.PUB)
    pub.bind('ipc://{}/{}'.format(SOCKET_DIR,msgName))

    time.sleep(0.2)
    pub.send(msg.SerializeToString())

    t = float(options.time)/1000.0
    while(t != 0):
        time.sleep(t)
        pub.send(msg.SerializeToString())
