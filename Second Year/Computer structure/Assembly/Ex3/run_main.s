	# Tomer Hadar
.section .rodata 
format_int_len: .string "%d"            #format for reciving a number from the user.
format_pstring: .string "%s"            #format for reciving a string from the user.

.text   
.globl run_main
.type run_main, @function
#this function get from the user two pstrings and an option for the jump table and then calling to run_func function with those parameters.
run_main:
    pushq   %rbp                        #open new scope by saving rbp value.
    movq    %rsp, %rbp                  #moving rsp to rbp for opening new frame.
    subq    $512, %rsp                  #allocate memory for the function variable.
    
    movq    $format_int_len, %rdi       #pass to rdi the format for the input from the user.
    leaq    -512(%rbp), %rsi            #puts inside rsi the address in the stack which we want to get into it the string length.
    xorq    %rax, %rax                  #resets rax register before calling scanf
    call    scanf                       #call scanf after puts arguments in rdi(first parameter) and rsi(second parameter)
    
    movq    $format_pstring, %rdi       #pass to rdi the format for the input from the user.
    leaq    -511(%rbp), %rsi            #puts inside rsi the address in the stack thath we want to get into it the string, which its one byte above the string length. 
    xorq    %rax, %rax                  #resets rax register before calling scanf
    call    scanf                       #call scanf after puts arguments in rdi(first parameter) and rsi(second parameter)
    
    movq    $format_int_len, %rdi       #pass to rdi the format for the input from the user
    leaq    -256(%rbp), %rsi            #puts inside rsi the address in the stack which we want to get into it the second string length.
    xorq    %rax, %rax                  #resets rax register before calling scanf.
    call    scanf                       #call scanf after puts arguments in rdi(first parameter) and rsi(second parameter)
    
    movq    $format_pstring, %rdi       #pass to rdi the format for the input from the user.
    leaq    -255(%rbp), %rsi            #puts inside rsi the address in the stack thath we want to get into it the string, which its one byte above the string length. 
    xorq    %rax, %rax                  #resets rax register before calling scanf
    call    scanf                       #call scanf after puts arguments in rdi(first parameter) and rsi(second parameter)
    
    movq    $format_int_len, %rdi       #pass to rdi the format for the input from the user.
    subq    $16, %rsp                   #allocate another 16 bytes for option in the switch case(allocate 16 for aligment).
    leaq    -520(%rbp), %rsi            #pass to rsi the address on the stack which we want to store there the user input.
    xorq    %rax, %rax                  #resets rax register before calling scanf
    call    scanf                       #call scanf after puts arguments in rdi(first parameter) and rsi(second parameter).
    
    #sets the parameters in the right registers before calling run_func.
    leaq    -512(%rbp), %rdi            #pass the first pstring to rdi.
    leaq    -256(%rbp), %rsi            #pass the second pstring to rsi.
    xorq    %rdx, %rdx                  #resets rdx before puts inside a number of single byte.
    movb    -520(%rbp), %dl             #pass to dl(which its the first byte of rdx) the option that the user pick.
    
    call    run_func                    #calling the function after all the parameters in the right register as required by the conventions.
    
    addq    $528, %rsp                  #returning rsp to where it was before we allocate it memory.(return to rbp)
    xorq    %rax, %rax                  #resets rax for finishing the program with right exit code.
    leave                               #poping rbp to rbp for returning the original state.
    ret                                 #returning to the function that called us.
