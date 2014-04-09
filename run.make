ifndef example
	example=default
endif

ifeq ($(example),default)
default: cleanFifo $(PROJECTS)
	@./fileToDescriptor  -o resources/termIn.fifo -i resources/termOut.fifo -- ./autorisation -b 0234567890123456 &
	@./fileToDescriptor -i resources/termIn.fifo -o resources/termOut.fifo -- ./terminal
endif

ifeq ($(example),std)
std: cleanFifo $(PROJECTS)
	@./fileToDescriptor  -o /dev/fd/1 -i resources/termOut.fifo -- ./autorisation -b 0234567890123456 &
	@./fileToDescriptor -i /dev/fd/0 -o resources/termOut.fifo -- ./terminal
endif

ifeq ($(example),acq)
acq: cleanFifo $(PROJECTS)
	@./fileToDescriptor -i resources/term.fifo -o resources/acquisition.fifo -- ./acquisition &
	@./fileToDescriptor  -o resources/autorisation.fifo -i resources/acquisition.fifo -- ./autorisation -b 0234567890123456 &
	@./fileToDescriptor -i resources/autorisation.fifo -o resources/term.fifo -- ./terminal
endif

cleanFifo:
	@rm resources/*

