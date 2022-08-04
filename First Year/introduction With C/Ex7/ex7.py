import sys
from collections import defaultdict
"""
Name: Tomer Hadar 
ID: 207651027
Group: 01
Assignment: ex7
"""


"""
Function Name:
    get_products
Input:
    gets a list with products and  prices for each product
Output:
    return a pair of product and price, as a dictionary.
Function Operation:
    the function split the list its get and separate the product name and his price
    and return a dictionary pair as a value to the main dictionary
"""
def get_products(productData):
    productDict = {}
    for i in range(len(productData)):
        productName, productPrice = productData[i].split(',', 1)
        productName = productName.lstrip()
        productPrice = productPrice.lstrip()
        productDict[productName] = productPrice
    return productDict


"""
Function Name:
    get_store_products
Input:
    function gets the variable that we read inside him the store categories and products
Output:
    returns the main dictionary that contains all the store data
Function Operation:
    the function using a for loop to go over all the lines in the file
    and sending each line to function that separated between the data.
"""
def get_store_products(storeFile):
    store = {}
    for line in storeFile:
        if line == '\n':
            continue
        catagoryName = line.strip().split(':')
        productData = catagoryName[1].split(';')
        del productData[-1]
        store[catagoryName[0]] = get_products(productData)
    return store


"""
Function Name:
    print_menu
Input:
    doest get parameters
Output:
    return the user choice or print error messege
Function Operation:
    the function print the menu to the screen and checks the user choice.
"""
def print_menu():
    choice = input('Please select an operation:\n\t0. Exit.\n\t1. Query by category.\
\n\t2. Query by item.\n\t3. Purchase an item.\n\t4. Admin panel.\n')
    if '0' <= choice <= '4':
        return choice
    print('Error: unrecognized operation.')


"""
Function Name:
    check_if_legal
Input:
    the function gets the main dictionary and the user input
    for choosing 1 on the menu.
Output:
    function return False if some data ilegal, else return list with all th legal data
Function Operation:
    the function checks with if statments that the user input is legal.
"""
def check_if_legal(category, store):
    saveList = category.split(',')
    for i in range(len(saveList)):
        saveList[i] = saveList[i].lstrip()
   #checks the length of the list
    if len(saveList) < 3:
        print('Error: not enough data.')
        return False
    #checks if category exsist
    elif store.get(saveList[0]) == None or store.get(saveList[1]) == None:
        print('Error: one of the categories does not exist.')
        return False 
    #checks if the operator is legal
    elif ((saveList[-1] != '&') and (saveList[-1] != '|') and (saveList[-1] != '^')) or (len(saveList) > 3):
        print('Error: unsupported query operation.')
        return False
    return saveList


"""
Function Name:
    print_intersection
Input:
    function gets list with category name and operator,
    and the main dictionary with the store data
Output:
    returns the intersection between to given categories.
Function Operation:
    the function put all the categories products inside 2 sets and than returns the intersection between them.
"""
def print_intersection(lst, store):
    s1 = set()
    s2 = set()
    #get the products in the first category inside the first set
    for data in store[lst[0]].keys():
        s1.add(data)
    #get the products in the second category inside the second set
    for data in store[lst[1]].keys():
        s2.add(data)
    print(sorted(s1 & s2))
    return sorted(s1 & s2)


"""
Function Name:
     print_union
Input:
    function gets list with category name and operator,
    and the main dictionary with the store data
Output:
     returns the union between to given categories.
Function Operation:
    the function put all the categories products inside 2 sets and than returns the union between them.
"""
def print_union(lst, store):
    s1 = set()
    s2 = set()
    #get the products in the first category inside the first set
    for data in store[lst[0]].keys():
        s1.add(data)
    #get the products in the second category inside the second set
    for data in store[lst[1]].keys():
        s2.add(data)
    print(sorted(s1 | s2))
    #returns the union 
    return sorted(s1 | s2)


"""
Function Name:
     print_symmetric
Input:
    function gets list with category name and operator,
    and the main dictionary with the store data
Output:
     returns the symmetrical difference between to given categories.
Function Operation:
    the function put all the categories products inside 2 sets and than returns the symmetrical difference between them.
"""
def print_symmetric(lst, store):
    s1 = set()
    s2 = set()
    #get the products in the first category inside the first set
    for data in store[lst[0]].keys():
        s1.add(data)
    #get the products in the second category inside the second set
    for data in store[lst[1]].keys():
        s2.add(data)
    print(sorted((s1 - s2) | (s2 - s1)))
   #returns the symmetrical difference
    return sorted((s1 - s2) | (s2 - s1))


