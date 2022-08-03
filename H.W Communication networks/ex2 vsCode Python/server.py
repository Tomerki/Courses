import socket
import os
import random
import string

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(('', 12346))
server.listen()

dic_clients = {}

"""
function name:
    check_sep
input:
    path and seperator of the path.
output:
    a path that contain seperators of the operating system on which the server is running.
"""
def check_sep(path, seperator):
    if os.sep == seperator:
        return path
    else:
        return path.replace(seperator, os.sep)

"""
function name:
    update_my_client
input:
    the ID of the client and the ID of his specific computer
output:
    doesnt return a value.
function oparation:
   the function sends updates to the other computers with the same ID clients    
"""
def update_my_client(data_client_id, data_computer_id):
    operation = dic_clients.get(data_client_id).get(data_computer_id)
    #if there are some updates
    if len(operation) != 0:
        client_socket.send('1'.encode() + b'\n')
        #every arr is the details of one change
        for arr in operation:
            if arr[0] == 'create_dir':
                #'create_dir' message so that the client will know to create a new directory
                client_socket.send(arr[0].encode() + b'\n')
                #the path to the directory
                client_socket.send(arr[1].encode() + b'\n')
                #the directory name
                client_socket.send(arr[2].encode() + b'\n')
            elif arr[0] == 'create_file':
                #'create_file' message so that the client will know to create a new file
                client_socket.send(arr[0].encode() + b'\n')
                #the path to the file
                client_socket.send(arr[1].encode() + b'\n')
                #the file name
                client_socket.send(arr[2].encode() + b'\n')
                #the size of the file
                client_socket.send(arr[3].encode() + b'\n')
                #the context od the file
                client_socket.send(arr[4] + b'\n')
            elif arr[0] == 'delete_dir':
                #'delete_dir' message so that the client will know to delete an old directory
                client_socket.send(arr[0].encode() + b'\n')
                 #the path to the directory
                client_socket.send(arr[1].encode() + b'\n')
            elif arr[0] == 'delete_file':
                #'delete_file' message so that the client will know to delete an old file
                client_socket.send(arr[0].encode() + b'\n')
                #the src path of file
                client_socket.send(arr[1].encode() + b'\n')
            elif arr[0] == 'move_file':
                #'move_file' message so that the client will know to move a file
                client_socket.send(arr[0].encode() + b'\n')
                 #the src path of file
                client_socket.send(arr[1].encode() + b'\n')
                #the dest path of file
                client_socket.send(arr[2].encode() + b'\n')
            elif arr[0] == 'move_dir':
                #'move_file' message so that the client will know to move a directory
                client_socket.send(arr[0].encode() + b'\n')
                #the src path of directory
                client_socket.send(arr[1].encode() + b'\n')
                #the dest path of directory
                client_socket.send(arr[2].encode() + b'\n')
                #remove the pdate from the list of the updates after telling he client to make the change
            dic_clients.get(data_client_id)[data_computer_id] = []
        #telling the client that the updates are over
        client_socket.send('None'.encode() + b'\n')
    else :
        #if there are no updates
        client_socket.send('0'.encode() + b'\n')


"""
function name:
    update_new_computer
input:
    get the client user key and the computer key for the new computer.
output:
    doesnt return a value.
function oparation:
   the function first creates new inner dictionary for the data of the new computer.
   then, the function go over all the sub directories and sub files
   of the client folder, and sending all this data to the new client computer.
"""   

def update_new_computer(data_client_id, data_computer_id):
    #send the client his data for the client identify with this computer
    client_socket.send(computer_id.encode() + b'\n')
    client_socket.send(os.sep.encode() + b'\n')
    #add the new computer client to the dictionary with his computer key as a key.
    inner_dic = dic_clients.get(data_client_id)
    #defines the value of this computer key that uses as a key in the dictionary as an empty list.
    inner_dic[data_computer_id] = []
    dic_clients.update({data_client_id: inner_dic})
    PATH_TO_DIRECTORY = os.getcwd()
    #start to scan the client directory that stored in the server.
    for root, sub_dir, sub_files in os.walk(PATH_TO_DIRECTORY):
        #extract the relative path for sending it to the server.
        not_using, rel_root = root.split(PATH_TO_DIRECTORY)
        #changing work location (where we are at the scanning of os.walk).
        os.chdir(root)
        #sending all the directory with the data about their location and name.
        for dir_name in sub_dir:
            #first sending the client that the next information is about a directory.
            client_socket.send('dir'.encode() + b'\n')
            client_socket.send(rel_root.encode() + b'\n')
            client_socket.send(dir_name.encode() + b'\n')
        #sending all the files with the data about their location and name.
        for file_name in sub_files:
            #first sending the client that the next information is about a file.
            client_socket.send('file'.encode() + b'\n')
            client_socket.send(rel_root.encode() + b'\n')
            client_socket.send(file_name.encode() + b'\n')
            #open a file, save its length and content.
            str_file = open(os.path.abspath(file_name), 'rb')
            read_file = str_file.read()
            length = len(read_file)
            #sending the client the length(to know how many bytes to read) and the content of the file.
            client_socket.send(str(length).encode() + b'\n')
            client_socket.send(read_file + b'\n')
            #closing the file we opend.
            str_file.close()
    #indicates that all the data pass so we can stop waiting for data.
    client_socket.send('None'.encode() + b'\n')



