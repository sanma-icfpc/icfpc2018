CXX=g++
CXXFLAGS=-O2 -Wall -Wno-sign-compare -std=c++17
CXXFLAGS+=$(pkg-config --libs --cflags boost)
CXXFLAGS+=-I .
CXXFLAGS+=-I ../libs
CXXFLAGS+=-I ../libs/googletest/googletest/
CXXFLAGS+=-I ../libs/googletest/googletest/include
CXXFLAGS+=-pg

BUILD_PATH=build
LIB_PATH=../libs

SRCS=command.cpp matrix.cpp nanobot.cpp nmms.cpp region.cpp vec3.cpp state.cpp system.cpp trace.cpp bounding_box.cpp traceutil.cpp
SRCS+=engine.cpp engines/naive_converter.cpp engines/naive_move.cpp

OBJS=$(SRCS:%.cpp=$(BUILD_PATH)/%.o)

TEST_SRCS=$(LIB_PATH)/googletest/googletest/src/gtest-all.cc
TEST_OBJS=$(TEST_SRCS:%.cpp=$(BUILD_PATH)/%.o)

.PHONY: all
all: dirs test engines evaluate

######################
# ADD YOUR ENGINE TARGET HERE
.PHONY: engines

ENGINES=stupid parallel parallel_v2 parallel_v3 parallel_optimized parallel_optimized_v2 parallel_optimized_v3 parallel_optimized_v4 parallel_optimized_v5 parallel_optimized_v6 parallel_optimized_v7 parallel_optimized_v8 parallel_optimized_v9 3x3_solver 3x3_solver_parallel cubee stupid_engine_v2 split_gvoid_solver scrap_and_build final_gfill

engines: $(ENGINES)

######################
# ADD YOUR ENGINE HERE
stupid: engine_main.cpp engines/stupid.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -Wall $^ -o $@ $(LDFLAGS)

stupid_engine_v2: engine_main.cpp engines/stupid_solver_v2.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -Wall $^ -o $@ $(LDFLAGS)

parallel: engine_main.cpp engines/parallel.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -Wall $^ -o $@ $(LDFLAGS)

parallel_v2: engine_main.cpp engines/parallel_v2.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -Wall $^ -o $@ $(LDFLAGS)

parallel_v3: engine_main.cpp engines/parallel_v3.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -Wall $^ -o $@ $(LDFLAGS)

parallel_optimized: engine_main.cpp engines/parallel_optimized.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -Wall $^ -o $@ $(LDFLAGS)

parallel_optimized_v2: engine_main.cpp engines/parallel_optimized_v2.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -Wall $^ -o $@ $(LDFLAGS)

parallel_optimized_v3: engine_main.cpp engines/parallel_optimized_v3.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -Wall $^ -o $@ $(LDFLAGS)

parallel_optimized_v4: engine_main.cpp engines/parallel_optimized_v4.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -Wall $^ -o $@ $(LDFLAGS)

parallel_optimized_v5: engine_main.cpp engines/parallel_optimized_v5.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -Wall $^ -o $@ $(LDFLAGS)

parallel_optimized_v6: engine_main.cpp engines/parallel_optimized_v6.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -Wall $^ -o $@ $(LDFLAGS)

parallel_optimized_v7: engine_main.cpp engines/parallel_optimized_v7.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -Wall $^ -o $@ $(LDFLAGS)

parallel_optimized_v8: engine_main.cpp engines/parallel_optimized_v8.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -Wall $^ -o $@ $(LDFLAGS)

parallel_optimized_v9: engine_main.cpp engines/parallel_optimized_v9.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -Wall $^ -o $@ $(LDFLAGS)


3x3_solver: engine_main.cpp engines/3x3_solver.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -Wall $^ -o $@ $(LDFLAGS)

3x3_solver_parallel: engine_main.cpp engines/3x3_solver_parallel.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -Wall $^ -o $@ $(LDFLAGS)

cubee: engine_main.cpp engines/cubee.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -Wall $^ -o $@ $(LDFLAGS)

split_gvoid_solver: engine_main.cpp engines/split_gvoid_solver.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -Wall $^ -o $@ $(LDFLAGS)

scrap_and_build: engine_main.cpp engines/scrap_and_build.cpp engines/parallel_optimized_v2.cpp engines/parallel_optimized_v5.cpp engines/parallel_optimized_v6.cpp engines/parallel_optimized_v7.cpp engines/parallel_optimized_v8.cpp engines/parallel_optimized_v9.cpp engines/cubee_classic.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -Wall $^ -o $@ $(LDFLAGS)

final_gfill: engine_main.cpp engines/final_gfill.cpp engines/parallel_optimized_v3.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -Wall $^ -o $@ $(LDFLAGS)

.PHONY: dirs
dirs:
	@mkdir -p $(BUILD_PATH)
	@mkdir -p $(BUILD_PATH)/engines

test: test_main.cpp engines/stupid.cpp engines/stupid_solver_v2.cpp engines/parallel.cpp engines/parallel_v2.cpp engines/parallel_optimized.cpp $(OBJS) $(TEST_OBJS)
	$(CXX) -DTEST_PROJECT $(CXXFLAGS) $^ -o $@ $(LDFLAGS) -lpthread

evaluate: evaluate_main.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

trace_sandbox: trace_sandbox_main.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_PATH)/%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean-results
clean-results:
	rm -f *.mdl *.nbt *.json
	rm -rf tmp-quick-info
	rm -rf tmp-quick-traces

.PHONY: clean
clean:
	rm -f $(ENGINES)
	rm -f $(OBJS)
	rm -f $(BUILD_PATH)/*.o
	rm -f $(BUILD_PATH)/engines/*.o
	rm -f test
	# generated files in test
	rm -f output.nbt output.nbt.json output2.nbt output2.nbt.json stupid_energy_log.json
	rm -f LA001_tgt_modified.mdl Planning_FastMove.json test_result.xml
