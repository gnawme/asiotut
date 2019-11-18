project('asio-tcpserver', 'cpp', default_options: ['cpp_std=gnu++17'])

add_project_arguments('-DASIO_STANDALONE', language: 'cpp')

src = [
    'AsioTCPServer.cpp',
]

threads = dependency('threads')

executable('asio-tcpserver',
    src,
    dependencies: [threads],
)
