project('asio-tcpclient', 'cpp', default_options: ['cpp_std=gnu++17'])

add_project_arguments('-DASIO_STANDALONE', language: 'cpp')

src = [
    'AsioTCPClient.cpp',
]

threads = dependency('threads')

executable('asio-tcpclient',
    src,
    dependencies: [threads],
)
