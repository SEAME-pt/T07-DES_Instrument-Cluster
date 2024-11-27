# compilation, linking and cleaning commands/flags
CXX = c++
CXXWARNS = -Wextra -Werror -Wall
CXXRESTR = -std=c++98
CXXDEBUG = -ggdb
CXXFLAGS = $(CXXWARNS) $(CXXRESTR) $(CXXDEBUG)
MKF = --no-print-directory
AR = ar -rcs
RM = rm -rf

# sources, objects and includes folders
SRCSD = sources/
INCSD = includes/
SUBSD = ./
OBJSD = build/
VPATH = $(SRCSD) $(addprefix $(SRCSD), $(SUBSD))

# files
# NAME = $(shell basename $(CURDIR))
NAME = PmergeMe
FILES =  main
FILES += PmergeMe
OBJS = $(FILES:%=%.o)
TARGET = $(addprefix $(OBJSD), $(OBJS))

# valgrind
LEAKS = valgrind
LEAKS_FILE = valgrind-log.txt
LF = --leak-check=full \
	 --show-leak-kinds=all \
	 --track-origins=yes \
	 --verbose \
	 --log-file=$(LEAKS_FILE) \
	 ./$(NAME)

# colors
GRN = \e[38;5;118m
YLW = \e[38;5;226m
RED = \e[38;5;196m
BLU = \e[38:5:31m
CYN = \33[1;36m
WHT = \e[0m
RESET = \033[0m
BOLD = \033[1m

# predefine user messages
_INFO		= $(WHT)[$(CYN)INFO $(WHT)]
_SUCCESS	= $(WHT)[$(GRN)$(BOLD)READY$(WHT)]
_WARNING	= $(WHT)[$(YLW)WARNING$(WHT)]
_ERROR 		= $(WHT)[$(RED)ERROR$(WHT)]

# rules
all: $(NAME)
	@printf "\n $(_SUCCESS) $(BOLD)$(NAME)$(RESET) executable ready!\n\n"

$(NAME): $(OBJSD) $(TARGET)
	@printf "\n $(_SUCCESS) $(BOLD)$(NAME)$(RESET) objects ready! \n"
	@printf "\n $(_INFO) Linking $(BOLD)$(NAME)$(RESET) executable...\n "
	$(CXX) $(CXXFLAGS) $(CXXDEBUG) $(TARGET) -o $@ -I $(INCSD)
	@printf "$(GRN)█$(RESET)"

$(OBJSD)%.o: $(SRCSD)%.cpp
	$(CXX) $(CXXFLAGS) $(CXXDEBUG) -c $< -o $@ -I $(INCSD)
	@printf "$(YLW)█$(RESET)"

$(OBJSD):
	@printf "\n $(_INFO) $(BOLD)$(OBJSD)$(RESET) directory created.\n"
	@mkdir -p $(OBJSD)
	@printf "\n $(_INFO) Compiling source files...$(WTH)\n "

leaks:
	@printf "\n$(_INFO) $(CYN)Running $(BOLD)$(LEAKS)$(RESET) on $(BOLD)$(NAME)$(RESET)...\n"
	@$(LEAKS) $(LF)
	@printf "\n$(_SUCCESS) $(BOLD)$(LEAKS)$(RESET) completed.\n"

clean:
	@printf "\n$(_INFO) Cleaning objects and $(BOLD)$(OBJSD)$(RESET) directory...\n"
	@$(RM) -rf $(OBJS)
	@$(RM) -rf $(OBJSD)
	@printf "$(_SUCCESS) All $(BOLD)$(NAME)$(WHT) objects files removed!$(WTH)\n"
	@printf "$(_SUCCESS) $(BOLD)$(OBJSD)$(RESET) directory cleaned.\n"
	@printf "$(_SUCCESS) $(BOLD)$(OBJSD)$(RESET) directory removed.\n\n"

fclean: clean
	@printf "\n$(_INFO) Cleaning $(BOLD)$(NAME)$(RESET) executable...\n"
	@$(RM) $(NAME)
	@printf "$(_SUCCESS) $(BOLD)$(NAME)$(RESET) executable removed.\n\n"

cleanleaks:
	@printf "\n$(_INFO) Cleaning $(BOLD)$(LEAKS_FILE)$(RESET) file...\n"
	@$(RM) $(LEAKS_FILE)
	@printf "$(_SUCCESS) $(BOLD)$(LEAKS_FILE)$(RESET) file removed.\n\n"

re: fclean all

show:
	@printf "\n"
	@printf "$(YLW)ALL PATHS (*invoked with > make show*) $(WTH)]\n"
	@printf "\n"
	@printf "$(YLW)██ Current directory    : $(WTH)$(CURDIR) $(WTH)\n"
	@printf "$(RED)██ Sources directory    : $(WTH)./$(SRCSD)$(WTH)\n"
	@printf "$(YLW)██ Include directory    : $(WTH)./$(INCSD)\n"
	@printf "$(CYN)██ Objects Directory    : $(WTH)./$(OBJSD)$(WTH)\n"
	@printf "$(YLW)██ Executable directory : $(WTH)$(CURDIR) $(WTH)\n"
	@printf "\n"
	@printf "$(RED)██ Sources files        : $(WTH)$(notdir $(FILES))\n"
	@printf "$(CYN)██ Objects files        : $(WTH)$(notdir $(OBJS))\n"
	@printf "$(YLW)██ Executable file      : $(WTH)$(notdir $(NAME))\n"
	@printf "\n"

.PHONY: all leaks clean fclean cleanleaks re show
.SILENT: