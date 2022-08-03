import socket
import sys
import time
from watchdog.events import PatternMatchingEventHandler
from watchdog.observers import polling
import os


SERVER_IP = sys.argv[1]
SERVER_PORT = int(sys.argv[2])
PATH_TO_DIRECTORY = sys.argv[3]
CHECK_TIME = int(sys.argv[4])


#using try - except block to define USER_KEY with 0 for new clients.

try:
    USER_KEY = sys.argv[5]
except IndexError:
    USER_KEY = '0'
#user computer key help us to store for every client a list of is computers
USER_COMP_KEY = '0'

#the path's seperator of the operating system on which the server is running.
SERVER_PATH_SEPERATOR = ''

def check_arguments(ip, port):
    ls = ip.split(".")
    if len(ls) != 4:
        return False
    for num in ls:
        if num.isdigit() is False:
            return False
    if str(port).isdigit() is not True: 
        return False
    b = 65535 - port
    if b < 0:
        return False
    return True

if not check_arguments(SERVER_IP, SERVER_PORT):
    sys.exit()

"""
function name:
    check_seperator
input:
    path and seperator of the path.
output:
    a path that contain seperators of the operating system on which the client is running.
"""
def check_seperator(path, seperator):
    if os.sep == seperator:
        return path
    return path.replace(seperator, os.sep)

"""
function name:
    open_socket
input:
    no parameters.
output:
    return value is the new socket that we open.
function operation:
    the function open a new socket on TCP protocol and return's it as a return value.
"""

def open_socket():
    new_socket = (socket.socket(socket.AF_INET, socket.SOCK_STREAM))
    new_socket.connect((SERVER_IP, SERVER_PORT))
    return new_socket

"""
function name:
    send_client_data()
input:
    no parameters.
output:
    doesnt return value.
function operation:
    the function sending the client data to the server,
    we send the user_key, user_computer_key and the seperator of the client
    operating system.
    in this way the server can detect this client in the next time that the client
    will connect to him.
    and the seperator of the client operating system help the server to know
    the seperator path of the client operating system and to change it if necessary.
    
"""

def send_client_data():
    s.send(str(USER_KEY).encode() + b'\n')
    s.send(str(USER_COMP_KEY).encode() + b'\n')
    s.send(os.sep.encode() + b'\n')
    return
    
"""
function name:
    on_created
input:
    get as parameter the event watchdog notify that occured.
output:
    doesnt return value
function operation:
    the function send the server data about a creation of new
    file or directory that are inside the client main folder.
"""

def on_created(event):
    #open socket to update the server with the event.
    s = open_socket()
    #send the server the client details for identification.
    s.send(str(USER_KEY).encode() + b'\n')
    s.send(str(USER_COMP_KEY).encode() + b'\n')
    #send the seperator of the OS.
    s.send(os.sep.encode() + b'\n')
    #notify the server that this connection goal is to update him with event that occured.
    s.send('take_an_update'.encode() + b'\n')
    if event.is_directory:
        #if the event is a creation of directory - we sent the server 'create_dir'
        s.send('create_dir'.encode() + b'\n')
        #split the name of the new directory from the path.
        pathDir, nameDir = os.path.split(event.src_path)
        #extract the relative path from the main client folder to the new directory.
        not_using, rel_path = str(pathDir).split(PATH_TO_DIRECTORY)
        #sending the relative path to the server.
        s.send(str(rel_path).encode() + b'\n')
        #sending the name of the new directory to the server.
        s.send(str(nameDir).encode() + b'\n')
    else:
        #if the event is a creation of a file - we sent the server 'create_file'
        s.send('create_file'.encode() + b'\n')
        #split the name of the new file from the path.
        path_file, nameFile = os.path.split(event.src_path)
        #extract the relative path from the main client folder to the new directory.
        not_using, rel_path = str(path_file).split(PATH_TO_DIRECTORY)
        #sending the relative path to the server.
        s.send(str(rel_path).encode() + b'\n')
        #sending the name of the new file to the server.
        s.send(str(nameFile).encode() + b'\n')
        #check the length of the new file that we create
        str_file = open(event.src_path, 'rb')
        read_file = str_file.read()
        length = len(read_file)
        #sending the file length to the server so it knows how many bytes to read.
        s.send(str(length).encode() + b'\n')
        #sending the file data
        s.send(read_file + b'\n')
        str_file.close()
    #sending none as a symbol that al the information pass.
    s.send('None'.encode() + b'\n')
    #after finishing to update the server, closing the socket.
    s.close()
        
def on_deleted(event):
    #open socket to update the server with the event.
    s = open_socket()
    #send the server the client details for identification.
    s.send(str(USER_KEY).encode() + b'\n')
    s.send(str(USER_COMP_KEY).encode() + b'\n')
    s.send(os.sep.encode() + b'\n')
    #notify the server that this connection goal is to update him with event that occured.
    s.send('take_an_update'.encode() + b'\n')
    if event.is_directory:
        #if the event is a directory deletion - we sent the server 'delete_dir'
        s.send('delete_dir'.encode() + b'\n')
        #extract the relative path from the main client folder to the directory that deleted.
        not_using, rel_path = str(event.src_path).split(PATH_TO_DIRECTORY)
        #sending the relative path to the server.
        s.send(str(rel_path).encode() + b'\n')
    else:
        #if the event is a file deletion - we sent the server 'delete_file'
        s.send('delete_file'.encode() + b'\n')
        #extract the relative path from the main client folder to the file that deleted.
        not_using, rel_path = str(event.src_path).split(PATH_TO_DIRECTORY)
        #sending the relative path to the server.
        s.send(str(rel_path).encode() + b'\n')
    #sending none as a symbol that al the information pass.
    s.send('None'.encode() + b'\n')
    #after finishing to update the server, closing the socket.
    s.close()
        
#doesnt using the function but has to override it.     
def on_modified(event):
    pass
        
def on_moved(event):
    #open socket to update the server with the event.
    s = open_socket()
    #send the server the client details for identification.
    s.send(str(USER_KEY).encode() + b'\n')
    s.send(str(USER_COMP_KEY).encode() + b'\n')
    s.send(os.sep.encode() + b'\n')
    #notify the server that this connection goal is to update him with event that occured.
    s.send('take_an_update'.encode() + b'\n')
    if not event.is_directory:
        #if the event is a file move - we sent the server 'move_file'
        s.send('move_file'.encode() + b'\n')
        #extract the relative path from the main client folder to the file that moved.
        not_using, rel_src_path = str(event.src_path).split(PATH_TO_DIRECTORY)
        #extract the relative path from the main client folder to the new destination of the moved file.
        not_using, rel_dest_path = str(event.dest_path).split(PATH_TO_DIRECTORY)
        #sending the relative source path to the server.
        s.send(str(rel_src_path).encode() + b'\n')
        #sending the relative destination path to the server.
        s.send(str(rel_dest_path).encode() + b'\n')
    else:
        #if the event is a directory move - we sent the server 'move_dir'
        s.send('move_dir'.encode() + b'\n')
        #extract the relative path from the main client folder to the directory that moved.
        not_using, rel_src_path = str(event.src_path).split(PATH_TO_DIRECTORY)
        #extract the relative path from the main client folder to the new destination of the moved directory.
        not_using, rel_dest_path = str(event.dest_path).split(PATH_TO_DIRECTORY)
        #sending the relative source path to the server.
        s.send(str(rel_src_path).encode() + b'\n')
        #sending the relative destination path to the server.
        s.send(str(rel_dest_path).encode() + b'\n')
    #sending none as a symbol that all the information pass.
    s.send('None'.encode() + b'\n')
    #after finishing to update the server, closing the socket.
    s.close()

