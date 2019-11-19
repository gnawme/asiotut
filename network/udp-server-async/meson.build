project('asio-udpserver', 'cpp', default_options: ['cpp_std=gnu++17'])

add_project_arguments('-DASIO_STANDALONE', language: 'cpp')

src = [
    'AsioUDPServerAsync.cpp',
]

ainclude = include_directories('../')

threads = dependency('threads')

executable('asio-udpserver',
    src,
    include_directories: [ainclude],
    dependencies: [threads],
)
