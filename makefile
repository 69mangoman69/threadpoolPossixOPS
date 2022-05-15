# base filename goes here:
FILENAME=threadsPool

# 1 for ez compile,
# 0 to see a few more useless warnings,
# -1 if you you're perfectionist,
# -2 if you want a bossfight with the compiler (try to compile even a hello world with this mode lmao)
FEELINGLAZY:=-1

# 1 to clean whenever you make, 0 to not
# is an automatic make clean :) kinda nice
CLEANONMAKE:=1

# 1 to clear whenever you make, 0 to not
CLEARONMAKE:=1

# set this to 1 to compile 2 server/client files at once, saves time
# this will look for two .c files that start with the base FILENAME you put above,
# but end in (for example) "...SRVR.c" or "...CLIENT.c", then will compile two programs with those names
#
# usually for lab6 and (sometimes?) later
DUALFILE=1
SERVERPOSTIX=Server
CLIENTPOSTFIX=Client

# you can list your message queues here and "make clean" will try to remove them if they exist
# I've found this useful when I mess up and have an open/full message queue or smthn
# remember: they can stay alive even after all processes using them exit
# also the directory isn't the same on all systems, but on the school ones I think it's /dev/mqueue
# you can change that tho
#
# probably only useful on lab6 tho
IPCMSGQS=
IPCMSGQPATH=/dev/mqueue

# approximately:
# 0 <= g <= 1 <= z <= s <= 2 <= 3 <= fast
# 0 or g are best for debugging, debugging is good for labs
OPTLVL=0

# 1 for ASAN
# 0 for no sanitizer screams
SHOULDSANITIZE=1

# 1 if you only want to preprocess,
# 0 normally
# sometimes useful for debugging macro expansion
PREPROCESSONLY=0

# 1 if you only want to assemble
# 0 normally
ASSEMBLEONLY=0

# in case you want to rename the header lol
# remember to change every #include in your files too
HEADERNAME=katwikOpsys

# can disable this makefile's header dependencies with this
# but... no ;)
USEHEADER=1

# tmp? idk lol
USECOLOR=1

ifeq ($(CLEANONMAKE), 0)
	SHOULDCLEAN =
else
	SHOULDCLEAN = clean
endif

ifeq ($(CLEARONMAKE), 0)
	SHOULDCLEAR =
else
	SHOULDCLEAR = clear
endif

PREPROCESSEXTENSION = _PREPROCESSED.c
ASSEMBLYEXTENSION = .asm
ifeq ($(PREPROCESSONLY), 1)
	PREPROCESS = -E
	OUTPUTEXTENSION = $(PREPROCESSEXTENSION)
else ifeq ($(ASSEMBLEONLY), 1)
	ASSEMBLE = -S
	OUTPUTEXTENSION = $(ASSEMBLYEXTENSION)
else
	PREPROCESS =
	ASSEMBLE =
	OUTPUTEXTENSION =
endif

ifeq ($(SHOULDSANITIZE), 0)
	SANITIZEFLAGS =
else
	SANITIZEFLAGS = -fsanitize=address,undefined 
endif

ifeq ($(USEHEADER), 0)
	FULLHEADERNAME =
else
	FULLHEADERNAME = $(HEADERNAME).h
endif

#ifneq ($(findstring xterm, ${TERM}),) # doesn't work with tmux? using a sad hack for now :(
ifeq ($(USECOLOR), 1)
	BLACK		:= $(shell tput -Txterm setaf 0)
	RED		:= $(shell tput -Txterm setaf 1)
	GREEN		:= $(shell tput -Txterm setaf 2)
	YELLOW		:= $(shell tput -Txterm setaf 3)
	LIGHTPURPLE	:= $(shell tput -Txterm setaf 4)
	PURPLE		:= $(shell tput -Txterm setaf 5)
	BLUE		:= $(shell tput -Txterm setaf 6)
	WHITE		:= $(shell tput -Txterm setaf 7)
	RESET		:= $(shell tput -Txterm sgr0)
else
	BLACK		:= ""
	RED		:= ""
	GREEN		:= ""
	YELLOW		:= ""
	LIGHTPURPLE	:= ""
	PURPLE		:= ""
	BLUE		:= ""
	WHITE		:= ""
	RESET		:= ""
endif

ifeq ($(FEELINGLAZY), 0)
	LAZYFLAGS =
else ifeq ($(FEELINGLAZY), -1)
	LAZYFLAGS = -Wpedantic -Werror

