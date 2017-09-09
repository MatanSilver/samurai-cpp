# Flags
CFLAGS = -std=c99 -pedantic -O1

#if shared library target
#CFLAGS += -shared -undefined dynamic_lookup

TARGET_EXEC = samurai-c++
TEST_EXEC = unittest
BUILD_DIR = ./build
SRC_DIRS = ./src
#HEAD_DIRS ?= ./include

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
SRCS_TARGET := $(shell find $(SRC_DIRS) -name *.cpp ! -name unittest.cpp -or -name *.c -or -name *.s)
SRCS_TEST := $(shell find $(SRC_DIRS) -name *.cpp ! -name samurai-c++.cpp -or -name *.c -or -name *.s)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
OBJS_TARGET := $(SRCS_TARGET:%=$(BUILD_DIR)/%.o)
OBJS_TEST := $(SRCS_TEST:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)


$(info $$SRCS_TARGET is [${SRCS_TARGET}])
$(info $$SRCS_TEST is [${SRCS_TEST}])
$(info $$OBJS_TARGET is [${OBJS_TARGET}])
$(info $$OBJS_TEST is [${OBJS_TEST}])

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
#INC_DIRS := $(shell find $(HEAD_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS = $(INC_FLAGS) -MMD -MP -DDEBUG -DTRUNCATE -ggdb
CXXFLAGS = -std=c++14 -stdlib=libc++
LDFLAGS = -stdlib=libc++

# main target
#$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
#	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS_TARGET)
	$(CXX) $(OBJS_TARGET) -o $@ $(LDFLAGS)

$(BUILD_DIR)/$(TEST_EXEC): $(OBJS_TEST)
	$(CXX) $(OBJS_TEST) -o $@ $(LDFLAGS)

# assembly
$(BUILD_DIR)/%.s.o: %.s
	$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p


.PHONY: run
run: $(BIN)
	./build/samurai-c++
