	#207651027 Tomer Hadar
.section .rodata
#formats for printing the right message every case.
format_char: .string " %c"
format_get_length:  .string "first pstring length: %d, second pstring length: %d\n"
format_replce:  .string "old char: %c, new char: %c, first string: %s, second string: %s\n"
format_copy_swap:  .string "length: %d, string: %s\n"
format_compare: .string "compare result: %d\n"
format_int_len: .string "%d"
format_invalid1: .string "invalid option!\n"

#resets the address to be doubles of eight
.align 8
#swith case that according to the user option we know to which case in the table to go.
.switch_case:
    .quad .get_length_50_60     #cases 50,60
    .quad .defult               #defult case
    .quad .replace_char_52      #case 52
    .quad .pstr_cpy_index_53    #case 53
    .quad .swap_case_54         #case 54
    .quad .pstr_cmp_index_55    #case 55
    .quad .defult               #defult case
    .quad .defult               #defult case
    .quad .defult               #defult case
    .quad .defult               #defult case
    .quad .get_length_50_60     #cases 50,60



.text
.globl run_func
.type run_func, @function
#first parameter: inside rdi a pointer for the first pstring.
#second parameter: inside rsi a pointer for the second pstring.
#third parameter: inside rdx the option that the user pick.
run_func:
    pushq   %rbp                            #saving the last rbp address value for opening new scope.
    movq    %rsp, %rbp                      #getting rsp to where rbp found at.(both rsp and rbp point for the same address on the stack)
    leaq    -50(%rdx), %rcx                 #subtracting 50 from rdx(which old the number of option that the user pick).
    cmpq    $10, %rcx                       #check if the option less or equal then 10.
    jle     .check_zero                     #if option less then 10- we check if its greater or equal to 0.
    jmp     .defult                         #if the option above 10 we going fot defult case.
#label that checks that the option greater ot equal to 0.
.check_zero:
    cmpq    $0, %rcx                        #compares between the option number to 0.
    jl      .defult                         #if the option less then 0 we go to defult case.
    jmp     *.switch_case(,%rcx,8)          #if the option greater or equal to 0 and less or equal then 10 we jump to it on the table.
                                            #we subtracting 50 from the user option because its between 50-60, so in this way we can 
                                            #jumping by multiplication of the ((option numer)-50) by 8 and go th the right case.
#case 60 or 50
.get_length_50_60:
    call    pstrlen                         #geting the length of the first pstring.(inside rdi we already have the first pstring address)
    xorq    %rdi, %rdi                      #resets rdi for puting inside it the second pstring address and sending it to pstrlen.
    movq    %rax, %r8                       #saving inside r8 the first pstring length.
    leaq    (%rsi), %rdi                    #puts the address of the second pstring inside rdi
    call    pstrlen                         #calling pstrlen for getting the length of the second pstring.
    movq    %rax, %rdx                      #pass the length that pstrlen returned into rdx.
    movq    %r8, %rsi                       #pass into rsi the first pstring length.
    movq    $format_get_length, %rdi        #pass to rdi the format which we want to print according to it.(after sets all the parameters to the right registers)
    xorq    %rax, %rax                      #resets rax before calling printf.
    call    printf                          #calling printf.
    xorq    %rax, %rax                      #resets rax for finishing the program with right exit code.
    
    leave                                   #poping rbp to rbp for returning the original state.
    ret                                     #returning to the function that called us.
    
