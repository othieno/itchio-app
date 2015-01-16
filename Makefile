CLIENT                  = itchio
TESTSUITE               = $(CLIENT)-testsuite
BENCHMARKSUITE          = $(CLIENT)-benchmarksuite

SRC_DIR                 = src
BUILD_DIR               = build

CLIENT_PRO              = itchio.pro
CLIENT_MAKEFILE         = $(BUILD_DIR)/Makefile.$(CLIENT)

TESTSUITE_DIR           = test/unit
TESTSUITE_PRO           = $(TESTSUITE_DIR)/unit.pro
TESTSUITE_MAKEFILE      = $(BUILD_DIR)/Makefile.$(TESTSUITE)

BENCHMARKSUITE_DIR      = test/benchmark
BENCHMARKSUITE_PRO      = $(BENCHMARKSUITE_DIR)/benchmark.pro
BENCHMARKSUITE_MAKEFILE = $(BUILD_DIR)/Makefile.$(BENCHMARKSUITE)

.PHONY: client tests benchmarks all run run-tests run-benchmarks format clean help

client     : $(CLIENT_MAKEFILE)
tests      : $(TESTSUITE_MAKEFILE) client
benchmarks : $(BENCHMARKSUITE_MAKEFILE) client

client tests benchmarks:
	@$(MAKE) --directory $(BUILD_DIR) --file $(notdir $<) -$(MAKEFLAGS)

all: client tests benchmarks

run: client
	@$(BUILD_DIR)/$(CLIENT)

run-tests: tests
	@$(BUILD_DIR)/$(TESTSUITE)

run-benchmarks: benchmarks
	@$(BUILD_DIR)/$(BENCHMARKSUITE)

format:
#	clang-format -i $$(git ls-files . | grep '.cpp$$')

clean:
	@rm -rf $(BUILD_DIR)

help:
	@echo "Available targets:"
	@echo "  client            Build the itch.io client."
	@echo "  tests             Build the itch.io unit test suite."
	@echo "  benchmarks        Build the itch.io benchmark suite."
	@echo "  all               Build the itch.io client, as well as the unit test and benchmark suites."
	@echo "  run               Build and execute the itch.io client."
	@echo "  run-tests         Build and execute the itch.io unit test suite."
	@echo "  run-benchmarks    Build and execute the itch.io benchmark suite."
	@echo "  format            Format the project's codebase."
	@echo "  clean             Delete built project files."
	@echo "  help              Print this help page."
	@echo

$(CLIENT_MAKEFILE)         : $(CLIENT_PRO)
$(TESTSUITE_MAKEFILE)      : $(TESTSUITE_PRO)
$(BENCHMARKSUITE_MAKEFILE) : $(BENCHMARKSUITE_PRO)

$(CLIENT_MAKEFILE) $(TESTSUITE_MAKEFILE) $(BENCHMARKSUITE_MAKEFILE):
	@mkdir -p $(BUILD_DIR)
	@qmake -Wall $< -o $@