"""
Function Name:
    cache_system
Input:
    gets a list with two categories and operator
Output:
    gets the same list but as a string and replace the categories place.
Function Operation:
    the function replace between the two categories indexes, for the cache system,
    in a case that the user put the same input but changing the order of the categories
"""
def cache_system(lst):
    tempList = []
    tempList.append(lst[1])
    tempList.append(lst[0])
    tempList.append(lst[2])
    reverseStr = ','.join(tempList)
    return reverseStr


"""
Function Name:
    query_by_category
Input:
    function gets the store dictionary and the dictionary of the cache system.
Output:
    doesnt return a value, only print the screen
Function Operation:
    he function gets input from the user and checks if its legal, if it is so 
    the function check if the input apear in the cache system, if it isnt, 
    the function check which operator the user ask and sending to the correct function
"""
def query_by_category(store, saveAnswers):
    category = input().lstrip()
   #send to function to check all the input
    lst = check_if_legal(category, store)
    if lst == False:
       return
    cache = ''
    cache = cache_system(lst)
    #checking if the input apears in the cache system
    if len(saveAnswers) != 0:
        if saveAnswers.get(category) != None:
            print('Cached:', saveAnswers[category])
            return
        if saveAnswers.get(cache) != None:
            print('Cached:', saveAnswers[cache])
            return
   #checks which operator the user choose.
    if lst[-1] == '&':
        saveAnswers[category] = print_intersection(lst, store)
        saveAnswers[cache] = saveAnswers[category]
    elif lst[-1] == '|':
        saveAnswers[category] = print_union(lst, store)
        saveAnswers[cache] = saveAnswers[category]
    else:
        saveAnswers[category] = print_symmetric(lst, store)
        saveAnswers[cache] = saveAnswers[category]


"""
Function Name:
     query_by_item
Input:
    function gets the store dictionary and the dictionary of the cache system.
Output:
    doesnt return a value, only print the screen
Function Operation:
    the function gets input from the user and print all the 
    products in the same produst's category that the user put as a input.
"""
def query_by_item(store, saveAnswers):
    product = input().lstrip()
    #checking if the input apears in the cache system
    if len(saveAnswers) != 0:
        if saveAnswers.get(product) != None:
            print('Cached:', saveAnswers[product])
            return
    s1 = set()
    #gets all the products inside a set to avoid duplication.
    for data in store:
        if product in store[data].keys():
            s1.update(store[data].keys())
    if len(s1) != 0:
        s1.remove(product)
        print(sorted(s1))
        saveAnswers[product] = sorted(s1)
        return
    #if the user input ilegal.
    print('Error: no such item exists.')


"""
Function Name:
    purchase_an_item
Input:
    function gets the store dictionary and the dictionary of the cache system.
Output:
    doesnt returns a value
Function Operation:
    the checks if the products that the user want to buy is in the store,
    if it is so we have indicator that tell us that the item exist.
    and than print a messege.
"""
def purchase_an_item(store, saveAnswers):
    temp = True
    #indicator if the products exist
    indicator = False
    theItem = input().lstrip()
    for data in store.values():
        #if we found the product the indicator True
        if theItem in data.keys(): 
            indicator = True
            temp = data.get(theItem)
            #remove the product after selling it
            data.pop(theItem)
    #if indicator true or false print the correct messege
    if indicator == True:
        print('You bought a brand new', '"' + theItem + '"', 'for ' + temp + '$.')
        saveAnswers.clear()
    else:
        print('Error: no such item exists.')


"""
Function Name:
    ask_for_password
Input:
    doesnt gets parameters
Output:
    returns False or True
Function Operation:
    the function reads the admin password from a file 
    and compare this password to the user input, if the user put the right password
    we return True, else False.
"""
def ask_for_password():

    with open(ADMIN_PASSWORD_FILE, "r") as passwordFile:
        password = input('Password: ')
        #checks if the password correct
        if passwordFile.readline() == password:
            return True
    #print Error if the password incorrect
    print('Error: incorrect password, returning to main menu.')
    #passwordFile.close()
    return False


"""
Function Name:
    check_admin_input
Input:
    gets list of categories, list with product and price and the main dictionary store.
Output:
    function return True or False
Function Operation:
    the function gets is the admin input legal
"""
def check_admin_input(categories, theProduct, store):
    #check the we have product and price
    if len(theProduct) < 2:
        print('Error: not enough data.')
        return False
    #checks that all the categories exist
    for keys in range(len(categories)):
        if categories[keys] not in store.keys():
            print('Error: one of the categories does not exist.')
            return False
    #checks if the price legal
    if theProduct[1] < '0' or theProduct[1].isdigit() == False:
        print('Error: price is not a positive integer.')
        return False
    return True


