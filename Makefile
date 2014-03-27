# GNU Make solution makefile autogenerated by Premake
# Type "make help" for usage help

ifndef config
  config=
endif
export config

PROJECTS := exec libCarteBancaire test

.PHONY: all clean help $(PROJECTS)

all: $(PROJECTS)

exec: libCarteBancaire
	@echo "==== Building exec ($(config)) ===="
	@${MAKE} --no-print-directory -C . -f exec.make

libCarteBancaire: 
	@echo "==== Building libCarteBancaire ($(config)) ===="
	@${MAKE} --no-print-directory -C . -f libCarteBancaire.make

test: 
	@echo "==== Building test ($(config)) ===="
	@${MAKE} --no-print-directory -C . -f test.make

clean:
	@${MAKE} --no-print-directory -C . -f exec.make clean
	@${MAKE} --no-print-directory -C . -f libCarteBancaire.make clean
	@${MAKE} --no-print-directory -C . -f test.make clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "   "
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   exec"
	@echo "   libCarteBancaire"
	@echo "   test"
	@echo ""
	@echo "For more information, see http://industriousone.com/premake/quick-start"