# lol:
else ifeq ($(FEELINGLAZY), -2)
	LAZYFLAGS = -ftrack-macro-expansion=2 -Wpedantic -Waggregate-return -Waggressive-loop-optimizations -Warray-bounds=2 -Wattributes -Wbad-function-cast -Wbuiltin-macro-redefined -Wc90-c99-compat -Wc99-c11-compat -Wcast-align -Wcast-qual -Wconversion -Wcoverage-mismatch -Wcpp -Wdate-time -Wdeclaration-after-statement -Wdeprecated -Wdeprecated-declarations -Wdesignated-init -Wdisabled-optimization -Wdiscarded-array-qualifiers -Wdiscarded-qualifiers -Wdiv-by-zero -Wdouble-promotion -Wendif-labels -Wfloat-equal -Wformat-contains-nul -Wformat-extra-args -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat-y2k -Wformat-zero-length -Wfree-nonheap-object -Wincompatible-pointer-types -Winline -Wint-conversion -Wint-to-pointer-cast -Winvalid-memory-model -Winvalid-pch -Wjump-misses-init -Wlogical-op -Wlong-long -Wmissing-declarations -Wmissing-include-dirs -Wmissing-prototypes -Wmultichar -Wnested-externs -Wodr -Wold-style-definition -Woverflow -Woverlength-strings -Wpacked -Wpacked-bitfield-compat -Wpadded -Wpointer-arith -Wpointer-to-int-cast -Wpragmas -Wredundant-decls -Wreturn-local-addr -Wshadow -Wshift-count-negative -Wshift-count-overflow -Wsizeof-array-argument -Wstack-protector -Wstrict-prototypes -Wsuggest-attribute=const -Wsuggest-attribute=format -Wsuggest-attribute=noreturn -Wsuggest-attribute=pure -Wsuggest-final-methods -Wsuggest-final-types -Wswitch-bool -Wswitch-default -Wswitch-enum -Wsync-nand -Wsystem-headers -Wtraditional -Wtraditional-conversion -Wtrampolines -Wundef -Wunsafe-loop-optimizations -Wunsuffixed-float-constants -Wunused -Wunused-but-set-parameter -Wunused-but-set-variable -Wunused-local-typedefs -Wunused-macros -Wunused-result -Wvarargs -Wvariadic-macros -Wvector-operation-performance -Wvla -Wwrite-strings -Werror
else # ifeq ($(FEELINGLAZY), 1) # default
	LAZYFLAGS = -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -Wno-cpp
endif

CC=gcc
CFLAGS=$(PREPROCESS) $(ASSEMBLE) -pthread -Wall -Wextra -ftrack-macro-expansion=0 -fno-omit-frame-pointer -g3 -O$(OPTLVL) $(SANITIZEFLAGS)
LDFLAGS=-lpthread -lrt

COMPILEMSG="$(BLUE)===\t$(GREEN)$<$(BLUE)\t->\t$(GREEN)$@$(OUTPUTEXTENSION)\t$(BLUE)===$(RESET)\n"
COMPILE=$(CC) $(CFLAGS) $(LAZYFLAGS) $< -o $@$(OUTPUTEXTENSION) $(LDFLAGS)

.PHONY: all docs dualFile clean clear preprocess assemble

all: $(SHOULDCLEAN) $(SHOULDCLEAR)
ifeq ($(DUALFILE), 1)
all: dualFile
else
all: $(FILENAME)
endif

$(FILENAME): $(FILENAME).c $(FULLHEADERNAME)
%: %.c
	@printf $(COMPILEMSG) 
	@$(COMPILE)

dualFile: $(FILENAME)$(SERVERPOSTIX) $(FILENAME)$(CLIENTPOSTFIX) $(FULLHEADERNAME)
$(FILENAME)$(SERVERPOSTIX): $(FILENAME)$(SERVERPOSTIX).c $(FULLHEADERNAME)
	@printf $(COMPILEMSG) 
	-@$(COMPILE)
$(FILENAME)$(CLIENTPOSTFIX): $(FILENAME)$(CLIENTPOSTFIX).c $(FULLHEADERNAME)
	@printf $(COMPILEMSG) 
	-@$(COMPILE)

ifeq ($(DUALFILE), 0)
clean: OUTPUTS=$(FILENAME)$(OUTPUTEXTENSION)
else
clean: OUTPUTS=$(FILENAME)$(SERVERPOSTIX)$(OUTPUTEXTENSION) $(FILENAME)$(CLIENTPOSTFIX)$(OUTPUTEXTENSION)
endif
clean:
ifneq ($(IPCMSGQS),)
	@printf "$(BLUE)Trying to remove $(GREEN)$(IPCMSGQS)$(RESET) (message queues) from $(GREEN)$(IPCMSGQPATH)$(RESET)\n"
	-@cd $(IPCMSGQPATH); rm -v -f $(IPCMSGQS)
endif
	@printf "$(BLUE)Trying to remove $(GREEN)$(OUTPUTS)$(GREEN)$(RESET)\n"
	-@rm -v -f $(OUTPUTS)

preprocess:
	@$(MAKE) -B -s PREPROCESS=-E OUTPUTEXTENSION=$(PREPROCESSEXTENSION) $(filter-out $@, $(MAKECMDGOALS))

assemble:
	@$(MAKE) -B -s ASSEMBLE=-S OUTPUTEXTENSION=$(ASSEMBLYEXTENSION) $(filter-out $@, $(MAKECMDGOALS))

clear:
	@clear
