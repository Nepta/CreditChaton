default: cleanFifo
	@./interbancaire -f resources/bank.txt &
	@./acquisition -b 0000 &
	@./autorisation -b 0000 &
	@./acquisition -b 1111 &
	@./autorisation -b 1111 &
#	@./acquisition -b 2222 &
#	@./autorisation -b 2222 &
	@./randGen -b 1111 -n 40 | ./terminal -b 0000 &
	@./randGen -b 1111 -n 4 | ./terminal -b 1111 &
#	@./randGen -b 0000 -n 40 | ./terminal -b 2222 &


cleanFifo:
	@rm resources/*/*.fifo || true