"""
function name:
    old_client
input:
    get a file stream from the socket, the client seperator
    to check if its fit to the server OS, the client user key and the computer key.
output:
    no return value
function operation:
    this function is called when the client make change in his directory
    and then the server recive data from the client about the event that occurs
    and make the needed changes according the client notifications.
    in parallel, we manage an array that stored akk the data about the changes
    that the server make to the client folder, thats help us to notify other
    computer of the same client about those changes that we keep.
"""        


def old_client(a,data_client_id, data_computer_id, data_seperator):
    with a as c_file:
        while True:
            #creates an empty list to save the changes we gonna make.
            oops = []
            #recive data that contain the event type that occurs.
            data = c_file.readline().rstrip().decode()
            if data == 'create_dir':
                #add the kind of the event to our list.
                oops.append(data)
                #recive the needed data from the client for the new directory creation.
                dir_path = c_file.readline().rstrip().decode()
                currect_dir_path = check_sep(dir_path, data_seperator)
                #add the location where the event occurs to our list.
                oops.append(dir_path)
                current_path = currect_dir_path
                start_path = os.getcwd()
                #array to save the directory we need to create for the new directory(the directory inside this folder)
                arr = []
                while not os.path.exists(os.getcwd() + current_path):
                    p = current_path
                    current_path, dir_name = os.path.split(p)
                    #add the directory we need to create for the new directory path.
                    arr.append(dir_name)
                #reverse the arr because we need the directory in Top-Bottom order, but we recive the opposite order.
                arr.reverse()
                os.chdir(os.getcwd() + current_path)
                #creates all the directories in the path to the new directory.
                for a in arr:
                    new_dir_path = os.path.join(os.getcwd(), a)
                    os.mkdir(new_dir_path)
                    os.chdir(new_dir_path)
                os.chdir(start_path)
                #recive the new directory name.
                dir_name = c_file.readline().rstrip().decode()
                #add to our list the name of the new directory.
                oops.append(dir_name)
                #if the directory doesnt exists we create it according the client data.
                if not os.path.exists(os.getcwd() + currect_dir_path + os.sep + dir_name):
                    new_dir_path = os.path.join(os.getcwd() + currect_dir_path, dir_name)
                    os.mkdir(new_dir_path)
            elif data == "create_file":
                #add the kind of the event to our list.
                oops.append(data)
                #recive the needed data from the client for the new file creation.
                file_path = c_file.readline().rstrip().decode()
                currect_file_path = check_sep(file_path, data_seperator)
                #add the path of the new file to the list.
                oops.append(file_path)
                current_path = currect_file_path
                start_path = os.getcwd()
                #array to save the directory we need to create for the new file(the file inside this folder)
                arr = []
                while not os.path.exists(os.getcwd() + current_path):
                    p = current_path
                    current_path, dir_name = os.path.split(p)
                    #add the directory we need to create for the new file path.
                    arr.append(dir_name)
                #reverse the arr because we need the directories in Top-Bottom order, but we recive the opposite order.
                arr.reverse()
                os.chdir(os.getcwd() + current_path)
                #creates all the directories in the path to the new file.
                for a in arr:
                    new_dir_path = os.path.join(os.getcwd(), a)
                    os.mkdir(new_dir_path)
                    os.chdir(new_dir_path)
                os.chdir(start_path)
                #recive the new file name
                file_name = c_file.readline().rstrip().decode()
                #add the bew file name to the list of changes.
                oops.append(file_name)
                #isContinue tells us that we opend file because its wasnt exists.
                isContinue = True
                if not os.path.exists(start_path + currect_file_path + os.sep + file_name):
                    isContinue = False
                    newFile = open(start_path + currect_file_path + os.sep + file_name, 'wb')
                #recive from the server the length(to know how many bytes to read) and the content of the file.
                size_file = c_file.readline().rstrip().decode()
                #add file size to the changes list
                oops.append(size_file)
                file_data = c_file.read(int(size_file)).rstrip()
                #add file content to the changes list
                oops.append(file_data)
                #according to isContinue value we know if we need to write and then closing the file.
                if isContinue:
                    continue
                else:
                    newFile.write(file_data)
                    newFile.close()
            elif data == "delete_dir":
                #add the kind of the event to our list.
                oops.append(data)
                #save the current work directory
                prev_path = os.getcwd()
                #recive the needed data from the client for the directory deletion.
                dir_path = c_file.readline().rstrip().decode()
                currect_dir_path = check_sep(dir_path, data_seperator)
                #add to our list the path to the directory we want to delete.
                oops.append(dir_path)
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
                #if the path doesnt exists its means that we deleted it on othet event.
                else:
                    continue
            elif data == "delete_file":
                #add the kind of the event to our list.
                oops.append(data)
                #recive the needed data from the client for the file deletion.
                file_path = c_file.readline().rstrip().decode()
                currect_file_path = check_sep(file_path, data_seperator)
                oops.append(file_path)
                path = os.getcwd() + currect_file_path
                #remove the file if its exists, means that maybe we already deleted it from another event.
                if os.path.exists(path):
                    os.remove(path)
                else:
                    continue
            elif data == "move_file":
                #add the kind of the event to our list.
                oops.append(data)
                #recive the needed data from the client for moving the file.
                rel_src_path = c_file.readline().rstrip().decode()
                currect_rel_src_path = check_sep(rel_src_path, data_seperator)
                #add the source path to our array of changes
                oops.append(rel_src_path)
                src_path = os.getcwd() + currect_rel_src_path
                rel_dest_path = c_file.readline().rstrip().decode()
                currect_rel_dest_path = check_sep(rel_dest_path, data_seperator)
                #add the destination path to our array of changes
                oops.append(rel_dest_path)
                dest_path = os.getcwd() + currect_rel_dest_path
                #extract the path to the directory that containd the file we want to move.
                current_path, name_file = os.path.split(currect_rel_dest_path)
                start_path = os.getcwd()
                #arr to save the directory we need to create for the moved file(the file inside this folder).
                #in case we moved a folder with a file in it and notify on file moved.
                arr = []
                while not os.path.exists(os.getcwd() + current_path):
                    p = current_path
                    current_path, dir_name = os.path.split(p)
                    arr.append(dir_name)
                arr.reverse()
                os.chdir(os.getcwd() + current_path)
                #creates all the directories in the path to the directory that we want to move the file to.
                for a in arr:
                    new_dir_path = os.path.join(os.getcwd(), a)
                    os.mkdir(new_dir_path)
                    os.chdir(new_dir_path)
                os.chdir(start_path)
                #check if the file already moved to the destantion folder, if no, we move it.
                if os.path.exists(src_path) and not os.path.exists(dest_path):
                    os.replace(src_path, dest_path)
                else:
                    continue
            elif data == "move_dir":
                #add the kind of the event to our list.
                oops.append(data)
                #recive the needed data from the client for moving the directory.
                rel_src_path = c_file.readline().rstrip().decode()
                currect_rel_src_path = check_sep(rel_src_path, data_seperator)
                #add the source path to our array of changes
                oops.append(rel_src_path)
                src_path = os.getcwd() + currect_rel_src_path
                rel_dest_path = c_file.readline().rstrip().decode()
                currect_rel_dest_path = check_sep(rel_dest_path, data_seperator)
                dest_path = os.getcwd() + currect_rel_dest_path
                #add the destination path to our array of changes
                oops.append(rel_dest_path)
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
                #save our working directory.
                prev_path = os.getcwd()
                path = src_path
                #delete all the sub directories and files after created them on the destination path.
                if os.path.exists(path):
                    for root, sub_dir, sub_files in os.walk(path, topdown=False):
                        os.chdir(root)
                        for file_name in sub_files:
                            os.remove(os.path.abspath(file_name))
                        for dir_name in sub_dir:
                            os.rmdir(os.path.abspath(dir_name))
                    os.chdir(prev_path)
                    os.rmdir(path)
            #recive None as a symbol that all the information pass.
            elif data == "None":
                break
            #creates new computer key in the dictionary that we stored in all the clients data.
            inner_dic = dic_clients.get(data_client_id)
            #add the changes array to all the other client computer, so when the client
            #reconnect with those computer we will know which updates they need to do.
            if len(oops) != 0 :
                for d in inner_dic.keys():
                    if d != data_computer_id:
                        inner_list = inner_dic.get(d)
                        inner_list.append(oops)