#case 52.
.replace_char_52:
    subq    $32, %rsp                       ##allocating 32(for aligment) bytes for the user input.
    push    %r12                            #r12 its a callee save, so before we using it we has to save its value by pushing it to the stack.
    push    %r13                            #r13 its a callee save, so before we using it we has to save its value by pushing it to the stack.
    leaq    (%rdi), %r12                    #saving the first pstring address inside r12.
    leaq    (%rsi), %r13                    #saving the first pstring address inside r13.
    movq    $format_char, %rdi              #pass rdi format for getting a single char from the user.
    leaq    -32(%rbp), %rsi                 #pass rsi the address in the stack which we want to store the user input.
    xorq    %rax, %rax                      #resets rax before calling scanf.
    call    scanf                           #calling scanf after sets all the parameters in the right registers. (reciving the char that we want to replace)
    
    movq    $format_char, %rdi              #pass rdi format for getting a single char from the user.
    leaq    -16(%rbp), %rsi                 #pass rsi the address in the stack which we want to store the user input.
    xorq    %rax, %rax                      #resets rax before calling scanf.
    call    scanf                           #calling scanf after sets all the parameters in the right registers. (reciving the new char).
        
    leaq    -32(%rbp), %r11                 #save in r11 the old char.
    xorq    %rsi,%rsi                       #resets rsi because we want to pass it a single byte.
    movb    (%r11), %sil                    #pass from r11 to sil(first byte of rsi) the char that we want to replace.
    
    xorq    %r11, %r11                      #resets r11 after using it.
    leaq    -16(%rbp), %r11                 #save in r11 the new char.
    movb    (%r11), %dl                     #pass from r11 to dl(first byte of rdx) the new char.
    
    leaq    (%r12), %rdi                    #pass to rdi the first string address(as remembered we saved inside r12 that address)
    call    replaceChar                     #call the function after we set all the parameters.
    leaq    (%rax), %rcx                    #inside rax we have an pointer to the pstring after changing it, so we pass it to rcx.
    incq    %rcx                            #the first byte of pstring its the length, so we promote rcx to point on the string without the length.
    
    leaq    (%r13), %rdi                    #pass to rdi the second string address(as remembered we saved inside r13 that address)
    call    replaceChar                     #call the function after we set all the parameters.(the chars(old and new) still inside rsi and rdx because they caller save)
    leaq    (%rax), %r8                     #inside rax we have an pointer to the pstring after changing it, so we pass it to r8.
    incq    %r8                             #the first byte of pstring its the length, so we promote r8 to point on the string without the length.
    
    movq    $format_replce, %rdi            #puts inside rdi the right print format we want for printf function
    xorq    %rax, %rax                      #resets rax before calling printf.
    call    printf                          #calling printf with 5 parameters that we set in the conventions register according the order.
    
    popq    %r13                            #returning r13 its original value before return(as remember we push r13 value)
    popq    %r12                            #returning r12 its original value before return(as remember we push r12 value)
    addq    $32, %rsp                       #returning rsp to where it was before we allocate it memory.(return to rbp)
    leave                                   #poping rbp to rbp for returning the original state.
    ret                                     #returning to the function that called us.

