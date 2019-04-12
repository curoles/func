TST := $(SRC)/test

CFLAGS := -g -O2 -I$(SRC) -Wall -Werror

TEST_LIST := test_file test_lambda test_factorial test_result
TEST_LIST += test_foreach test_vector test_string test_integer
TEST_LIST += test_list test_cprintf

.PHONY: test $(TEST_LIST)
test: $(TEST_LIST)
	@echo done testing

define do_test
        @echo $@
	@rm -rf $@
	@$(TIME) gcc $(CFLAGS) $(TST)/$1 -o $@
	@$(TIME) ./$@ > /dev/null
endef

test_file:
	$(call do_test,file.c)

test_lambda:
	$(call do_test,lambda.c)

test_factorial:
	$(call do_test,factorial.c)

test_result:
	$(call do_test,result.c)

test_foreach:
	$(call do_test,foreach.c)

test_vector:
	$(call do_test,vector.c)

test_string:
	$(call do_test,string.c)

test_integer:
	$(call do_test,integer.c)

test_list:
	$(call do_test,list.c)

test_cprintf:
	$(call do_test,cprintf.c)