"""
Function Name:
    remove_spaces
Input:
    gets list of categories and list of product name and his price
Output:
    doesnt return a value
Function Operation:
    the function go over the 2 lists in for loop and remove all the 
    spaces in each index
"""
def remove_spaces(categories, theProduct):
    for i in range(len(categories)):
        categories[i] = categories[i].lstrip()
    for i in range(len(theProduct)):
        theProduct[i] = theProduct[i].lstrip()


"""
Function Name:
    insert_or_update_items
Input:
     function gets the store dictionary and the dictionary of the cache system.
Output:
    doesnt return a value
Function Operation:
    the function gets the user input and and the product to the 
    categories that the admin ask if all the data is legal.
"""
def insert_or_update_items(store, saveAnswers):
    adminInput = input()
    if ':' not in adminInput:
        print('Error: not enough data.')
        return
    #split all the admin input to check that all data legal
    adminRequest = adminInput.split(':')
    categories = adminRequest[0].split(',')
    theProduct = adminRequest[1].split(',')
    remove_spaces(categories, theProduct)
    if not check_admin_input(categories, theProduct, store):
        return
    #add/update the product to the categories
    for i in range(len(categories)):
        store[categories[i]][theProduct[0]] = theProduct[1]
    #change the price in all the categories that the product apear.
    for key in store.keys():
       if theProduct[0] in store[key]:
           store[key][theProduct[0]] = theProduct[1]
    print('Item', '"' + theProduct[0] + '"', 'added.')
    #clear all the cache system after adding/updating new product
    saveAnswers.clear()
    

"""
Function Name:
    print_admin_menu
Input:
    doest get any parameters
Output:
    return the admin choice
Function Operation:
    the function print the admin menu or error message if the 
    admin choine ilegal.
"""
def print_admin_menu():
    adminChoice = input('Admin panel:\n\t0. Return to main menu.\n\t1. Insert or update an item.\n\t2. Save.\n')
    #checks if the admin choice is legal
    if '0' <= adminChoice <= '2':
        return adminChoice
    print('Error: unrecognized operation.')
    return adminChoice


"""
Function Name:
    save_store_in_file
Input:
    gets the store dictionary
Output:
    doesnt return a value
Function Operation:
    the function puts inside a string every category and his products
    and write every string to a file.
"""
def  save_store_in_file(store):
    str1 = ''
    sortedDict = {}
    sortedCategories = sorted(store.keys())
    #2 for loop that put the category and products in a string, than into the file
    for key in range(len(sortedCategories)):
        str1 += sortedCategories[key] + ':'
        sortedProducts = sorted(store[sortedCategories[key]].keys())
        for product in range(len(sortedProducts)):
            str1 += ' ' + sortedProducts[product] + ', ' + store[sortedCategories[key]][sortedProducts[product]] + ';'
        str1 += '\n'
    #add the line to the file
    with open(OUTPUT_FILE, "w+") as storeFile:
        storeFile.write(str1)
        print('Store saved to', '"' + OUTPUT_FILE + '".')


"""
Function Name:
    admin_panel
Input:
    function gets the store dictionary and the dictionary of the cache system.
Output:
    doesnt return a value
Function Operation:
    the function manage the admin panel and send 
    us to the right function according the admin choice.
"""
def admin_panel(store, saveAnswers):
    #first, ask for password
    if ask_for_password() == False:
        return
    #print the admin panel menu
    adminChoice =print_admin_menu()
    #while loop that keep the admin in the panel until he choosing 0(exit)
    while True:
        if adminChoice == '0':
            return
        elif adminChoice == '1':
            insert_or_update_items(store, saveAnswers)
        elif adminChoice == '2':
            save_store_in_file(store)
        adminChoice = print_admin_menu()


"""
Function Name:
    main
Input:
    doestn gets parameters
Output:
    doesnt return a value
Function Operation:
    the function manage all the program functions, we send from here 
    the data for the right function according the user choice.
"""
def main():
    saveAnswers = {}
    #first, read the store data from a file
    with open(STORE_FILE, "r") as store_file:
        store = get_store_products(store_file)
    #print the user menu
    userChoice = print_menu()
    #while loop keep the user in the store until he choose 0(exit)
    while True:
        if userChoice == '0':
            return
        elif userChoice == '1':
            query_by_category(store, saveAnswers)
        elif userChoice == '2':
            query_by_item(store, saveAnswers)
        elif userChoice == '3':
            purchase_an_item(store, saveAnswers)
        elif userChoice == '4':
            admin_panel(store, saveAnswers)
        userChoice = print_menu()


if __name__ == '__main__':
    STORE_FILE = sys.argv[1]
    ADMIN_PASSWORD_FILE = sys.argv[2]
    OUTPUT_FILE = sys.argv[3]
    main()
  
   
 

    