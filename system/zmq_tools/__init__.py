from protos.ProtobufFiles.python import *

from google.protobuf import descriptor_pool
from google.protobuf import message_factory


SOCKET_DIR = '/tmp'


POOL = descriptor_pool.DescriptorPool()

for imp_proto in SERIALS:
	POOL.AddSerializedFile(imp_proto.DESCRIPTOR.serialized_pb)

def getMessageByName(name):
    desc = POOL.FindMessageTypeByName(name)
    msg = message_factory.MessageFactory().GetPrototype(desc)()
    return msg
