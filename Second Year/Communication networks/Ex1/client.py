import socket
import sys

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.settimeout(11)

PORT_NUMBER = sys.argv[1]
IP_ADDRESS = sys.argv[2]
FILE_TO_READ = sys.argv[3]


def check_arguments(ip, port):
    ls = ip.split(".")
    if len(ls) != 4:
        return False
    for num in ls:
        if num.isdigit() is False:
            return False
    if port.isdigit() is not True:
        return False
    b = 65535 - int(port)
    if b < 0:
        return False
    return True

"""
Input:
    the main function receive IP address, port address and a file.
Output:
    doesnt return a value.
Function Operation:
    the function reading the file that we get as an argument and sending the file data
    in a 100 bytes packages maximum.
    the function send the packages to the IP and Port address that we got as an arguments.
    we using a while loop that every iteration send one package, after sending we wait to receive
    an answer from the server, if we dont get this answer so we sending the package again
    after 11 seconds.
    but if we did receive the an answer from the server we just keep sending packages 
    until we send all the file.
    we are also using a flag - sending in the 10 first bytes the package number,
    and then the server know the right order of the packages.
"""

if check_arguments(IP_ADDRESS, PORT_NUMBER) == False:
    # exit the program if at least one of the arguments illegal.
    sys.exit('IP or Port address illegal')
    # check that the file exist.
try:
    myfile = open(FILE_TO_READ, "r")
    read_text = myfile.read(90)
    packge_number = 1
    packge_str = str(packge_number)
except IOError:
    print('file doesnt exist')
    myfile.close()
    s.close()
# while loop until we finished reading the file and send all the data.
while read_text:
    # flag to know if the server send us an answer and we got it.
    if_recived = False
    # send the 10 first bytes as the packge number and the rest 90 bytes data of the file.
    s.sendto(bytes(packge_str.zfill(10) + str(read_text), 'utf-8'), (IP_ADDRESS, int(PORT_NUMBER)))
    while if_recived == False:
        # try block - if didnt receive any answer sending the package again.
        try:
            data, addr = s.recvfrom(1024)
            if_recived = True
            # riding 90 bytes (the first 10 using for a flag)
            read_text = myfile.read(90)
            packge_number += 1
            packge_str = str(packge_number)
        except socket.timeout:
            # stop the internal loop and sending again the same package
            break

# closing the file and the socket.
myfile.close()
s.close()