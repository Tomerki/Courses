	# Tomer Hadar
.section .rodata 
format_invalid: .string "invalid input!\n"
.text


#label for pstrijcpy function and pstrijcmp function in case we got an invaild input
.invalid_input:
    xorq    %rdi, %rdi
    movq    $format_invalid, %rdi
    xorq    %rax, %rax
    call    printf                      #calling printf after pass all the parameters we need.
    xorq    %rax, %rax
    movq    $-2, %rax                   #puts inside rax the value -2 that indicates that pstrijcmp got an invalid input.
    ret

.globl pstrlen
.type pstrlen, @function
#parameter one: inside rdi we recived the address for the pstring that we want its length.
pstrlen:
    xorq    %rax, %rax                  #resets rax because we want to pass it a single byte.
    movb    (%rdi), %al                 #puts inside al(first byte of rax) the pstring length.
    ret                                 #returning the function that called us.
    
    
.globl replaceChar
.type replaceChar, @function
#parameter one: pointer to string inside %rdi. 
#parameter two: oldChar inside %rsi.
#parameter three: newChar inside %rdx
#this function replace each instance of the old char in the new char that we recive as parameters in rsi and rdx respectively.
replaceChar:
    call    pstrlen                     #get string size inside rax.
    xorq    %r8, %r8                    #initialize conter in r8.

.check_Equal:
    incq    %rdi                        #promote the address inside rdi by 1 to point on the string itself without the length.
    xorq    %r11, %r11                  #resets r11 because we want to pass it a single byte.
    movb    (%rdi), %r11b               #puts inside r11b(first byte of r11) the first char in the string.
    cmpq    %r11, %rsi                  #compare the first string char(in r11) to the old char that we want to replace(inside rsi).
    je      .switch_Chars               #if the two chars are equal(according the ascii value), we switch the old char to the new char.
    incq    %r8                         #promote the counter by 1 for next iteration.
    cmpq    %rax, %r8                   #in rax we have the string length so we compare it to our counter to know if we finish to scanning all the string.
    jle     .check_Equal                #if the counter still less or equal to the string length we keep to check the next char.
    decq    %rdi                        #if the counter greater then the string length we return rdi to point on the start of the pstring
    jmp     .finish_replace             #if the counter greater then the string length we finish the loop.    

.finish_replace:                      
    subq    %rax, %rdi                  #return the pointer to the start of the pstring.
    xorq    %rax, %rax                  #resets rax.
    leaq    (%rdi), %rax                #puts inside rax the returned value(new string after changing it).
    ret                                 #returning the function that called us.
#on this label we make the replace of the old char in the new one.    
.switch_Chars:
    movb    %dl, (%rdi)                 #replace  a single byte from rdi to the byte inside dl(first byte of rdx)
    incq    %r8                         #promoting our counter.
    cmpq    %rax, %r8                   #check if we finishing go over all the string.
    je      .finish_replace             #if the counter and the length equal we finish.             
    jmp     .check_Equal                #else, we keep checking by continue our loop that last as the string length times.

    

.globl pstrijcpy
.type pstrijcpy, @function
#parameter one: pointer to dest inside %rdi. 
#parameter two: pointer to src inside %rsi, 
#parameter three: start index in %rdx(i).
#parameter four: end index in %rcx(j).
pstrijcpy:
    cmpq    %rdx, %rcx                  #check that the end index(in %rcx) is greater or equal to the start index(in %rdx)
    jl      .invalid_input              #if start index greater then the end index we go to error label.
    movq    %rdi, %r8                   #save the address of dest string in %r8
    xorq    %rdi, %rdi                  #resets rdi.
    leaq    (%rsi), %rdi                #puts inside rdi the sourc pstring to get its length.
    call    pstrlen                     #get the src string length in %rax
    cmpq    %rcx, %rax                  #checks that the indexs that the user enter inside the second string limits.
    jle     .invalid_input              #if there is an exception we go to error label.
    xorq    %rdi, %rdi                  #resets rdi.
    movq    %r8, %rdi                   #as we know we saved in r8 the first pstring(dest) adress, so we pass it to rdi.
    call    pstrlen                     #get the dest string length in %rax
    cmpq    %rcx, %rax                  #checks that the indexs that the user enter inside the first string limits.      
    jle     .invalid_input              #if there is an exception we go to error label.
    
    incq    %rdi                        #promote the address in rdi by 1 for pointing the string itself without the length.
    incq    %rsi                        #promote the address in rsi by 1 for pointing the string itself without the length.
    addq    %rdx, %rdi                  #promote the address in rdi by the index that we want to start copy from it.
    addq    %rdx, %rsi                  #promote the address in rsi by the index that we want to start copy from it.
    jmp     .start_copy                 #go to label to start the loop of copy.
