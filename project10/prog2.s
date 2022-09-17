# Name: Changlin Jiang
# TerpConnect login ID: jiangcl
# university ID: 117243543
# Discussion section number: 0102
#
# This program reads an integer into a global variable number. The golobal 
# variables number is passed into the parameter n of the function jacobsthal(),
# which returns the n'th Jacobsthal number. 
# The function jacobsthal() calls another function helper(), which helps 
# jacobsthal() to get the result.
# The value returned by jacobsthal() is stored in the global variable result 
# in main(), and the result will be printed, followed by a newline.


        .data
number: .word 0
result: .word 0

        .text
main:   li    $sp, 0x7ffffffc        # main
        
        li    $v0, 5                 # scanf("%d", &number)
        syscall
        sw    $v0, number
        move  $t0, $v0
        
        sw    $t0, ($sp)             # push argument number onto the stack
        sub   $sp, $sp, 4
        
        jal   jaco                   # call jacobsthal
        
        add   $sp, $sp, 4            # pop argument from stack
        
        sw    $v0, result            # result = jacobsthal(number)
        
        lw    $t1, result
        li    $v0, 1                 # printf("%d\n", result)
        move  $a0, $t1
        syscall
        li    $v0, 11
        li    $a0, 10
        syscall
        
        li    $v0, 10                # return 0
        syscall
        
                                     # ans = 16($sp) 
                                     # prev = 12($sp) 
                                     # temp = 8($sp) 
                                     # i = 4($sp) 
                                     # n = 4($fp)
                                     # prologue
jaco:   sub   $sp, $sp, 24           # set new stack pointer
        sw    $ra, 24($sp)           # save return address in stack
        sw    $fp, 20($sp)           # save old frame pointer in stack
        add   $fp, $sp, 24           # set new frame pointer
        
        lw    $t0, 4($fp)            # get value of argument
        
        lw    $t1, 16($sp)           # get local variables
        lw    $t2, 12($sp)
        lw    $t3, 8($sp)
        lw    $t4, 4($sp)
        
        li    $t1, -1                # ans = -1
        sw    $t1, 16($sp)
        
        bltz  $t0, end               # jump to end if n < 0
        
        beqz  $t0, label             # jump to label if n == 0 or n == 1
        beq   $t0, 1, label        

        li    $t1, 1                 # ans = 1
        sw    $t1, 16($sp)
        
        li    $t2, 0                 # prev = 0
        sw    $t2, 12($sp)
        
        j     start
label:  sw    $t0, 16($sp)           # ans = n
        lw    $t1, 16($sp)
        j     end

start:  lw    $t4, 4($sp)            # i= 2
        li    $t4, 2
        sw    $t4, 4($sp)
        
loop:   bgt   $t4, $t0, end          # end the loop if i>n
        
        sw    $t2, ($sp)             # push 1st argument onto the stack
        sub   $sp, $sp, 4
        
        sw    $t1, ($sp)             # push 2nd argument onto the stack
        sub   $sp, $sp, 4
        
        jal   helper
        
        add   $sp, $sp, 8            # pop both arguments from stack
        
        sw    $v0, 8($sp)            # temp = helper(prev, ans)       
        lw    $t3, 8($sp)
        

        sw    $t1, 12($sp)           # prev = ans
        lw    $t2, 12($sp) 

        sw    $t3, 16($sp)           # ans = temp
        lw    $t1, 16($sp) 
        
        add   $t4, $t4, 1            # i++
        sw    $t4, 4($sp)
        
        j     loop                   # jump back to loop statement
        
end:    move  $v0, $t1               # return ans  
      
                                     # epilogue
        lw    $ra, 24($sp)           # load return address from stack
        lw    $fp, 20($sp)           # restore old frame pointer from stack
        add   $sp, $sp, 24           # reset stack pointer
        jr    $ra                    # return to caller using saved return 
                                     # address



                                     # prologue
helper: sub   $sp, $sp, 8            # set new stack pointer
        sw    $ra, 8($sp)            # save return address in stack
        sw    $fp, 4($sp)            # save old frame pointer in stack
        add   $fp, $sp, 8            # set new frame pointer
 
        lw    $t5, 8($fp)            # 2 * x + y
        lw    $t6, 4($fp)      
        mul   $t5, $t5, 2
        add   $t5, $t5, $t6
        
        move  $v0, $t5               # return 2 * x + y
 
                                     # epilogue
        lw    $ra, 8($sp)            # load return address from stack
        lw    $fp, 4($sp)            # restore old frame pointer from stack
        add   $sp, $sp, 8            # reset stack pointer
        jr    $ra                    # return to caller using saved return 
                                     # address
 