.DEFAULT_GOAL := key-value-db

INCLUDE_PATH="./src/include"

# Compiler
CC := gcc

# Compiler flags
CXX_FLAGS = -std=c++14 -g -Wall -Werror -c -fmessage-length=0 -fstack-protector -Og -Wfatal-errors
LD_FLAGS = -pthread

# Files to be compiled
C_FILES := $(shell find src -type f -name '*.cpp')
O_FILES := $(patsubst %.cpp,%.o,$(C_FILES))
# Headers 
C_DEPS := $(patsubst %.cpp,%.d,$(C_FILES))

ifneq ($(strip $(C_DEPS)),)
-include $(C_DPES)
endif

# Dynamic c files compilation
src/source/%.o: src/source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: gcc Compiler'
	#@echo $(CXX) -I$(INCLUDE_PATH) $(CXX_FLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	#@echo $(CXX) -I$(INCLUDE_PATH) $(CXX_FLAGS) -MMD -MP -MF"$(patsubst %.o,%.d,$(O_FILES))" -MT"$(@)" -o "$@" "$<"
	$(CXX) -I$(INCLUDE_PATH) $(CXX_FLAGS) -MMD -MP -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

# Final target will result in key-value-db binary
key-value-db: $(O_FILES)
	@echo 'Building Target: $@'
	@echo 'Invoking Linker'
	$(CXX) $(LD_FLAGS) -o "key-value-db" $(O_FILES)
	@echo 'Finished building: $@'
	@echo ' '

#######################################################################################################
#######################################################################################################
############################################ GOOGLE TEST #############################################
#######################################################################################################
#######################################################################################################
G_TEST_COMPILER := g++
GTEST_DIR = googletest/googletest
USER_DIR = tests
GTEST_CPPFLAGS += -isystem $(GTEST_DIR)/include
GTEST_CXXFLAGS += -g -Wall -Wextra -pthread #-Wfatal-errors

GTEST_HEADERS_DIRS = $(GTEST_DIR)/include $(GTEST_DIR)/include/gtest $(GTEST_DIR)/include/gtest/internal

GTEST_SRCS = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

gtest-all.o : $(GTEST_SRCS)
	@echo 'Building file: gtest-all.cc'
	$(G_TEST_COMPILER) $(GTEST_CPPFLAGS) -I$(GTEST_DIR) $(GTEST_CPPFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS)
	@echo 'Building file: gtest_main.cc'
	$(G_TEST_COMPILER) $(GTEST_CPPFLAGS) -I$(GTEST_DIR) $(GTEST_CXXFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	@echo 'Running AR for gtest.a'
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	@echo 'Running AR for gtest_main.a'
	$(AR) $(ARFLAGS) $@ $^

GTEST_CPP_FILES := $(shell find tests  -name '*.cpp')

G_TEST_O_FILES := $(patsubst %.cpp,%.o,$(GTEST_CPP_FILES))
GTEST_C_DEPS := $(patsubst %.cpp,%.d,$(GTEST_CPP_FILES))

O_FILES_NO_MAIN := $(filter-out src/source/main.o, $(O_FILES))

$(USER_DIR)/%.o: $(USER_DIR)/%.cpp $(O_FILES_NO_MAIN) gtest_main.a
	@echo 'Building file: $<'
	@echo 'Invoking: G++ Compiler'
	@echo 'NO MAIN: $(O_FILES_NO_MAIN)'
	$(G_TEST_COMPILER) $(foreach DIR, $(GTEST_HEADERS_DIRS), -I"$(DIR)") -I$(INCLUDE_PATH) $(GTEST_CPPFLAGS) $(GTEST_CXXFLAGS) $(LD_FLAGS) gtest_main.a $^ -o $@
	@echo 'Finished building: $<'
	@echo ' '

# Test target
test: $(G_TEST_O_FILES)
	@echo 'Init on test target'
	@echo 'Compiled tests: $(G_TEST_O_FILES)'
	$(foreach tst,$(G_TEST_O_FILES),printf "\n\n\n"; echo '[INFO] executing $(tst)'; ./$(tst);)

# Test target with valgrind for memory analysis
test-valgrind: $(G_TEST_O_FILES)
	@echo 'Init on test target'
	@echo 'Compiled tests: $(G_TEST_O_FILES)'
	$(foreach tst,$(G_TEST_O_FILES),printf "\n\n\n"; echo '[INFO] executing $(tst)'; valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./$(tst);)

clean:
	$(RM) $(O_FILES) $(C_DEPS) key-value-db *.a *.o $(USER_DIR)/*.d $(USER_DIR)/*.o

.PHONY: key-value-db clean test test-valgrind

