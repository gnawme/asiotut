project('asio-timers', 'cpp', default_options: ['cpp_std=gnu++17'])

add_project_arguments('-DASIO_STANDALONE', language: 'cpp')

src = [
    'AsioTimers.cpp',
]

threads = dependency('threads')

executable('asio-timers',
    src,
    dependencies: [threads],
)
