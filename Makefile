ERL_INCLUDE_PATH=$(shell erl -eval 'io:format("~s~n", [lists:concat([code:root_dir(), "/erts-", erlang:system_info(version), "/include"])])' -s init stop -noshell)

UNAME := $(shell uname -s)

CFLAGS += -Wno-unused-function

ifeq ($(UNAME), Darwin)
	CC := clang
	CFLAGS := -undefined dynamic_lookup -dynamiclib
endif

ifeq ($(UNAME), Linux)
	CC := gcc
	CFLAGS += -g -O3 -fpic -shared -Wall -Wextra -Wno-unused-parameter
endif

BUILD = $(MIX_APP_PATH)/priv

all: $(BUILD)/nif.so

$(BUILD):
	mkdir -p priv

$(BUILD)/nif.so: c_src/nif.c $(BUILD)
	$(CC) $(CFLAGS) -I$(ERL_INCLUDE_PATH) c_src/*.c -o $(BUILD)/nif.so

clean:
	@rm -rf $(BUILD)/nif.so