#on this label we getting from the user two indexs and copy this range from second pstring to the first.
.pstr_cpy_index_53:
    subq    $32, %rsp                       #allocating 32(for aligment) bytes for the user input.
    push    %r12                            #r12 its a callee save, so before we using it we has to save its value by pushing it to the stack.
    push    %r13                            #r13 its a callee save, so before we using it we has to save its value by pushing it to the stack.
    leaq    (%rdi), %r12                    #saving the first pstring address inside r12.
    leaq    (%rsi), %r13                    #saving the second pstring address inside r13.
    
    movq    $format_int_len, %rdi           #pass to rdi the format for the first index input from the user.(the start index)
    leaq    -16(%rbp), %rsi                 #pass rsi the address in the stack which we want to store the user input.
    xorq    %rax, %rax                      #resets rax before calling scanf.  
    call    scanf                           #calling scanf after sets all the parameters in the right registers. (reciving the first index to start copy from it)
    
    movq    $format_int_len, %rdi           #pass to rdi the format for the second index input from the user.(the end index)
    leaq    -32(%rbp), %rsi                 #pass rsi the address in the stack which we want to store the user input.
    xorq    %rax, %rax                      #resets rax before calling scanf.  
    call    scanf                           #calling scanf after sets all the parameters in the right registers. (reciving the end index to end the copy in)
    
    leaq    -16(%rbp), %r11                 #save in r11 the old char.
    xorq    %rdx, %rdx                      #resets rdx because we want to pass it a single byte.
    movb    (%r11), %dl                     #pass from r11 to dl(first byte of rdx) the start index that we want to copy from it.
    
    xorq    %r11, %r11                      #resets r11 after using it.
    leaq    -32(%rbp), %r11                 #save in r11 the old char.
    xorq    %rcx, %rcx                      #resets rcx because we want to pass it a single byte.
    movb    (%r11), %cl                     #pass from r11 to cl(first byte of rcx) the end index that we want to finish the copy in.
    
    leaq    (%r12), %rdi                    #pass to rdi the first pstring address(as remembered we saved inside r12 that address)
    leaq    (%r13), %rsi                    #pass to rsi the second pstring address(as remembered we saved inside r13 that address)
    
    call    pstrijcpy                       #calling to the function to copy the indexs after we put all the parameters data in the right registers.
    
    movq    $format_copy_swap, %rdi         #puts inside rdi the right print format we want for printf function.(first parameter)
    xorq    %rsi, %rsi                      #resets rsi because we want to pass it a single byte.
    movb    (%r12), %sil                    #pass from r12 to sil(first byte of rsi) the string length.(as remembered we saved inside r12 the pstring address).(second parameter)
    leaq    1(%r12), %rdx                   #pass to rdx a pointer to the pstring by promoting the pstring by 1, for pointing the string.(third parameter)
    xorq    %rax, %rax                      #resets rax before calling printf.
    call    printf                          #calling printf with 3 parameters that we set in the conventions register according the order.
    
    movq    $format_copy_swap, %rdi         #puts inside rdi the right print format we want for printf function.(first parameter)
    xorq    %rsi, %rsi                      #resets rsi because we want to pass it a single byte.
    movb    (%r13), %sil                    #pass from r13 to sil(first byte of rsi) the string length.(as remembered we saved inside r13 the pstring address).(second parameter)
    leaq    1(%r13), %rdx                   #pass to rdx a pointer to the pstring by promoting the pstring by 1, for pointing the string.(third parameter)
    xorq    %rax, %rax                      #resets rax before calling printf.
    call    printf                          #calling printf with 3 parameters that we set in the conventions register according the order.
    
    popq    %r13                            #returning r13 its original value before return(as remember we push r13 value)
    popq    %r12                            #returning r12 its original value before return(as remember we push r12 value)
    addq    $32, %rsp                       #returning rsp to where it was before we allocate it memory.(return to rbp)
    leave                                   #poping rbp to rbp for returning the original state.
    ret                                     #returning to the function that called us.
    
#on this label we calling swapCase function and print the result.
.swap_case_54:
    leaq    (%rsi), %rbx                    #saving the address of the second pstring inside rbx
    call    swapCase                        #calling swapCase while inside rdi we got the address of the first pstirng as parameter.
    movq    $format_copy_swap, %rdi         #puts inside rdi the right print format we want for printf function.(first parameter)
    xorq    %rsi, %rsi                      #resets rsi because we want to pass it a single byte.
    movb    (%rax), %sil                    #pass from rax to sil(first byte of rsi) the string length.(as we know inside rax we got the returned value of swapcase).(second parameter)
    leaq    1(%rax), %rdx                   #pass to rdx a pointer to the first pstring by promoting the pstring address by 1, for pointing the string.(third parameter)
    xorq    %rax, %rax                      #resets rax before calling printf.
    call    printf                          #calling printf with 3 parameters that we set in the conventions register according the order.
    
    leaq    (%rbx), %rdi                    #as we know, inside rbx we saved the second pstring address, so we pass it to rdi.
    call    swapCase                        #calling swapCase while inside rdi we got the address of the second pstirng as parameter.
    movq    $format_copy_swap, %rdi         #puts inside rdi the right print format we want for printf function.(first parameter)
    xorq    %rsi, %rsi                      #resets rsi because we want to pass it a single byte.
    movb    (%rax), %sil                    #pass from rax to sil(first byte of rsi) the string length.(as we know inside rax we got the returned value of swapcase).(second parameter)
    leaq    1(%rax), %rdx                   #pass to rdx a pointer to the second pstring by promoting the pstring address by 1, for pointing the string.(third parameter)
    xorq    %rax, %rax                      #resets rax before calling printf.
    call    printf                          #calling printf with 3 parameters that we set in the conventions register according the order.
    
    leave                                   #poping rbp to rbp for returning the original state.
    ret                                     #returning to the function that called us.
  

