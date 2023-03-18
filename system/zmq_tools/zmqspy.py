import sys, os, stat
import threading
import zmq

from zmq_tools import *
from google.protobuf import json_format

def getSocketList(dirname):
    socketList = list()
    for name in os.listdir(dirname):
        if(len(sys.argv)>1 and (not name in sys.argv)):
            continue
        path = os.path.join(dirname, name)
        mode = os.stat(path).st_mode
        if stat.S_ISSOCK(mode):
            try:
                msg = getMessageByName(name)
                socketList.append(name)
            except:
                print("Not Listening to: ", name)
                pass
    return socketList

def recvThread(name, subscriber):
    msg = getMessageByName(name)
    print("Listening to: ", name)
    while(True):
        msg.ParseFromString(subscriber.recv())
        string = json_format.MessageToJson(msg).replace('\n', '').replace(' ', '')
        print("MESSAGE: {} - {}".format(msg.DESCRIPTOR.full_name, string))

if __name__ == '__main__':

    context = zmq.Context()

    threads = list()
    subscribers = list()
    sockets = getSocketList(SOCKET_DIR)
    
    for socket in sockets:
        sub = context.socket(zmq.SUB)
        sub.connect('ipc://{}/{}'.format(SOCKET_DIR,socket))
        sub.setsockopt(zmq.SUBSCRIBE, b"")

        thread = threading.Thread(target=recvThread, args=(socket, sub))
        thread.start()

        subscribers.append(sub)
        threads.append(thread)

    for thread in threads:
        thread.join()
