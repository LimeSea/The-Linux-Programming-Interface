export PRJ_TOP_DIR=${shell pwd}
export BUILD_DIR=${PRJ_TOP_DIR}/build

export COMMON_OBJ=${BUILD_DIR}/common.o
export COMMON_INCLUDE=${PRJ_TOP_DIR}/common/include

-include ${PRJ_TOP_DIR}/Chapter-4/subdir.mk



${COMMON_OBJ} : ${PRJ_TOP_DIR}/common/src/error_functions.c
	$(shell if [ ! -e $(BUILD_DIR) ];then mkdir -p $(BUILD_DIR); fi)
	gcc -c $^ -o $@ -I${COMMON_INCLUDE}





