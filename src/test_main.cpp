// std
#include <iostream>
// 3rd
#include <gtest/gtest.h>
// project
#include "state.h"
#include "trace.h"
// TODO(peria): Split test for solvers
#include "engines/stupid_solver.h"
#include "engines/stupid_solver_v2.h"

TEST(Matrix, LoadAndDumpMatrix) {
    Matrix m("../data/problems/LA001_tgt.mdl");
    EXPECT_EQ(m.R, 20);

    // add some voxels.
    for (int x = 0; x < m.R / 2; ++x) {
        if (x % 2 == 0) {
            m(x, 0, 1) = Voxel::Full;
        } else {
            m(Vec3(x, 1, 0)) = Voxel::Full;
        }
    }

    m.dump("LA001_tgt_modified.mdl");

    // load again to check identity.
    Matrix m2("LA001_tgt_modified.mdl");
    ASSERT_TRUE(m2);
    EXPECT_EQ(m.buf, m2.buf);
}

TEST(Trace, OutputTraceExample) {
    Trace trace;
    trace.push_back(CommandWait{}); // 0
    trace.push_back(CommandFlip{}); // 0
    trace.push_back(CommandSMove{Vec3(0, 0, 10)}); // 0
    trace.push_back(CommandLMove{Vec3(0, 0, 1), Vec3(0, 1, 0)}); // 0
    trace.push_back(CommandFission{Vec3(0, 0, 1), 2}); // 0

    trace.push_back(CommandFill{Vec3(0, 1, 0)}); // 0
    trace.push_back(CommandWait{}); // 1
    trace.push_back(CommandFusionP{Vec3(0, 1, 0)}); // 0
    trace.push_back(CommandFusionS{Vec3(0, -1, 0)}); // 1

    trace.push_back(CommandLMove{Vec3(0, 0, -1), Vec3(0, -1, 0)}); // 0
    trace.push_back(CommandSMove{Vec3(0, 0, -10)}); // 0
    trace.push_back(CommandHalt{}); // 0

    EXPECT_TRUE(trace.output_trace("output.nbt"));

    Trace trace2;
    EXPECT_TRUE(trace2.input_trace("output.nbt"));
    EXPECT_TRUE(trace2.output_trace("output2.nbt"));

    // EXPECT_EQ(trace, trace2);
}

TEST(System, StupidSolver) {
    Matrix m("../data/problems/LA001_tgt.mdl");
    auto trace = stupid_solver(System(m.R), m);

    State state(m);
    EXPECT_FALSE(state.is_finished());
    state.simulate(trace);

    EXPECT_TRUE(state.is_finished());
}

TEST(System, StupidSolverV2) {
    Matrix m("../data/problems/LA001_tgt.mdl");
    auto trace = stupid_solver_v2(System(m.R), m);

    State state(m);
    EXPECT_FALSE(state.is_finished());
    state.simulate(trace);

    EXPECT_TRUE(state.is_finished());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
// vim: set si et sw=4 ts=4:
