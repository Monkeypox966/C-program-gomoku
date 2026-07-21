cmake_minimum_required(VERSION 3.10)

project(jing_zi_qi)

add_executable(jing_zi_qi 
    main.c
    print_board.c
    judge.c
    print_the_result.c
    ai_move.c
)

if(WIN32)
    target_link_options(jing_zi_qi PRIVATE -mconsole)
endif()