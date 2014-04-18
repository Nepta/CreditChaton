# GNU Make project makefile autogenerated by Premake
ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifndef CC
  CC = gcc
endif

ifndef CXX
  CXX = g++
endif

ifndef AR
  AR = ar
endif

ifeq ($(config),debug)
  OBJDIR     = obj/debug/acquisition
  TARGETDIR  = .
  TARGET     = $(TARGETDIR)/acquisition
  DEFINES   += 
  INCLUDES  += 
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -Wall -g -std=c99
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -pthread -L.
  LIBS      += -llibCarteBancaire
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += liblibCarteBancaire.a
  LINKCMD    = $(CC) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),release)
  OBJDIR     = obj/release/acquisition
  TARGETDIR  = .
  TARGET     = $(TARGETDIR)/acquisition
  DEFINES   += 
  INCLUDES  += 
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -O3 -std=c99
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -s -pthread -L.
  LIBS      += -llibCarteBancaire
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += liblibCarteBancaire.a
  LINKCMD    = $(CC) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),debug)
  OBJDIR     = obj/debug/acquisition
  TARGETDIR  = .
  TARGET     = $(TARGETDIR)/acquisition
  DEFINES   += 
  INCLUDES  += 
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -Wall -g -std=c99
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -pthread -L.
  LIBS      += -llibCarteBancaire
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += liblibCarteBancaire.a
  LINKCMD    = $(CC) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),release)
  OBJDIR     = obj/release/acquisition
  TARGETDIR  = .
  TARGET     = $(TARGETDIR)/acquisition
  DEFINES   += 
  INCLUDES  += 
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -O3 -std=c99
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -s -pthread -L.
  LIBS      += -llibCarteBancaire
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += liblibCarteBancaire.a
  LINKCMD    = $(CC) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),debug)
  OBJDIR     = obj/debug/acquisition
  TARGETDIR  = .
  TARGET     = $(TARGETDIR)/acquisition
  DEFINES   += 
  INCLUDES  += 
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -Wall -g -std=c99
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -pthread -L.
  LIBS      += -llibCarteBancaire
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += liblibCarteBancaire.a
  LINKCMD    = $(CC) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),release)
  OBJDIR     = obj/release/acquisition
  TARGETDIR  = .
  TARGET     = $(TARGETDIR)/acquisition
  DEFINES   += 
  INCLUDES  += 
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -O3 -std=c99
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -s -pthread -L.
  LIBS      += -llibCarteBancaire
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += liblibCarteBancaire.a
  LINKCMD    = $(CC) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),debug)
  OBJDIR     = obj/debug/acquisition
  TARGETDIR  = .
  TARGET     = $(TARGETDIR)/acquisition
  DEFINES   += 
  INCLUDES  += 
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -Wall -g -std=c99
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -pthread -L.
  LIBS      += -llibCarteBancaire
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += liblibCarteBancaire.a
  LINKCMD    = $(CC) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),release)
  OBJDIR     = obj/release/acquisition
  TARGETDIR  = .
  TARGET     = $(TARGETDIR)/acquisition
  DEFINES   += 
  INCLUDES  += 
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -O3 -std=c99
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -s -pthread -L.
  LIBS      += -llibCarteBancaire
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += liblibCarteBancaire.a
  LINKCMD    = $(CC) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),debug)
  OBJDIR     = obj/debug/acquisition
  TARGETDIR  = .
  TARGET     = $(TARGETDIR)/acquisition
  DEFINES   += 
  INCLUDES  += 
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -Wall -g -std=c99
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -pthread -L.
  LIBS      += -llibCarteBancaire
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += liblibCarteBancaire.a
  LINKCMD    = $(CC) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),release)
  OBJDIR     = obj/release/acquisition
  TARGETDIR  = .
  TARGET     = $(TARGETDIR)/acquisition
  DEFINES   += 
  INCLUDES  += 
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -O3 -std=c99
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -s -pthread -L.
  LIBS      += -llibCarteBancaire
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += liblibCarteBancaire.a
  LINKCMD    = $(CC) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),release)
  OBJDIR     = obj/release/acquisition
  TARGETDIR  = .
  TARGET     = $(TARGETDIR)/acquisition
  DEFINES   += 
  INCLUDES  += 
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -O3 -std=c99
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -s -pthread -L.
  LIBS      += -llibCarteBancaire
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += liblibCarteBancaire.a
  LINKCMD    = $(CC) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),release)
  OBJDIR     = obj/release/acquisition
  TARGETDIR  = .
  TARGET     = $(TARGETDIR)/acquisition
  DEFINES   += 
  INCLUDES  += 
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -O3 -std=c99
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -s -pthread -L.
  LIBS      += -llibCarteBancaire
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += liblibCarteBancaire.a
  LINKCMD    = $(CC) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

OBJECTS := \
	$(OBJDIR)/acquisition.o \

RESOURCES := \

SHELLTYPE := msdos
ifeq (,$(ComSpec)$(COMSPEC))
  SHELLTYPE := posix
endif
ifeq (/bin,$(findstring /bin,$(SHELL)))
  SHELLTYPE := posix
endif

.PHONY: clean prebuild prelink

all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

$(TARGET): $(GCH) $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking acquisition
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(OBJDIR))
endif

clean:
	@echo Cleaning acquisition
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild:
	$(PREBUILDCMDS)

prelink:
	$(PRELINKCMDS)

ifneq (,$(PCH))
$(GCH): $(PCH)
	@echo $(notdir $<)
	-$(SILENT) cp $< $(OBJDIR)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
endif

$(OBJDIR)/acquisition.o: src/acquisition.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
