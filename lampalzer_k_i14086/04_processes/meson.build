project('aba', 'cpp',
        license : ['Boost'],
        version : '0.1',
        default_options : ['cpp_std=c++17', 'warning_level=3', 'werror=true'])

thread_dep = dependency('threads')

add_global_arguments('-I ~/workspace/builds/asio/asio/include/', language : 'cpp')
add_global_arguments('-DASIO_STANDALONE', language : 'cpp')
add_global_arguments('-DASIO_NO_DEPRECATED', language : 'cpp')

# subdir('SUBDIR1')

inc_dir = include_directories('include')

executable('aba',
           sources : 'src/aba.cpp',
           include_directories : inc_dir,
           dependencies : thread_dep
          )

executable('charout',
           sources : 'src/charout.cpp',
           include_directories : inc_dir,
           dependencies : thread_dep
          )