"""
function name:
    update_client_computer
input:
    does get parameters.
output:
    doesnt return a value.
function operation:
    this function is called every CHECK_TIME(parameter that we get as an argument) seconds,
    and check with the server if the client folder that its keep is changed, and if the server
    answer is positive, so the client is updated from the server, it means that the server
    sending the client the new client's data that been changed and this function get this
    information from the server and update the client folder according the server data.
"""        
def update_client_computer():
    s = open_socket()
    #send the server the client details for identification.
    s.send(str(USER_KEY).encode() + b'\n')
    s.send(str(USER_COMP_KEY).encode() + b'\n')
    s.send(os.sep.encode() + b'\n')
    #open a file stream for the client could read the data that the server updates him with.
    stream_file = s.makefile('rb')
    #tells the server that we waiting for him to tell us if there are any changes.
    s.send('waiting_for_an_update'.encode() + b'\n')
    #recive an answer from the server about possible changes.
    server_answer = stream_file.readline().rstrip().decode()
    if server_answer != '1':
        return
    with stream_file as new_file:
        while True:
            #recive data that contain the event type that occurs.
            data = new_file.readline().rstrip().decode()
            if data == 'create_dir':
                #recive the needed data from the server for the new directory creation.
                dir_path = new_file.readline().rstrip().decode()
                currect_dir_path = check_seperator(dir_path, SERVER_PATH_SEPERATOR)
                dir_name = new_file.readline().rstrip().decode()
                #if the directory doesnt exists we create it according the server data.
                if not os.path.exists(os.getcwd() + currect_dir_path + os.sep + dir_name):
                    new_dir_path = os.path.join(os.getcwd() + currect_dir_path, dir_name)
                    os.mkdir(new_dir_path)
            elif data == "create_file":
                #recive the needed data from the server for the new file creation.
                file_path = new_file.readline().rstrip().decode()
                currect_file_path = check_seperator(file_path, SERVER_PATH_SEPERATOR)
                current_path = currect_file_path
                start_path = os.getcwd()
                #array to save the directory we need to create for the new file(the file inside this folder)
                arr = []
                while not os.path.exists(os.getcwd() + current_path):
                    prev = current_path
                    current_path, dir_name = os.path.split(prev)
                    #add the directory we need to create for the new file path.
                    arr.append(dir_name)
                #reverse the arr because we need the directory in Top-Bottom order, but we recive the opposite order.
                arr.reverse()
                os.chdir(os.getcwd() + current_path)
                #creates all the directories in the path to the new file.
                for a in arr:
                    new_dir_path = os.path.join(os.getcwd(), a)
                    os.mkdir(new_dir_path)
                    os.chdir(new_dir_path)
                os.chdir(start_path)
                #recive the new file name
                file_name = new_file.readline().rstrip().decode()
                bool = False
                #check if the file already exists, if no, we open it.
                if not os.path.exists(start_path + currect_file_path + os.sep + file_name):
                    #bool tells us that we opend file because its wasnt exists.
                    bool = True
                    newFile = open(start_path + currect_file_path + os.sep + file_name, 'wb')
                #recive from the server the length(to know how many bytes to read) and the content of the file.
                size_file = new_file.readline().rstrip().decode()
                file_data = new_file.read(int(size_file)).rstrip()
                #according to bool value we know if we need to write and then closing the file.
                if bool:
                    newFile.write(file_data)
                    newFile.close()
            elif data == "delete_dir":
                #save the current work directory
                prev_path = os.getcwd()
                #recive the needed data from the server for the directory deletion.
                dir_path = new_file.readline().rstrip().decode()
                currect_dir_path = check_seperator(dir_path, SERVER_PATH_SEPERATOR)
                path = os.getcwd() + currect_dir_path
                #if the folder exists, we delete all its content and then delete the folder.
                if os.path.exists(path):
                    for root, sub_dir, sub_files in os.walk(path, topdown=False):
                        os.chdir(root)
                        for file_name in sub_files:
                            os.remove(os.path.abspath(file_name))
                        for dir_name in sub_dir:
                            os.rmdir(os.path.abspath(dir_name))
                    #return to our original work directory (where the client directory found at)
                    os.chdir(prev_path)
                    #remove the folder after delete all its sub directories and sub files.
                    os.rmdir(path)
            elif data == "delete_file":
                #recive the needed data from the server for the file deletion.
                file_path = new_file.readline().rstrip().decode()
                currect_file_path = check_seperator(file_path, SERVER_PATH_SEPERATOR)
                path = os.getcwd() + currect_file_path
                #remove the file if its exists, means that maybe we already deleted it from another event.
                if os.path.exists(path):
                    os.remove(path)
            elif data == "move_file":
                #recive the needed data from the server for moving the file.
                rel_src_path = new_file.readline().rstrip().decode()
                currect_rel_src_path = check_seperator(rel_src_path, SERVER_PATH_SEPERATOR)
                src_path = os.getcwd() + currect_rel_src_path
                rel_dest_path = new_file.readline().rstrip().decode()
                currect_rel_dest_path = check_seperator(rel_dest_path, SERVER_PATH_SEPERATOR)
                dest_path = os.getcwd() + currect_rel_dest_path
                #extract the path to the directory that containd the file we want to move
                current_path, name_file = os.path.split(currect_rel_dest_path)
                start_path = os.getcwd()
                #arr to save the directory we need to create for the moved file(the file inside this folder).
                #in case we moved a folder with a file in it and notify on file moved.
                arr = []
                while not os.path.exists(os.getcwd() + current_path):
                    p = current_path
                    current_path, dir_name = os.path.split(p)
                    arr.append(dir_name)
                #reverse the arr because we need the directory in Top-Bottom order, but we recive the opposite order.
                arr.reverse()
                os.chdir(os.getcwd() + current_path)
                #creates all the directories in the path to the directory that we want to move the file to.
                for a in arr:
                    new_dir_path = os.path.join(os.getcwd(), a)
                    os.mkdir(new_dir_path)
                    os.chdir(new_dir_path)
                os.chdir(start_path)
                #check if the file already moved to the destantion folder, if no, we move it.
                if not os.path.exists(dest_path):
                    os.replace(src_path, dest_path)
            elif data == "move_dir":
                #recive the needed data from the server for moving the directory.
                rel_src_path = new_file.readline().rstrip().decode()
                currect_rel_src_path = check_seperator(rel_src_path, SERVER_PATH_SEPERATOR)
                src_path = os.getcwd() + currect_rel_src_path
                rel_dest_path = new_file.readline().rstrip().decode()
                currect_rel_dest_path = check_seperator(rel_dest_path, SERVER_PATH_SEPERATOR)
                dest_path = os.getcwd() + currect_rel_dest_path
                current_path = currect_rel_dest_path
                start_path = os.getcwd()
                #arr to save the directory we need to create for the moved directory.
                #in case we moved a folder that isnt empty.
                arr = []
                while not os.path.exists(os.getcwd() + current_path):
                    p = current_path
                    current_path, dir_name = os.path.split(p)
                    arr.append(dir_name)
                #reverse the arr because we need the directory in Top-Bottom order, but we recive the opposite order.
                arr.reverse()
                os.chdir(os.getcwd() + current_path)
                for a in arr:
                    new_dir_path = os.path.join(os.getcwd(), a)
                    os.mkdir(new_dir_path)
                    os.chdir(new_dir_path)
                os.chdir(start_path)
                #delete all the sub directories and files after created them on the destination path.
                if os.path.exists(src_path):
                    for root, sub_dir, sub_files in os.walk(src_path, topdown=False):
                        os.chdir(root)
                        for file_name in sub_files:
                            os.remove(os.path.abspath(file_name))
                        for dir_name in sub_dir:
                            os.rmdir(os.path.abspath(dir_name))
                    os.chdir(start_path)
                    os.rmdir(src_path)
            #recive None as a symbol that all the information pass.
            elif data == "None":
                break
        s.close()
        

"""
function name:
    active_observer
input:
    no parameters.
output:
    doesnt return a value.
function oparation:
    first, the function creates an observer and event handler.
    the observer rule is to watch on the client directory and notify the event handler
    about events that occurs in this directory(and sub directories and files).

    the event handler get the information and sending the event to the right function
    that know to handle it. to do so, we over-ride the functions in the event handler class,
    and re-write them to our needs.

"""

def active_observer():
    #define the event handler and over-ride its functions.
    handler_event = PatternMatchingEventHandler(["*"],ignore_directories=False, case_sensitive=False)
    handler_event.on_created = on_created
    handler_event.on_modified = on_modified
    handler_event.on_deleted = on_deleted
    handler_event.on_moved = on_moved
    #define our observer with the event handler.
    my_observer = polling.PollingObserver()
    my_observer.schedule(handler_event, path = PATH_TO_DIRECTORY, recursive = True)
    #start the observer thread.
    my_observer.start()
    
    #try-except is necessary for the case that we finish the program but need to close the observer thread.
    try:
        #every CHECK_TIME seconds we ask the server fot updates.
        while True:
            time.sleep(CHECK_TIME)
            update_client_computer()
    except (KeyboardInterrupt, SystemExit):
        my_observer.stop()
    my_observer.join()


"""
function name:
    new_client
input:
    no parameters.
output:
    doesnt return a value.
function oparation:
    first, check if the folder of the client already exist and creates it if isnt.
    then we using the os.walk function that know to scan all the sub directories and sub files
    of the folder its get as argument.
    while scanning the directory we sending the server all the directories from top to bottom,
    and then sending all the files with their contents.
"""   

