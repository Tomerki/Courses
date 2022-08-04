import socket
import sys

# creates a socket
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

#checking that the port address legal.
PORT_ADDRESS = sys.argv[1]
if PORT_ADDRESS.isdigit() is not True :
    sys.exit('Port Address illegal')
PORT_ADDRESS = int(sys.argv[1])
if 65535 - PORT_ADDRESS < 0:
    sys.exit('Port Address illegal')

# bind the server to listen the given port
s.bind(('', PORT_ADDRESS))
# dictionary for saving the massage from the client
dic = {}
# variable that saves the last massage that printed
last_print = 0
"""
the server wait until he gets a massage
"""
while True:
    # the information from the sender - tha data and his address
    data, addr = s.recvfrom(1024)
    # the first chars are the number of the package
    num = int(data[0:10])
    # the rest data from index ten is the data from the sender
    inner_data = data[10:100]
    # insert the massage to the dictionary only if it is a message
    if num not in dic.keys():
        dic[num] = inner_data
        # if the new massage is in the correct order (the one after the last print) - we will print it
        if last_print + 1 == num:
            print(inner_data.decode(), flush=True, end="")
            # update the last print to be the new massage
            last_print = num
            # checking if there are some massage that was arrived to the server (so we insert them to the dictionary)
            # but because they comer before the next massage - we dont printed them and we prints them now in the
            # correct order
            for i in sorted(dic.keys()):
                if i == last_print + 1:
                    print(dic.get(i).decode(), flush=True, end="")
                    # update the last print to be the new massage
                    last_print = i
    # the server confirms he get the massage
    s.sendto(inner_data, addr)