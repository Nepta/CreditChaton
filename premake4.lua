solution "Template"
	configurations {""}
	buildoptions{"-std=c99"}
	flags {"Unicode"}
	
	project "exec"
		kind "ConsoleApp"
		language "C"

		files {"*.c"}
		excludes{"test*.c"}
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
		
		files {"test*.c"}

		flags {"ExtraWarnings", "Symbols"}

