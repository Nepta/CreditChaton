default: cleanFifo
	@./interbancaire -j 1 &
	@./acquisition -b 0000 &
	@./autorisation -b 0000 &
	@./acquisition -b 1111 &
	@./autorisation -b 1111 &
	@./randGen -b 1111 -n 2000  | ./terminal -b 0000 &

cleanFifo:
	@rm resources/*/*.fifo || true