.pstr_cmp_index_55:
    subq    $32, %rsp                       #allocating 32(for aligment) bytes for the user input.
    push    %r12                            #r12 its a callee save, so before we using it we has to save its value by pushing it to the stack.
    push    %r13                            #r13 its a callee save, so before we using it we has to save its value by pushing it to the stack.
    leaq    (%rdi), %r12                    #saving the first pstring address inside r12.
    leaq    (%rsi), %r13                    #saving the second pstring address inside r13.
    
    movq    $format_int_len, %rdi           #pass to rdi the format for the first index input from the user.(the start index for compare)
    leaq    -16(%rbp), %rsi                 #pass rsi the address in the stack which we want to store the user input.
    xorq    %rax, %rax                      #resets rax before calling scanf.
    call    scanf                           #calling scanf after sets all the parameters in the right registers. (reciving the first index to start compare from it)
    
    movq    $format_int_len, %rdi           #pass to rdi the format for the end index input from the user.(the end index for compare)         
    leaq    -32(%rbp), %rsi                 #pass rsi the address in the stack which we want to store the user input.
    xorq    %rax, %rax                      #resets rax before calling scanf.
    call    scanf                           #calling scanf after sets all the parameters in the right registers. (reciving the end index to end compare in it)
    
    leaq    -16(%rbp), %r11                 #save in r11 the start index.
    xorq    %rdx,%rdx                       #resets rdx because we want to pass it a single byte.
    movb    (%r11), %dl                     #pass from r11 to dl(first byte of rdx) the start index that we want to compare from it.
    
    xorq    %r11, %r11                      #resets r11 after using it.
    leaq    -32(%rbp), %r11                 #save in r11 the start index.
    xorq    %rcx, %rcx                      #resets rcx because we want to pass it a single byte.
    movb    (%r11), %cl                     #pass from r11 to cl(first byte of rcx) the end index that we want to compare until it.
    
    leaq    (%r12), %rdi                    #pass to rdi the first pstring address(as remembered we saved inside r12 that address)
    leaq    (%r13), %rsi                    #pass to rsi the second pstring address(as remembered we saved inside r13 that address)
    
    call    pstrijcmp                       #calling to the function to compare the string in the given indexs after we put all the parameters data in the right registers.
    
    movq    $format_compare, %rdi           #puts inside rdi the right print format we want for printf function.(first parameter)
    movq    %rax, %rsi                      #pass from rax to rsi the answer of pstrijcmp function.(as we know inside rax we got the returned value of pstrijcmp).(second parameter)
    xorq    %rax, %rax                      #resets rax before calling printf.
    call    printf                          #calling printf with 2 parameters that we set in the conventions register according the order.
    
    popq    %r13                            #returning r13 its original value before return(as remember we push r13 value)
    popq    %r12                            #returning r12 its original value before return(as remember we push r12 value)
    addq    $32, %rsp                       #returning rsp to where it was before we allocate it memory.(return to rbp)
    leave                                   #poping rbp to rbp for returning the original state.
    ret                                     #returning to the function that called us.
    

#defult label that we jump into if the user option not defined in one of the options above.         
.defult:
    movq    $format_invalid1, %rdi          #puts inside rdi the right print format we want for printf function.(first parameter)
    xorq    %rax, %rax                      #resets rax before calling printf.
    call    printf                          #calling printf with 1 parameter that we set in the conventions register according the order.
    leave                                   #poping rbp to rbp for returning the original state.
    ret                                     #returning to the function that called us.