# mude somente essa linha abaixo para apontar p o diretorio do hellfireos
#HFOS_ROOT=/home/ale/repos/gaph/anderson/hf-risc-st
#HFOS_ROOT=/home/10084214/Downloads/hf-risc-st
HFOS_SW=$(HFOS_ROOT)/software/
SIMDIR = $(HFOS_SW)/tools/sim/hf_riscv_sim/

include $(HFOS_SW)/defs.mk

all:


crt:
	#$(AS_$(ARCH)) -o crt0.o -x assembler-with-cpp lib/$(ARCH)/crt0.S
	$(GCC_$(ARCH)) -o crt0.o -DTEST -x assembler-with-cpp $(HFOS_SW)/lib/$(ARCH)/crt0.S 
	$(GCC_$(ARCH)) -o libc.o $(HFOS_SW)/lib/libc.c -I$(HFOS_SW)/include
	$(GCC_$(ARCH)) -o interrupt.o $(HFOS_SW)/lib/interrupt.c -I$(HFOS_SW)/include
	$(GCC_$(ARCH)) -o math.o $(HFOS_SW)/lib/math.c -I$(HFOS_SW)/include
	$(GCC_$(ARCH)) -o malloc.o $(HFOS_SW)/lib/malloc.c -I$(HFOS_SW)/include
	$(GCC_$(ARCH)) -o hf-unit.o $(HFOS_SW)/lib/hf-unit.c -I$(HFOS_SW)/include

link:
	$(LD_$(ARCH)) -T$(HFOS_SW)lib/$(ARCH)/$(LD_SCRIPT) -Map test.map -N -o test.elf *.o
	$(DUMP_$(ARCH)) --disassemble --reloc test.elf > test.lst
	$(DUMP_$(ARCH)) -h test.elf > test.sec
	$(DUMP_$(ARCH)) -s test.elf > test.cnt
	$(OBJ_$(ARCH)) -O binary test.elf test.bin
	$(SIZE_$(ARCH)) test.elf
	mv test.elf code.elf
	mv test.bin code.bin
	mv test.lst code.lst
	mv test.sec code.sec
	mv test.cnt code.cnt
	mv test.map code.map
	hexdump -v -e '4/1 "%02x" "\n"' code.bin > code.txt


app: crt
	$(GCC_$(ARCH)) -o sort.o $(HFOS_SW)/app/sort.c -I$(HFOS_SW)/include
	@$(MAKE) --no-print-directory link

sim: $(HFOS_ROOT)/tools/sim/hf_riscv_sim/hf_riscv_sim.c
	gcc -o hf_riscv_sim $(HFOS_ROOT)/tools/sim/hf_riscv_sim/*.c

test: crt sim 
	$(GCC_$(ARCH)) -o test.o test.c -I$(HFOS_SW)/include  # compila o teste
	$(GCC_$(ARCH)) -o tester.o tester.c -I$(HFOS_SW)/include  # compila o testador
	@$(MAKE) --no-print-directory app
	./hf_riscv_sim ./code.bin

clean:
	-rm -rf *~ *.o *.elf *.map *.lst *.sec *.cnt *.txt *.bin *.vhd
