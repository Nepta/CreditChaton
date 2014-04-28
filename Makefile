# GNU Make solution makefile autogenerated by Premake
# Type "make help" for usage help

ifndef config
  config=debug
endif
export config

PROJECTS := terminal randGen autorisation acquisition interbancaire fileToDescriptor libCarteBancaire libAnnuaire

.PHONY: all clean help $(PROJECTS)

all: $(PROJECTS)

terminal: libCarteBancaire
	@echo "==== Building terminal ($(config)) ===="
	@${MAKE} --no-print-directory -C . -f terminal.make

randGen: 
	@echo "==== Building randGen ($(config)) ===="
	@${MAKE} --no-print-directory -C . -f randGen.make

autorisation: libCarteBancaire libAnnuaire
	@echo "==== Building autorisation ($(config)) ===="
	@${MAKE} --no-print-directory -C . -f autorisation.make

acquisition: libCarteBancaire
	@echo "==== Building acquisition ($(config)) ===="
	@${MAKE} --no-print-directory -C . -f acquisition.make

interbancaire: libCarteBancaire libAnnuaire
	@echo "==== Building interbancaire ($(config)) ===="
	@${MAKE} --no-print-directory -C . -f interbancaire.make

fileToDescriptor: libCarteBancaire
	@echo "==== Building fileToDescriptor ($(config)) ===="
	@${MAKE} --no-print-directory -C . -f fileToDescriptor.make

libCarteBancaire: 
	@echo "==== Building libCarteBancaire ($(config)) ===="
	@${MAKE} --no-print-directory -C . -f libCarteBancaire.make

libAnnuaire: 
	@echo "==== Building libAnnuaire ($(config)) ===="
	@${MAKE} --no-print-directory -C . -f libAnnuaire.make

clean:
	@${MAKE} --no-print-directory -C . -f terminal.make clean
	@${MAKE} --no-print-directory -C . -f randGen.make clean
	@${MAKE} --no-print-directory -C . -f autorisation.make clean
	@${MAKE} --no-print-directory -C . -f acquisition.make clean
	@${MAKE} --no-print-directory -C . -f interbancaire.make clean
	@${MAKE} --no-print-directory -C . -f fileToDescriptor.make clean
	@${MAKE} --no-print-directory -C . -f libCarteBancaire.make clean
	@${MAKE} --no-print-directory -C . -f libAnnuaire.make clean

doxygen: 
	@echo "==== Building doxygen ===="
	@doxygen doc/Doxyfile

run: annuaire
	@echo "==== Runing auth and terminal ===="
	@${MAKE} -s --no-print-directory -C . -f run.make

annuaire: randGen
	@echo "==== Creating annuaires files ===="
	@/bin/bash -c 'for d in resources/bank*/; do bankId=$${d:14:4}; ./randGen -b $$bankId -n $$(($$RANDOM%1000)) > $${d}annuaire.txt 2> /dev/null ; done'

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
	@echo "   debug"
	@echo "   release"
	@echo "   debug"
	@echo "   release"
	@echo "   release"
	@echo "   release"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   terminal"
	@echo "   randGen"
	@echo "   autorisation"
	@echo "   acquisition"
	@echo "   interbancaire"
	@echo "   fileToDescriptor"
	@echo "   libCarteBancaire"
	@echo "   libAnnuaire"
	@echo "   debug"
	@echo "   release"
	@echo ""
	@echo "For more information, see http://industriousone.com/premake/quick-start"
