default: cleanFifo
	@./interbancaire -j 9 -f resources/bank.txt &
	@./acquisition -b 0000 &
	@./autorisation -b 0000 &
	@./acquisition -b 1111 &
	@./autorisation -b 1111 &
	@./randGen -b 1111 -n 5000 -u | ./terminal -b 0000 &
	@./randGen -b 1111 -n 5000 -u | ./terminal -b 1111 &


cleanFifo:
	@rm resources/*/*.fifo || true

