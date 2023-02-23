.globl get_el
get_el:
    mrs x0, CurrentEL
    lsr x0, x0, #2      //first 2 bits in the CurrentEL register are reserved and always have value 0
    ret
