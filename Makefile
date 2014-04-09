# GNU Make solution makefile autogenerated by Premake
# Type "make help" for usage help

ifndef config
  config=debug
endif
export config

PROJECTS := terminal autorisation acquisition fileToDescriptor libCarteBancaire

.PHONY: all clean help $(PROJECTS)

all: $(PROJECTS)

terminal: libCarteBancaire
	@echo "==== Building terminal ($(config)) ===="
	@${MAKE} --no-print-directory -C . -f terminal.make

autorisation: libCarteBancaire
	@echo "==== Building autorisation ($(config)) ===="
	@${MAKE} --no-print-directory -C . -f autorisation.make

acquisition: libCarteBancaire
	@echo "==== Building acquisition ($(config)) ===="
	@${MAKE} --no-print-directory -C . -f acquisition.make

fileToDescriptor: libCarteBancaire
	@echo "==== Building fileToDescriptor ($(config)) ===="
	@${MAKE} --no-print-directory -C . -f fileToDescriptor.make

libCarteBancaire: 
	@echo "==== Building libCarteBancaire ($(config)) ===="
	@${MAKE} --no-print-directory -C . -f libCarteBancaire.make

doxygen: 
	@echo "==== Building doxygen ===="
	@doxygen doc/Doxyfile

run:
	@echo "==== Runing auth and terminal ===="
	@${MAKE} -s --no-print-directory -C . -f run.make

clean:
	@${MAKE} --no-print-directory -C . -f terminal.make clean
	@${MAKE} --no-print-directory -C . -f autorisation.make clean
	@${MAKE} --no-print-directory -C . -f acquisition.make clean
	@${MAKE} --no-print-directory -C . -f fileToDescriptor.make clean
	@${MAKE} --no-print-directory -C . -f libCarteBancaire.make clean
	@${MAKE} --no-print-directory -C . -f doxygen.make clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "   debug"
	@echo "   release"
	@echo "   debug"
	@echo "   release"
	@echo "   debug"
	@echo "   release"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   terminal"
	@echo "   autorisation"
	@echo "   acquisition"
	@echo "   fileToDescriptor"
	@echo "   libCarteBancaire"
	@echo "   doxygen"
	@echo "   run"
	@echo "      HOWTO"
	@echo "      std"
	@echo ""
	@echo "For more information, see http://industriousone.com/premake/quick-start"
