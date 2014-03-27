solution "Template"
	buildoptions{"-std=c99"}
	flags {"Unicode"}
	
	project "terminal"
		configurations {"debug", "release"}
		kind "ConsoleApp"
		language "C"

		files {"src/terminal.c"}
		excludes{"src/test*.c"}
		links {"libCarteBancaire"}
--		links {"SDL","SDL_image","SDL_ttf", "m"}

--		linkoptions{"libjsmn.a"} --small linking hack
		configuration "debug"
			flags {"ExtraWarnings", "Symbols"}
		
		configuration "release"
			flags {"OptimizeSpeed"}

	project "libCarteBancaire"
		kind "StaticLib"
		language "C"
		flags {"OptimizeSpeed"}
		
		files {"libCarteBancaire/alea.c",
				 "libCarteBancaire/message.c",}
		
	project "test"
		kind "ConsoleApp"
		language "C"
		
		files {"src/test*.c"}

		flags {"ExtraWarnings", "Symbols"}

