# Compiler
CXX = g++

# Executable name
CXXFLAGS = -std=c++11 -Wall -Wextra -Wno-sign-compare

.PHONY: make-main test-run check-outputs check-output-optimal check-output-online check-output-offline check-output-total

make-main:
	@OUTPUT=$$(make 2>&1) ;\
	CODE=$$? ;\
	if [ $$CODE -eq 0 ] && [ -e "main" ]; then \
		echo "Successfully compiled main!"; \
	else \
		echo "Cannot compile main using \"make\"!"; \
		exit 1; \
	fi

test-run: make-main
	@echo "Test running main ..."
	@./main > /dev/null 2>&1 ;\
	if [ $$? -eq 0 ]; then \
		echo "The run of ./main exit successfully!"; \
	else \
		echo "The run of ./main exit with error!"; \
		exit 1; \
	fi

check-outputs: check-output-total check-output-optimal check-output-online check-output-offline

check-output-total: make-main
	@echo "Checking output of main on total items loaded from file ..."
	@OUTPUT=$$(./main) ;\
	if echo $$OUTPUT | grep -Eiq "total items: +7"; then \
		echo "Total items count displayed correctly"; \
	else \
		echo "Total items count displayed incorrectly"; \
		exit 1; \
	fi

check-output-optimal: make-main
	@echo "Checking output of main on optimal algorithm ..."
	@OUTPUT=$$(./main) ;\
	if echo $$OUTPUT | grep -Eiq "optimal solution +| *4"; then \
		echo "Optimal solution displayed correctly"; \
	else \
		echo "Optimal solution displayed incorrectly"; \
		exit 1; \
	fi

check-output-online: make-main
	@echo "Checking output of main on online algorithm ..."
	@OUTPUT=$$(./main) ;\
	if echo $$OUTPUT | grep -Eiq "online *- *next fit *| *5"; then \
		echo "Online next fit solution displayed correctly"; \
	else \
		echo "Online next fit solution displayed incorrectly"; \
		exit 1; \
	fi ;\

check-output-offline: make-main
	@echo "Checking output of main ..."
	@OUTPUT=$$(./main) ;\
	if echo $$OUTPUT | grep -Eiq "offline *- *best fit +| *4"; then \
		echo "Offline best fit solution count displayed correctly"; \
	else \
		echo "Offline best fit solution count displayed incorrectly"; \
		exit 1; \
	fi ;\
	if echo $$OUTPUT | grep -Eiq "bin *0: *0.90"; then \
		echo "Offline solution detail displayed correctly"; \
	else \
		echo "Offline solution detail displayed incorrectly"; \
		exit 1; \
	fi
