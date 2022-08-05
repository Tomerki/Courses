# Tomer Hadar   
       .file	"main2.c"
	.text
	.globl	even
	.type	even, @function
even:
    movq %rsi,%rcx  #puts rsi value(i) in rcx because salq command work with part of rcx(cl).
    salq %cl,%rdi   #left shift to A[i] i times(A[i] << i).
    xorq %rax,%rax  #initialize rax with 0 to put inside the return value. 
    movq %rdi,%rax  #puts inside rax the return value.
    ret
.LFE23:
	.size	even, .-even
	.globl	go
	.type	go, @function
go:
    #get as arguments an array of 10 ints inside rdi.
    movq $0,%rbx    #initialize rbx with 0. same as i=0.
    movq $0,%r12    #initialize r12 with 0 for the sum. same as sum=0.
    jmp .L2         #directed jump to .L2 label.
.L2:
    cmpq $10,%rbx   #compare between i(inside rbx) to 10.
    jl .L1          #conditinal jump - if i < 10, jump to label .L1.
    movq %r12,%rax  #puts the return value(sum) inside rax.
    ret
.L1:
    leaq (%rdi,%rbx,4),%r13     #puts in r13 the address of A[i]. multiply rbx(i) with 4 because int is 4 bytes.
    movl (%r13),%eax            #puts the value inside the address in r13 inside eax.
    andq $1,%rax                #rax & 1 tells us if inside rax there is an even number. (A[i] % 2).
    cmpq $0,%rax                #if rax value is 0 so the number was even, else, it was odd.
    je .L3                      #jump to .L3 label if rax value equal to 0.
    xorq %r14,%r14              #intialize r14 with 0.
    leaq (%rdi,%rbx,4),%r14     #puts inside r14 the adderss of A[i].
    addq (%r14),%r12            #puts the value inside the address in r14 inside r12.
    incq %rbx                   #promote by 1 the value in rbx (i).
    jmp .L2                     #directed jump to .L2 label.
.L3:
    movq %rdi,%r11              #save rdi value inside r11.
    movq %rbx,%rsi              #puts inside rsi the value of rbx(i).
    xorq %rdi,%rdi              #initialize rdi with 0 after saving his real value because we pass parameters in rdi.
    leaq (%r11,%rbx,4),%rdi     #puts inside rdi the address of A[i].
    movl (%rdi),%ecx            #puts inside ecx the value(A[i]) inside the address in rdi.
    movq %rcx,%rdi              #puts inside rdi the value of A[i].
    call even                   #call even function after puting the arguments inside rdi(first arg) and rsi(second arg).
    movq %r11,%rdi              #recover rdi to his real value before we called evem function.
    addq %rax,%r12              #add the returning value of even function to r12(sum).
    incq %rbx                   #promote by 1 the value in rbx (i).
    jmp .L2                     #directed jump to .L2.
