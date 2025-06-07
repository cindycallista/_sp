LOAD R0 <- 5
LOAD R1 <- 3
ADD R0 <- R1 (result: 8)
JZ R0 != 0, no jump
SUB R0 <- R1 (result: 5)
HALT

Final Registers:
R0: 5
R1: 3
R2: 0
R3: 0