#in this label we start the copy loop.
.start_copy:
    xorq    %r8, %r8                    #resets r8 because we want to pass it a single byte.
    movb    (%rsi), %r8b                #pass from rsi address value 1 byte to r8b.(the first char to copy)
    movb    %r8b, (%rdi)                #copy the char inside r8b to the dest string(inside rdi).
    incq    %rdi                        #promote rdi to the next char.
    incq    %rsi                        #promote rsi to the next char.
    incq    %rdx                        #promote by 1 the index that we check.
    cmpq    %rdx, %rcx                  #check if the start index greater then the end index.
    jl      .finish_copy                #if it is, we finish to copy from index i to index j ang go to finish label.
    jmp     .start_copy                 #else, we go for the next iteration and keep on copy.
#in this label we finishing the copy and puts the return value inside rax.
.finish_copy:
    decq    %rdi                        #returning rdi to point to the start of the pstring.
    subq    %rdx, %rdi                  #returning rdi to point to the start of the pstring.
    leaq    (%rdi), %rax                #puts the return value inside rax.
    ret
                      
    
.globl swapCase
.type swapCase, @function
#pointer to pstring inside %rdi
swapCase:
    call    pstrlen                     #get inside %rax the string length
    xorq    %r8, %r8                    #initialize conter in r8.
    incq    %rdi                        #promote rdi by 1 for point on the string withot the length.
    jmp     .check_letter_range         #start the loop of changing the case-letter.

.check_letter_range:
    xorq    %r11, %r11                  #resets r11 because we want to pass it a single byte.
    movb    (%rdi), %r11b               #puts inside r11b(first byte of r11) the first char in the string.
    cmpq    $90, %r11                   #check if the ascii value of the char in r11 less or equal to 90(90=Z).
    jle     .check_upper_case           #if it is, maybe its an upper case, so we go to label that checks it.
    cmpq    $122, %r11                  #else, we check if its less or equal then 122(122=z).
    jle     .check_lower_case           #if it is, maybe its an lower case, so we go to label that checks it.
    jmp     .promote                    #else, we know that its not even a letter, so we jump to promote label.
    
.check_upper_case:
    cmpq    $65, %r11                   #check if the ascii value of the char in r11 greater or equal to 65(65=A).
    jge     .change_to_lower_case       #if it is, we changing it to lower case.
    jmp     .promote                    #else, jump to promote label.(not a letter)

.check_lower_case:
    cmpq    $97, %r11                   #check if the ascii value of the char in r11 greater or equal to 97(97=a).
    jge     .change_to_upper_case       #if it is, we changing it to upper case.
    jmp     .promote                    #else, jump to promote label.(not a letter)

.change_to_lower_case:
    addq    $32, (%rdi)                 #add 32 to an upper case make it a lower case.
    jmp     .promote                    #then jump to promote.

.change_to_upper_case:
    subq    $32, (%rdi)                 #subtract 32 from lower case make it an upper case letter.
    jmp     .promote                    #then jump to promote.
