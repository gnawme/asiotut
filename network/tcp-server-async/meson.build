project('asio-tcpasync', 'cpp', default_options: ['cpp_std=gnu++17'])

add_project_arguments('-DASIO_STANDALONE', language: 'cpp')

src = [
    'AsioTCPServerAsync.cpp',
]

ainclude = include_directories('../')

threads = dependency('threads')

executable('asio-tcpasync',
    src,
    include_directories: [ainclude],
    dependencies: [threads],
)