"""
function name:
    new_client
input:
    get a file stream from the socket and the client seperator
    to check if its fit to the server OS.
output:
    no return value.
function oparation:
   first, creates a user key and computer key for the new client, to be able to recognize
   the client and his computer when he reconnect the server.
   then we add to a dictionary the client user key as a key and an empty dictionary as a value.
   the keys in the inner dictionary its the computer user and an empty list for the value.
   in the list of every computer we store changes in directories from other computers
   of the same client. when the client reconnect from other computers,
   we will check which changes we collect in those computers lists, and send it to the client.
"""   
def new_client(a, data_seperator):
    #creates random user key and computer key.
    client_id = "".join(random.choice(string.ascii_letters + string.digits) for i in range(128))
    computer_id = "".join(random.choice(string.ascii_letters + string.digits) for i in range(128))
    print(client_id)
    #add the new client to the dictionary with his user key as a key.
    dic_clients[client_id] = {}
    #defines the value to be an empty dictionary.
    inner_dic = dic_clients.get(client_id)
    #defines the value of this computer key that uses as a key in the dictionary as an empty list.
    inner_dic[computer_id] = []
    dic_clients.update({client_id: inner_dic})
    #send the client his keys data so that he can identify next time he reconnect.
    client_socket.send(client_id.encode() + b'\n')
    client_socket.send(computer_id.encode() + b'\n')
    client_socket.send(os.sep.encode() + b'\n')
    #creats a path for new directory for the new client.
    new_path = os.path.join(os.getcwd(), client_id)
    #creates the directory in the path we defined.
    os.mkdir(new_path)
    os.chdir(os.path.abspath(client_id))

    with a as c_file:
        while True:
            #data that indicates about the kind of creation(file or directory)
            data = c_file.readline().rstrip().decode()
            if data == "dir":
                #recive the needed data from the client for the new directory.
                dir_path = c_file.readline().rstrip().decode()
                currect_dir_path = check_sep(dir_path, data_seperator)
                dir_name = c_file.readline().rstrip().decode()
                #build a path to the location of the new directory according our OS seperator.
                path = os.path.join(os.getcwd() + currect_dir_path, dir_name)
                #creates the new directory.
                os.mkdir(path)
            elif data == "file":
                #recive the needed data from the client for the new file.
                file_path = c_file.readline().rstrip().decode()
                currect_file_path = check_sep(file_path, data_seperator)
                file_name = c_file.readline().rstrip().decode()
                #open a file to be able to write the content of the file(in the client) to new file(in the server).
                newFile = open(os.getcwd() + currect_file_path + os.sep + file_name, 'wb')
                #recive the content length of the file.
                size_file = c_file.readline().rstrip().decode()
                #recive the file content.
                file_data = c_file.read(int(size_file)).rstrip()
                #write the content to our new file.
                newFile.write(file_data)
                #closing the file.
                newFile.close()
            #indicates that all the data pass so we can stop waiting for data.
            elif data == "None":
                break
    return

