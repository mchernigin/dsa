CC = gcc
CFLAGS = -Wall -Wextra
TARGET = benchmark

PY = python3

CSV = results.csv
RESGRAPH = graph.png
RESTABLE = table.png
RESDIR = results

all: run plot								## do everything nicely (*)
	@printf "[INFO] Moving results into separate directory\n"
	@printf "[CMD] "
	mkdir -p $(RESDIR)
	@printf "[CMD] "
	mv $(RESGRAPH) $(RESTABLE) $(RESDIR)

build: benchmark.c							## build benchmark
	@printf "[INFO] Compiling benchmark\n"
	@printf "[CMD] "
	$(CC) $(CFLAGS) -o $(TARGET) $^ 

run: build									## build & run benchmark
	@printf "[INFO] Running benchmark\n"
	@printf "[CMD] "
	./$(TARGET)

plot: results.csv							## generate a plot from results.csv
	@printf "[INFO] Generating results\n"
	@printf "[CMD] "
	$(PY) plot.py
	@printf "[CMD] "
	rm -f $(CSV)

clean:										## clean everything
	@printf "[INFO] Cleaning executables\n"
	@printf "[CMD] "
	rm -f $(TARGET)
	@printf "[INFO] Cleaning results\n"
	@printf "[CMD] "
	rm -rf $(CSV) $(RESGRAPH) $(RESTABLE) $(RESDIR)

help:										## print this help msg
	@printf "Usage:\n\tmake <command>\n\n"
	@printf "Commands:\n"
	@egrep -h '\s##\s' $(MAKEFILE_LIST) \
		| awk 'BEGIN {FS = ":.*?## "}; {printf "\t%-10s%s\n", $$1, $$2}'
