cmake_minimum_required(VERSION 3.8)
project(CRsim)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp chan_hop/chan_hop.h global/include.h global/global.h global/configure.h chan_hop/chan_hop.cpp chan_hop/en_jump_stay.h lib/graph.h lib/graph.cpp lib/math.h lib/vec2.h lib/math.cpp lib/debug.h lib/util.h lib/lib.h chan_hop/jump_stay.h chan_hop/my_seq.h chan_hop/my_split_spec.h chan_hop/sector_hop.h chan_hop/my_send_rev_hop.h chan_hop/en_jump_stay.cpp chan_hop/jump_stay.cpp chan_hop/my_seq.cpp chan_hop/my_split_spec.cpp chan_hop/sector_hop.cpp chan_hop/my_send_rev_hop.cpp user/user.h chan_hop/all_chan_hop.h network/packet.h network/channel.h user/cognitive_radio.h user/cognitive_radio.cpp user/pu.h user/pu.cpp user/user.cpp user/su.h user/su.cpp simulation/past/Globecom15.h network/network.h simulation/my_su.h network/network.cpp network/channel.cpp network/packet.cpp simulation/past/Globecom15.cpp simulation/past/Infocom2016.h simulation/past/Infocom2016.cpp simulation/my_su.cpp simulation/past/SendSeq.h simulation/past/SendSeq.cpp simulation/DirectionalAntennaImprove.h simulation/DirectionalAntennaImprove.cpp simulation/all_simu.h)
add_executable(CRsim ${SOURCE_FILES})