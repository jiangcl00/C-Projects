# Name: Changlin Jiang
# TerpConnect login ID: jiangcl
# university ID: 117243543
# Discussion section number: 0102
#
# This program reads three integers from the input, store them into the global
# variables length, width and height, and this program prints out the surface 
# area of the rectangular prism with sides length, width, and height(followed
# by a newline).


        .data
length: .word 0
width:  .word 0
height: .word 0
ans:    .word 0

        .text
main:   li    $sp, 0x7ffffffc        # main
        li    $t0, -1                # ans = -1
        sw    $t0, ans
        
        li    $v0, 5                 # scanf("%d", &length)
        syscall
        sw    $v0, length
        move  $t1, $v0
        
        li    $v0, 5                 # scanf("%d", &width)
        syscall
        sw    $v0, width
        move  $t2, $v0
        
        li    $v0, 5                 # scanf("%d", &height)
        syscall
        sw    $v0, height
        move  $t3, $v0
        
        blez  $t1, endif             # jump to endif if length <= 0
        blez  $t2, endif             # jump to endif if width <= 0
        blez  $t3, endif             # jump to endif if height <= 0
        
        mul   $t0, $t2, $t1          # width * length
        mul   $t1, $t1, $t3          # length * height
        add   $t0, $t0, $t1          # width * length + length * height
        mul   $t1, $t2, $t3          # width * height
        add   $t0, $t0, $t1          # width * length + length * height 
                                     # + width * height
        
        mul   $t0, $t0, 2            # ans = 2 * (width * length 
                                     # + length * height + width * height)
        sw    $t0, ans
        
endif:  li    $v0, 1                 # printf("%d\n", ans)
        move  $a0, $t0
        syscall
        li    $v0, 11
        li    $a0, 10
        syscall
        
        li    $v0, 10                # return 0
        syscall