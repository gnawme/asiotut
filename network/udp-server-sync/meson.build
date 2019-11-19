project('asio-udpserver', 'cpp', default_options: ['cpp_std=gnu++17'])

add_project_arguments('-DASIO_STANDALONE', language: 'cpp')

src = [
    'AsioUDPServer.cpp',
]

threads = dependency('threads')

executable('asio-udpserver',
    src,
    dependencies: [threads],
)