#in this label we promote the counter and the pointer to the string by 1.
.promote:
    incq    %rdi                        #promote the pointer to point on the next char in the string.
    incq    %r8                         #promote the counter by 1.
    cmpq    %rax, %r8                   #if the counter value is less then the string length, we keep the loop.
    jl      .check_letter_range         #keep the loop if counter less then string length.
    jmp     .finish_case_change         #else, we know that we had scan all the string and go to finish label.

.finish_case_change:
    decq    %rdi                        #returning rdi to point to the start of the pstring.
    subq    %rax, %rdi                  #returning rdi to point to the start of the pstring.
    xorq    %rax, %rax                  #resets rax before puts in it the return value.
    movq    %rdi, %rax                  #puts the return value inside rax.
    ret



.globl pstrijcmp
.type pstrijcmp, @function
#parameter one: pointer to pstring1 inside %rdi. 
#parameter two: pointer to pstring2 inside %rsi. 
#parameter three: start index in %rdx(i).
#parameter four: end index in %rcx(j).
pstrijcmp:
    cmpq    %rdx, %rcx                  #check that the end index(in %rcx) is greater or equal to the start index(in %rdx)
    jl      .invalid_input              #if start index greater then the end index we go to error label.
    xorq    %rax, %rax                  #resets rax because we want to pass it a single byte.                  
    movb    (%rdi), %al                 #puts inside al(first byte of rax) the first string length.
    cmpq    %rcx, %rax                  #checks that the indexs that the user enter inside the first string limits.
    jle     .invalid_input              #if there is an exception we go to error label.
    xorq    %rax, %rax                  #resets rax because we want to pass it a single byte. 
    movb    (%rsi), %al                 #puts inside al(first byte of rax) the second string length.
    cmpq    %rcx, %rax                  #checks that the indexs that the user enter inside the second string limits.      
    jle     .invalid_input              #if there is an exception we go to error label.
    
    incq    %rdi                        #promote the address in rdi by 1 for pointing the string itself without the length.
    incq    %rsi                        #promote the address in rsi by 1 for pointing the string itself without the length.
    addq    %rdx, %rdi                  #promote the address in rdi(first string) by the index that we want to start compare from it.
    addq    %rdx, %rsi                  #promote the address in rsi(second string) by the index that we want to start compare from it.
    jmp     .compare                    #start to compare between the sub-strings in a loop.
    
.compare:
    xorq    %r8, %r8                    #resets r8 because we want to pass it a single byte.
    movb    (%rdi), %r8b                #puts inside r8b(first byte of r8) the char to compare from the first string.
    xorq    %r9, %r9                    #resets r9 because we want to pass it a single byte.
    movb    (%rsi), %r9b                #puts inside r9b(first byte of r9) the char to compare from the second string.
    cmpb    %r8b, %r9b                  #compare between the two chars.
    je      .next                       #if the chars equal we go to next label for promote the variables and keep with the loop.
    jl      .first_greater              #if the first greater, we go to label that finish the loop and set the right return value.
    jg      .second_greater             #if the first smaller, we go to label that finish the loop and set the right return value.
#next label rule its to promote the value of the pointers string and check if we can end or that we finish to go over the sub-strings.
.next:
    incq    %rdi                        #promote the pointer of the first string by 1 to point the next char.
    incq    %rsi                        #promote the pointer of the second string by 1 to point the next char.
    incq    %rdx                        #promote our index.
    cmpq    %rcx, %rdx                  #if the start index less or equal to the end index we keep the loop.
    jle     .compare                    #keeping the loop with conditinal jump.
    jmp     .equal                      #else, we know that we finish and return that the string equal.
#in this label we puts in rax value of 0 that indicates on equality of the strings.
.equal:
    xorq    %rax, %rax
    movq    $0, %rax
    ret
 #in this label we puts in rax value of 1 that indicates that the first string greater.(come after the second string on the dictionary). 
.first_greater:
    xorq    %rax, %rax
    movq    $1, %rax
    ret
#in this label we puts in rax value of 1 that indicates that the first string greater.(come after the second string on the dictionary). 
.second_greater:
    xorq    %rax, %rax
    movq    $-1, %rax
    ret
