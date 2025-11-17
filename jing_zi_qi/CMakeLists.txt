cmake_minimum_required(VERSION 3.10)

project(jing_zi_qi)

set(SOURCES print_board.c judge.c print_the_result.c ai_move.c)

add_executable(jing_zi_qi ${SOURCES})