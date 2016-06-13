/** enterSysROM function jumps to STM32 System Memory
  */

.text
.syntax unified
.thumb
.type enterSysROM, %function

.globl enterSysROM

enterSysROM:
	/* Enable SYSCFG Clock */
	LDR     R0, =0x40023844 // RCC_APB2ENR (+0x44)
	MOVS    R1, #0x4000
	STR     R1, [R0, #0]    // ENABLE SYSCFG CLOCK (1<<14)

	/* Remap System ROM at 0x0 and sync */
	MOVS    R1, #1
	LDR     R0, =0x40013800 // SYSCFG_CFGR1 (+0x00)
	STR     R1, [R0, #0]    // MAP ROM AT ZERO (1)
	DSB

	/* Load SP and PC from new Vector Table */
	MOVS    R1, #0          // ADDRESS OF ZERO
	LDR     R0, [R1, #0]    // SP @ +0
	MOV     SP, R0
	LDR     R0, [R1, #4]    // PC @ +4
	BX      R0
.end
