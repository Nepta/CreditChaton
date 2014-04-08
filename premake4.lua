solution "Template"
	buildoptions{"-std=c99"}
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

		files {"src/autorisation.c"}
		excludes{"src/test*.c"}
		links {"libCarteBancaire"}

	project "acquisition"
		configurations {"debug", "release"}
		kind "ConsoleApp"
		language "C"

		files {"src/acquisition.c"}
		excludes{"src/test*.c"}
		links {"libCarteBancaire"}

	project "fileToDescriptor"
		kind "ConsoleApp"
		language "C"
		
		files {"src/fileToDescriptor.c"}
		links {"libCarteBancaire"}

	project "libCarteBancaire"
		kind "StaticLib"
		language "C"
		flags {"OptimizeSpeed"}
		
		files {"libCarteBancaire/alea.c",
				 "libCarteBancaire/message.c",
				 "libCarteBancaire/lectureEcriture.c"}

	
	project "doxygen"
		language "C"
		kind "ConsoleApp"
		buildaction "None"
		files {"doc/Doxyfile"}		
--	newoption{
--		trigger     = "doxygen",
--		description = "Build doxygen documentation",
--		execute = function()
--			os.execute("doxygen doc/Doxyfile")
--		end,
--	}
--	
