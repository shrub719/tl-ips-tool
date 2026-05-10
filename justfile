name := "tl-ips-tool"

build:
    gcc -Wall -o ./target/{{name}} src/*.c

[default]
test file="./ips/code.ips": build
    ./target/{{name}} {{file}}

dump file="./ips/code.ips":
    hexdump -C {{file}}