def new_client():
    #open the new directory if needed
    if not os.path.exists(PATH_TO_DIRECTORY):
        os.mkdir(PATH_TO_DIRECTORY)
    #start to scan the client directory.
    for root, sub_dir, sub_files in os.walk(PATH_TO_DIRECTORY):
        #extract the relative path for sending it to the server.
        not_using,rel_root = root.split(PATH_TO_DIRECTORY)
        #changing work location (where we are at the scanning of os.walk).
        os.chdir(root)
        #sending all the directory with the data about their location and name.
        for dir_name in sub_dir:
            #first sending the server that the next information is about a directory.
            s.send('dir'.encode() + b'\n')
            s.send(rel_root.encode() + b'\n')
            s.send(dir_name.encode() + b'\n')
        #sending all the files with the data about their location and name.
        for file_name in sub_files:
            #first sending the server that the next information is about a file.
            s.send('file'.encode() + b'\n')
            s.send(rel_root.encode() + b'\n')
            s.send(file_name.encode() + b'\n')
            #open a file, save its length and content.
            str_file = open(os.path.abspath(file_name), 'rb')
            read_file = str_file.read()
            length = len(read_file)
            #sending the server the length(to know how many bytes to read) and the content of the file.
            s.send(str(length).encode() + b'\n')
            s.send(read_file + b'\n')
            #closing the file we opend.
            str_file.close()
    #indicates that all the data pass so we can stop waiting for data.
    s.send('None'.encode() + b'\n')


"""
function name:
    new_computer_client.
input:
    no parameters.
output:
    doesnt return a value.
function oparation:
    first, check if the folder of the client already exist and creates it if isnt.
    then we start to get data from the server about the content of the client folder
    and by conditions we check if the data from the server is a directory creation or a file creation.
    after that we recive all the needed information from he server about the file\directory
    that we need to create, means, we getting the location of the new creation(relative path),
    then reciving the name.
    with all this information we build the right path and open the new creation with the right name.

    if the creation is a new file, we also recive the size of the file, because we need to know
    how many bytes to read, and then the server send us the content of the file.
"""   
def new_computer_client():
    #open the new directory if needed
    if not os.path.exists(PATH_TO_DIRECTORY):
        os.mkdir(PATH_TO_DIRECTORY)
    #changing to the work location (where we keep the client folder).
    os.chdir(PATH_TO_DIRECTORY)
    with stream_file as new_file:
        while True:
            #data that indicates about the kind of creation(file or directory)
            data = new_file.readline().rstrip().decode()
            if data == "dir":
                #recive the needed data from the server for the new directory.
                dir_path = new_file.readline().rstrip().decode()
                currect_dir_path = check_seperator(dir_path, SERVER_PATH_SEPERATOR)
                dir_name = new_file.readline().rstrip().decode()
                #build a path to the location of the new directory according our OS seperator.
                path = os.path.join(os.getcwd() + currect_dir_path, dir_name)
                #creates the new directory.
                os.mkdir(path)
            elif data == "file":
                #recive the needed data from the server for the new file.
                file_path = new_file.readline().rstrip().decode()
                currect_file_path = check_seperator(file_path, SERVER_PATH_SEPERATOR)
                file_name = new_file.readline().rstrip().decode()
                #open a file to be able to write the content of the file(in the server) to new file(in the client).
                newFile = open(os.getcwd() + currect_file_path + os.sep + file_name, 'wb')
                #recive the content length of the file.
                size_file = new_file.readline().rstrip().decode()
                #recive the file content.
                file_data = new_file.read(int(size_file)).rstrip()
                #write the content to our new file.
                newFile.write(file_data)
                #closing the file.
                newFile.close()
            #indicates that all the data pass so we can stop waiting for data.
            elif data == "None":
                break
    return

#check if the client user is 0, so we know to treat him as a new client.
if USER_KEY == '0':
    s = open_socket()
    stream_file = s.makefile('rb')
    #after open a socket sending the client data to the server.
    send_client_data()
    with stream_file as new_file:
        #reading back our new user key and computer key so the client will identify when reconnect.
        USER_KEY = stream_file.readline().rstrip().decode()
        USER_COMP_KEY = stream_file.readline().rstrip().decode()
        SERVER_PATH_SEPERATOR = stream_file.readline().rstrip().decode()
    #function that sending the server all the data in the folder that we want to backup.
    new_client()
    #returning to the work location (where we keep the client folder).
    os.chdir(PATH_TO_DIRECTORY)
    #closing the socket after the client backup his data on the server.
    s.close()
#that case handle with old client that connect the server with new computer.
elif USER_KEY != '0' and USER_COMP_KEY == '0':
    s = open_socket()
    stream_file = s.makefile('rb')
    send_client_data()
    #reading our new computer key so the client computer will identify when reconnect from this computer.
    USER_COMP_KEY = stream_file.readline().rstrip().decode()
    SERVER_PATH_SEPERATOR = stream_file.readline().rstrip().decode()
    #function that recive from the server all the folder data of the client to his new computer.
    new_computer_client()
    #closing the socket after the client backup his data on the server.
    s.close()
#start to track after changes in the folder that the client want to backup.
active_observer()