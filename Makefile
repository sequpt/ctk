################################################################################
# INCLUDE
################################################################################
MAKEFILE_PATH := makefiles
include $(MAKEFILE_PATH)/global.mk
################################################################################
# CTK
################################################################################
PROJECT := ctk
PROJECT_TYPE := shared
################################################################################
# TARGETS
################################################################################
# Default targets
include $(MAKEFILE_PATH)/targets.mk
