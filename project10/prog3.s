# Name: Changlin Jiang
# TerpConnect login ID: jiangcl
# university ID: 117243543
# Discussion section number: 0102
#
# This program reads an integer into a global variable number. The golobal 
# variables number is passed into the parameter n of the function jacobsthal(),
# which returns the n'th Jacobsthal number. 
# The function jacobsthal() is a recursive function that calls itself 
# recursively and returns 0 or 1 for base cases 0 or 1.
# The value returned by jacobsthal() is stored in the global variable result 
# in main(), and the result will be printed, followed by a newline.


        .data
number: .word 0
result: .word 0

        .text
main:   li    $sp, 0x7ffffffc              # main
        
        li    $v0, 5                       # scanf("%d", &number)
        syscall
        sw    $v0, number
        move  $t0, $v0
        
        sw    $t0, ($sp)                   # push argument number onto the stack
        sub   $sp, $sp, 4
        
        jal   jacobsthal                   # call jacobsthal
        
        add   $sp, $sp, 4                  # pop argument from stack
        
        sw    $v0, result                  # result = jacobsthal(number)
        
        lw    $t1, result
        
        li    $v0, 1                       # printf("%d\n", result)
        move  $a0, $t1
        syscall
        li    $v0, 11
        li    $a0, 10
        syscall
        
        li    $v0, 10                      # return 0
        syscall
                                      
                                           # ans = 12($sp) 
                                           # temp1 = 8($sp) 
                                           # temp2 = 4($sp) 
                                           # n = 4($fp)
                                           # prologue
jacobsthal:   sub   $sp, $sp, 20           # set new stack pointer
              sw    $ra, 20($sp)           # save return address in stack
              sw    $fp, 16($sp)           # save old frame pointer in stack
              add   $fp, $sp, 20           # set new frame pointer
        
              lw    $t0, 4($fp)            # get value of argument
        
        
              li    $t1, -1                # ans = -1
              sw    $t1, 12($sp)
        
              bltz  $t0, end               # jump to end if n < 0
        
              beqz  $t0, label             # jump to label if n == 0 or n == 1
              beq   $t0, 1, label        
              
              sub   $t4, $t0, 2            # push argument onto the stack
              sw    $t4, ($sp)             # push argument onto the stack
              sub   $sp, $sp, 4
        
              jal   jacobsthal             # call jacobsthal
        
              add   $sp, $sp, 4            # pop both arguments from stack
        
              sw    $v0, 8($sp)            # temp1= 2  jacobsthal(n - 2)       
              lw    $t2, 8($sp)
              mul   $t2, $t2, 2
              sw    $t2, 8($sp)
              
              lw    $t0, 4($fp)
              sub   $t4, $t0, 1            # push argument onto the stack
              sw    $t4, ($sp)
              sub   $sp, $sp, 4
        
              jal   jacobsthal             # call jacobsthal
        
              add   $sp, $sp, 4            # pop both arguments from stack
        
              sw    $v0, 4($sp)            # temp2= jacobsthal(n - 1)     
              lw    $t3, 4($sp)
        
              lw    $t2, 8($sp)
              
              add   $t1, $t2, $t3          # ans= temp1 + temp2
              sw    $t1, 12($sp) 
        
              j     end
              
label:        sw    $t0, 12($sp)           # ans = n
              lw    $t1, 12($sp) 


        

        
end:          move  $v0, $t1               # return ans  
      
                                           # epilogue
              lw    $ra, 20($sp)           # load return address from stack
              lw    $fp, 16($sp)           # restore old frame pointer from
                                           # stack
              add   $sp, $sp, 20           # reset stack pointer
              jr    $ra                    # return to caller using saved return
                                           # address

