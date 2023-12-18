4-2 : ${PRJ_TOP_DIR}/Chapter-4/4-2.c ${COMMON_OBJ}
	$(shell if [ ! -e $(BUILD_DIR) ];then mkdir -p $(BUILD_DIR); fi)
	gcc -c $^ -o ${BUILD_DIR}$@ -I${COMMON_INCLUDE}

4-1 : ${PRJ_TOP_DIR}/Chapter-4/4-1.c ${COMMON_OBJ}
	$(shell if [ ! -e $(BUILD_DIR) ];then mkdir -p $(BUILD_DIR); fi)
	gcc -c $^ -o ${BUILD_DIR}/$@ -I${COMMON_INCLUDE}