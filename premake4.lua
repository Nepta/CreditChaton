solution "Template"
	buildoptions{"-std=c99"}
	linkoptions{"-pthread"}
	flags {"Unicode"}

	configuration "release"
		flags {"OptimizeSpeed"}
	configuration "debug"
		flags {"ExtraWarnings", "Symbols"}
	
	project "terminal"
		configurations {"debug", "release"}
		kind "ConsoleApp"
		language "C"

		files {"src/terminal.c"}
		excludes{"src/test*.c"}
		links {"libCarteBancaire"}

	project "autorisation"
		configurations {"debug", "release"}
		kind "ConsoleApp"
		language "C"

		files {"src/autorisation.c","src/communicationThread.c"}
		excludes{"src/test*.c"}
		links {"libCarteBancaire","libAnnuaire"}

	project "acquisition"
		configurations {"debug", "release"}
		kind "ConsoleApp"
		language "C"

		files {"src/acquisition.c"}
		excludes{"src/test*.c"}
		links {"libCarteBancaire"}
	
	project "interbancaire"
		configurations {"debug", "release"}
		kind "ConsoleApp"
		language "C"
		
		files {"src/interbancaire.c"}
		excludes{"src/test*.c"}
		links {"libCarteBancaire","libAnnuaire"}

	project "fileToDescriptor"
		kind "ConsoleApp"
		language "C"
		
		files {"src/fileToDescriptor.c"}
		links {"libCarteBancaire"}

	project "libCarteBancaire"
		configurations {"release"}
		kind "StaticLib"
		language "C"
		flags {"OptimizeSpeed"}
		
		files {"libCarteBancaire/alea.c",
				 "libCarteBancaire/message.c",
				 "libCarteBancaire/lectureEcriture.c"}

	project "libAnnuaire"
		configurations {"release"}
		kind "StaticLib"
		language "C"
		flags {"OptimizeSpeed"}
		files {"src/annuaire.c"}
	