while True:
    client_socket, client_address = server.accept()
    #save the current path to update the path with the connected client
    prev_path = os.getcwd()
    a = client_socket.makefile('rb')
    with a as c_file:
        #the client ID
        data_client_id = c_file.readline().rstrip().decode()
        #the computer ID - the specific computer of the client
        data_computer_id = c_file.readline().rstrip().decode()
        #for update the path according to our operation system if the client has fifferent one
        data_seperator = c_file.readline().rstrip().decode()
        #new client
        if data_client_id == '0':
            new_client(a, data_seperator)
            #change the current path to the directory of the client
            os.chdir(prev_path)
        #new coumputer of an exsist client
        elif data_client_id != '0' and data_computer_id == '0':
            computer_id = "".join(random.choice(string.ascii_letters + string.digits) for i in range(128))
            #change the current path to the directory of the client
            os.chdir(os.path.abspath(data_client_id))
            update_new_computer(data_client_id, computer_id)
            os.chdir(prev_path)
        #exsist coumputer of an exsist client
        elif data_client_id != '0' and data_computer_id != '0':
            data_needed = c_file.readline().rstrip().decode()
            #change the current path to the directory of the client
            os.chdir(os.path.abspath(data_client_id))
            if (data_needed == 'take_an_update'):
                old_client(a, data_client_id, data_computer_id, data_seperator)
            elif (data_needed == 'waiting_for_an_update'):
                update_my_client(data_client_id, data_computer_id)
            os.chdir(prev_path)

        client_socket.close()