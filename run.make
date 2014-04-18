default: cleanFifo
	@./interbancaire &
	@./acquisition -b 0000 &
	@./autorisation -b 0000 &
	@./acquisition -b 1111 &
	@./autorisation -b 1111 &
	@./terminal -b 0000

cleanFifo:
	@rm resources/*/*.fifo || true

