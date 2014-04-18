ifndef example
	example=default
endif

ifeq ($(example),default)
default: cleanFifo
	@./interbancaire &
	@./fileToDescriptor -i resources/localRouter0000.fifo -o resources/localAuth0000.fifo -- ./acquisition -b 0000 &
	@./autorisation -b 0000 &
	@./fileToDescriptor -i resources/autorisation.fifo -o resources/localRouter0000.fifo -- ./terminal
endif

ifeq ($(example),ata)
ata: cleanFifo
	@./fileToDescriptor -i resources/acquisition.fifo -o resources/autorisation.fifo -- ./acquisition &
	@./fileToDescriptor  -o resources/acquisition.fifo -i resources/autorisation.fifo -- ./autorisation -b 0234567890123456 &
	@./fileToDescriptor -i resources/autorisation.fifo -o resources/acquisition.fifo -- ./terminal
endif


ifeq ($(example),std)
std: cleanFifo
	@./fileToDescriptor  -o /dev/fd/1 -i resources/termOut.fifo -- ./autorisation -b 0234567890123456 &
	@./fileToDescriptor -i /dev/fd/0 -o resources/termOut.fifo -- ./terminal
endif

ifeq ($(example),acq)
authonly: cleanFifo
	@./fileToDescriptor  -o resources/termIn.fifo -i resources/termOut.fifo -- ./autorisation -b 0234567890123456 &
	@./fileToDescriptor -i resources/termIn.fifo -o resources/termOut.fifo -- ./terminal
endif

cleanFifo:
	@rm resources/*.fifo || true

