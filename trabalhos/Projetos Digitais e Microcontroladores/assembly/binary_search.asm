        addi sp, sp, -1
main:
        addi a0, zero, arr ; &arr
        addi a1, zero, 0 ; l
        addi a2, zero, 4 ; r
        addi a3, zero, 1 ; x
        jal ra, binary_search
        ebreak
        
; s0 : mid
binary_search:
        addi sp, sp, -16
        sw sp, ra, 12
        sw sp, s0, 8
        sw sp, s1, 4
        sw sp, s2, 0
        
        blt a2, a1, not_found
        
        sub s0, a2, a1
        srli s0, s0, 1
        add s0, s0, a1
        
        add t1, s0, zero
        slli t1, t1, 2
        add t2, t1, a0
        lw t3, t2, 0
        
        beq t3, a3, found
        
        bge a3, t3, search_right
        
        addi s1, a2, 0 ; salva r
        addi s2, s0, 0 ; salva mid
        addi a2, s0, -1 ; a2 = mid - 1
        jal ra, binary_search
        
        lw ra, sp, 12
        lw s0, sp, 8
        lw s1, sp, 4
        lw s2, sp, 0
        addi sp, sp, 16
        
        jalr zero, ra, 0
        
not_found:
        addi a0, zero, -1
        jalr zero, ra, 0
        
found:
        addi a0, s0, 0
        jalr zero, ra, 0       

search_right:
        addi s1, a1, 0 ; salva l
        addi s2, s0, 0 ; salva mid
        addi a1, s0, 1 ; a1 = mid + 1
        jal ra, binary_search
        
        lw ra, sp, 12
        lw s0, sp, 8
        lw s1, sp, 4
        lw s2, sp, 0
        addi sp, sp, 16
        
        jalr zero, ra, 0
arr:
#%02%00%00%00
#%03%00%00%00
#%05%00%00%00
#%07%00%00%00
#%09%00%00%00
